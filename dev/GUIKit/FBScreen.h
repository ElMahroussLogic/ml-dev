/**
 *
 * Copyright (c) 2024 EL Mahrouss Logic
 *
 */

#pragma once

#include <GUIKit/AbstractScreen.h>

class IKFBScreen final IK_SCREEN
{
public:
	explicit IKFBScreen(const MLRect& dim);
	~IKFBScreen() override;

	const MLString toString() override;
	void draw() override;
	bool shouldDraw() override;

private:
	MLInteger* mFramebuffer{nullptr};

};
