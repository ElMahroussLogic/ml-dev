/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#include <inc/Launcher.hxx>

static std::string			  cDeviceTitle	= "StageBoard";
static bool					  cDeviceLocked = true;
static std::string			  cDeviceHour;
static bool					  cDevicePainting		  = false;
static bool					  cDeviceLockTimeout	  = false;
static MLCoreGraphicsContext* cDeviceCtx			  = CGRequestContext(0, false, cDeviceWidth, cDeviceHeight);
static CGReal				  cDeviceLockAlphaCurrent = 10.0;
static CGReal				  cDeviceLockAlpha		  = 0.0;
static CGReal				  cDeviceLockAlphaIndex	  = 0.0;

static int zka_paint_screen(GtkWidget* widget, cairo_t* cr, void* user_data)
{
	cairo_t** data;
	cDeviceCtx->leak((void***)&data);

	if (!*data)
	{
		*data = cr;
	}

	cDeviceCtx->present(0.0, 0.0, 0.0);

	if (cDeviceLocked)
	{
		constexpr auto cStopAt = 255.0;

		if (cDeviceLockAlphaCurrent < cStopAt)
		{
			cDeviceLockAlphaCurrent = CALerp(cDeviceLockAlphaCurrent, cStopAt, cDeviceLockAlphaIndex);
			cDeviceLockAlphaIndex += 0.001;
			cDeviceLockAlpha += 0.01;
		}
	}
	else
	{
		constexpr auto cStopAt = 0.0;

		if (cDeviceLockAlphaCurrent > cStopAt)
		{
			cDeviceLockAlphaCurrent = CALerp(cDeviceLockAlphaCurrent, cStopAt, cDeviceLockAlphaIndex);
			cDeviceLockAlphaIndex += 0.001;
			cDeviceLockAlpha -= 0.01;
		}
	}

	cDeviceCtx->color(1, 1, 1, cDeviceLockAlpha)->fontSize(120.0)->fontFamily("Inter", true)->move(40, cDeviceHeight - 200 + 40)->text(cDeviceHour.c_str(), false);
	cDeviceCtx->color(1, 1, 1, cDeviceLockAlpha)->fontSize(20.0)->fontFamily("Inter", false)->move(40, cDeviceHeight - 60)->text("Swipe to Unlock.", false);

	return TRUE;
}

static gboolean zka_paint_update(gpointer user_data)
{
	GtkWidget* widget = GTK_WIDGET(user_data);
	gtk_widget_queue_draw(widget);

	return TRUE;
}

static gboolean zka_lock_screen(GtkWidget* widget, GdkEventKey* event, gpointer user_data)
{
	if (cDeviceLockTimeout)
	{
		return TRUE;
	}

	switch (event->keyval)
	{
	case GDK_KEY_L: {
		cDeviceLocked = !cDeviceLocked;

		if (!cDeviceLocked)
		{
			cDeviceLockAlpha		= 1.0;
			cDeviceLockAlphaCurrent = 255.0;
		}
		else
		{
			cDeviceLockAlpha		= 0.0;
			cDeviceLockAlphaCurrent = 10.0;
		}

		cDeviceLockAlphaIndex = 0;
		cDeviceLockTimeout	  = true;

		GtkWidget* widget = GTK_WIDGET(user_data);
		gtk_widget_queue_draw(widget);

		break;
	}
	default:
		break;
	}
	return FALSE;
}

/* @brief Proxy function for lock screen. */
int main(int argc, char** argv)
{
	std::atexit([]() -> void {
		if (!cDeviceCtx)
			return;

		CGReleaseContext(cDeviceCtx);
	});

	std::thread hour_job([]() -> void {
		while (TRUE)
		{
			cDevicePainting = true;

			auto		end		 = std::chrono::system_clock::now();
			std::time_t end_time = std::chrono::system_clock::to_time_t(end);

			std::tm* tm = std::localtime(&end_time);

			cDeviceHour = std::to_string(tm->tm_hour);

			if (tm->tm_hour <= 9)
			{
				cDeviceHour = "0";
				cDeviceHour += std::to_string(tm->tm_hour);
			}

			cDeviceHour += ":";

			if (tm->tm_min <= 9)
			{
				cDeviceHour += "0";
				cDeviceHour += std::to_string(tm->tm_min);
			}
			else
			{
				cDeviceHour += std::to_string(tm->tm_min);
			}

			cDevicePainting = false;

			sleep(2);

			if (cDeviceLockTimeout)
				cDeviceLockTimeout = false;
		}
	});

	hour_job.detach();

	gtk_init(&argc, (char***)&argv);

	GtkWidget* window		= nullptr;
	GtkWidget* drawing_area = nullptr;

	window		 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	drawing_area = gtk_drawing_area_new();

	gtk_container_add(GTK_CONTAINER(window), drawing_area);

	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

	g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(zka_paint_screen), drawing_area);
	g_signal_connect(G_OBJECT(window), "key-press-event", G_CALLBACK(zka_lock_screen), drawing_area);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), drawing_area);

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), cDeviceWidth, cDeviceHeight);
	gtk_window_set_title(GTK_WINDOW(window), cDeviceTitle.c_str());
	gtk_widget_show_all(window);

	g_timeout_add(16, zka_paint_update, drawing_area);
	gtk_main();

	return 0;
}
