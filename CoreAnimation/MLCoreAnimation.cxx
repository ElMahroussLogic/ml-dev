/*
 * Created on Fri May 17 2024
 *
 * Copyright (c) 2024 Zeta Electronics Corporation
 */

#include <MLCoreAnimation.hxx>

/// @brief Linear interop helper function.
/// @param start where to begin
/// @param end where to end
/// @param status the status
/// @return the returned result of the lerp.
ML_IMPORT CAReal CALerp(CAReal start, CAReal end, CAReal status)
{
	return (start + status * (end - start));
}
