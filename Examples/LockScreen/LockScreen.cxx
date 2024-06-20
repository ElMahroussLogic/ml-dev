/*
 * Created on Sat May 11 2024
 *
 * Copyright (c) 2024 Zeta Electronics Corporation
 */

#include <CoreAnimation.hxx>
#include <CoreGraphics.hxx>
#include <MLString.hxx>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <ctime>

extern "C"
{
#	include <gtk/gtk.h>
}

constexpr auto cWidth  = 436;
constexpr auto cHeight = 644;

MLCoreGraphicsContext* cContext = CGRequestContext(0, 0, cWidth, cHeight);

namespace Events
{
	static bool on_draw(GtkWidget* widget, cairo_t* cr, void* user_data)
	{
		(void)user_data;

		static CGReal cur	 = 10.0;
		static CGReal index	 = 0.0;
		static CGReal indexA = 1.0;

		cContext->SetContext(cr);

		std::time_t now = std::time(nullptr);
		// Convert it to local time
		std::tm* localTime = std::localtime(&now);

		cContext->Move(0.0, 0.0);
		cContext->Color(0.0, 0.0, 0.0, 1.0);

		cContext->Rectangle(cWidth, cHeight, 0);

		cContext->Color(1.0, 1.0, 1.0, 1.0);

		if (localTime->tm_min > 9)
		{
			cContext->FontFamily("Inter", true)->FontSize(100.0)
				->Move(cur, 90.0)->Text((std::to_string(localTime->tm_hour) + ":" + std::to_string(localTime->tm_min)).c_str(), false);
		}
		else
		{
			cContext->FontFamily("Inter", true)->FontSize(100.0)
				->Move(cur, 90.0)->Text((std::to_string(localTime->tm_hour) + ":0" + std::to_string(localTime->tm_min)).c_str(), false);
		}

		constexpr auto cStopAt = 75.0;

		if (cur < cStopAt)
		{
			cur = CALerp(cur, cStopAt, index);
			index += 0.001;
			indexA -= 0.01;

			MLLog("currrent X position: %r\n", cur);
		}
		else
		{
			if (indexA > 0)
				indexA = 0;
		}

		cContext->Move(0.0, 0.0);
		cContext->Color(0, 0, 0, indexA);
		cContext->Rectangle(cWidth, cHeight, 0);

		return FALSE;
	}

	static gboolean update_canvas(gpointer user_data)
	{
		GtkWidget* widget = GTK_WIDGET(user_data);
		gtk_widget_queue_draw(widget);

		return TRUE;
	}
} // namespace Events

int main(int argc, char const* argv[])
{
	atexit([]() -> void {
		if (!cContext)
			return;

		CGReleaseContext(cContext);
	});

	GtkWidget* window;
	GtkWidget* drawing_area;

	gtk_init(&argc, (char***)&argv);

	GtkWidget* introDlg = gtk_message_dialog_new(
        NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
        "Hi!\nYou'll be introduced to a fake lock screen to demo Zeta OS\ncapabilities..");

	int response = gtk_dialog_run(GTK_DIALOG(introDlg));

	gtk_widget_destroy(introDlg);

	window		 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
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
