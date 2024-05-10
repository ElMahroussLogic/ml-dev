/*
 * Created on Fri May 10 2024
 *
 * Copyright (c) 2024 Oreala B.V
 */

#pragma once

#include <Foundation.hxx>
#include <MLFont.hxx>

typedef double CGReal;
typedef size_t CGSizeT;

/// @brief Core Graphics context.
class MLCoreGraphicsContext {
public:
    explicit MLCoreGraphicsContext() = default;
    virtual ~MLCoreGraphicsContext() = default;

    MLCoreGraphicsContext& operator=(const MLCoreGraphicsContext&) = default;
    MLCoreGraphicsContext(const MLCoreGraphicsContext&) = default;

public:
    /// @brief Draw vertices. 
    /// @param floatVerts ther vertices.
    /// @param vertCnt the vertices count
    virtual void Draw(CGReal* floatVerts, CGSizeT vertCnt) = 0;

    /// @brief Draw vertices starting from an index. 
    /// @param floatVerts ther vertices.
    /// @param vertCnt the vertices count
    /// @param indiceStart where to start?
    virtual void DrawIndexed(CGReal* floatVerts, CGSizeT vertCnt,
                            CGSizeT indiceStart) = 0;

    /// @brief Grants a new feature to Context.
    /// @param flag the feature flag.
    virtual MLCoreGraphicsContext& operator|=(const CGSizeT flag) = 0;

    /// @brief Revokes a new feature to Context.
    /// @param flag the feature flag.
    virtual MLCoreGraphicsContext& operator&=(const CGSizeT flag) = 0;

    /// @brief Check for a feature.
    /// @param flag The feature in question.
    /// @retval true feature exists.
    /// @retval false not supported by this context.
    virtual bool operator&(const CGSizeT flag) = 0;
};

/// @brief Request a context regarding the features set.
/// @param featureSet the feature set.
/// @param strict should we require all the features to be here?
/// @note if no, please check for feature with operator& inside MLCoreGraphicsContext.
/// @return The new graphics context.
ML_IMPORT MLCoreGraphicsContext* CGRequestContext(CGSizeT featureSet);
