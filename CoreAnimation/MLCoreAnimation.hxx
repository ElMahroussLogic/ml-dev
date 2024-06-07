/*
 * Created on Sat May 11 2024
 *
 * Copyright (c) 2024 SoftwareLabs B.V
 */

#pragma once

#include <Foundation.hxx>
#include <CoreGraphics.hxx>

/// @brief Linear interop helper function.
/// @param start where to begin
/// @param end where to end
/// @param status the status
/// @return the returned value.
inline CGReal CGLerp(float start, float end, float status)
{
    return (start + status * (end - start));
}

// END OF HEADER.