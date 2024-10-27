/*
 * AnimationKit
 * Copyright (c) 2024 ZKA Web Services Co
 */

#ifndef MLCOMPOSER_H
#define MLCOMPOSER_H

#include <FoundationKit/FoundationKit.h>

#define kCAMaxFrameCells (255)

class CAComposerKeyFrameCell;
class CAComposerKeyFrame;

class CAComposerKeyFrameCell final ML_OBJECT
{
public:
	MLString mFrameName;
	MLPoint	 mOrigin;
	MLRect	 mSize;
	MLInteger64 (*mAnimationFrame)(CAComposerKeyFrameCell* cell);
};

class CAComposer ML_OBJECT
{
protected:
	MLArray<CAComposerKeyFrameCell, kCAMaxFrameCells> mFrames;

public:
	CAComposer() = default;
	~CAComposer() = default;

	ML_COPY_DEFAULT(CAComposer);

public:
	virtual void setKeyFrame(const MLString name) = 0;
	virtual MLString getKeyFrame() = 0;
	virtual MLArray<CAComposerKeyFrameCell, kCAMaxFrameCells> & getFrames() = 0;
	virtual bool runFrames() = 0;
	virtual bool runFrameAt(MLInteger64 at) = 0;
};

#endif // MLCOMPOSER_H
