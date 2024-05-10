#pragma once

#include <MLCoreGraphicsContext.hxx>
#include <cairo/cairo.h>
#include <math.h>
#include <string.h>

/// @file: MLCoreGraphicsContextCairo.inl
/// @brief: Cairo backend for multiplatform code.

/// @brief Cairo implement of CoreGraphics.
class MLCoreGraphicsContextCairo : public MLCoreGraphicsContext {
public:
  explicit MLCoreGraphicsContextCairo(const CGReal widht, const CGReal height);
  virtual ~MLCoreGraphicsContextCairo();

  /// @brief Grants a new feature to Context.
  /// @param flag the feature flag.
  virtual MLCoreGraphicsContext &operator|=(const CGSizeT flag) {
    mContextFlags |= flag;
    return *this;
  }

  /// @brief Revokes a new feature to Context.
  /// @param flag the feature flag.
  virtual MLCoreGraphicsContext &operator&=(const CGSizeT flag) {
    mContextFlags &= flag;
    return *this;
  }

  /// @brief Check for a feature.
  /// @param flag The feature in question.
  /// @retval true feature exists.
  /// @retval false not supported by this context.
  virtual bool operator&(const CGSizeT flag) { return mContextFlags & flag; }

  virtual MLCoreGraphicsContext &Move(CGReal X, CGReal Y) {
    cairo_move_to(mCairo, X, Y);
    return *this;
  }

  virtual MLCoreGraphicsContext &Text(const CGCharacter *T) {
    cairo_show_text(mCairo, T);
    return *this;
  }

  virtual MLCoreGraphicsContext &Font(const CGCharacter *T,
                                            const bool isBold) {
    cairo_select_font_face(mCairo, T, CAIRO_FONT_SLANT_NORMAL,
                           isBold ? CAIRO_FONT_WEIGHT_BOLD
                                  : CAIRO_FONT_WEIGHT_NORMAL);
    return *this;
  }

  virtual MLCoreGraphicsContext &TextSize(const CGReal T) {
    cairo_set_font_size(mCairo, T);
    return *this;
  }

  virtual MLCoreGraphicsContext &FlushAs(const CGCharacter *T) {
    memcpy(mOutputPath, T, strlen(T));
    return *this;
  }

  virtual MLCoreGraphicsContext &Color(CGReal R, CGReal G, CGReal B, CGReal A) {
    cairo_set_source_rgba(mCairo, R, G, B, A);
    return *this;
  }

  virtual MLCoreGraphicsContext &Stroke(CGReal strokeStrength) {
    cairo_set_line_width(mCairo, strokeStrength);
    cairo_stroke(mCairo);
    return *this;
  }

  virtual MLCoreGraphicsContext &Rect(CGReal width, CGReal height,
                                      CGReal radius) {
    double aspect = 1.0,        /* aspect ratio */
        corner_radius = height / 10.0; /* and corner curvature radius */

    double degrees = M_PI / 180.0;

    cairo_new_sub_path(mCairo);
    cairo_arc(mCairo, width - radius, radius, radius, -90 * degrees,
              0 * degrees);
    cairo_arc(mCairo, width - radius, height - radius, radius,
              0 * degrees, 90 * degrees);
    cairo_arc(mCairo, radius, height - radius, radius, 90 * degrees,
              180 * degrees);
    cairo_arc(mCairo, radius, radius, radius, 180 * degrees,
              270 * degrees);
    cairo_close_path(mCairo);

    cairo_fill_preserve(mCairo);

    return *this;
  }

private:
  CGSizeT mContextFlags{0};
  cairo_surface_t *mSurface{nullptr};
  cairo_t *mCairo{nullptr};
  CGCharacter mOutputPath[255];
};

MLCoreGraphicsContextCairo::MLCoreGraphicsContextCairo(const CGReal width, const CGReal height) {
  mSurface =
      cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
  mCairo = cairo_create(mSurface);

  this->Font("serif", false).TextSize(12.0);
}

MLCoreGraphicsContextCairo::~MLCoreGraphicsContextCairo() {

  cairo_destroy(mCairo);

  if (*mOutputPath)
    cairo_surface_write_to_png(mSurface, mOutputPath);

  cairo_surface_destroy(mSurface);
}
