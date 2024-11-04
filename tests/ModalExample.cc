/* -------------------------------------------

	Copyright EL Mahrouss Logic

------------------------------------------- */

#include "FoundationKit/Foundation.h"
#include <FoundationKit/MLXML.h>
#include <FoundationKit/MLAlert.h>
#include <FoundationKit/MLString.h>
#include <FoundationKit/MLURL.h>
#include <FoundationKit/MLUUID.h>

#include <FoundationKit/MLProcess.h>

#ifdef __linux__
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
#endif // __linux__

int main(int argc, char** argv)
{
#ifdef __linux__
	gtk_init(&argc, &argv);
#endif // __linux__

	MLXMLNode coder("<Phone phone_number=\"0658573014\" region_code=\"+33\">Amlal 📱.</Phone>");
	MLString	   phone = coder.getXMLDataFromMarkup("Phone", 4096, false, false);

	MLLog("%s\n", phone.asBytes());

	MLAlert alert;
	MLUUID uuid;

	alert.runModal("ZT Framework", "%s %s", "Modal on ZT.", uuid.uuidAsString().asConstBytes());

	MLURL url("https://www.google.com");
	url.openPath();

	return 0;
}
