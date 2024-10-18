/* -------------------------------------------

	Copyright ZKA Web Services Co

------------------------------------------- */

#include <FoundationKit/MLXMLCoder.hxx>
#include <FoundationKit/MLAlert.hxx>
#include <FoundationKit/MLString.hxx>

#ifndef __NDK__
extern "C"
{
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
}
#endif

int main(int argc, char** argv)
{
#ifndef __NDK__
	gtk_init(&argc, &argv);
#endif

    MLXMLCoder coder("<Phone phone_number=\"0658573014\" region_code=\"+33\">Amlal 📱.</Phone>");
    auto phone = coder.getXML("phone_number", 4096, false, true);

    MLLog("%u\n", phone.asBytes());

	MLAlert alert;
	alert.runModal("ZT Framework", "%s", "Modal on ZT.");

	return 0;
}
