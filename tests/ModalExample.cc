/* -------------------------------------------

	Copyright ZKA Web Services Co

------------------------------------------- */

#include <FoundationKit/MLXMLCoder.h>
#include <FoundationKit/MLAlert.h>
#include <FoundationKit/MLString.h>
#include <FoundationKit/MLURL.h>
#include <FoundationKit/MLUUID.h>

#ifndef __TOOLCHAINKIT__
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
#endif

int main(int argc, char** argv)
{
#ifndef __TOOLCHAINKIT__
	gtk_init(&argc, &argv);
#endif

	MLXMLCoder coder("<Phone phone_number=\"0658573014\" region_code=\"+33\">Amlal 📱.</Phone>");
	auto	   phone = coder.getXML("phone_number", 4096, false, true);

	MLLog("%u\n", phone.asBytes());

	MLAlert alert;
	MLUUID uuid;

	alert.runModal("ZT Framework", "%s %s", "Modal on ZT.", uuid.uuidAsString().asConstBytes());
    
    MLURL url("https://www.google.com");
    url.openPath();

	return 0;
}
