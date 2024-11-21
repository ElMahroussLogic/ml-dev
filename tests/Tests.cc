/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved

------------------------------------------- */

#include <FoundationKit/MLXML.h>
#include <FoundationKit/MLURL.h>
#include <FoundationKit/MLAlert.h>

#include <sstream>
#include <fstream>

int main(int argc, char** argv)
{
	std::ifstream file("../resources/sample-window.ib");
	std::stringstream ss_file;

	ss_file << file.rdbuf();
	auto xml_as_str = ss_file.str();

	MLXMLNode xml_struct(xml_as_str.c_str());

	MLAlert modal;

	MLString output = xml_struct.getValue("IKLabel", 8196);
	modal.runModal("XML", "%s", output.asConstBytes());

	return 0;
}
