/**
 *
 * Copyright (c) 2024 Amlal EL Mahrouss
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
	MLRect	fFrame;
};
