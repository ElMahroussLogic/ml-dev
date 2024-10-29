/**
 *
 * Copyright (c) 2024 EL Mahrouss Logic
 *
 */

#pragma once

#include <GUIKit/Foundation.h>

class IKAbstractScreen ML_OBJECT
{
public:
	explicit IKAbstractScreen() = default;
	virtual IKAbstractScreen() = default;

	ML_COPY_DELETE(IKAbstractScreen);

	virtual const MLString toString()
	{
		return "IKAbstractScreen";
	}
};
