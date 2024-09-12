/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#include <GraphicsKit/GraphicsKit.hxx>
#include <filesystem>
#include <ctime>

extern "C"
{
#include <gtk/gtk.h>
}

#define cDeviceWidth		 (1045 / 2)
#define cDeviceHeight		 (1750 / 2)
#define cDeviceTaskBarHeight (40)

static bool					  cDeviceLocked = true;
static std::string			  cHourFormat;
static bool					  cPainting	 = false;
static MLCoreGraphicsContext* cCGContext = CGRequestContext(0, false, cDeviceWidth, cDeviceHeight);

int AL_ShowLockScreen(GtkWidget* widget, cairo_t* cr, void* user_data)
{
	cairo_t** data;
	cCGContext->leak((void***)&data);

	if (!*data)
	{
		*data = cr;
	}

	cCGContext->present(0, 0.13, 0.6);

	if (cDeviceLocked)
	{
		cCGContext->color(1, 1, 1, 1)->fontSize(120.0)->fontFamily("Inter", true)->move(40, cDeviceHeight - 200 + 40)->text(cHourFormat.c_str(), false);
		cCGContext->color(1, 1, 1, 1)->fontSize(20.0)->fontFamily("Inter", false)->move(40, cDeviceHeight - 60)->text("Swipe to Unlock.", false);
	}
	else
	{
		cCGContext->color(0.0, 0.0, 0.0, 0.5)->move(0, 0)->rectangle(cDeviceWidth, cDeviceTaskBarHeight, 0);
	}

	return FALSE;
}

static gboolean AL_UpdateCanvas(gpointer user_data)
{
	if (!cPainting)
		return FALSE;

	GtkWidget* widget = GTK_WIDGET(user_data);
	gtk_widget_queue_draw(widget);

	return TRUE;
}

/* @brief Proxy function for lock screen. */
int main(int argc, char** argv)
{
	atexit([]() -> void {
		if (!cCGContext)
			return;

		CGReleaseContext(cCGContext);
	});

	std::thread job([]() -> void {
		while (true)
		{
			cPainting = true;

			auto		end		 = std::chrono::system_clock::now();
			std::time_t end_time = std::chrono::system_clock::to_time_t(end);

			std::tm* tm = std::localtime(&end_time);

			cHourFormat = std::to_string(tm->tm_hour);

			if (tm->tm_hour <= 9)
			{
				cHourFormat = "0";
				cHourFormat += std::to_string(tm->tm_hour);
			}

			cHourFormat += ":";

			if (tm->tm_min <= 9)
			{
				cHourFormat += "0";
				cHourFormat += std::to_string(tm->tm_min);
			}
			else
			{
				cHourFormat += std::to_string(tm->tm_min);
			}

			cPainting = false;

			sleep(1);
		}
	});

	job.detach();

	GtkWidget* window		= nullptr;
	GtkWidget* drawing_area = nullptr;

	gtk_init(&argc, (char***)&argv);

	window		 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	drawing_area = gtk_drawing_area_new();

	gtk_container_add(GTK_CONTAINER(window), drawing_area);

	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

	g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(AL_ShowLockScreen), nullptr);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), nullptr);

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), cDeviceWidth, cDeviceHeight);
	gtk_window_set_title(GTK_WINDOW(window), "AppLauncher");
	gtk_widget_show_all(window);

	g_timeout_add(24, AL_UpdateCanvas, drawing_area);
	gtk_main();

	return 0;
}
