/*
 * Created on Fri May 10 2024
 * Last Updated: Sun Oct 27 06:55:01 PM CET 2024
 * Copyright (c) 2024 EL Mahrouss Logic
 */

#pragma once

#include <GraphicsKit/Foundation.h>

/// @brief Forward declaration of context class.
class GKContextInterface;
enum class GKLineCap;

/// @brief Line cap enum.
enum class GKLineCap
{
	kLineCapNormal,	 /// no cap.
	kLineCapRounded, /// rounded cap.
	kLineCapSquare	 /// square cap.
};

/// @brief GraphicsKit context class.
class GKContextInterface ML_OBJECT
{
public:
	explicit GKContextInterface() = default;
	virtual ~GKContextInterface() = default;

	/// @brief Copy constructor.
	GKContextInterface& operator=(const GKContextInterface&) = default;
	GKContextInterface(const GKContextInterface&)			   = default;

public:
	/// @brief Grants a new feature to Context.
	/// @param flag the feature flag.
	virtual GKContextInterface* operator|=(const GKSizeType flag) = 0;

	/// @brief Revokes a new feature to Context.
	/// @param flag the feature flag.
	virtual GKContextInterface* operator&=(const GKSizeType flag) = 0;

	/// @brief Check for a feature.
	/// @param flag The feature in question.
	/// @retval true feature exists.
	/// @retval false not supported by this context.
	virtual BOOL operator&(const GKSizeType flag) = 0;

	/// @brief Move to coord.
	/// @param X the x coord.
	/// @param Y the y coord.
	/// @return the context.
	virtual GKContextInterface* move(GKReal X, GKReal Y) = 0;

	/// @brief Write Text to image.
	/// @param T the text itself.
	/// @param X the x coord.
	/// @param Y the y coord.
	/// @param W the width.
	/// @param H the height.
	/// @return the context.
	virtual GKContextInterface* text(const GKCharacter* Text, GKBoolean Center, GKReal X = 0.0, GKReal Y = 0.0, GKReal W = 0.0, GKReal H = 0.0) = 0;

	/// @brief Set font.
	/// @param T font name
	/// @param isBold should the font be bold?
	/// @return The graphics context.
	virtual GKContextInterface* fontFamily(const GKCharacter* Text,
								  const BOOL		 IsBold) = 0;
	/// @brief
	/// @param T
	/// @return The graphics context.
	virtual GKContextInterface* fontSize(const GKReal Text) = 0;

	/// @brief Draw rounded rectangle
	/// @param width Rectangle width.
	/// @param height Rectangle height.
	/// @param radius Rectangle radius.
	/// @return The graphics context.
	virtual GKContextInterface* rectangle(GKReal Width, GKReal Height, GKReal Radius) = 0;

	/// @brief Write to file as SVG using T as the filepath.
	/// @param T file name to write.
	/// @return The graphics context.
	virtual GKContextInterface* svg(const GKCharacter* T) = 0;

	/// @brief Write to file as PDF using T as the filepath.
	/// @param T file name to write.
	/// @return The graphics context.
	virtual GKContextInterface* pdf(const GKCharacter* T) = 0;

	/// @brief Set the page label.
	/// @param T page label name.
	/// @return The graphics context.
	virtual GKContextInterface* pageLabel(const GKCharacter* T) = 0;

	/// @brief Set the thumbnail size.
	/// @param W width.
	/// @param H height.
	/// @return The graphics context.
	virtual GKContextInterface* thumbnailSize(const GKInteger W, const GKInteger H) = 0;

	/// @brief Present the context.
	/// @return The graphics context.
	virtual GKContextInterface* present(GKReal R = 0, GKReal G = 0, GKReal B = 0) = 0;

	/// @brief Set color or current pen.
	/// @param R Red channel.
	/// @param G Green channel.
	/// @param B Blue channel.
	/// @param A Alpha channel.
	/// @return The graphics context.
	virtual GKContextInterface* color(GKReal R = 1, GKReal G = 1, GKReal B = 1, GKReal A = 1) = 0;

	/// @brief Set stroke of pen.
	/// @param strokeStrength Stroke strength
	/// @return The graphics context.
	virtual GKContextInterface* stroke(GKReal strokeStrength) = 0;

	/// @brief Set line cap.
	/// @param Type type according to enum *GKLineCap*.
	/// @return The graphics context.
	virtual GKContextInterface* lineCap(GKLineCap Type) = 0;

	/// @brief Line from **start** to **finish**.
	/// @param Start Start position.
	/// @param Finish End position.
	/// @return The graphics context.
	virtual GKContextInterface* lineTo(GKReal Start, GKReal Finish) = 0;

	/// @brief Draws a gaussian blur.
	/// @param radius blur's radius
	/// @return The graphics context.
	virtual GKContextInterface* blur(GKReal	   radius,
							GKSizeType width,
							GKSizeType height) = 0;

	/// @brief Load image (PNG) from disk.
	/// @param Path The PNG image path to read on.
	/// @param W width.
	/// @param H height.
	/// @return The graphics context.
	virtual GKContextInterface* image(const GKCharacter* Path, GKSizeType W, GKSizeType H, GKReal X, GKReal Y) = 0;

	/// @brief Scale context.
	/// @param width the view's width.
	/// @param height the view's height.
	/// @return
	virtual GKContextInterface* scale(GKReal width, GKReal height) = 0;

	/// @brief To string method.
	/// @return The class data as a string.
	virtual const MLString toString();

public:
	/// @brief Start drawing.
	/// @return
	virtual GKContextInterface* start() = 0;

	/// @brief End drawing, flush.
	/// @return
	virtual GKContextInterface* end() = 0;

	/// @brief Leak or set graphics context.
	/// @param pvtCtx the new internal context.
	/// @internal
	virtual void leak(void*** pvtCtx) = 0;

public:
	/// @brief Overloaded move, for MLPoint.
	/// @param point the point to move to.
	/// @return The context.
	GKContextInterface* move(MLPoint& point)
	{
		this->move(point.x, point.y);
		return this;
	}

	/// @brief Overloaded move, for MLPoint.
	/// @param point the point to move to.
	/// @return The context.
	GKContextInterface* move(const MLPoint& point)
	{
		this->move(point.x, point.y);
		return this;
	}
};

/// @brief Request a context regarding the features set.
/// @param featureSet the feature set.
/// @param strict should we require all the features to be here?
/// @note if no, please check for feature with operator& inside
/// GKContextInterface.
/// @return The new graphics context.
ML_IMPORT GKContextInterface* GKRequestContext(GKSizeType featureSet, BOOL strict, GKReal width, GKReal height);

/// @brief Releases a Core Graphics context.
/// @param context The context itself.
/// @return This function returns void.
ML_IMPORT void GKReleaseContext(GKContextInterface* context);
