/*
 * Created on Fri May 10 2024
 *
 * Copyright (c) 2024 ZKA Technologies
 */

#include <GraphicsKit/MLCoreGraphicsContext.hxx>

typedef size_t platform_size_t;

/// @brief To string method.
/// @return the class as a string
const MLString MLCoreGraphicsContext::toString()
{
	constexpr platform_size_t cDefaultSz = 4096;

	MLString ctxStr = MLString(cDefaultSz);
	ctxStr += "[ { \'MLCoreGraphicsContext\': { \'Renderer\': \'Cairo\' } } ]";

	return ctxStr;
}
