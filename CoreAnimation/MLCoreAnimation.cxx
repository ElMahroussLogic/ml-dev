/*
 * Created on Fri May 17 2024
 *
 * Copyright (c) 2024 SoftwareLabs 
 */

#include <MLCoreAnimation.hxx>

/// @brief Linear interop helper function.
/// @param start where to begin
/// @param end where to end
/// @param status the status
/// @return the returned result of the lerp.
ML_IMPORT CGReal CGLerp(CGReal start, CGReal end, CGReal status)
{
    return (start + status * (end - start));
}
