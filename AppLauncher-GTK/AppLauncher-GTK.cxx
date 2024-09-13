/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#include <GraphicsKit/GraphicsKit.hxx>
#include <AnimationKit/MLCoreAnimation.hxx>
#include <ctime>

extern "C"
{
#   include <gtk/gtk.h>
}

#define cDeviceWidth		 (1045 / 2)
#define cDeviceHeight		 (1750 / 2)
#define cDeviceTaskBarHeight (40)

static std::string            cTitle = "AppLauncher (GTK Backend)";
static bool					  cDeviceLocked = true;
static std::string			  cHourFormat;
static bool					  cPainting			 = false;
static bool					  cDeviceLockTimeout = false;
static MLCoreGraphicsContext* cCGContext		 = CGRequestContext(0, false, cDeviceWidth, cDeviceHeight);
static CGReal cDeviceLockAlphaCurrent = 10.0;
static CGReal cDeviceLockAlpha		  = 0.0;
static CGReal cDeviceLockAlphaIndex	  = 0.0;

static int AL_ShowLockScreen(GtkWidget* widget, cairo_t* cr, void* user_data)
{
	cairo_t** data;
	cCGContext->leak((void***)&data);

	if (!*data)
	{
		*data = cr;
	}

	cCGContext->present(0.0, 0.0, 0.0);

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

	cCGContext->color(1, 1, 1, cDeviceLockAlpha)->fontSize(120.0)->fontFamily("Inter", true)->move(40, cDeviceHeight - 200 + 40)->text(cHourFormat.c_str(), false);
	cCGContext->color(1, 1, 1, cDeviceLockAlpha)->fontSize(20.0)->fontFamily("Inter", false)->move(40, cDeviceHeight - 60)->text("Swipe to Unlock.", false);

	return TRUE;
}

static gboolean AL_UpdateCanvas(gpointer user_data)
{
	GtkWidget* widget = GTK_WIDGET(user_data);
	gtk_widget_queue_draw(widget);

	return TRUE;
}

static gboolean AL_EnableLockScreen(gpointer user_data)
{
	if (cDeviceLockTimeout)
	{
		return TRUE;
	}

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

	return FALSE;
}

/* @brief Proxy function for lock screen. */
int main(int argc, char** argv)
{
	std::atexit([]() -> void {
		if (!cCGContext)
			return;

		CGReleaseContext(cCGContext);
	});

	std::thread hour_job([]() -> void {
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

	g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(AL_ShowLockScreen), drawing_area);
	g_signal_connect(G_OBJECT(window), "button-press-event", G_CALLBACK(AL_EnableLockScreen), drawing_area);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), drawing_area);

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), cDeviceWidth, cDeviceHeight);
	gtk_window_set_title(GTK_WINDOW(window), cTitle.c_str());
	gtk_widget_show_all(window);

	g_timeout_add(16, AL_UpdateCanvas, drawing_area);
	gtk_main();

	return 0;
}
