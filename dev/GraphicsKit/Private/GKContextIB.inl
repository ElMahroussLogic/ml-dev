/*
 *	========================================================
 *
 *	GraphicsKit
 *	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.
 *
 *  ========================================================
 */

#pragma once

#include <GraphicsKit/Foundation.h>
#include <IBKit/IBKit.h>
#include <filesystem>

/// @file: GKContextIB.inl
/// @brief: Cairo backend for multiplatform code.
/// @note: Cairo will be used for SVG rendering. so that an AbstractScreen can render it.

/// @brief Cairo implement of GraphicsKit.
class GKContextIB : public GKContextInterface
{
public:
	GKContextIB(const GKReal width, const GKReal height);
	~GKContextIB();

public:
	/// @brief Grants a new feature to Context.
	/// @param flag the feature flag.
	GKContextInterface* operator|=(const GKSizeType flag) override
	{
		mContextFlags |= flag;
		return this;
	}

	/// @brief Revokes a new feature to Context.
	/// @param flag the feature flag.
	GKContextInterface* operator&=(const GKSizeType flag) override
	{
		mContextFlags &= flag;
		return this;
	}

	/// @brief Check for a feature.
	/// @param flag The feature in question.
	/// @retval true feature exists.
	/// @retval false not supported by this context.
	bool operator&(const GKSizeType flag) override
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

	GKContextInterface* move(GKReal X, GKReal Y) override
	{
		ib_move_to(mIB, X, Y);

		mX = X;
		mY = Y;

		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	GKContextInterface* text(const GKChar* T, GKBoolean Center, GKReal X, GKReal Y, GKReal W, GKReal H) override
	{
		if (Center)
		{
			ib_text_extents_t extents;
			ib_font_extents_t font_extents;

			ib_text_extents(mIB, T, &extents);
			ib_font_extents(mIB, &font_extents);

			// Calculate the position to center the text
			double x_center = X + (W - extents.width) / 2 - extents.x_bearing;
			double y_center = Y + (H - font_extents.height) / 2 + font_extents.ascent;

			// Move to the calculated position and show the text
			ib_move_to(mIB, x_center, y_center);
		}

		ib_show_text(mIB, T);

		if (Center)
		{
			ib_move_to(mIB, mX, mY);
		}

		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	GKContextInterface* fontFamily(const GKChar* T, const bool isBold) override
	{
		ib_select_font_face(mIB, T, CAIRO_FONT_SLANT_NORMAL,
							   isBold ? CAIRO_FONT_WEIGHT_BOLD
									  : CAIRO_FONT_WEIGHT_NORMAL);
		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	GKContextInterface* fontSize(const GKReal T) override
	{
		ib_set_font_size(mIB, T);
		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	GKContextInterface* pdf(const GKChar* T) override
	{
		if (mSurface)
			return this;

		std::basic_string<GKChar> strPath = T;

		constexpr auto dirSeparator = "/";

		if (strPath.find(kRsrcProtocol) != std::string::npos)
		{
			strPath.replace(strPath.find(kRsrcProtocol), strlen(kRsrcProtocol),
							std::filesystem::current_path().string() + dirSeparator);
		}

		memcpy(mOutputPath, strPath.c_str(), strPath.size());
		mSurface = ib_pdf_surface_create(mOutputPath, mWidth, mHeight);

		return this;
	}

	GKContextInterface* svg(const GKChar* T) override
	{
		if (mSurface)
			return this;

		std::basic_string<GKChar> strPath = T;

		constexpr auto dirSeparator = "/";

		if (strPath.find(kRsrcProtocol) != std::string::npos)
		{
			strPath.replace(strPath.find(kRsrcProtocol), strlen(kRsrcProtocol),
							std::filesystem::current_path().string() + dirSeparator);
		}

		memcpy(mOutputPath, strPath.c_str(), strPath.size());
		mSurface = ib_svg_surface_create(mOutputPath, mWidth, mHeight);

		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	GKContextInterface* color(GKReal R, GKReal G, GKReal B, GKReal A) override
	{
		ib_set_source_rgba(mIB, R, G, B, A);
		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	GKContextInterface* stroke(GKReal strokeStrength) override
	{
		ib_set_line_width(mIB, strokeStrength);
		ib_stroke(mIB);
		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	GKContextInterface* rectangle(GKReal width, GKReal height, GKReal radius) override
	{
		if (radius == 0.0)
		{
			ib_rectangle(mIB, mX, mY, width, height);
			ib_paint(mIB);

			return this;
		}

		double aspect	  = 1.0,		   /* aspect ratio */
			corner_radius = height / 10.0; /* and corner curvature radius */

		double degrees = kMathPI / 180.0;

		ib_new_sub_path(mIB);

		GKReal x = mX;
		GKReal y = mY;

		ib_arc(mIB, x + width - radius, y + radius, radius, -90 * degrees,
				  0 * degrees);
		ib_arc(mIB, x + width - radius, y + height - radius, radius, 0 * degrees,
				  90 * degrees);
		ib_arc(mIB, x + radius, y + height - radius, radius, 90 * degrees,
				  180 * degrees);
		ib_arc(mIB, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);

		ib_close_path(mIB);

		ib_fill_preserve(mIB);

		ib_paint(mIB);

		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	GKContextInterface* lineTo(GKReal start, GKReal finish) override
	{
		ib_line_to(mIB, start, finish);

		return this;
	}

	///////////////////////////////////////////////////////////////////////////

	GKContextInterface* lineCap(GKLineCap type) override
	{
		switch (type)
		{
		case GKLineCap::kLineCapNormal:
		default:
			ib_set_line_cap(mIB, CAIRO_LINE_CAP_BUTT);
			break;
		case GKLineCap::kLineCapRounded:
			ib_set_line_cap(mIB, CAIRO_LINE_CAP_ROUND);
		case GKLineCap::kLineCapSquare:
			ib_set_line_cap(mIB, CAIRO_LINE_CAP_SQUARE);
			break;
		}

		return this;
	}

	/// @brief Draws a gaussian blur. (taken from Cairo cookbook.)
	/// @param radius blur's radius
	/// @return the context.
	/// @note the blur doesn't work on PDF backends.
	GKContextInterface* blur(GKReal	radius,
								GKSizeType width,
								GKSizeType height) override
	{
		ib_surface_t* tmp;
		int				 src_stride, dst_stride;
		long long		 x, y, z, w;
		uint8_t *		 src, *dst;
		uint32_t *		 s, *d, a, p;
		int				 i, j, k;
		uint8_t			 kernel[256];
		const int		 size = ML_ARRAY_LENGTH(kernel);
		const int		 half = size / 2;

		if (!mSurface)
			mSurface = ib_get_target(mIB);

		if (ib_surface_status(mSurface))
			return this;

		switch (ib_image_surface_get_format(mSurface))
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

		tmp = ib_image_surface_create(CAIRO_FORMAT_ARGB32, mWidth,
										 mHeight);

		if (ib_surface_status(tmp))
			return this;

		src		   = ib_image_surface_get_data(mSurface);
		src_stride = ib_image_surface_get_stride(mSurface);

		dst		   = ib_image_surface_get_data(tmp);
		dst_stride = ib_image_surface_get_stride(tmp);

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

		ib_surface_destroy(tmp);

		ib_surface_mark_dirty(mSurface);

		return this;
	}

	/// @note This only supports the PNG format.
	GKContextInterface* image(const GKChar* Path,
								 GKSizeType			W,
								 GKSizeType			H,
								 GKReal				X,
								 GKReal				Y) override
	{
		static std::basic_string<GKChar> cPath;
		static std::basic_string<GKChar> cPathReal;

		if (cPath != Path)
		{
			cPath = Path;

			std::basic_string<GKChar> strPath = Path;

			constexpr auto cDirSeparator = "/";

			if (strPath.find(kRsrcProtocol) != std::string::npos)
			{
				strPath.replace(strPath.find(kRsrcProtocol), strlen(kRsrcProtocol),
								std::filesystem::current_path().string() + cDirSeparator);
			}

			cPathReal = strPath;

			auto image = ib_image_surface_create_from_png(strPath.c_str());
			ib_set_source_surface(mIB, image, X, Y);

			ib_paint(mIB);
		}
		else
		{
			auto image = ib_image_surface_create_from_png(cPathReal.c_str());
			ib_set_source_surface(mIB, image, X, Y);

			ib_paint(mIB);
		}

		return this;
	}

	GKContextInterface* scale(GKReal X, GKReal Y) override
	{
		ib_scale(mIB, X, Y);
		return this;
	}

	/// @note placeholder for now.
	GKContextInterface* start() override
	{
		if (mIB)
			return this;

		mIB = ib_create(mSurface);

		return this;
	}

	/// @brief Present PDF rendering of one page.
	/// @return
	GKContextInterface* present(GKReal r, GKReal g, GKReal b) override
	{
		ib_set_source_rgb(mIB, r, g, b);
		ib_paint(mIB);

		return this;
	}

	/// @note Placeholder for now.
	/// @brief End draw command.
	GKContextInterface* end() override
	{
		if (!mSurface || !mIB)
			return this;

		if (!mCustomSurface && mSurface)
		{
			ib_surface_destroy(mSurface);
			mSurface = nullptr;
		}

		if (!mCustomCairo && mIB)
		{
			ib_destroy(mIB);
			mIB = nullptr;
		}

		return this;
	}

	/// @brief Leak or set private internal context
	/// @param PvtCtx The cairo context.
	void leak(void*** pvtCtx) override
	{
		*pvtCtx = (void**)&mIB;
	}

	/// @brief
	/// @param T
	/// @return
	GKContextInterface* pageLabel(const GKChar* T) override
	{
		ib_pdf_surface_set_page_label(mSurface, T);
		return this;
	}

	/// @brief
	/// @param T
	/// @return
	GKContextInterface* thumbnailSize(const int Width, const int Height) override
	{
		ib_pdf_surface_set_thumbnail_size(mSurface, Width, Height);
		return this;
	}

private:
	typedef ib_surface_t* GKSurfacePtr;
	typedef ib_t*		 GKPtr;

	GKSizeType		 mContextFlags{0};
	GKSurfacePtr mSurface{nullptr};
	GKPtr		 mIB{nullptr};
	GKReal		 mWidth{0};
	GKReal		 mHeight{0};
	GKChar	 mOutputPath[255] = {0};
	GKBoolean	 mCustomCairo{false};
	GKBoolean	 mCustomSurface{false};
	GKReal		 mX{0};
	GKReal		 mY{0};
};

////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Cairo context constructor.
/// @param width the width.
/// @param height the height.
GKContextIB::GKContextIB(const GKReal width,
													   const GKReal height)
	: mWidth(width), mHeight(height)
{
	ML_MUST_PASS(width > 0 && height > 0);
}

/// @brief C++ destrcutor, the End() method is called as well.
GKContextIB::~GKContextIB()
{
	this->end();
}

/// TODO: Cairo as GX.framework
