/**
 *
 * Copyright (c) 2024 ELMH Group
 *
 */

#pragma once

#include <GUIKit/Foundation.h>

class IKWidget ML_OBJECT
{
	explicit IKWidget() = default;
	virtual IKWidget()  = default;

	ML_COPY_DELETE(IKWidget);

	virtual const MLString toString()
	{
		return "IKWidget";
	}
};
