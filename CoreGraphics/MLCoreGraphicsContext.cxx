/*
 * Created on Fri May 10 2024
 *
 * Copyright (c) 2024 ZKA Technologies
 */

#include <CoreGraphics/MLCoreGraphicsContext.hxx>
#include <CoreGraphics/Private/MLCoreGraphicsContextCairo.inl>

/// @brief Request a context regarding the features set.
/// @param featureSet the feature set.
/// @param strict should we require all the features to be here?
/// @note if no, please check for feature with operator& inside
/// MLCoreGraphicsContext.
/// @return The new graphics context.
MLCoreGraphicsContext*
		  CGRequestContext(CGSizeT featureSet, bool strict, CGReal width, CGReal height)
{
	MLCoreGraphicsContext* context =
		new MLCoreGraphicsContextCairo(width, height);
	return context;
}

/// @brief Releases a Core Graphics context.
/// @param context The context itself.
/// @return This function returns void.
void CGReleaseContext(MLCoreGraphicsContext* context)
{
	if (context)
	{
		delete context;
	}
}

#if 1
#include <string>

typedef size_t platform_size_t;
typedef std::string platform_string_t;

#else
typedef MLStrongString platform_string_t;
#endif

/// @brief To string method.
/// @return the class as a string
const MLString MLCoreGraphicsContext::toString()
{
	platform_string_t objectName = "{ \'MLCoreGraphicsContext\': {";
	platform_size_t defaultSz = 4096;

	MLString ctxStr = MLString(defaultSz);
	ctxStr += objectName.c_str();
	ctxStr += "\'Renderer\': \'Hardware Accelerated Cairo based PDF renderer\' } }";

	return ctxStr;
}

/// @brief => string method, same as before..
/// @return the class as a string
const MLString MLCoreGraphicsContext::ToString()
{
	return this->toString();
}
