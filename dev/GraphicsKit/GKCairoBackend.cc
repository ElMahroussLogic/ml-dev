/*
 * Created on Fri May 10 2024
 *
 * Copyright (c) 2024 ZKA Web Services Co
 */

#include <GraphicsKit/GKContext.h>
#include <GraphicsKit/Private/GKContextCairo.inl>

/// @brief Request a context regarding the features set.
/// @param featureSet the feature set.
/// @param strict should we require all the features to be here?
/// @note if no, please check for feature with operator& inside GKContext.
/// @return The new graphics context.
GKContext*
GKequestContext(GKSizeType featureSet, bool strict, GKReal width, GKReal height)
{
	GKContext* context =
		new GKContextCairo(width, height);
	ML_MUST_PASS(context);

	return context;
}

/// @brief To string method.
/// @return the class as a string
const MLString GKContext::toString()
{
	MLString ctxBackendJson = MLString("['Backend': 'Cairo']");
	return ctxBackendJson;
}
