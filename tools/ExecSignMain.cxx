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

///@note just add a sign indicator for a signed executable.
#define kAppSignedExt            \
	{                            \
		".sign.exe", ".sign.dll" \
	}
#define kAppExt        \
	{                  \
		".exe", ".dll" \
	}
#define kSignedAppMagic "SEFF"

namespace details
{
	struct SIGNED_EXEC_HEADER final
	{
		// end of executable zone.
		char d_binary_padding_end_of_exec[512];
		// doesn't change.
		char d_binary_magic[5];
		int	 d_binary_version;
		// can change according to version.
		char		  d_binary_name[4096];
		std::uint64_t d_binary_checksum;
		std::uint64_t d_binary_size;
		char		  d_binary_padding[512];
	};

	/***********************************************************************************/
	/* This handles the detection of a MZ header. */
	/***********************************************************************************/

	bool drvsign_check_for_mz(std::string mz_blob) noexcept
	{
		return mz_blob[0] == 'M' &&
			   mz_blob[1] == 'Z';
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
	const char* ext[2]	= kAppExt;
	const char* cur_ext = nullptr;

	// for output exe/dll!
	const char* ext_out[2]	= kAppSignedExt;
	const char* cur_ext_dll = nullptr;

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

	sig.d_binary_version = 1;

	memcpy(sig.d_binary_magic, kSignedAppMagic, strlen(kSignedAppMagic));
	memcpy(sig.d_binary_name, argv[1], strlen(argv[1]));

	sig.d_binary_size = std::filesystem::file_size(argv[1]);

	memset(sig.d_binary_padding, 0x00, 512);
	memset(sig.d_binary_padding_end_of_exec, 0x00, 512);

	sig.d_binary_checksum = 0;

	std::string signed_path = argv[1];
	signed_path.erase(signed_path.find(cur_ext), strlen(cur_ext));
	signed_path += cur_ext_dll;

	std::ofstream of_drv(signed_path, std::ios::binary);
	std::ifstream if_drv(argv[1], std::ios::binary);

	std::stringstream ss;
	ss << if_drv.rdbuf();

	if (!details::drvsign_check_for_mz(ss.str()))
	{
		std::filesystem::remove(signed_path);
		std::cout << "execsign: Couldn't sign current driver, Input executable isn't a valid.\n";

		return 1;
	}

	for (auto ch : ss.str())
	{
		sig.d_binary_checksum |= (ch * rand());
	}

	sig.d_binary_checksum |= sig.d_binary_size;

	of_drv.write(ss.str().c_str(), ss.str().size());
	of_drv.write((char*)&sig, sizeof(details::SIGNED_EXEC_HEADER));

	std::cout << "execsign: Signing is done, quiting, here is the key: " << sig.d_binary_checksum << ".\n";

	return 0;
}
