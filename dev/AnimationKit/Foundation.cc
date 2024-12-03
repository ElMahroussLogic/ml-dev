/*
 * Created on Fri May 17 2024
 *
 * Copyright (c) 2024 Amlal EL Mahrouss
 */

#include <AnimationKit/Foundation.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Linear interop helper function.
/// @param start where to begin
/// @param end where to end
/// @param status the status
/// @return the returned result of the lerp.
///////////////////////////////////////////////////////////////////////////////////////////////////
ML_IMPORT CAReal CALerp(CAReal start, CAReal end, CAReal status)
{
	return (start + status * (end - start));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Fade in animation.
/// @param r Red channel.
/// @param g Green channel.
/// @param b Blue channel.
/// @param a Alpha channel.
/// @return CAReal the returned alpha.
///////////////////////////////////////////////////////////////////////////////////////////////////
ML_IMPORT CAReal CAFadeIn(MLInteger red, MLInteger green, MLInteger blue, MLInteger alpha, CAReal x, CAReal y, CAReal width, CAReal height)
{
	alpha -= 0.001;

	GKDrawRoundedRectangle(x, y, width, height, 0, {.r = red, .g = green, .b = blue, .a = alpha});

	return alpha;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Fade out animation.
/// @param red Red channel.
/// @param green Green channel.
/// @param blue Blue channel.
/// @param alpha Alpha channel.
/// @return CAReal the returned alpha.
///////////////////////////////////////////////////////////////////////////////////////////////////
ML_IMPORT CAReal CAFadeOut(MLInteger red, MLInteger green, MLInteger blue, MLInteger alpha, CAReal x, CAReal y, CAReal width, CAReal height)
{
	alpha += 0.001;

	GKDrawRoundedRectangle(x, y, width, height, 0, {.r = red, .g = green, .b = blue, .a = alpha});

	return alpha;
}
