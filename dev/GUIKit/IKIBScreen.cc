/**
 *
 * Copyright (c) 2024 Amlal EL Mahrouss
 *
 */

#include <GUIKit/IKIBScreen.h>
#include <cstring>

#ifdef GUIKIT_USE_IBKIT

IKIBScreen::IKIBScreen(const MLRect& dimensions, ib_surface_t* surface)
{
	mDim = dimensions;
	ML_MUST_PASS(mDim);

	mFramebuffer = new MLInteger8[mDim.width * mDim.height];
	ML_MUST_PASS(mFramebuffer);

	mSurface = surface;
	ML_MUST_PASS(mSurface);
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
		MLInteger tex_w = ib_image_surface_get_width(mSurface);
		MLInteger tex_h = ib_image_surface_get_height(mSurface);

		MLInteger8* dataOfIB = ib_image_surface_get_data(mSurface);

		MLRect texDim;

		texDim.width = tex_w;
		texDim.height = tex_h;

		if (mDim.sizeMatches(texDim))
		{
			memcpy(mFramebuffer, dataOfIB, tex_w * tex_h);
		}
	}
}

const MLString IKIBScreen::toString()
{
	return MLString("IKIBScreen");
}

#endif // ifdef GUIKIT_USE_CAIRO
