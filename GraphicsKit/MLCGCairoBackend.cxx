/*
 * Created on Fri May 10 2024
 *
 * Copyright (c) 2024 ZKA Technologies
 */

#include <GraphicsKit/MLCoreGraphicsContext.hxx>
#include <GraphicsKit/Private/MLCoreGraphicsContextCairo.inl>

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

	MLLog("%s", "Testing context...");
    ML_MUST_PASS(context);

	return context;
}
