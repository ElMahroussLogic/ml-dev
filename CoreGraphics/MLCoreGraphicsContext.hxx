/*
 * Created on Fri May 10 2024
 *
 * Copyright (c) 2024 SystemLabs B.V
 */

#pragma once

#include <Foundation.hxx>
#include <MLFont.hxx>
#include <MLString.hxx>

typedef double CGReal;
typedef size_t CGSizeT;
typedef char   CGCharacter;

/// @brief Core Graphics context.
class MLCoreGraphicsContext : public MLObject
{
public:
	explicit MLCoreGraphicsContext() = default;
	virtual ~MLCoreGraphicsContext() = default;

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
	virtual MLCoreGraphicsContext* Text(const CGCharacter* T) = 0;

	/// @brief Set font.
	/// @param T font name
	/// @param isBold should the font be bold?
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* Font(const CGCharacter* T,
										const bool		   isBold) = 0;
	/// @brief
	/// @param T
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* TextSize(const CGReal T) = 0;

	/// @brief Draw rounded rectangle
	/// @param width Rectangle width.
	/// @param height Rectangle height.
	/// @param radius Rectangle radius.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* Rectangle(CGReal width, CGReal height, CGReal radius) = 0;

	/// @brief Write to file as PNG using T.
	/// @param T file name.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* WriteTo(const CGCharacter* T) = 0;

	/// @brief Set color or current pen.
	/// @param R Red channel.
	/// @param G Green channel.
	/// @param B Blue channel.
	/// @param A Alpha channel.
	/// @return The graphics context.
	virtual MLCoreGraphicsContext* Color(CGReal R, CGReal G, CGReal B, CGReal A) = 0;

	/// @brief Set stroke of pen.
	/// @param strokeStrength Stroke strength
	/// @return
	virtual MLCoreGraphicsContext* Stroke(CGReal strokeStrength) = 0;

	/// @brief Set line cap.
	/// @param type type according to enum *MLCoreGraphicsLineCap*.
	/// @return
	virtual MLCoreGraphicsContext* LineCap(int32_t type) = 0;

	/// @brief Line from **start** to **finish**.
	/// @param start Start position.
	/// @param finish End position.
	/// @return
	virtual MLCoreGraphicsContext* LineTo(CGReal start, CGReal finish) = 0;

	/// @brief draw Gaussian blur.
	/// @param radius the radius of the blur.
	/// @return
	virtual MLCoreGraphicsContext* Blur(CGReal	radius,
												CGSizeT width,
												CGSizeT height) = 0;

	/// @brief Load image (PNG) from disk.
	/// @param Path PNG image.
	/// @return context ptr.
	virtual MLCoreGraphicsContext* Image(const CGCharacter* Path, CGSizeT W, CGSizeT H, CGReal X, CGReal Y) = 0;

	/// @brief Scale context.
	/// @param X
	/// @param Y
	/// @return
	virtual MLCoreGraphicsContext* Scale(CGReal X, CGReal Y) = 0;

	/// @brief To string method.
	/// @return the class as a string
	virtual const MLString toString() override;

	virtual MLCoreGraphicsContext* Start() = 0;
	virtual MLCoreGraphicsContext* End() = 0;

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