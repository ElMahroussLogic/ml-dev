/**
 *
 * Copyright (c) 2024 EL Mahrouss Logic
 *
 */

#pragma once

#include <FoundationKit/Foundation.h>

typedef MLInteger64 MLDisplayRef;

/// @brief Creates a display from **name** and coordinates.
/// @param name Display name.
MLDisplayRef MLCreateDisplay(const MLChar* name, const MLInteger& x,
                            const MLInteger& y, const MLInteger& w, const MLInteger& h);

/// @brief Removes a display from the renderables.
/// @param display display reference.
MLInteger MLRemoveDisplay(MLDisplayRef& display);
