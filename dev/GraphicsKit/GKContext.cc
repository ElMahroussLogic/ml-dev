/*
 * Created on Fri May 10 2024
 *
 * Copyright (c) 2024 ZKA Web Services Co
 */

#include <GraphicsKit/GKContext.h>

/// @brief To string method.
/// @return the class as a string
const MLString GKContext::toString()
{
	MLString ctxBackendJson = MLString("['ClassName': 'GKContext']");
	return ctxBackendJson;
}

/// @brief Releases a GraphicsKit context.
/// @param context The context itself.
/// @return This function returns void.
void GKReleaseContext(GKContext* context)
{
	if (context)
	{
		delete context;
		context = nullptr;
	}
}
