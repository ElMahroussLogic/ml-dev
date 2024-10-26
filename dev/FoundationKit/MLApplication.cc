/* -------------------------------------------

	Copyright ZKA Web Services Co

------------------------------------------- */

#include <FoundationKit/MLApplication.h>

#ifdef _WIN32
#include <FoundationKit/Win32/Win32.h>
#else
#include <FoundationKit/MLAlert.h>
#endif

#include <filesystem>
#include <fstream>
#include <sstream>

/// @brief Returns the application's name as given by the bundle.
/// @return the app string.
const MLString MLApplication::getAppName()
{
	MLString strKey("MLAppName");
	auto	 strValue = this->getAppField(strKey);

	return strValue;
}

/// @brief Returns the application's version as given by the bundle.
/// @return the app string.
const MLString MLApplication::getAppVersion()
{
	MLString strKey("MLAppVersion");
	auto	 strValue = this->getAppField(strKey);

	return strValue;
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

/// @brief Returns the application's field.
/// @param fieldName The field's name. (such as MLAppName, MLFooField)
/// @return the field's value.
const MLString MLApplication::getAppField(MLString fieldName, MLSizeType fieldLen)
{
	constexpr auto kPkgPath = "/ZKA/Manifests/.alist";

	auto baseAppPath = std::filesystem::current_path().string();
	baseAppPath += kPkgPath;

	std::ifstream streamXml(baseAppPath);

	std::stringstream streamXmlSS;
	streamXmlSS << streamXml.rdbuf();

	MLXMLMarkup parser(streamXmlSS.str().c_str());

	MLString appName = parser.getXML(fieldName, fieldLen, NO);
	return appName;
}

/// @brief returns the app path as a string.
const MLString MLApplication::toString()
{
	constexpr auto kPkgPath = "/ZKA/";

	auto baseAppPath = std::filesystem::current_path().string();
	baseAppPath += kPkgPath;

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
	alert.runModal("FoundationKit", "%s\n%s", "FoundationKit Framework.", "FoundationKit is a property of ZKA, Copyright ZKA Web Services Co all rights reserved.");
#endif
}
