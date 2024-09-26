/* -------------------------------------------

	Copyright ZKA Technologies

------------------------------------------- */

#include <FoundationKit/MLApplication.hxx>

#ifdef _WIN32
#include <FoundationKit/Win32/Win32.hxx>
#else
#include <FoundationKit/MLAlert.hxx>
#endif

#include <filesystem>
#include <fstream>
#include <sstream>

/// @brief Returns the application's name as given by the bundle.
/// @return the app string.
const MLString MLApplication::getAppName()
{
	constexpr auto cPkgXmlPath = "/ZKA/Manifests/App.alist";

	auto baseAppPath = std::filesystem::current_path().string();
	baseAppPath += cPkgXmlPath;

	std::ifstream streamXml(baseAppPath);

	std::stringstream ss;
	ss << streamXml.rdbuf();

	auto strCxx = ss.str();

	MLXMLCoder parser(strCxx.c_str());

	MLString appName = parser.getInnerXML("MLAppName", 255, true);
	return appName;
}

/// @brief Returns the application's version as given by the bundle.
/// @return the app string.
const MLString MLApplication::getAppVersion()
{
	constexpr auto cPkgXmlPath = "/ZKA/Manifests/App.alist";

	auto baseAppPath = std::filesystem::current_path().string();
	baseAppPath += cPkgXmlPath;

	std::ifstream streamXml(baseAppPath);

	std::stringstream ss;
	ss << streamXml.rdbuf();

	auto strCxx = ss.str();

	MLXMLCoder parser(strCxx.c_str());

	MLString appName = parser.getInnerXML("MLAppVersion", 255, true);
	return appName;
}

/// @brief Application singleton
/// @return The singleton.
MLApplication& MLApplication::shared()
{
	static MLApplication* app = nullptr;

	if (!app)
		app = new MLApplication();

	return *app;
}

/// @brief returns the app path as a string.
const MLString MLApplication::toString()
{
	constexpr auto cPkgPath = "/ZKA/";

	auto baseAppPath = std::filesystem::current_path().string();
	baseAppPath += cPkgPath;

	MLString appName = MLString(baseAppPath.size());
	appName += baseAppPath.data();

	return appName;
}

/// @brief Show about modal.
void MLApplication::showAboutModal() noexcept
{
#ifdef _WIN32
	ShellAboutA(nullptr, "FoundationKit for Windows", "FoundationKit is property of ZKA, all rights reserved.", nullptr);
#else
	MLAlert alert;
	alert.runModal("FoundationKit", "%s\n%s", "FoundationKit Framework.", "FoundationKit is a property of ZKA, Copyright ZKA Technologies all rights reserved.");
#endif
}
