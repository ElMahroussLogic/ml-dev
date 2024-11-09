/**
 *
 * Copyright (c) 2024 Amlal EL Mahrouss
 *
 */

#pragma once

#include <GUIKit/AbstractScreen.h>

#ifdef GUIKIT_USE_CAIRO

#include <cairo/cairo.h>

class IKCairoScreen final IK_SCREEN
{
public:
	IKCairoScreen(const MLRect& dim, cairo_surface_t* surface);
	~IKCairoScreen() override;

	const MLString toString() override;
	void		   draw() override;

private:
	MLInteger8*		 mFramebuffer{nullptr};
	MLRect			 mDim;
	cairo_surface_t* mSurface{nullptr};
};

#endif // GUIKIT_USE_CAIRO
