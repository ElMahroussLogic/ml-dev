/*
 * AnimationKit
 * Copyright (c) 2024 ZKA Web Services Co
 */

#pragma once

#include <FoundationKit/MLRect.h>
#include <FoundationKit/MLPoint.h>
#include <FoundationKit/FoundationKit.h>
#include <AnimationKit/Private/MLCoreAnimationBase.h>
#include <GraphicsKit/GraphicsKit.h>
#include <FoundationKit/MLArray.h>

class CAComposerFrame;
class CAComposerKeyFrame;
class CAComposerKeyFrameCell;

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
ML_IMPORT CAReal CAFadeIn(CAReal r, CAReal g, CAReal b, CAReal a, GKContext* cg_ctx, CAReal w, CAReal h);

/// @brief Fade out animation.
/// @param r Red channel.
/// @param g Green channel.
/// @param b Blue channel.
/// @param a Alpha channel.
/// @return CAReal the returned alpha.
ML_IMPORT CAReal CAFadeOut(CAReal r, CAReal g, CAReal b, CAReal a, GKContext* cg_ctx, CAReal w, CAReal h);

#define kCAMaxFrameCells (255)

struct CAComposerKeyFrameCell
{
	MLString mFrameName;
	MLPoint	 mOrigin;
	MLRect	 mSize;
	MLInteger64 (*mAnimationFrame)(CAComposerKeyFrameCell* cell);
};

class CAComposerKeyFrame
{
protected:
	MLArray<CAComposerKeyFrameCell, kCAMaxFrameCells> mFrames;

public:
	virtual void operator()() = 0;
};
