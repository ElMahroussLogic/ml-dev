/*
 * Created on Fri May 10 2024
 *
 * Copyright (c) 2024 ELMH Group
 */

#include <GraphicsKit/GKContextInterface.h>

/// @brief To string method.
/// @return the class as a string
const MLString GKContextInterface::toString()
{
	MLString ctxBackendJson = MLString("['ClassName': 'GKContextInterface']");
	return ctxBackendJson;
}

/// @brief Releases a GraphicsKit context.
/// @param context The context itself.
/// @return This function returns void.
BOOL GKReleaseContext(GKContextInterface* context)
{
	if (context)
	{
		delete context;
		context = nullptr;
	
		return YES;
	}

	return NO;
}
