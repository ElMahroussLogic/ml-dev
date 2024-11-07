/**
 *
 * Copyright (c) 2024 EL Mahrouss Logic
 *
 */

#pragma once

#include <GUIKit/AbstractScreen.h>

#ifdef GUIKIT_USE_IBKIT

class IKIBScreen final IK_SCREEN
{
public:
	IKIBScreen(const MLRect& dim, MLInteger8* surface);
	~IKIBScreen() override;

	const MLString toString() override;
	void		   draw() override;

private:
	MLInteger8*		 mFramebuffer{nullptr};
	MLInteger8*      mTargetFramebuffer{nullptr};
	MLRect			 mFrame;
};

#endif // GUIKIT_USE_CAIRO
