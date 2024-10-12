/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#include <FoundationKit/MLAlert.hxx>

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

	MLAlert alert;
	alert.runModal("ZT Framework", "%s", "Modal on ZKA.");

	return 0;
}
