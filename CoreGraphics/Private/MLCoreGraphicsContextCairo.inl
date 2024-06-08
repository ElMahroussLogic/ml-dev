/*
 * Created on Fri May 10 2024
 *
 * Copyright (c) 2024 SoftwareLabs B.V
 */

#pragma once

#include <MLCoreGraphicsContext.hxx>

#include <cairo/cairo.h>
#include <cairo/cairo-pdf.h>

#ifndef CAIRO_HAS_PDF_SURFACE
#error CairoGX needs to have a PDF backend!
#endif // !CAIRO_HAS_PDF_SURFACE

#include <math.h>
#include <string.h>
#include <string>
#include <filesystem>

#ifdef __MAHROUSS__
#include <cgx.h>
#endif

/// @file: MLCoreGraphicsContextCairo.inl
/// @brief: Cairo backend for multiplatform code.

/// @brief Cairo implement of CoreGraphics.
class MLCoreGraphicsContextCairo : public MLCoreGraphicsContext
{
public:
	explicit MLCoreGraphicsContextCairo(const CGReal widht, const CGReal height);
	virtual ~MLCoreGraphicsContextCairo();

	/// @brief Grants a new feature to Context.
	/// @param flag the feature flag.
	virtual MLCoreGraphicsContext* operator|=(const CGSizeT flag) override
	{
		mContextFlags |= flag;
		return this;
	}

	/// @brief Revokes a new feature to Context.
	/// @param flag the feature flag.
	virtual MLCoreGraphicsContext* operator&=(const CGSizeT flag) override
	{
		mContextFlags &= flag;
		return this;
	}

	/// @brief Check for a feature.
	/// @param flag The feature in question.
	/// @retval true feature exists.
	/// @retval false not supported by this context.
	virtual bool operator&(const CGSizeT flag) override
	{
		return mContextFlags & flag;
	}

	/// @brief To string method.
	/// @return the class as a string
	virtual const MLString toString() override
	{
		std::string buffer = "{ ";
		buffer += "URI: ";
		buffer += "file://";
		buffer += this->mOutputPath;
		buffer += " }";

		MLString str = MLString(buffer.size());
		str += buffer.c_str();

		return str;
	}

	///////////////////////////////////////////////////////////////////////////

	virtual MLCoreGraphicsContext* Move(CGReal X, CGReal Y) override
	{
		cairo_move_to(mCairo, X, Y);

		mX = X;
		mY = Y;

		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	virtual MLCoreGraphicsContext* Text(const CGCharacter* T) override
	{
		cairo_show_text(mCairo, T);
		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	virtual MLCoreGraphicsContext* FontFamily(const CGCharacter* T, const bool isBold) override
	{
		cairo_select_font_face(mCairo, T, CAIRO_FONT_SLANT_NORMAL,
							   isBold ? CAIRO_FONT_WEIGHT_BOLD
									  : CAIRO_FONT_WEIGHT_NORMAL);
		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	virtual MLCoreGraphicsContext* FontSize(const CGReal T) override
	{
		cairo_set_font_size(mCairo, T);
		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	virtual MLCoreGraphicsContext* PDF(const CGCharacter* T) override
	{
		if (mSurface) return this;

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

	///////////////////////////////////////////////////////////////////////////

	virtual MLCoreGraphicsContext* Color(CGReal R, CGReal G, CGReal B, CGReal A) override
	{
		cairo_set_source_rgba(mCairo, R, G, B, A);
		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	virtual MLCoreGraphicsContext* Stroke(CGReal strokeStrength) override
	{
		cairo_set_line_width(mCairo, strokeStrength);
		cairo_stroke(mCairo);
		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	virtual MLCoreGraphicsContext* Rectangle(CGReal width, CGReal height, CGReal radius) override
	{
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

		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	virtual MLCoreGraphicsContext* LineTo(CGReal start, CGReal finish) override
	{
		cairo_line_to(mCairo, start, finish);

		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	virtual MLCoreGraphicsContext* LineCap(int32_t type) override
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
	virtual MLCoreGraphicsContext* Blur(CGReal radius,
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
				d[j] = rgb;
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
				d[j] = rgb;
			}
		}

		cairo_surface_destroy(tmp);

		cairo_surface_mark_dirty(mSurface);

		return this;
	}

	/// @note This only supports the PNG format.
	virtual MLCoreGraphicsContext* Image(const CGCharacter* Path, 
										CGSizeT W, CGSizeT H, 
										CGReal X, CGReal Y) override
	{
		std::basic_string<CGCharacter> strPath = Path;

		constexpr auto dirSeparator = "/";

		if (strPath.find(kRsrcProtocol) != std::string::npos)
		{
			strPath.replace(strPath.find(kRsrcProtocol), strlen(kRsrcProtocol),
							std::filesystem::current_path().string() + dirSeparator);
		}

		auto image = cairo_image_surface_create_from_png(strPath.c_str());

		cairo_set_source_surface(mCairo, image, X, Y);

		cairo_paint(mCairo);

		return this;
	}

	virtual MLCoreGraphicsContext* Scale(CGReal X, CGReal Y) override
	{
		cairo_scale(mCairo, X, Y);
		return this;
	}

	/// @note placeholder for now.
	virtual MLCoreGraphicsContext* Start() override
	{
		if (mCairo) return this;

		mCairo = cairo_create(mSurface);

		return this;
	}

	/// @brief Present PDF rendering of one page.
	/// @return 
	virtual MLCoreGraphicsContext* Present() override
	{
		
		if (!mSurface || !mCairo) return this;

		cairo_surface_copy_page(mSurface);

		cairo_set_source_rgb(mCairo, 1, 1, 1);
		cairo_paint(mCairo);

		return this;
	}

	/// @note Placeholder for now.
	/// @brief End draw command.
	virtual MLCoreGraphicsContext* End() override
	{
		if (!mSurface || !mCairo) return this;

		cairo_surface_destroy(mSurface);
		mSurface = nullptr;

		cairo_destroy(mCairo);
		mCairo = nullptr;

		return this;
	}

	/// @brief Set private internal context
	/// @param pvtCtx The cairo context.
	virtual void SetContext(void* pvtCtx) override
	{
		mCairo = (cairo_t*)pvtCtx;
		mCustomSurface = pvtCtx != nullptr;
	}

	/// @brief 
	/// @param T 
	/// @return 
	virtual MLCoreGraphicsContext* PageLabel(const CGCharacter* T) override
	{
		cairo_pdf_surface_set_page_label(mSurface, T);
		return this;
	}

	/// @brief 
	/// @param T 
	/// @return 
	virtual MLCoreGraphicsContext* ThumbnailSize(const int Width, const int Height) override
	{
		cairo_pdf_surface_set_thumbnail_size(mSurface, Width, Height);
		return this;
	}

private:
	CGSizeT			 mContextFlags{0};
	cairo_surface_t* mSurface{nullptr};
	cairo_t*		 mCairo{nullptr};
	CGReal			 mWidth{0};
	CGReal			 mHeight{0};
	CGCharacter		 mOutputPath[255] = {0};
	CGBoolean 		 mCustomSurface{false};
	CGReal			 mX{0};
	CGReal			 mY{0};
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
	this->End();
}

/// TODO: Port cairo as libcgx as a kernel driver.