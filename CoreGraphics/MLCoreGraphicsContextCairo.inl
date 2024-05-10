#pragma once

#include <MLCoreGraphicsContext.hxx>
#include <cairo/cairo.h>
#include <string.h>

/// @brief Cairo implement of CoreGraphics.
class MLCoreGraphicsContextCairo : public MLCoreGraphicsContext {
public:
  explicit MLCoreGraphicsContextCairo();
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

  virtual MLCoreGraphicsContext &FontFace(const CGCharacter *T) {
    cairo_select_font_face(mCairo, T, CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_NORMAL);
    return *this;
  }

  virtual MLCoreGraphicsContext &FontSize(const CGReal T) {
    cairo_set_font_size(mCairo, T);
    return *this;
  }

  virtual MLCoreGraphicsContext &WriteAs(const CGCharacter *T) {
    memcpy(mOutputPath, T, strlen(T));
    return *this;
  }

private:
  CGSizeT mContextFlags{0};
  cairo_surface_t *mSurface{nullptr};
  cairo_t *mCairo{nullptr};
  CGCharacter mOutputPath[255];
};

constexpr auto cMLWidth = 800;
constexpr auto cMLHeight = 600;

MLCoreGraphicsContextCairo::MLCoreGraphicsContextCairo() {
  mSurface =
      cairo_image_surface_create(CAIRO_FORMAT_ARGB32, cMLWidth, cMLHeight);
  mCairo = cairo_create(mSurface);

  this->FontFace("serif").FontSize(12.0);
}

MLCoreGraphicsContextCairo::~MLCoreGraphicsContextCairo() {

  cairo_destroy(mCairo);
  if (*mOutputPath)
    cairo_surface_write_to_png(mSurface, mOutputPath);
  cairo_surface_destroy(mSurface);
}
