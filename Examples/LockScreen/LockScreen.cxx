/*
 * Created on Sat May 11 2024
 *
 * Copyright (c) 2024 SoftwareLabs B.V
 */

#ifdef __linux__
#include <CoreGraphics.hxx>
#include <MLString.hxx>
#include <stdio.h>
#include <string.h>
#include <thread>

extern "C" {
#	include <gtk/gtk.h>
}

constexpr auto cWidth = 436;
constexpr auto cHeight = 644;

MLCoreGraphicsContext* cContext = CGRequestContext(0, 0, cWidth, cHeight);

namespace Events
{
	static bool on_draw(GtkWidget *widget, cairo_t* cr, void* user_data) 
	{
		(void)user_data;

		cContext->ProvidePrivateContext(cr);
		cContext->Image("./Background.png", cWidth, cHeight, 0, 0);

		return FALSE;
	}
}

int main(int argc, char const* argv[])
{	
	atexit([] () -> void {
		if (!cContext)
			return;

		CGReleaseContext(cContext);
	});

    GtkWidget *window;
    GtkWidget *darea;

    gtk_init(&argc, (char***)&argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    darea = gtk_drawing_area_new();

	gtk_container_add(GTK_CONTAINER(window), darea);

	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

 	g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(Events::on_draw), nullptr);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), nullptr);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), cWidth, cHeight);
    gtk_window_set_title(GTK_WINDOW(window), "StageBoard LockScreen - Demo");
    gtk_widget_show_all(window);

    gtk_main();

	return 0;
}
#endif