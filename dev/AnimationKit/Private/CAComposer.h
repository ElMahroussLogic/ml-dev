/*
 * AnimationKit
 * Copyright (c) 2024 ELMH Group
 */

#ifndef AK_CACOMPOSER_H
#define AK_CACOMPOSER_H

#include <FoundationKit/FoundationKit.h>

/* 255 frames per cells. */
#define kCAMaxFrameCells (255U)

class CAComposerKeyFrameCell;
class CAAbstractComposerKeyFrame;

/// @brief Cell frame structure.
class CAComposerKeyFrameCell ML_OBJECT
{
protected:
	MLString mName;
	MLPoint	 mOrigin;
	MLRect	 mScale;

public:
	explicit CAComposerKeyFrameCell() = default;
	virtual ~CAComposerKeyFrameCell() = default;

	ML_COPY_DEFAULT(CAComposerKeyFrameCell);

protected:
	/// @brief Plays the frame of this cell.
	/// @param composer the CAAbstractComposer parent instance.
	virtual MLInteger64 playFrame(CAAbstractComposer* composer) = 0;
};

class CAAbstractComposer ML_OBJECT
{
protected:
	MLArray<CAComposerKeyFrameCell, kCAMaxFrameCells> mFrames;

public:
	CAAbstractComposer()  = default;
	~CAAbstractComposer() = default;

public:
	ML_COPY_DEFAULT(CAAbstractComposer);

public:
	virtual void											   setKeyFrameID(const MLString& name) = 0;
	virtual MLString										   getKeyFrameByID()				   = 0;
	virtual MLArray<CAComposerKeyFrameCell, kCAMaxFrameCells>& getFrames()						   = 0;
	virtual BOOL											   runFrames()						   = 0;
	virtual BOOL											   runFrameAt(const MLInteger64& at)   = 0;
};

#endif // AK_CACOMPOSER_H
