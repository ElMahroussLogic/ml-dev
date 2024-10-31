/**
 *
 * Copyright (c) 2024 EL Mahrouss Logic
 *
 */

#include <GUIKit/FBScreen.h>

IKFBScreen::IKFBScreen(const MLRect& dim)
{
	mFramebuffer = new MLInteger[dim.width * dim.height];
}

IKFBScreen::~IKFBScreen() override
{
	if (mFramebuffer)
	{
		delete[] mFramebuffer;
		mFramebuffer = nullptr;
	}
}


void IKFBScreen::draw()
{
	if (this->shouldDraw())
	{

	}
}

bool IKFBScreen::shouldDraw()
{
	return mShouldDraw;
}

const MLString IKFBScreen::toString() override
{
	return "IKFBScreen";
}
