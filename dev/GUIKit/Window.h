/**
 *
 * Copyright (c) 2024 ZKA Web Services Co
 *
 */

#pragma once

#include <GUIKit/Foundation.h>

class IKWindow final ML_OBJECT
{
public:
	explicit IKWindow() = default;
	virtual IKWindow() = default;

	ML_COPY_DELETE(IKWindow);

	virtual const MLString toString()
	{
		return "IKWindow";
	}

public:
	MLPoint fPosition;
	MLRect fFrame;

};
