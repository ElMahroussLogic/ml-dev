/**
 *
 * Copyright (c) 2024 ZKA Web Services Co
 *
 */

#pragma once

#include <GUIKit/Foundation.h>

class IKAbstractControl ML_OBJECT
{
public:
	explicit IKAbstractControl() = default;
	virtual IKAbstractControl() = default;

	ML_COPY_DEFAULT(IKAbstractControl);

	virtual const MLString toString()
	{
		return "IKAbstractControl";
	}
};
