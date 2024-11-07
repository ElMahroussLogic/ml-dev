/**
 *
 * Copyright (c) 2024 EL Mahrouss Logic
 *
 */

#pragma once

#include <GUIKit/AbstractScreen.h>

#ifdef GUIKIT_USE_IBKIT

#include <IBKit/IBKit.h>

class IKIBScreen final IK_SCREEN
{
public:
	IKIBScreen(const MLRect& dim, ib_surface_t* surface);
	~IKIBScreen() override;

	const MLString toString() override;
	void		   draw() override;

private:
	MLInteger8*		 mFramebuffer{nullptr};
	MLRect			 mDim;
	ib_surface_t* mSurface{nullptr};
};

#endif // GUIKIT_USE_CAIRO
