/*
 * Created on Thu Aug 22 09:29:13 CEST 2024
 *
 * Copyright (c) 2024 ZKA Technologies
 */

#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

#define kDriverSignedExt   ".sigg"
#define kDriverExt		   ".sys"
#define kSignedDriverMagic "SIGG"

namespace details
{
	struct SIGNED_DRIVER_HEADER final
	{
		// doesn't change.
		char d_binary_magic[5];
		int	 d_binary_version;
		// can change.
		char		  d_binary_name[4096];
		std::uint64_t d_binary_checksum;
		std::uint64_t d_binary_size;
		char		  d_binary_padding[512];
	};
} // namespace details

int main(int argc, char* argv[])
{
	if (!std::filesystem::exists(argv[1]) ||
		!std::string(argv[1]).ends_with(kDriverExt))
		return -1;

	std::cout << "ZKA Driver Signer (Internal Tool)\n";
	std::cout << "Signing current driver...\n";

	details::SIGNED_DRIVER_HEADER sig{0};

	sig.d_binary_version = 1;

	memcpy(sig.d_binary_magic, kSignedDriverMagic, strlen(kSignedDriverMagic));
	memcpy(sig.d_binary_name, argv[1], strlen(argv[1]));

	sig.d_binary_size = std::filesystem::file_size(argv[1]);

	memset(sig.d_binary_padding, 0xFF, 512);

	sig.d_binary_checksum = 0;

	std::string signed_path = argv[1];
	signed_path.erase(signed_path.find(kDriverExt), strlen(kDriverExt));
	signed_path += kDriverSignedExt;

	std::ofstream of_drv(signed_path, std::ios::binary);
	std::ifstream if_drv(argv[1], std::ios::binary);

	std::stringstream ss;
	ss << if_drv.rdbuf();

	for (auto ch : ss.str())
	{
		sig.d_binary_checksum |= ch;
	}

	sig.d_binary_checksum ^= sig.d_binary_size;

	of_drv.write((char*)&sig, sizeof(details::SIGNED_DRIVER_HEADER));

	of_drv.write(ss.str().c_str(), ss.str().size());

	std::cout << "Done, quiting, here is the key: " << sig.d_binary_checksum << "...\n";

	return 0;
}
