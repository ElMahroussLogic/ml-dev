/*
 * Created on Fri May 10 2024
 *
 * Copyright (c) 2024 SoftwareLabs 
 */

#include <MLCoreGraphicsContext.hxx>
#include <Private/MLCoreGraphicsContextCairo.inl>

/// @brief Request a context regarding the features set.
/// @param featureSet the feature set.
/// @param strict should we require all the features to be here?
/// @note if no, please check for feature with operator& inside
/// MLCoreGraphicsContext.
/// @return The new graphics context.
ML_EXPORT MLCoreGraphicsContext*
		  CGRequestContext(CGSizeT featureSet, bool strict, CGReal width, CGReal height)
{
	MLCoreGraphicsContext* context =
		new MLCoreGraphicsContextCairo(width, height);
	return context;
}

/// @brief Releases a Core Graphics context.
/// @param context The context itself.
/// @return This function returns void.
ML_EXPORT void CGReleaseContext(MLCoreGraphicsContext* context)
{
	if (context)
	{
		delete context;
	}
}

/// @brief To string method.
/// @return the class as a string
const MLString MLCoreGraphicsContext::toString()
{
	constexpr auto objectName = "MLCoreGraphicsContext";

	MLString ctxStr = MLString(strlen(objectName));
	ctxStr += objectName;

	return ctxStr;
}