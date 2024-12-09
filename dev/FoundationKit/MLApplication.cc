/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved

------------------------------------------- */

#include <FoundationKit/MLApplication.h>
#include <FoundationKit/MLAlert.h>
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
	constexpr auto kPkgPath = "/ML/Resources/plist.xml";

	auto baseAppPath = std::filesystem::current_path().string();
	baseAppPath += kPkgPath;

	std::ifstream streamXml(baseAppPath);

	std::stringstream streamXmlSS;
	streamXmlSS << streamXml.rdbuf();

	MLXMLNode parser(streamXmlSS.str().c_str());

	MLString appName = parser.getValue(fieldName, fieldLen);
	return appName;
}

/// @brief returns the app path as a string.
const MLString MLApplication::toString()
{
	constexpr auto kPkgPath = "/ML/";

	auto baseAppPath = std::filesystem::current_path().string();
	baseAppPath += kPkgPath;

	MLString appName = MLString(baseAppPath.size());
	appName += baseAppPath.data();

	return appName;
}

/// @brief Show about modal.
void MLApplication::showAboutModal() noexcept
{
	MLAlert alert;
	alert.runModal("FoundationKit", "%s\n%s", "FoundationKit Framework", "Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.");
}
