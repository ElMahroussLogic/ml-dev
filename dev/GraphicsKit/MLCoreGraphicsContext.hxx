/*
 * Created on Fri May 10 2024
 *
 * Copyright (c) 2024 ZKA Web Services Co
 */

#pragma once

#include <GraphicsKit/Private/MLCoreGraphicsBase.hxx>

/// @brief Core Graphics context.
class MLCoreGraphicsContext ML_OBJECT
{
public:
	explicit MLCoreGraphicsContext() = default;
	virtual ~MLCoreGraphicsContext() = default;

	/// @brief Copy constructor.
	MLCoreGraphicsContext& operator=(const MLCoreGraphicsContext&) = default;
	MLCoreGraphicsContext(const MLCoreGraphicsContext&)			   = default;

public:
	/// @brief Grants a new feature to Context.
	/// @param flag the feature flag.
	virtual MLCoreGraphicsContext* operator|=(const CGSizeT flag) = 0;

	/// @brief Revokes a new feature to Context.
	/// @param flag the feature flag.
	virtual MLCoreGraphicsContext* operator&=(const CGSizeT flag) = 0;

	/// @brief Check for a feature.
	/// @param flag The feature in question.
	/// @retval true feature exists.
	/// @retval false not supported by this context.
	virtual bool operator&(const CGSizeT flag) = 0;

	/// @brief Move to coord.
	/// @param T the text itself.
	/// @return the context.
	virtual MLCoreGraphicsContext* move(CGReal X, CGReal Y) = 0;

	/// @brief Write Text to image.
	/// @param T the text itself.
	/// @return the context.
	virtual MLCoreGraphicsContext* text(const CGCharacter* T, CGBoolean Center, CGReal X = 0.0, CGReal Y = 0.0, CGReal W = 0.0, CGReal H = 0.0) = 0;

	/// @brief Set font.
	/// @param T font name
	/// @param isBold should the font be bold?
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* fontFamily(const CGCharacter* T,
											  const bool		 isBold) = 0;
	/// @brief
	/// @param T
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* fontSize(const CGReal T) = 0;

	/// @brief Draw rounded rectangle
	/// @param width Rectangle width.
	/// @param height Rectangle height.
	/// @param radius Rectangle radius.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* rectangle(CGReal width, CGReal height, CGReal radius) = 0;

	/// @brief Write to file as SVG using T as the filepath.
	/// @param T file name to write.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* svg(const CGCharacter* T) = 0;

	/// @brief Write to file as PDF using T as the filepath.
	/// @param T file name to write.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* pdf(const CGCharacter* T) = 0;

	/// @brief Set the page label.
	/// @param T page label name.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* pageLabel(const CGCharacter* T) = 0;

	/// @brief Set the thumbnail size.
	/// @param W width.
	/// @param H height.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* thumbnailSize(const int W, const int H) = 0;

	/// @brief Present the context.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* present(CGReal r = 0, CGReal g = 0, CGReal b = 0) = 0;

	/// @brief Set color or current pen.
	/// @param R Red channel.
	/// @param G Green channel.
	/// @param B Blue channel.
	/// @param A Alpha channel.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* color(CGReal R, CGReal G, CGReal B, CGReal A) = 0;

	/// @brief Set stroke of pen.
	/// @param strokeStrength Stroke strength
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* stroke(CGReal strokeStrength) = 0;

	/// @brief Set line cap.
	/// @param type type according to enum *MLCoreGraphicsLineCap*.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* lineCap(int type) = 0;

	/// @brief Line from **start** to **finish**.
	/// @param start Start position.
	/// @param finish End position.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* lineTo(CGReal start, CGReal finish) = 0;

	/// @brief Draws a gaussian blur.
	/// @param radius blur's radius
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* blur(CGReal	radius,
										CGSizeT width,
										CGSizeT height) = 0;

	/// @brief Load image (PNG) from disk.
	/// @param Path The PNG image path to read on.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* image(const CGCharacter* Path, CGSizeT W, CGSizeT H, CGReal X, CGReal Y) = 0;

	/// @brief Scale context.
	/// @param width the view's width.
	/// @param height the view's height.
	/// @return
	virtual MLCoreGraphicsContext* scale(CGReal width, CGReal height) = 0;

	/// @brief To string method.
	/// @return The class data as a string.
	virtual const MLString toString();

public:
	/// @brief Start drawing.
	/// @return
	virtual MLCoreGraphicsContext* start() = 0;

	/// @brief End drawing, flush.
	/// @return
	virtual MLCoreGraphicsContext* end() = 0;

	/// @brief Leak or set graphics context.
	/// @param pvtCtx the new internal context.
	/// @internal
	virtual void leak(void*** pvtCtx) = 0;

public:
	/// @brief Overloaded move, for MLCoreGraphicsPoint.
	/// @param point the point to move to.
	/// @return The context.
	MLCoreGraphicsContext* move(MLCoreGraphicsPoint& point)
	{
		this->move(point.X, point.Y);
		return this;
	}

	/// @brief Overloaded move, for MLCoreGraphicsPoint.
	/// @param point the point to move to.
	/// @return The context.
	MLCoreGraphicsContext* move(const MLCoreGraphicsPoint& point)
	{
		this->move(point.X, point.Y);
		return this;
	}

private:
	friend class MLCoreGraphicsPen;
	friend class MLCoreGraphicsShape;
	friend class MLCoreGraphicsShader;
};

/// @brief Request a context regarding the features set.
/// @param featureSet the feature set.
/// @param strict should we require all the features to be here?
/// @note if no, please check for feature with operator& inside
/// MLCoreGraphicsContext.
/// @return The new graphics context.
ML_IMPORT MLCoreGraphicsContext*
		  CGRequestContext(CGSizeT featureSet, bool strict, CGReal width, CGReal height);

/// @brief Releases a Core Graphics context.
/// @param context The context itself.
/// @return This function returns void.
ML_IMPORT void CGReleaseContext(MLCoreGraphicsContext* context);

/// @brief Line cap enum.
enum MLCoreGraphicsLineCap
{
	MLCoreGraphicsLineCapNormal,  /// no cap.
	MLCoreGraphicsLineCapRounded, /// rounded cap.
	MLCoreGraphicsLineCapSquare	  /// square cap.
};
