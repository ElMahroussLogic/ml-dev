/*
 * Created on Thu Aug 22 09:29:13 CEST 2024
 *
 * Copyright (c) 2024 ZKA Technologies
 */

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

#define kAppSignedExtLen 3

///@note just add a sign indicator for a signed executable.
#define kAppSignedExt                         \
	{                                         \
		".sign.exe", ".sign.dll", ".sign.sys" \
	}

#define kAppExt                \
	{                          \
		".exe", ".dll", ".sys" \
	}

#define kSignedAppMagic "SEFF"

#define kPaddingLen	 512
#define kPathLen	 4096
#define kChecksumLen 8
#define kMagicLen	 5
#define kSignVersion 2

namespace details
{
	struct SIGNED_EXEC_HEADER final
	{
		// end of executable zone.
		char d_binary_padding_end_of_exec[kPaddingLen];
		// doesn't change.
		char d_binary_magic[kMagicLen];
		int	 d_binary_version;
		// can change according to version.
		char d_binary_name[kPathLen];

		// checksum len
		union {
			struct
			{
				std::uint16_t d_binary_checksum_u16[kChecksumLen - 4];
				std::uint16_t d_binary_checksum_u32[4];
			};
			std::uint32_t d_binary_checksum[kChecksumLen];
		};

		std::uint64_t d_binary_size;
		char		  d_binary_padding[kPaddingLen];
	};

	/***********************************************************************************/
	/* This handles the detection of a MZ header. */
	/***********************************************************************************/

	bool execsign_check_for_mz(std::string mz_blob) noexcept
	{
		return mz_blob[0] == 'M' &&
			   mz_blob[1] == 'Z';
	}

	void execsign_print_exec_id(struct SIGNED_EXEC_HEADER& sig)
	{
		for (auto& id_num : sig.d_binary_checksum_u32)
		{
			std::cout << id_num;
			std::cout << "-";
		}

		auto counter = 0;

		for (auto& id_num : sig.d_binary_checksum_u16)
		{
			++counter;

			std::cout << id_num;

			if ((kChecksumLen - 4) > counter)
				std::cout << "-";
		}

		std::cout << '\r';
		std::cout << std::endl;
	}

	void execsign_write_sign_id(struct SIGNED_EXEC_HEADER& sig, std::string& ss_blob)
	{
		size_t index = 0UL;

		// fill sign key.
		for (auto& ch_byte : ss_blob)
		{
			if (index < kChecksumLen)
			{
				++index;
				sig.d_binary_checksum[index] = ((ch_byte | (uint64_t)kSignedAppMagic));
			}
			else
			{
				break;
			}
		}

		sig.d_binary_checksum_u16[0] = kMagicLen;			 // magic number length
		sig.d_binary_checksum_u16[1] = sig.d_binary_version; // the version of the signed executable.

		sig.d_binary_checksum[index] = 0;
	}
} // namespace details

int main(int argc, char* argv[])
{
	for (size_t i = 1ul; i < argc; ++i)
	{
		if (strcmp(argv[i], "/?") == 0)
		{
			std::cout << "execsign: ZKA Executable Signing Tool.\n";
			std::cout << "execsign: Use this tool to indicate that this executable is made for ZKA.\n";
			std::cout << "execsign: © ZKA Technologies, all rights reserved.\n";

			return 0;
		}
	}

	// for input exe/dll!
	const char* ext[kAppSignedExtLen]	= kAppExt;
	const char* cur_ext = nullptr;

	// for output exe/dll!
	const char* ext_out[kAppSignedExtLen] = kAppSignedExt;
	const char* cur_ext_dll				  = nullptr;

	int index_cur = 0;

	for (auto ext_cur : ext)
	{
		if (std::string(argv[1]).ends_with(ext_cur))
		{
			cur_ext		= ext_cur;
			cur_ext_dll = ext_out[index_cur];

			break;
		}

		++index_cur;
	}

	if (!std::filesystem::exists(argv[1]) ||
		!cur_ext)
		return -1;

	details::SIGNED_EXEC_HEADER sig{0};

	sig.d_binary_version = kSignVersion;

	memcpy(sig.d_binary_magic, kSignedAppMagic, kMagicLen);
	memcpy(sig.d_binary_name, argv[1], strlen(argv[1]));

	sig.d_binary_size = std::filesystem::file_size(argv[1]);

	memset(sig.d_binary_padding, 0x00, kPaddingLen);
	memset(sig.d_binary_padding_end_of_exec, 0x00, kPaddingLen);

	std::string signed_path = argv[1];
	signed_path.erase(signed_path.find(cur_ext), strlen(cur_ext));
	signed_path += cur_ext_dll;

	std::ofstream of_drv(signed_path, std::ios::binary);
	std::ifstream if_drv(argv[1], std::ios::binary);

	std::stringstream ss;
	ss << if_drv.rdbuf();

	if (!details::execsign_check_for_mz(ss.str()))
	{
		std::filesystem::remove(signed_path);
		std::cout << "execsign: Couldn't sign current driver, Input executable isn't a valid.\n";

		return 1;
	}

	auto blob_on_stack = ss.str();

	details::execsign_write_sign_id(sig, blob_on_stack);

	of_drv.write(ss.str().c_str(), ss.str().size());
	of_drv.write((char*)&sig, sizeof(details::SIGNED_EXEC_HEADER));

	std::cout << "execsign: Executable's signature: ";
	details::execsign_print_exec_id(sig);

	return 0;
}
