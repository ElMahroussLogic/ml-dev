/*
 * AnimationKit
 * Copyright (c) 2024 ZKA Web Services Co
 */

#pragma once

#include <FoundationKit/FoundationKit.hxx>
#include <AnimationKit/Private/MLCoreAnimationBase.hxx>
#include <GraphicsKit/GraphicsKit.hxx>

/// @brief Linear interop helper function.
/// @param start where to begin
/// @param end where to end
/// @param status the status
/// @return the returned result of the lerp.
ML_IMPORT CAReal CALerp(CAReal start, CAReal end, CAReal status);

/// @brief Fade in animation.
/// @param r Red channel.
/// @param g Green channel.
/// @param b Blue channel.
/// @param a Alpha channel.
/// @return CAReal the returned alpha.
ML_IMPORT CAReal CAFadeIn(CAReal r, CAReal g, CAReal b, CAReal a, MLCoreGraphicsContext* cg_ctx, CAReal w, CAReal h);

/// @brief Fade out animation.
/// @param r Red channel.
/// @param g Green channel.
/// @param b Blue channel.
/// @param a Alpha channel.
/// @return CAReal the returned alpha.
ML_IMPORT CAReal CAFadeOut(CAReal r, CAReal g, CAReal b, CAReal a, MLCoreGraphicsContext* cg_ctx, CAReal w, CAReal h);
