/**
 *
 * Copyright (c) 2024 ELMH Group
 *
 */

#pragma once

#include <GUIKit/AbstractScreen.h>

#ifdef GUIKIT_USE_IBKIT

class IKFBScreen final IK_SCREEN
{
public:
	IKFBScreen(const MLRect& dim, MLInteger8* surface);
	~IKFBScreen() override;

	const MLString toString() override;
	void		   draw() override;

private:
	MLInteger8* mFramebuffer{nullptr};
	MLInteger8* mTargetFramebuffer{nullptr};
	MLRect		mFrame;
};

#endif // GUIKIT_USE_CAIRO
