/* -------------------------------------------

	Copyright (C) 2024, ELMH Group, all rights reserved

------------------------------------------- */

#include <FoundationKit/MLXML.h>
#include <FoundationKit/MLURL.h>
#include <FoundationKit/MLAlert.h>

#include <gtk/gtk.h>

#include <sstream>
#include <fstream>

int main(int argc, char** argv)
{
	gtk_init(&argc, &argv);

	std::ifstream file("../resources/sample-window.ib");
	std::stringstream ss_file;

	ss_file << file.rdbuf();
	auto xml_as_str = ss_file.str();

	if (xml_as_str.empty())
	{
		return EXIT_FAILURE;
	}

	MLXMLNode xml_struct(xml_as_str.c_str());
	MLAlert modal;

	constexpr auto kMaxLabelLength = 8196;

	MLString output = xml_struct.getValue("IKLabel", kMaxLabelLength);
	modal.runModal("IKLabel", "%s", output.asConstBytes());

	return 0;
}
