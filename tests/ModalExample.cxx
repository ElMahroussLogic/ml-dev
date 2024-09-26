/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#include <FoundationKit/MLAlert.hxx>
extern "C"
{
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
}

int main(int argc, char** argv)
{
    gtk_init(&argc, &argv);

    MLAlert alert;
    alert.runModal("ZT Framework", "%s", "ZT Framework modal on Linux.");

    return 0;
}
