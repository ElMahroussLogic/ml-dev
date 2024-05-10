/*
 * Created on Fri May 10 2024
 *
 * Copyright (c) 2024 SystemLabs B.V
 */

#pragma once

#include <Foundation.hxx>
#include <MLFont.hxx>

typedef double CGReal;
typedef size_t CGSizeT;
typedef char CGCharacter;

/// @brief Core Graphics context.
class MLCoreGraphicsContext {
public:
  explicit MLCoreGraphicsContext() = default;
  virtual ~MLCoreGraphicsContext() = default;

  MLCoreGraphicsContext &operator=(const MLCoreGraphicsContext &) = default;
  MLCoreGraphicsContext(const MLCoreGraphicsContext &) = default;

public:
  /// @brief Grants a new feature to Context.
  /// @param flag the feature flag.
  virtual MLCoreGraphicsContext &operator|=(const CGSizeT flag) = 0;

  /// @brief Revokes a new feature to Context.
  /// @param flag the feature flag.
  virtual MLCoreGraphicsContext &operator&=(const CGSizeT flag) = 0;

  /// @brief Check for a feature.
  /// @param flag The feature in question.
  /// @retval true feature exists.
  /// @retval false not supported by this context.
  virtual bool operator&(const CGSizeT flag) = 0;

  /// @brief Move to coord.
  /// @param T the text itself.
  /// @return the context.
  virtual MLCoreGraphicsContext &Move(CGReal X, CGReal Y) = 0;

  /// @brief Write Text to image.
  /// @param T the text itself.
  /// @return the context.
  virtual MLCoreGraphicsContext &Text(const CGCharacter *T) = 0;

  /// @brief
  /// @param T
  /// @return
  virtual MLCoreGraphicsContext &Font(const CGCharacter *T,
                                            const bool isBold) = 0;
  /// @brief
  /// @param T
  /// @return
  virtual MLCoreGraphicsContext &TextSize(const CGReal T) = 0;

  /// @brief
  /// @param width
  /// @param height
  /// @param radius
  /// @return
  virtual MLCoreGraphicsContext &Rect(CGReal width, CGReal height,
                                      CGReal radius) = 0;

  /// @brief Write to file as PNG using T.
  /// @param T
  /// @return
  virtual MLCoreGraphicsContext &FlushAs(const CGCharacter *T) = 0;

  virtual MLCoreGraphicsContext &Color(CGReal R, CGReal G, CGReal B, CGReal A) = 0;

  virtual MLCoreGraphicsContext &Stroke(CGReal strokeStrength) = 0;
};

/// @brief Request a context regarding the features set.
/// @param featureSet the feature set.
/// @param strict should we require all the features to be here?
/// @note if no, please check for feature with operator& inside
/// MLCoreGraphicsContext.
/// @return The new graphics context.
ML_IMPORT MLCoreGraphicsContext* CGRequestContext(CGSizeT featureSet, bool strict,
                                                  CGReal width, CGReal height);

/// @brief Releases a Core Graphics context.
/// @param context The context itself.
/// @return This function returns void.
ML_IMPORT void CGReleaseContext(MLCoreGraphicsContext *context);