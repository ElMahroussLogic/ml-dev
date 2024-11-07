/**
 *
 * Copyright (c) 2024 Amlal EL Mahrouss
 *
 */

#include <GUIKit/IKCairoScreen.h>
#include <cstring>

#ifdef GUIKIT_USE_CAIRO

IKCairoScreen::IKCairoScreen(const MLRect& dimensions, cairo_surface_t* surface)
{
	mDim = dimensions;
	ML_MUST_PASS(mDim);

	mFramebuffer = new MLInteger8[mDim.width * mDim.height];
	ML_MUST_PASS(mFramebuffer);

	mSurface = surface;
	ML_MUST_PASS(mSurface);
}

IKCairoScreen::~IKCairoScreen()
{
	if (mFramebuffer)
	{
		delete[] mFramebuffer;
		mFramebuffer = nullptr;
	}
}


void IKCairoScreen::draw()
{
	if (this->shouldDraw)
	{
		MLInteger tex_w = cairo_image_surface_get_width(mSurface);
		MLInteger tex_h = cairo_image_surface_get_height(mSurface);

		MLInteger8* data = cairo_image_surface_get_data(mSurface);

		MLRect texDim;

		texDim.width = tex_w;
		texDim.height = tex_h;

		if (mDim.sizeMatches(texDim))
		{
			memcpy(mFramebuffer, data, tex_w * tex_h);
		}
	}
}

const MLString IKCairoScreen::toString()
{
	return MLString("IKCairoScreen");
}

#endif // ifdef GUIKIT_USE_CAIRO
