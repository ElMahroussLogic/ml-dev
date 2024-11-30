/**
 *
 * Copyright (c) 2024 ELMH Group
 *
 */

#pragma once

#include <GUIKit/Foundation.h>
#include <GUIKit/AbstractControl.h>

class IKButton IK_CONTROL
{
public:
	explicit IKButton() = default;
	virtual ~IKButton() = default;

	ML_COPY_DEFAULT(IKButton);

	virtual const MLString toString()
	{
		return "IKButton";
	}
};
