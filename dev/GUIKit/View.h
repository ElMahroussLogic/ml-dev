/**
 *
 * Copyright (c) 2024 ELMH Group
 *
 */

#pragma once

#include <GUIKit/Foundation.h>

class IKView ML_OBJECT
{
	explicit IKView() = default;
	virtual IKView()  = default;

	ML_COPY_DELETE(IKView);

	virtual const MLString toString()
	{
		return "IKView";
	}
};
