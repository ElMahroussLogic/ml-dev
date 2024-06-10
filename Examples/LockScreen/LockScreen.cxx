/*
 * Created on Sat May 11 2024
 *
 * Copyright (c) 2024 SoftwareLabs 
 */

#include <MLCoreAnimation.hxx>
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

		static CGReal cur = 10.0;
		static CGReal index = 0;

		cContext->SetContext(cr);
		cContext->Image("../Common/Background.png", cWidth, cHeight, 0, 0);

		cContext->Move(0.0, 0.0);
		cContext->Color(0.2, 0.2, 0.2, index);

		cContext->Rectangle(cWidth, 110.0, 0);

		cContext->Color(1.0, 1.0, 1.0, 1.0);

		cContext->FontFamily("HelveticaNeue", true)->FontSize(100.0)->Move(cur, 100.0)->Text("10:00");

		if (cur < 110.0)
		{
			cur = CGLerp(cur, 110.0, index);
			index += 0.01;
		}
		else
		{
			cur = 0.0;
			index = 0.0;
		}

		printf("pos: %f\n", cur);

		return FALSE;
	}

	static gboolean update_canvas(gpointer user_data)
	{
    	GtkWidget *widget = GTK_WIDGET(user_data);
		gtk_widget_queue_draw(widget);

		return TRUE;
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
    GtkWidget *drawing_area;

    gtk_init(&argc, (char***)&argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    drawing_area = gtk_drawing_area_new();

	gtk_container_add(GTK_CONTAINER(window), drawing_area);

	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

 	g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(Events::on_draw), nullptr);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), nullptr);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), cWidth, cHeight);
    gtk_window_set_title(GTK_WINDOW(window), "StageBoard LockScreen - Demo");
    gtk_widget_show_all(window);

	g_timeout_add(16, Events::update_canvas, drawing_area); 

    gtk_main();

	return 0;
}