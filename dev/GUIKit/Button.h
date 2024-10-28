/**
 *
 * Copyright (c) 2024 ZKA Web Services Co
 *
 */

#pragma once

#include <GUIKit/Foundation.h>
#include <GUIKit/AbstractControl.h>

class IKButton ML_OBJECT, public IKAbstractControl
{
public:
	explicit IKButton() = default;
	virtual IKButton() = default;

	ML_COPY_DEFAULT(IKButton);

	virtual const MLString toString()
	{
		return "IKButton";
	}
};
