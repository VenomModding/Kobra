#pragma once

#include <cstdint>
#include <memory>
#include <algorithm>

// We need the following WraithX classes
#include <WraithModel.h>

// We need the cod assets
#include "CoDAssets.h"

// -- Structures for storing data

struct WeightsData
{
    // The weight value for each bone
    float WeightValues[8];
    // The bone ids for each value
    uint32_t BoneValues[8];
    // The count of weights this set contains
    uint8_t WeightCount;

    WeightsData()
    {
        // Defaults
        WeightCount = 1;
        // Clear memory
        WeightValues[0] = 1.0f;
        WeightValues[1] = 1.0f;
        WeightValues[2] = 1.0f;
        WeightValues[3] = 1.0f;
        WeightValues[4] = 1.0f;
        WeightValues[5] = 1.0f;
        WeightValues[6] = 1.0f;
        WeightValues[7] = 1.0f;
        BoneValues[0] = 0;
        BoneValues[1] = 0;
        BoneValues[2] = 0;
        BoneValues[3] = 0;
        BoneValues[4] = 0;
        BoneValues[5] = 0;
        BoneValues[6] = 0;
        BoneValues[7] = 0;
    }
};

// -- End storage structures

// A class that handles translating generic Call of Duty XModels to Wraith Models
class CoDXModelTranslator
{
public:
    // -- Translation functions

    // Translates an in-game XModel to a WraithModel
    static std::unique_ptr<WraithModel> TranslateXModel(const std::unique_ptr<XModel_t>& Model, uint32_t LodIndex, bool JustBones = false);
    // Translates an in-game XModel to a WraithModel
    static std::unique_ptr<WraithModel> TranslateXMap(const std::unique_ptr<XMap_t>& Map, bool ExpotXModels);
    // Translates an in-game XModel's hitbox to a WraithModel
    static std::unique_ptr<WraithModel> TranslateXModelHitbox(const std::unique_ptr<XModel_t>& Model);

    // -- Utility functions

    // Calculates the index of the biggest lod, returns -1 if there are no lods
    static int32_t CalculateBiggestLodIndex(const std::unique_ptr<XModel_t>& Model);

private:
    // -- Translation utilities

    static std::unique_ptr<uint16_t> ReadGfxIndices(uint64_t Address, uint32_t Count);
    static GfxVertexBuffer ReadGfxVertices(uint64_t Address, uint32_t StartIndex);
    static std::vector<std::string> SplitString(std::string String, char Splitter);

    // Normal unpack method A
    static Vector3 UnpackNormalA(uint32_t Normal);
    // Normal unpack method B
    static Vector3 UnpackNormalB(uint32_t Normal);
    // Normal unpack method C
    static Vector3 UnpackNormalC(uint32_t Normal);

    // Prepares vertex weights A
    static void PrepareVertexWeightsA(std::vector<WeightsData>& Weights, const XModelSubmesh_t& Submesh);
    // Prepares vertex weights B
    static void PrepareVertexWeightsB(std::vector<WeightsData>& Weights, const XModelSubmesh_t& Submesh);
    // Prepares vertex weights C
    static void PrepareVertexWeightsC(std::vector<WeightsData>& Weights, const XModelSubmesh_t& Submesh);
};