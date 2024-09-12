/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#include <GraphicsKit/GraphicsKit.hxx>

#include <ctime>
#include <filesystem>

class LockScreen final
{
public:
	int operator()();
};

int LockScreen::operator()()
{
	MLCoreGraphicsContext* ctx = CGRequestContext(0, false, 1045, 1750);

	auto		end		 = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::tm* tm = std::localtime(&end_time);

	std::string hour_fmt = std::to_string(tm->tm_hour);

	if (tm->tm_hour < 9)
	{
		hour_fmt = "0";
		hour_fmt += std::to_string(tm->tm_hour);
	}

	hour_fmt += ":";

	if (tm->tm_min < 9)
	{
		hour_fmt += "0";
		hour_fmt += std::to_string(tm->tm_min);
	}
	else
	{
		hour_fmt += std::to_string(tm->tm_min);
	}

	ctx->svg("./AppLauncher-Lock.svg")->start();

	if (!std::filesystem::exists("./Background.png"))
		ctx->color(0.6, 0.0, 0.69, 1)->move(0, 0)->rectangle(1045, 1750, 0);
	else
		ctx->image("./Background.png", 1045, 1750, 0, 0);

	ctx->color(1, 1, 1, 1)->fontSize(200.0)->fontFamily("Inter", true)->move(40, 1750 - 200 + 40)->text(hour_fmt.c_str(), false);
	ctx->color(1, 1, 1, 1)->fontSize(40.0)->fontFamily("Inter", false)->move(40, 1750 - 40)->text("Swipe to auth.", false);
	ctx->end();

	CGReleaseContext(ctx);

	return 0;
}

/* @brief Proxy function for lock screen. */
int main()
{
	return LockScreen()();
}
