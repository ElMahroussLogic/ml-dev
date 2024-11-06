/*
 * Created on Fri May 10 2024
 *
 * Copyright (c) 2024 Amlal EL Mahrouss
 */

#include <GraphicsKit/GKContext.h>
#include <GraphicsKit/Private/GKContextCairo.inl>

/// @brief Request a context regarding the features set.
/// @param feature_sets the feature set flags list.
/// @param strict should we require all the features to be here?
/// @note if no, please check for feature with operator& inside GKContext.
/// @return The new graphics context.
GKContext* GKequestContext(GKSizeType feature_sets, BOOL strict, GKReal width, GKReal height)
{
	ML_UNUSED(feature_sets);

	GKContext* context =
		new GKContextCairo(width, height);
	ML_MUST_PASS(context);

	return context;
}
