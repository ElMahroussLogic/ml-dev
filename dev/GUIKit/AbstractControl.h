/**
 *
 * Copyright (c) 2024 Amlal EL Mahrouss
 *
 */

#pragma once

#include <GUIKit/Foundation.h>

#define IK_CONTROL : public IKAbstractControl

class IKAbstractControl ML_OBJECT
{
public:
	explicit IKAbstractControl() = default;
	virtual ~IKAbstractControl() = default;

	ML_COPY_DEFAULT(IKAbstractControl);

	virtual const MLString toString()
	{
		return "IKAbstractControl";
	}
};
