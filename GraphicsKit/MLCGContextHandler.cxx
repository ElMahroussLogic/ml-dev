/*
 * Created on Fri May 10 2024
 *
 * Copyright (c) 2024 ZKA Technologies
 */

#include <GraphicsKit/MLCoreGraphicsContext.hxx>

/// @brief Releases a Core Graphics context.
/// @param context The context itself.
/// @return This function returns void.
void CGReleaseContext(MLCoreGraphicsContext* context)
{
	if (context)
	{
		delete context;
	}
}
