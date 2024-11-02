/**
 *
 * Copyright (c) 2024 EL Mahrouss Logic
 *
 */

#pragma once

#include <GUIKit/AbstractScreen.h>
#include <cairo/cairo.h>

class IKCairoScreen final IK_SCREEN
{
public:
	explicit IKCairoScreen(const MLRect& dim, cairo_surface_t* surface);
	~IKCairoScreen() override;

	const MLString toString() override;
	void		   draw() override;

private:
	MLInteger8*		 mFramebuffer{nullptr};
	MLRect			 mDim;
	cairo_surface_t* mSurface{nullptr};
};
