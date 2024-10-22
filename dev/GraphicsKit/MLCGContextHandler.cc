/*
 * Created on Fri May 10 2024
 *
 * Copyright (c) 2024 ZKA Web Services Co
 */

#include <GraphicsKit/MLCoreGraphicsContext.h>

/// @brief Releases a Core Graphics context.
/// @param context The context itself.
/// @return This function returns void.
void CGReleaseContext(MLCoreGraphicsContext* context)
{
	if (context)
	{
		delete context;
		context = nullptr;
	}
}
