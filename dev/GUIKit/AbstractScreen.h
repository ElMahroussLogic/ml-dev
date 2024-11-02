/**
 *
 * Copyright (c) 2024 EL Mahrouss Logic
 *
 */

#pragma once

#include <GUIKit/Foundation.h>

#define IK_SCREEN : public IKAbstractScreen

class IKAbstractScreen ML_OBJECT
{
public:
	explicit IKAbstractScreen() = default;
	~IKAbstractScreen()			= default;

	ML_COPY_DELETE(IKAbstractScreen);

	virtual const MLString toString()
	{
		return MLString("IKAbstractScreen");
	}

	virtual void draw() = 0;

public:
	BOOL shouldDraw{false};

protected:
	MLRect	mDimensions;
	MLPoint mPosition;
};

#define kIKMaxDisplayPerWorkstation (14U)

using IKScreenArray = MLArray<IKAbstractScreen*, kIKMaxDisplayPerWorkstation>;
