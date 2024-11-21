/**
 *
 * Copyright (c) 2024 Amlal EL Mahrouss
 *
 */

#include <GUIKit/IKIBScreen.h>
#include <cstring>

#ifdef GUIKIT_USE_IBKIT

IKIBScreen::IKIBScreen(const MLRect& dimensions, MLInteger8* framebuffer)
{
	mFrame = dimensions;
	ML_MUST_PASS(mFrame);

	mTargetFramebuffer = framebuffer;
	ML_MUST_PASS(mTargetFramebuffer);

	mFramebuffer = new MLInteger8[mFrame.width * mFrame.height];
	ML_MUST_PASS(mFramebuffer);
}

IKIBScreen::~IKIBScreen()
{
	if (mFramebuffer)
	{
		delete[] mFramebuffer;
		mFramebuffer = nullptr;
	}
}


void IKIBScreen::draw()
{
	if (this->shouldDraw)
	{
		memcpy(mFramebuffer, mTargetFramebuffer, mFrame.width * mFrame.height);
	}
}

const MLString IKIBScreen::toString()
{
	return MLString("IKIBScreen");
}

#endif // ifdef GUIKIT_USE_CAIRO
