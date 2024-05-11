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
  virtual MLCoreGraphicsContext *operator|=(const CGSizeT flag) {
    mContextFlags |= flag;
    return this;
  }

  /// @brief Revokes a new feature to Context.
  /// @param flag the feature flag.
  virtual MLCoreGraphicsContext *operator&=(const CGSizeT flag) {
    mContextFlags &= flag;
    return this;
  }

  /// @brief Check for a feature.
  /// @param flag The feature in question.
  /// @retval true feature exists.
  /// @retval false not supported by this context.
  virtual bool operator&(const CGSizeT flag) { return mContextFlags & flag; }

  ///////////////////////////////////////////////////////////////////////////

  virtual MLCoreGraphicsContext *Move(CGReal X, CGReal Y) {
    cairo_move_to(mCairo, X, Y);
    return this;
  }

  ///////////////////////////////////////////////////////////////////////////

  virtual MLCoreGraphicsContext *Text(const CGCharacter *T) {
    cairo_show_text(mCairo, T);
    return this;
  }

  ///////////////////////////////////////////////////////////////////////////

  virtual MLCoreGraphicsContext *Font(const CGCharacter *T, const bool isBold) {
    cairo_select_font_face(mCairo, T, CAIRO_FONT_SLANT_NORMAL,
                           isBold ? CAIRO_FONT_WEIGHT_BOLD
                                  : CAIRO_FONT_WEIGHT_NORMAL);
    return this;
  }

  ///////////////////////////////////////////////////////////////////////////

  virtual MLCoreGraphicsContext *TextSize(const CGReal T) {
    cairo_set_font_size(mCairo, T);
    return this;
  }

  ///////////////////////////////////////////////////////////////////////////

  virtual MLCoreGraphicsContext *FlushAs(const CGCharacter *T) {
    memcpy(mOutputPath, T, strlen(T));
    return this;
  }

  ///////////////////////////////////////////////////////////////////////////

  virtual MLCoreGraphicsContext *Color(CGReal R, CGReal G, CGReal B, CGReal A) {
    cairo_set_source_rgba(mCairo, R, G, B, A);
    return this;
  }

  ///////////////////////////////////////////////////////////////////////////

  virtual MLCoreGraphicsContext *Stroke(CGReal strokeStrength) {
    cairo_set_line_width(mCairo, strokeStrength);
    cairo_stroke(mCairo);
    return this;
  }

  ///////////////////////////////////////////////////////////////////////////

  virtual MLCoreGraphicsContext *Rectangle(CGReal width, CGReal height,
                                           CGReal radius) {
    double aspect = 1.0,               /* aspect ratio */
        corner_radius = height / 10.0; /* and corner curvature radius */

    double degrees = M_PI / 180.0;

    cairo_new_sub_path(mCairo);
    cairo_arc(mCairo, width - radius, radius, radius, -90 * degrees,
              0 * degrees);
    cairo_arc(mCairo, width - radius, height - radius, radius, 0 * degrees,
              90 * degrees);
    cairo_arc(mCairo, radius, height - radius, radius, 90 * degrees,
              180 * degrees);
    cairo_arc(mCairo, radius, radius, radius, 180 * degrees, 270 * degrees);
    cairo_close_path(mCairo);

    cairo_fill_preserve(mCairo);

    return this;
  }

  ///////////////////////////////////////////////////////////////////////////

  virtual MLCoreGraphicsContext *LineTo(CGReal start, CGReal finish) {
    cairo_line_to(mCairo, start, finish);
    return this;
  }

  ///////////////////////////////////////////////////////////////////////////

  virtual MLCoreGraphicsContext *LineCap(int32_t type) {
    switch (type) {
    case 0:
    default:
      cairo_set_line_cap(mCairo, CAIRO_LINE_CAP_BUTT);
      break;
    case 1:
      cairo_set_line_cap(mCairo, CAIRO_LINE_CAP_ROUND);
    case 2:
      cairo_set_line_cap(mCairo, CAIRO_LINE_CAP_SQUARE);
      break;
    }

    return this;
  }

  /// @brief Draws a gaussian blur, (taken from Cairo cookbook.)
  /// @param radius 
  /// @return 
  virtual MLCoreGraphicsContext *Blur(CGReal radius) {
    cairo_surface_t *tmp;
    int width, height;
    int src_stride, dst_stride;
    int x, y, z, w;
    uint8_t *src, *dst;
    uint32_t *s, *d, a, p;
    int i, j, k;
    uint8_t kernel[17];
    const int size = ML_ARRAY_LENGTH(kernel);
    const int half = size / 2;

    if (cairo_surface_status(mSurface))
      return this;

    width = cairo_image_surface_get_width(mSurface);
    height = cairo_image_surface_get_height(mSurface);

    switch (cairo_image_surface_get_format(mSurface)) {
    case CAIRO_FORMAT_A1:
    default:
      /* Don't even think about it! */
      return this;

    case CAIRO_FORMAT_A8:
      /* Handle a8 surfaces by effectively unrolling the loops by a
       * factor of 4 - this is safe since we know that stride has to be a
       * multiple of uint32_t. */
      width /= 4;
      break;

    case CAIRO_FORMAT_RGB24:
    case CAIRO_FORMAT_ARGB32:
      break;
    }

    tmp = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);

    if (cairo_surface_status(tmp))
      return this;

    src = cairo_image_surface_get_data(mSurface);
    src_stride = cairo_image_surface_get_stride(mSurface);

    dst = cairo_image_surface_get_data(tmp);
    dst_stride = cairo_image_surface_get_stride(tmp);

    a = 0;
    for (i = 0; i < size; i++) {
      double f = i - half;
      a += kernel[i] = exp(-f * f / 30.0) * 80;
    }

    /* Horizontally blur from mSurface -> tmp */
    for (i = 0; i < height; i++) {
      s = (uint32_t *)(src + i * src_stride);
      d = (uint32_t *)(dst + i * dst_stride);
      for (j = 0; j < width; j++) {
        if (radius < j && j < width - radius) {
          d[j] = s[j];
          continue;
        }

        x = y = z = w = 0;
        for (k = 0; k < size; k++) {
          if (j - half + k < 0 || j - half + k >= width)
            continue;

          p = s[j - half + k];

          x += ((p >> 24) & 0xff) * kernel[k];
          y += ((p >> 16) & 0xff) * kernel[k];
          z += ((p >> 8) & 0xff) * kernel[k];
          w += ((p >> 0) & 0xff) * kernel[k];
        }
        d[j] = (x / a << 24) | (y / a << 16) | (z / a << 8) | w / a;
      }
    }

    /* Then vertically blur from tmp -> mSurface */
    for (i = 0; i < height; i++) {
      s = (uint32_t *)(dst + i * dst_stride);
      d = (uint32_t *)(src + i * src_stride);
      for (j = 0; j < width; j++) {
        if (radius <= i && i < height - radius) {
          d[j] = s[j];
          continue;
        }

        x = y = z = w = 0;
        for (k = 0; k < size; k++) {
          if (i - half + k < 0 || i - half + k >= height)
            continue;

          s = (uint32_t *)(dst + (i - half + k) * dst_stride);
          p = s[j];

          x += ((p >> 24) & 0xff) * kernel[k];
          y += ((p >> 16) & 0xff) * kernel[k];
          z += ((p >> 8) & 0xff) * kernel[k];
          w += ((p >> 0) & 0xff) * kernel[k];
        }
        d[j] = (x / a << 24) | (y / a << 16) | (z / a << 8) | w / a;
      }
    }

    cairo_surface_destroy(tmp);
    cairo_surface_mark_dirty(mSurface);

    return this;
  }

private:
  CGSizeT mContextFlags{0};
  cairo_surface_t *mSurface{nullptr};
  cairo_t *mCairo{nullptr};
  CGReal mWidth{0};
  CGReal mHeight{0};
  CGCharacter mOutputPath[255];
};

MLCoreGraphicsContextCairo::MLCoreGraphicsContextCairo(const CGReal width,
                                                       const CGReal height)
    : mWidth(width), mHeight(height) {
  ML_MUST_PASS(width && height);

  mSurface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
  mCairo = cairo_create(mSurface);

  this->Font("serif", false)->TextSize(12.0);
}

MLCoreGraphicsContextCairo::~MLCoreGraphicsContextCairo() {

  cairo_destroy(mCairo);

  if (*mOutputPath)
    cairo_surface_write_to_png(mSurface, mOutputPath);

  cairo_surface_destroy(mSurface);
}
