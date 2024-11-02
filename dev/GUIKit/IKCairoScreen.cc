/**
 *
 * Copyright (c) 2024 EL Mahrouss Logic
 *
 */

#include <GUIKit/IKCairoScreen.h>
#include <cstring>

IKCairoScreen::IKCairoScreen(const MLRect& dimensions, cairo_surface_t* surface)
{
	mDim = dimensions;
	mFramebuffer = new MLInteger8[dim.width * dim.height];
	mSurface = surface;

	ML_MUST_PASS(mSurface);
	ML_MUST_PASS(mFramebuffer);
	ML_MUST_PASS(mDim);
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
