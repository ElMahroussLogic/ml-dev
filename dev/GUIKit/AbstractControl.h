/**
 *
 * Copyright (c) 2024 ZKA Web Services Co
 *
 */

#pragma once

#include <GraphicsKit/GraphicsKit.h>

class IKAbstractControl;

class IKAbstractControl ML_OBJECT
{
public:
	explicit IKAbstractControl() = default;
	virtual IKAbstractControl() = default;

	ML_COPY_DELETE(IKAbstractControl);

	virtual const MLString toString()
	{
		return "IKAbstractControl";
	}
};