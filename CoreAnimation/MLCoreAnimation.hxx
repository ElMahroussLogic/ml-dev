/*
 * Created on Sat May 11 2024
 *
 * Copyright (c) 2024 Zeta Electronics Corporation
 */

#pragma once

#include <Foundation.hxx>
#include <Private/MLCoreAnimationBase.hxx>

/// @brief Linear interop helper function.
/// @param start where to begin
/// @param end where to end
/// @param status the status
/// @return the returned result of the lerp.
ML_IMPORT CAReal CALerp(CAReal start, CAReal end, CAReal status);

// END OF HEADER.
