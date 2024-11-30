/*
 * Created on Fri May 10 2024
 *
 * Copyright (c) 2024 ELMH Group
 */

#include <GraphicsKit/GKContextInterface.h>
#include <GraphicsKit/Private/GKContextCairo.inl>

#ifdef GK_CAIRO_SUPPORT
/// @brief Request a context regarding the features set.
/// @param feature_sets the feature set flags list.
/// @param strict should we require all the features to be here?
/// @note if no, please check for feature with operator& inside GKContextInterface.
/// @return The new graphics context.
GKContextInterface* GKequestContext(GKSizeType feature_sets, BOOL strict, GKReal width, GKReal height)
{
	ML_UNUSED(feature_sets);

	GKContextInterface* context =
		new GKContextCairo(width, height);
	ML_MUST_PASS(context);

	return context;
}
#endif // ifdef GK_CAIRO_SUPPORT