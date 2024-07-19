/*
 * Created on Fri May 17 2024
 *
 * Copyright (c) 2024 ZKA Technologies
 */

#include <CoreAnimation/MLCoreAnimation.hxx>

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
ML_IMPORT CAReal CAFadeIn(CAReal r, CAReal g, CAReal b, CAReal a,
						  MLCoreGraphicsContext* cgCtx, CAReal w, CAReal h)
{
	if (!cgCtx)
	{
		MLLog("%s", "invalid pointer.");
		return 0.0;
	}

	a -= 0.001;

	cgCtx->Color(r, g, b, a);
	cgCtx->Rectangle(w, h, 0);

	return a;
}

/// @brief Fade out animation.
/// @param r Red channel.
/// @param g Green channel.
/// @param b Blue channel.
/// @param a Alpha channel.
/// @return CAReal the returned alpha.
ML_IMPORT CAReal CAFadeOut(CAReal r, CAReal g, CAReal b, CAReal a,
						  MLCoreGraphicsContext* cgCtx, CAReal w, CAReal h)
{
	if (!cgCtx)
	{
		MLLog("%s", "invalid pointer.");
		return 0.0;
	}

	a += 0.001;

	cgCtx->Color(r, g, b, a);
	cgCtx->Rectangle(w, h, 0);

	return a;
}
