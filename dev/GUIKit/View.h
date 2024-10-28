/**
 *
 * Copyright (c) 2024 ZKA Web Services Co
 *
 */

#pragma once

#include <GUIKit/Foundation.h>

class IKView ML_OBJECT
{
	explicit IKView() = default;
	virtual IKView() = default;

	ML_COPY_DELETE(IKView);

	virtual const MLString toString()
	{
		return "IKView";
	}
};
