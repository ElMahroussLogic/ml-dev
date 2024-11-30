/*
 * Created on Fri May 17 2024
 *
 * Copyright (c) 2024 ELMH Group
 */

#include <AnimationKit/Foundation.h>

/// @brief Linear interop helper function.
/// @param start where to begin
/// @param end where to end
/// @param status the status
/// @return the returned result of the lerp.
ML_IMPORT CAReal CALerp(CAReal start, CAReal end, CAReal status)
{
	return (start + status * (end - start));
}

/// @brief Fade in animation.
/// @param r Red channel.
/// @param g Green channel.
/// @param b Blue channel.
/// @param a Alpha channel.
/// @return CAReal the returned alpha.
ML_IMPORT CAReal CAFadeIn(CAReal red, CAReal green, CAReal blue, CAReal alpha, GKContextInterface* cg_ctx, CAReal width, CAReal height)
{
	if (!cg_ctx)
	{
		MLLog("%s", "invalid pointer given to function.");
		return 0.0;
	}

	alpha -= 0.001;

	cg_ctx->color(red, green, blue, alpha);
	cg_ctx->rectangle(width, height, 0);

	return alpha;
}

/// @brief Fade out animation.
/// @param red Red channel.
/// @param green Green channel.
/// @param blue Blue channel.
/// @param alpha Alpha channel.
/// @return CAReal the returned alpha.
ML_IMPORT CAReal CAFadeOut(CAReal red, CAReal green, CAReal blue, CAReal alpha, GKContextInterface* cg_ctx, CAReal width, CAReal height)
{
	if (!cg_ctx)
	{
		MLLog("%s", "invalid pointer given to function.");
		return 0.0;
	}

	alpha += 0.001;

	cg_ctx->color(red, green, blue, alpha);
	cg_ctx->rectangle(width, height, 0);

	return alpha;
}
