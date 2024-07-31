/*
 * Created on Fri May 10 2024
 *
 * Copyright (c) 2024 ZKA Technologies
 */

#pragma once

class MLString;

#include <GraphicsKit/Private/MLCoreGraphicsBase.hxx>

/// @brief Core Graphics context.
class MLCoreGraphicsContext : public MLObject
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
	virtual MLCoreGraphicsContext* Move(CGReal X, CGReal Y) = 0;

	/// @brief Write Text to image.
	/// @param T the text itself.
	/// @return the context.
	virtual MLCoreGraphicsContext* Text(const CGCharacter* T, CGBoolean Center, CGReal X = 0.0, CGReal Y = 0.0, CGReal W = 0.0, CGReal H = 0.0) = 0;

	/// @brief Set font.
	/// @param T font name
	/// @param isBold should the font be bold?
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* FontFamily(const CGCharacter* T,
											  const bool		 isBold) = 0;
	/// @brief
	/// @param T
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* FontSize(const CGReal T) = 0;

	/// @brief Draw rounded rectangle
	/// @param width Rectangle width.
	/// @param height Rectangle height.
	/// @param radius Rectangle radius.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* Rectangle(CGReal width, CGReal height, CGReal radius) = 0;

	/// @brief Write to file as SVG using T as the filepath.
	/// @param T file name to write.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* SVG(const CGCharacter* T) = 0;

	/// @brief Write to file as PDF using T as the filepath.
	/// @param T file name to write.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* PDF(const CGCharacter* T) = 0;

	/// @brief Set the page label.
	/// @param T page label name.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* PageLabel(const CGCharacter* T) = 0;

	/// @brief Set the thumbnail size.
	/// @param W width.
	/// @param H height.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* ThumbnailSize(const int W, const int H) = 0;

	/// @brief Present the context.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* Present() = 0;

	/// @brief Set color or current pen.
	/// @param R Red channel.
	/// @param G Green channel.
	/// @param B Blue channel.
	/// @param A Alpha channel.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* Color(CGReal R, CGReal G, CGReal B, CGReal A) = 0;

	/// @brief Set stroke of pen.
	/// @param strokeStrength Stroke strength
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* Stroke(CGReal strokeStrength) = 0;

	/// @brief Set line cap.
	/// @param type type according to enum *MLCoreGraphicsLineCap*.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* LineCap(int type) = 0;

	/// @brief Line from **start** to **finish**.
	/// @param start Start position.
	/// @param finish End position.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* LineTo(CGReal start, CGReal finish) = 0;

	/// @brief Draws a gaussian blur.
	/// @param radius blur's radius
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* Blur(CGReal	radius,
										CGSizeT width,
										CGSizeT height) = 0;

	/// @brief Load image (PNG) from disk.
	/// @param Path The PNG image path to read on.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* Image(const CGCharacter* Path, CGSizeT W, CGSizeT H, CGReal X, CGReal Y) = 0;

	/// @brief Scale context.
	/// @param width the view's width.
	/// @param height the view's height.
	/// @return
	virtual MLCoreGraphicsContext* Scale(CGReal width, CGReal height) = 0;

	/// @brief To string method.
	/// @return The class data as a string.
	virtual const MLString toString();

public:
	/// @brief Start drawing.
	/// @return
	virtual MLCoreGraphicsContext* Start() = 0;

	/// @brief End drawing, flush.
	/// @return
	virtual MLCoreGraphicsContext* End() = 0;

public:
	/// @brief Overloaded move, for MLCoreGraphicsPoint.
	/// @param point the point to move to.
	/// @return The context.
	MLCoreGraphicsContext* Move(MLCoreGraphicsPoint& point)
	{
		this->Move(point.X, point.Y);
		return this;
	}

	/// @brief Overloaded move, for MLCoreGraphicsPoint.
	/// @param point the point to move to.
	/// @return The context.
	MLCoreGraphicsContext* Move(const MLCoreGraphicsPoint& point)
	{
		this->Move(point.X, point.Y);
		return this;
	}

	/// @brief Set graphics context.
	/// @param pvtCtx
	virtual void SetContext(void* pvtCtx) = 0;

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
