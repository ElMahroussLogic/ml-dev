/* -------------------------------------------

	Copyright Amlal EL Mahrouss

------------------------------------------- */

#include <FoundationKit/Linux/Linux.h>

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>

/// @brief Launches an alert box from the API.
/// @param title title of dialog.
/// @param msg message of dialog.
/// @return which option was selected.
ML_EXTERN_C MLInteger MLAlertBox(const char* title, const char* msg, const char* link_provider)
{
	GtkWidget* dialog = gtk_message_dialog_new(nullptr, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", title);
	gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "%s", msg);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(GTK_WIDGET(dialog));

	return 0;
}
