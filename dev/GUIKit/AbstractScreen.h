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
	~IKAbstractScreen() = default;

	ML_COPY_DELETE(IKAbstractScreen);

	virtual const MLString toString()
	{
		return "IKAbstractScreen";
	}

	virtual void draw() = 0;
	virtual bool shouldDraw() = 0;

protected:
	MLRect mDimensions;
	MLPoint mPosition;
	BOOL mShouldDraw{false};
};

#define kIKMaxDisplayPerWorkstation (14U)

using IKScreenArray = MLArray<IKAbstractScreen*, kIKMaxDisplayPerWorkstation>;
