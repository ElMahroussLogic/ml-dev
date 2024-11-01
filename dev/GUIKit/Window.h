/**
 *
 * Copyright (c) 2024 EL Mahrouss Logic
 *
 */

#pragma once

#include <GUIKit/Foundation.h>

class IKWindow ML_OBJECT
{
public:
	explicit IKWindow();
	virtual ~IKWindow();

	ML_COPY_DELETE(IKWindow);

	virtual const MLString toString();

public:
	MLPoint fPosition;
	MLRect fFrame;

};
