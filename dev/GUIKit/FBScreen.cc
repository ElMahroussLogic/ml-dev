/**
 *
 * Copyright (c) 2024 Amlal EL Mahrouss
 *
 */

#include <GUIKit/FBScreen.h>

#ifdef GUIKIT_USE_IBKIT

IKFBScreen::IKFBScreen(const MLRect& dimensions, MLInteger8* framebuffer)
{
	mFrame = dimensions;
	ML_MUST_PASS(mFrame);

	mTargetFramebuffer = framebuffer;
	ML_MUST_PASS(mTargetFramebuffer);

	mFramebuffer = new MLInteger8[mFrame.width * mFrame.height];
	ML_MUST_PASS(mFramebuffer);
}

IKFBScreen::~IKFBScreen()
{
	if (mFramebuffer)
	{
		delete[] mFramebuffer;
		mFramebuffer = nullptr;
	}
}


void IKFBScreen::draw()
{
	if (this->shouldDraw)
	{
		memcpy(mFramebuffer, mTargetFramebuffer, mFrame.width * mFrame.height);
	}
}

const MLString IKFBScreen::toString()
{
	return MLString("IKFBScreen");
}

#endif // ifdef GUIKIT_USE_CAIRO
