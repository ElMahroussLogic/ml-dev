/*
 * ========================================================
 *
 * GraphicsKit
 * Copyright ZKA Technologies, all rights reserved.
 *
 *  ========================================================
 */

#pragma once

#include <GraphicsKit/MLCoreGraphicsContext.hxx>

extern "C"
{

#include <math.h>
#include <string.h>
}

#include <string>
#include <filesystem>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // !M_PI

#include <cairo/cairo.h>
#include <cairo/cairo-svg.h>
#include <cairo/cairo-pdf.h>

/// @file: MLCoreGraphicsContextCairo.inl
/// @brief: Cairo backend for multiplatform code.

/// @brief Cairo implement of GraphicsKit.
class MLCoreGraphicsContextCairo : public MLCoreGraphicsContext
{
public:
	explicit MLCoreGraphicsContextCairo(const CGReal width, const CGReal height);
	~MLCoreGraphicsContextCairo();

public:
	/// @brief Grants a new feature to Context.
	/// @param flag the feature flag.
	MLCoreGraphicsContext* operator|=(const CGSizeT flag) override
	{
		mContextFlags |= flag;
		return this;
	}

	/// @brief Revokes a new feature to Context.
	/// @param flag the feature flag.
	MLCoreGraphicsContext* operator&=(const CGSizeT flag) override
	{
		mContextFlags &= flag;
		return this;
	}

	/// @brief Check for a feature.
	/// @param flag The feature in question.
	/// @retval true feature exists.
	/// @retval false not supported by this context.
	bool operator&(const CGSizeT flag) override
	{
		return mContextFlags & flag;
	}

	/// @brief To string method.
	/// @return the class as a string
	const MLString toString() override
	{
		std::string bufferUrl = "{ ";

		bufferUrl += "URL: ";
		bufferUrl += "file://";
		bufferUrl += this->mOutputPath;
		bufferUrl += " }";

		static MLString strUrlFile = MLString(bufferUrl.size());

		if (strUrlFile.size() != bufferUrl.size())
		{
			strUrlFile.dispose();
			strUrlFile = MLString(bufferUrl.size());
		}

		strUrlFile += bufferUrl.c_str();

		return strUrlFile;
	}

	///////////////////////////////////////////////////////////////////////////

	MLCoreGraphicsContext* move(CGReal X, CGReal Y) override
	{
		cairo_move_to(mCairo, X, Y);

		mX = X;
		mY = Y;

		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	MLCoreGraphicsContext* text(const CGCharacter* T, CGBoolean Center, CGReal X, CGReal Y, CGReal W, CGReal H) override
	{
		if (Center)
		{
			cairo_text_extents_t extents;
			cairo_font_extents_t font_extents;

			cairo_text_extents(mCairo, T, &extents);
			cairo_font_extents(mCairo, &font_extents);

			// Calculate the position to center the text
			double x_center = X + (W - extents.width) / 2 - extents.x_bearing;
			double y_center = Y + (H - font_extents.height) / 2 + font_extents.ascent;

			// Move to the calculated position and show the text
			cairo_move_to(mCairo, x_center, y_center);
		}

		cairo_show_text(mCairo, T);

		if (Center)
		{
			cairo_move_to(mCairo, mX, mY);
		}

		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	MLCoreGraphicsContext* fontFamily(const CGCharacter* T, const bool isBold) override
	{
		cairo_select_font_face(mCairo, T, CAIRO_FONT_SLANT_NORMAL,
							   isBold ? CAIRO_FONT_WEIGHT_BOLD
									  : CAIRO_FONT_WEIGHT_NORMAL);
		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	MLCoreGraphicsContext* fontSize(const CGReal T) override
	{
		cairo_set_font_size(mCairo, T);
		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	MLCoreGraphicsContext* pdf(const CGCharacter* T) override
	{
		if (mSurface)
			return this;

		std::basic_string<CGCharacter> strPath = T;

		constexpr auto dirSeparator = "/";

		if (strPath.find(kRsrcProtocol) != std::string::npos)
		{
			strPath.replace(strPath.find(kRsrcProtocol), strlen(kRsrcProtocol),
							std::filesystem::current_path().string() + dirSeparator);
		}

		memcpy(mOutputPath, strPath.c_str(), strPath.size());
		mSurface = cairo_pdf_surface_create(mOutputPath, mWidth, mHeight);

		return this;
	}

	MLCoreGraphicsContext* svg(const CGCharacter* T) override
	{
		if (mSurface)
			return this;

		std::basic_string<CGCharacter> strPath = T;

		constexpr auto dirSeparator = "/";

		if (strPath.find(kRsrcProtocol) != std::string::npos)
		{
			strPath.replace(strPath.find(kRsrcProtocol), strlen(kRsrcProtocol),
							std::filesystem::current_path().string() + dirSeparator);
		}

		memcpy(mOutputPath, strPath.c_str(), strPath.size());
		mSurface = cairo_svg_surface_create(mOutputPath, mWidth, mHeight);

		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	MLCoreGraphicsContext* color(CGReal R, CGReal G, CGReal B, CGReal A) override
	{
		cairo_set_source_rgba(mCairo, R, G, B, A);
		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	MLCoreGraphicsContext* stroke(CGReal strokeStrength) override
	{
		cairo_set_line_width(mCairo, strokeStrength);
		cairo_stroke(mCairo);
		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	MLCoreGraphicsContext* rectangle(CGReal width, CGReal height, CGReal radius) override
	{
		if (radius == 0.0)
		{
			cairo_rectangle(mCairo, mX, mY, width, height);
			cairo_paint(mCairo);

			return this;
		}

		double aspect	  = 1.0,		   /* aspect ratio */
			corner_radius = height / 10.0; /* and corner curvature radius */

		double degrees = M_PI / 180.0;

		cairo_new_sub_path(mCairo);

		CGReal x = mX;
		CGReal y = mY;

		cairo_arc(mCairo, x + width - radius, y + radius, radius, -90 * degrees,
				  0 * degrees);
		cairo_arc(mCairo, x + width - radius, y + height - radius, radius, 0 * degrees,
				  90 * degrees);
		cairo_arc(mCairo, x + radius, y + height - radius, radius, 90 * degrees,
				  180 * degrees);
		cairo_arc(mCairo, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);

		cairo_close_path(mCairo);

		cairo_fill_preserve(mCairo);

		cairo_paint(mCairo);

		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	MLCoreGraphicsContext* lineTo(CGReal start, CGReal finish) override
	{
		cairo_line_to(mCairo, start, finish);

		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	MLCoreGraphicsContext* lineCap(int32_t type) override
	{
		switch (type)
		{
		case MLCoreGraphicsLineCap::MLCoreGraphicsLineCapNormal:
		default:
			cairo_set_line_cap(mCairo, CAIRO_LINE_CAP_BUTT);
			break;
		case MLCoreGraphicsLineCap::MLCoreGraphicsLineCapRounded:
			cairo_set_line_cap(mCairo, CAIRO_LINE_CAP_ROUND);
		case MLCoreGraphicsLineCap::MLCoreGraphicsLineCapSquare:
			cairo_set_line_cap(mCairo, CAIRO_LINE_CAP_SQUARE);
			break;
		}

		return this;
	}

	/// @brief Draws a gaussian blur. (taken from Cairo cookbook.)
	/// @param radius blur's radius
	/// @return the context.
	/// @note the blur doesn't work on PDF backends.
	MLCoreGraphicsContext* blur(CGReal	radius,
								CGSizeT width,
								CGSizeT height) override
	{
		cairo_surface_t* tmp;
		int				 src_stride, dst_stride;
		long long		 x, y, z, w;
		uint8_t *		 src, *dst;
		uint32_t *		 s, *d, a, p;
		int				 i, j, k;
		uint8_t			 kernel[256];
		const int		 size = ML_ARRAY_LENGTH(kernel);
		const int		 half = size / 2;

		if (!mSurface)
			mSurface = cairo_get_target(mCairo);

		if (cairo_surface_status(mSurface))
			return this;

		switch (cairo_image_surface_get_format(mSurface))
		{
		case CAIRO_FORMAT_A1:
		default:
			/* Don't even think about it! */
			return this;

		case CAIRO_FORMAT_A8:
			/* Handle a8 surfaces by effectively unrolling the loops by a
			 * factor of 4 - this is safe since we know that stride has to be a
			 * multiple of uint32_t. */
			{
				width /= 4;
				break;
			}

		case CAIRO_FORMAT_RGB24:
		case CAIRO_FORMAT_ARGB32: {
			break;
		}
		}

		tmp = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, mWidth,
										 mHeight);

		if (cairo_surface_status(tmp))
			return this;

		src		   = cairo_image_surface_get_data(mSurface);
		src_stride = cairo_image_surface_get_stride(mSurface);

		dst		   = cairo_image_surface_get_data(tmp);
		dst_stride = cairo_image_surface_get_stride(tmp);

		a = 0;
		for (i = 0; i < size; i++)
		{
			double f	   = i - half;
			a += kernel[i] = exp(-f * f / 30.0) * 80;
		}

		auto heightTmp = height;
		auto widthTmp  = width;

		/// Apply some translations according to a magic number '64'.

		constexpr auto cMagicNumber = 2; // ...?

		if (width > mX)
			width = widthTmp + (((widthTmp % cMagicNumber)) + mX);

		if (height > mY)
			height = heightTmp + (((heightTmp % cMagicNumber)) + mY);

		/* Horizontally blur from mSurface -> tmp */
		for (i = mY; i < (height); i++)
		{
			s = (uint32_t*)(src + i * src_stride);
			d = (uint32_t*)(dst + i * dst_stride);
			for (j = mX; j < (width); j++)
			{
				if (radius < j && j < width - radius)
				{
					d[j] = s[j];
					continue;
				}

				x = y = z = w = 0;

				for (k = 0; k < size; k++)
				{
					if (j - half + k < 0 || j - half + k >= width)
						continue;

					p = s[j - half + k];

					x += ((p >> 24) & 0xff) * kernel[k];
					y += ((p >> 16) & 0xff) * kernel[k];
					z += ((p >> 8) & 0xff) * kernel[k];
					w += ((p >> 0) & 0xff) * kernel[k];
				}

				auto rgb = (x / a << 24) | (y / a << 16) | (z / a << 8) | w / a;
				d[j]	 = rgb;
			}
		}

		/* Then vertically blur from tmp -> mSurface */
		for (i = mY; i < (height); i++)
		{
			s = (uint32_t*)(dst + i * dst_stride);
			d = (uint32_t*)(src + i * src_stride);

			for (j = mX; j < (width); j++)
			{
				if (radius <= i && i < height - radius)
				{
					d[j] = s[j];
					continue;
				}

				x = y = z = w = 0;

				for (k = 0; k < size; k++)
				{
					if (i - half + k < 0 || i - half + k >= height)
						continue;

					s = (uint32_t*)(dst + (i - half + k) * dst_stride);
					p = s[j];

					x += ((p >> 24) & 0xff) * kernel[k];
					y += ((p >> 16) & 0xff) * kernel[k];
					z += ((p >> 8) & 0xff) * kernel[k];
					w += ((p >> 0) & 0xff) * kernel[k];
				}

				auto rgb = (x / a << 24) | (y / a << 16) | (z / a << 8) | w / a;
				d[j]	 = rgb;
			}
		}

		cairo_surface_destroy(tmp);

		cairo_surface_mark_dirty(mSurface);

		return this;
	}

	/// @note This only supports the PNG format.
	MLCoreGraphicsContext* image(const CGCharacter* Path,
								 CGSizeT			W,
								 CGSizeT			H,
								 CGReal				X,
								 CGReal				Y) override
	{
		static std::basic_string<CGCharacter> cPath;
		static std::basic_string<CGCharacter> cPathReal;

		if (cPath != Path)
		{
			cPath = Path;

			std::basic_string<CGCharacter> strPath = Path;

			constexpr auto cDirSeparator = "/";

			if (strPath.find(kRsrcProtocol) != std::string::npos)
			{
				strPath.replace(strPath.find(kRsrcProtocol), strlen(kRsrcProtocol),
								std::filesystem::current_path().string() + cDirSeparator);
			}

			cPathReal = strPath;

			auto image = cairo_image_surface_create_from_png(strPath.c_str());
			cairo_set_source_surface(mCairo, image, X, Y);

			cairo_paint(mCairo);
		}
		else
		{
			auto image = cairo_image_surface_create_from_png(cPathReal.c_str());
			cairo_set_source_surface(mCairo, image, X, Y);

			cairo_paint(mCairo);
		}

		return this;
	}

	MLCoreGraphicsContext* scale(CGReal X, CGReal Y) override
	{
		cairo_scale(mCairo, X, Y);
		return this;
	}

	/// @note placeholder for now.
	MLCoreGraphicsContext* start() override
	{
		if (mCairo)
			return this;

		mCairo = cairo_create(mSurface);

		return this;
	}

	/// @brief Present PDF rendering of one page.
	/// @return
	MLCoreGraphicsContext* present(CGReal r, CGReal g, CGReal b) override
	{
		cairo_set_source_rgb(mCairo, r, g, b);
		cairo_paint(mCairo);

		return this;
	}

	/// @note Placeholder for now.
	/// @brief End draw command.
	MLCoreGraphicsContext* end() override
	{
		if (!mSurface || !mCairo)
			return this;

		if (!mCustomSurface && mSurface)
		{
			cairo_surface_destroy(mSurface);
			mSurface = nullptr;
		}

		if (!mCustomCairo && mCairo)
		{
			cairo_destroy(mCairo);
			mCairo = nullptr;
		}

		return this;
	}

	/// @brief Leak or set private internal context
	/// @param PvtCtx The cairo context.
	void leak(void*** pvtCtx) override
	{
		*pvtCtx = (void**)&mCairo;
	}

	/// @brief
	/// @param T
	/// @return
	MLCoreGraphicsContext* pageLabel(const CGCharacter* T) override
	{
		cairo_pdf_surface_set_page_label(mSurface, T);
		return this;
	}

	/// @brief
	/// @param T
	/// @return
	MLCoreGraphicsContext* thumbnailSize(const int Width, const int Height) override
	{
		cairo_pdf_surface_set_thumbnail_size(mSurface, Width, Height);
		return this;
	}

private:
	typedef cairo_surface_t* CGSurfacePtr;
	typedef cairo_t*		 CGPtr;

	CGSizeT		 mContextFlags{0};
	CGSurfacePtr mSurface{nullptr};
	CGPtr		 mCairo{nullptr};
	CGReal		 mWidth{0};
	CGReal		 mHeight{0};
	CGCharacter	 mOutputPath[255] = {0};
	CGBoolean	 mCustomCairo{false};
	CGBoolean	 mCustomSurface{false};
	CGReal		 mX{0};
	CGReal		 mY{0};
};

////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Cairo context constructor.
/// @param width the width.
/// @param height the height.
MLCoreGraphicsContextCairo::MLCoreGraphicsContextCairo(const CGReal width,
													   const CGReal height)
	: mWidth(width), mHeight(height)
{
	ML_MUST_PASS(width > 0 && height > 0);
}

/// @brief C++ destrcutor, the End() method is called as well.
MLCoreGraphicsContextCairo::~MLCoreGraphicsContextCairo()
{
	this->end();
}

/// TODO: Cairo as GX.framework
