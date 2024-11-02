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

public:
	virtual const MLString toString() = 0;
	virtual void draw() = 0;

public:
	BOOL shouldDraw{NO};

protected:
	MLRect	mFrame;
	MLPoint mOrigin;
};

#define kIKMaxDisplayPerWorkstation (14U)

using IKScreenArray = MLArray<IKAbstractScreen*, kIKMaxDisplayPerWorkstation>;
