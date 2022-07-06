/*****************************************************************************
 * Copyright (c) 2014-2020 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#pragma once

#include "../Cheats.h"
#include "../core/MemoryStream.h"
#include "../core/String.hpp"
#include "../entity/Guest.h"
#include "../localisation/Localisation.h"
#include "../network/NetworkTypes.h"
#include "../network/network.h"
#include "../object/Object.h"
#include "../ride/RideColour.h"
#include "../ride/TrackDesign.h"
#include "../world/Location.hpp"
#include "../world/TileElement.h"
#include "DataSerialiserTag.h"
#include "Endianness.h"
#include "MemoryStream.h"

#include <cstdio>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

template<typename T> struct DataSerializerTraits_t
{
    static void encode(OpenRCT2::IStream* stream, const T& v) = delete;
    static void decode(OpenRCT2::IStream* stream, T& val) = delete;
    static void log(OpenRCT2::IStream* stream, const T& val) = delete;
};

template<typename T> struct DataSerializerTraits_enum
{
    using TUnderlying = std::underlying_type_t<T>;

    static void encode(OpenRCT2::IStream* stream, const T& val)
    {
        TUnderlying temp = ByteSwapBE(static_cast<TUnderlying>(val));
        stream->Write(&temp);
    }
    static void decode(OpenRCT2::IStream* stream, T& val)
    {
        TUnderlying temp;
        stream->Read(&temp);
        val = static_cast<T>(ByteSwapBE(temp));
    }
    static void log(OpenRCT2::IStream* stream, const T& val)
    {
        std::stringstream ss;
        ss << std::hex << std::setw(sizeof(TUnderlying) * 2) << std::setfill('0') << static_cast<TUnderlying>(val);

        std::string str = ss.str();
        stream->Write(str.c_str(), str.size());
    }
};

template<typename T>
using DataSerializerTraits = std::conditional_t<std::is_enum_v<T>, DataSerializerTraits_enum<T>, DataSerializerTraits_t<T>>;

template<typename T> struct DataSerializerTraitsIntegral
{
    static void encode(OpenRCT2::IStream* stream, const T& val)
    {
        T temp = ByteSwapBE(val);
        stream->Write(&temp);
    }
    static void decode(OpenRCT2::IStream* stream, T& val)
    {
        T temp;
        stream->Read(&temp);
        val = ByteSwapBE(temp);
    }
    static void log(OpenRCT2::IStream* stream, const T& val)
    {
        std::stringstream ss;
        ss << std::hex << std::setw(sizeof(T) * 2) << std::setfill('0') << +val;

        std::string str = ss.str();
        stream->Write(str.c_str(), str.size());
    }
};

template<> struct DataSerializerTraits_t<bool>
{
    static void encode(OpenRCT2::IStream* stream, const bool& val)
    {
        stream->Write(&val);
    }
    static void decode(OpenRCT2::IStream* stream, bool& val)
    {
        stream->Read(&val);
    }
    static void log(OpenRCT2::IStream* stream, const bool& val)
    {
        if (val)
            stream->Write("true", 4);
        else
            stream->Write("false", 5);
    }
};

template<> struct DataSerializerTraits_t<uint8_t> : public DataSerializerTraitsIntegral<uint8_t>
{
};

template<> struct DataSerializerTraits_t<int8_t> : public DataSerializerTraitsIntegral<int8_t>
{
};

template<> struct DataSerializerTraits_t<utf8> : public DataSerializerTraitsIntegral<utf8>
{
};

template<> struct DataSerializerTraits_t<uint16_t> : public DataSerializerTraitsIntegral<uint16_t>
{
};

template<> struct DataSerializerTraits_t<int16_t> : public DataSerializerTraitsIntegral<int16_t>
{
};

template<> struct DataSerializerTraits_t<uint32_t> : public DataSerializerTraitsIntegral<uint32_t>
{
};

template<> struct DataSerializerTraits_t<int32_t> : public DataSerializerTraitsIntegral<int32_t>
{
};

template<> struct DataSerializerTraits_t<uint64_t> : public DataSerializerTraitsIntegral<uint64_t>
{
};

template<> struct DataSerializerTraits_t<int64_t> : public DataSerializerTraitsIntegral<int64_t>
{
};

template<> struct DataSerializerTraits_t<std::string>
{
    static void encode(OpenRCT2::IStream* stream, const std::string& str)
    {
        uint16_t len = static_cast<uint16_t>(str.size());
        uint16_t swapped = ByteSwapBE(len);
        stream->Write(&swapped);
        if (len == 0)
        {
            return;
        }
        stream->WriteArray(str.c_str(), len);
    }
    static void decode(OpenRCT2::IStream* stream, std::string& res)
    {
        uint16_t len;
        stream->Read(&len);
        len = ByteSwapBE(len);
        if (len == 0)
        {
            res.clear();
            return;
        }
        auto str = stream->ReadArray<char>(len);
        res.assign(str.get(), len);
    }
    static void log(OpenRCT2::IStream* stream, const std::string& str)
    {
        stream->Write("\"", 1);
        if (str.size() != 0)
        {
            stream->Write(str.data(), str.size());
        }
        stream->Write("\"", 1);
    }
};

template<> struct DataSerializerTraits_t<NetworkPlayerId_t>
{
    static void encode(OpenRCT2::IStream* stream, const NetworkPlayerId_t& val)
    {
        uint32_t temp = static_cast<uint32_t>(val.id);
        temp = ByteSwapBE(temp);
        stream->Write(&temp);
    }
    static void decode(OpenRCT2::IStream* stream, NetworkPlayerId_t& val)
    {
        uint32_t temp;
        stream->Read(&temp);
        val.id = static_cast<decltype(val.id)>(ByteSwapBE(temp));
    }
    static void log(OpenRCT2::IStream* stream, const NetworkPlayerId_t& val)
    {
        char playerId[28] = {};
        snprintf(playerId, sizeof(playerId), "%u", val.id);

        stream->Write(playerId, strlen(playerId));

        int32_t playerIndex = network_get_player_index(val.id);
        if (playerIndex != -1)
        {
            const char* playerName = network_get_player_name(playerIndex);
            if (playerName != nullptr)
            {
                stream->Write(" \"", 2);
                stream->Write(playerName, strlen(playerName));
                stream->Write("\"", 1);
            }
        }
    }
};

template<typename T> struct DataSerializerTraits_t<DataSerialiserTag<T>>
{
    static void encode(OpenRCT2::IStream* stream, const DataSerialiserTag<T>& tag)
    {
        DataSerializerTraits<T> s;
        s.encode(stream, tag.Data());
    }
    static void decode(OpenRCT2::IStream* stream, DataSerialiserTag<T>& tag)
    {
        DataSerializerTraits<T> s;
        s.decode(stream, tag.Data());
    }
    static void log(OpenRCT2::IStream* stream, const DataSerialiserTag<T>& tag)
    {
        const char* name = tag.Name();
        stream->Write(name, strlen(name));
        stream->Write(" = ", 3);

        DataSerializerTraits<T> s;
        s.log(stream, tag.Data());

        stream->Write("; ", 2);
    }
};

template<> struct DataSerializerTraits_t<OpenRCT2::MemoryStream>
{
    static void encode(OpenRCT2::IStream* stream, const OpenRCT2::MemoryStream& val)
    {
        DataSerializerTraits<uint32_t> s;
        s.encode(stream, val.GetLength());

        stream->Write(val.GetData(), val.GetLength());
    }
    static void decode(OpenRCT2::IStream* stream, OpenRCT2::MemoryStream& val)
    {
        DataSerializerTraits<uint32_t> s;

        uint32_t length = 0;
        s.decode(stream, length);

        auto buf = std::make_unique<uint8_t[]>(length);
        stream->Read(buf.get(), length);

        val.Write(buf.get(), length);
    }
    static void log(OpenRCT2::IStream* stream, const OpenRCT2::MemoryStream& tag)
    {
    }
};

template<typename _Ty, size_t _Size> struct DataSerializerTraitsPODArray
{
    static void encode(OpenRCT2::IStream* stream, const _Ty (&val)[_Size])
    {
        uint16_t len = static_cast<uint16_t>(_Size);
        uint16_t swapped = ByteSwapBE(len);
        stream->Write(&swapped);

        DataSerializerTraits<_Ty> s;
        for (auto&& sub : val)
        {
            s.encode(stream, sub);
        }
    }
    static void decode(OpenRCT2::IStream* stream, _Ty (&val)[_Size])
    {
        uint16_t len;
        stream->Read(&len);
        len = ByteSwapBE(len);

        if (len != _Size)
            throw std::runtime_error("Invalid size, can't decode");

        DataSerializerTraits<_Ty> s;
        for (auto&& sub : val)
        {
            s.decode(stream, sub);
        }
    }
    static void log(OpenRCT2::IStream* stream, const _Ty (&val)[_Size])
    {
        stream->Write("{", 1);
        DataSerializerTraits<_Ty> s;
        for (auto&& sub : val)
        {
            s.log(stream, sub);
            stream->Write("; ", 2);
        }
        stream->Write("}", 1);
    }
};

template<size_t _Size> struct DataSerializerTraits_t<uint8_t[_Size]> : public DataSerializerTraitsPODArray<uint8_t, _Size>
{
};

template<size_t _Size> struct DataSerializerTraits_t<utf8[_Size]> : public DataSerializerTraitsPODArray<utf8, _Size>
{
};

template<size_t _Size> struct DataSerializerTraits_t<uint16_t[_Size]> : public DataSerializerTraitsPODArray<uint16_t, _Size>
{
};

template<size_t _Size> struct DataSerializerTraits_t<uint32_t[_Size]> : public DataSerializerTraitsPODArray<uint32_t, _Size>
{
};

template<size_t _Size> struct DataSerializerTraits_t<uint64_t[_Size]> : public DataSerializerTraitsPODArray<uint64_t, _Size>
{
};

template<typename T, T TNullValue, typename TTag, size_t _Size>
struct DataSerializerTraits_t<TIdentifier<T, TNullValue, TTag>[_Size]>
    : public DataSerializerTraitsPODArray<TIdentifier<T, TNullValue, TTag>, _Size>
{
};

template<typename _Ty, size_t _Size> struct DataSerializerTraits_t<std::array<_Ty, _Size>>
{
    static void encode(OpenRCT2::IStream* stream, const std::array<_Ty, _Size>& val)
    {
        uint16_t len = static_cast<uint16_t>(_Size);
        uint16_t swapped = ByteSwapBE(len);
        stream->Write(&swapped);

        DataSerializerTraits<_Ty> s;
        for (auto&& sub : val)
        {
            s.encode(stream, sub);
        }
    }
    static void decode(OpenRCT2::IStream* stream, std::array<_Ty, _Size>& val)
    {
        uint16_t len;
        stream->Read(&len);
        len = ByteSwapBE(len);

        if (len != _Size)
            throw std::runtime_error("Invalid size, can't decode");

        DataSerializerTraits<_Ty> s;
        for (auto&& sub : val)
        {
            s.decode(stream, sub);
        }
    }
    static void log(OpenRCT2::IStream* stream, const std::array<_Ty, _Size>& val)
    {
        stream->Write("{", 1);
        DataSerializerTraits<_Ty> s;
        for (auto&& sub : val)
        {
            s.log(stream, sub);
            stream->Write("; ", 2);
        }
        stream->Write("}", 1);
    }
};

template<typename _Ty> struct DataSerializerTraits_t<std::vector<_Ty>>
{
    static void encode(OpenRCT2::IStream* stream, const std::vector<_Ty>& val)
    {
        uint16_t len = static_cast<uint16_t>(val.size());
        uint16_t swapped = ByteSwapBE(len);
        stream->Write(&swapped);

        DataSerializerTraits<_Ty> s;
        for (auto&& sub : val)
        {
            s.encode(stream, sub);
        }
    }
    static void decode(OpenRCT2::IStream* stream, std::vector<_Ty>& val)
    {
        uint16_t len;
        stream->Read(&len);
        len = ByteSwapBE(len);

        DataSerializerTraits<_Ty> s;
        for (auto i = 0; i < len; ++i)
        {
            _Ty sub{};
            s.decode(stream, sub);
            val.push_back(std::move(sub));
        }
    }
    static void log(OpenRCT2::IStream* stream, const std::vector<_Ty>& val)
    {
        stream->Write("{", 1);
        DataSerializerTraits<_Ty> s;
        for (auto&& sub : val)
        {
            s.log(stream, sub);
            stream->Write("; ", 2);
        }
        stream->Write("}", 1);
    }
};

template<> struct DataSerializerTraits_t<MapRange>
{
    static void encode(OpenRCT2::IStream* stream, const MapRange& v)
    {
        stream->WriteValue(ByteSwapBE(v.GetLeft()));
        stream->WriteValue(ByteSwapBE(v.GetTop()));
        stream->WriteValue(ByteSwapBE(v.GetRight()));
        stream->WriteValue(ByteSwapBE(v.GetBottom()));
    }
    static void decode(OpenRCT2::IStream* stream, MapRange& v)
    {
        auto l = ByteSwapBE(stream->ReadValue<int32_t>());
        auto t = ByteSwapBE(stream->ReadValue<int32_t>());
        auto r = ByteSwapBE(stream->ReadValue<int32_t>());
        auto b = ByteSwapBE(stream->ReadValue<int32_t>());
        v = MapRange(l, t, r, b);
    }
    static void log(OpenRCT2::IStream* stream, const MapRange& v)
    {
        char coords[128] = {};
        snprintf(
            coords, sizeof(coords), "MapRange(l = %d, t = %d, r = %d, b = %d)", v.GetLeft(), v.GetTop(), v.GetRight(),
            v.GetBottom());

        stream->Write(coords, strlen(coords));
    }
};

template<> struct DataSerializerTraits_t<TileElement>
{
    static void encode(OpenRCT2::IStream* stream, const TileElement& tileElement)
    {
        stream->WriteValue(tileElement.type);
        stream->WriteValue(tileElement.Flags);
        stream->WriteValue(tileElement.base_height);
        stream->WriteValue(tileElement.clearance_height);
        stream->WriteValue(tileElement.owner);
        for (int i = 0; i < 3; ++i)
        {
            stream->WriteValue(tileElement.pad_05[i]);
        }
        for (int i = 0; i < 8; ++i)
        {
            stream->WriteValue(tileElement.pad_08[i]);
        }
    }
    static void decode(OpenRCT2::IStream* stream, TileElement& tileElement)
    {
        tileElement.type = stream->ReadValue<uint8_t>();
        tileElement.Flags = stream->ReadValue<uint8_t>();
        tileElement.base_height = stream->ReadValue<uint8_t>();
        tileElement.clearance_height = stream->ReadValue<uint8_t>();
        tileElement.owner = stream->ReadValue<uint8_t>();
        for (int i = 0; i < 3; ++i)
        {
            tileElement.pad_05[i] = stream->ReadValue<uint8_t>();
        }
        for (int i = 0; i < 8; ++i)
        {
            tileElement.pad_08[i] = stream->ReadValue<uint8_t>();
        }
    }
    static void log(OpenRCT2::IStream* stream, const TileElement& tileElement)
    {
        char msg[128] = {};
        snprintf(
            msg, sizeof(msg), "TileElement(type = %u, flags = %u, base_height = %u)", tileElement.type, tileElement.Flags,
            tileElement.base_height);
        stream->Write(msg, strlen(msg));
    }
};

template<> struct DataSerializerTraits_t<TileCoordsXY>
{
    static void encode(OpenRCT2::IStream* stream, const TileCoordsXY& coords)
    {
        stream->WriteValue(ByteSwapBE(coords.x));
        stream->WriteValue(ByteSwapBE(coords.y));
    }
    static void decode(OpenRCT2::IStream* stream, TileCoordsXY& coords)
    {
        auto x = ByteSwapBE(stream->ReadValue<int32_t>());
        auto y = ByteSwapBE(stream->ReadValue<int32_t>());
        coords = TileCoordsXY{ x, y };
    }
    static void log(OpenRCT2::IStream* stream, const TileCoordsXY& coords)
    {
        char msg[128] = {};
        snprintf(msg, sizeof(msg), "TileCoordsXY(x = %d, y = %d)", coords.x, coords.y);
        stream->Write(msg, strlen(msg));
    }
};

template<> struct DataSerializerTraits_t<CoordsXY>
{
    static void encode(OpenRCT2::IStream* stream, const CoordsXY& coords)
    {
        stream->WriteValue(ByteSwapBE(coords.x));
        stream->WriteValue(ByteSwapBE(coords.y));
    }
    static void decode(OpenRCT2::IStream* stream, CoordsXY& coords)
    {
        auto x = ByteSwapBE(stream->ReadValue<int32_t>());
        auto y = ByteSwapBE(stream->ReadValue<int32_t>());
        coords = CoordsXY{ x, y };
    }
    static void log(OpenRCT2::IStream* stream, const CoordsXY& coords)
    {
        char msg[128] = {};
        snprintf(msg, sizeof(msg), "CoordsXY(x = %d, y = %d)", coords.x, coords.y);
        stream->Write(msg, strlen(msg));
    }
};

template<> struct DataSerializerTraits_t<CoordsXYZ>
{
    static void encode(OpenRCT2::IStream* stream, const CoordsXYZ& coord)
    {
        stream->WriteValue(ByteSwapBE(coord.x));
        stream->WriteValue(ByteSwapBE(coord.y));
        stream->WriteValue(ByteSwapBE(coord.z));
    }

    static void decode(OpenRCT2::IStream* stream, CoordsXYZ& coord)
    {
        auto x = ByteSwapBE(stream->ReadValue<int32_t>());
        auto y = ByteSwapBE(stream->ReadValue<int32_t>());
        auto z = ByteSwapBE(stream->ReadValue<int32_t>());
        coord = CoordsXYZ{ x, y, z };
    }

    static void log(OpenRCT2::IStream* stream, const CoordsXYZ& coord)
    {
        char msg[128] = {};
        snprintf(msg, sizeof(msg), "CoordsXYZ(x = %d, y = %d, z = %d)", coord.x, coord.y, coord.z);
        stream->Write(msg, strlen(msg));
    }
};

template<> struct DataSerializerTraits_t<CoordsXYZD>
{
    static void encode(OpenRCT2::IStream* stream, const CoordsXYZD& coord)
    {
        stream->WriteValue(ByteSwapBE(coord.x));
        stream->WriteValue(ByteSwapBE(coord.y));
        stream->WriteValue(ByteSwapBE(coord.z));
        stream->WriteValue(ByteSwapBE(coord.direction));
    }

    static void decode(OpenRCT2::IStream* stream, CoordsXYZD& coord)
    {
        auto x = ByteSwapBE(stream->ReadValue<int32_t>());
        auto y = ByteSwapBE(stream->ReadValue<int32_t>());
        auto z = ByteSwapBE(stream->ReadValue<int32_t>());
        auto d = ByteSwapBE(stream->ReadValue<uint8_t>());
        coord = CoordsXYZD{ x, y, z, d };
    }

    static void log(OpenRCT2::IStream* stream, const CoordsXYZD& coord)
    {
        char msg[128] = {};
        snprintf(
            msg, sizeof(msg), "CoordsXYZD(x = %d, y = %d, z = %d, direction = %d)", coord.x, coord.y, coord.z, coord.direction);
        stream->Write(msg, strlen(msg));
    }
};

template<> struct DataSerializerTraits_t<NetworkCheatType_t>
{
    static void encode(OpenRCT2::IStream* stream, const NetworkCheatType_t& val)
    {
        uint32_t temp = ByteSwapBE(val.id);
        stream->Write(&temp);
    }
    static void decode(OpenRCT2::IStream* stream, NetworkCheatType_t& val)
    {
        uint32_t temp;
        stream->Read(&temp);
        val.id = ByteSwapBE(temp);
    }
    static void log(OpenRCT2::IStream* stream, const NetworkCheatType_t& val)
    {
        const char* cheatName = CheatsGetName(static_cast<CheatType>(val.id));
        stream->Write(cheatName, strlen(cheatName));
    }
};

template<> struct DataSerializerTraits_t<rct_object_entry>
{
    static void encode(OpenRCT2::IStream* stream, const rct_object_entry& val)
    {
        uint32_t temp = ByteSwapBE(val.flags);
        stream->Write(&temp);
        stream->WriteArray(val.nameWOC, 12);
    }
    static void decode(OpenRCT2::IStream* stream, rct_object_entry& val)
    {
        uint32_t temp;
        stream->Read(&temp);
        val.flags = ByteSwapBE(temp);
        auto str = stream->ReadArray<char>(12);
        memcpy(val.nameWOC, str.get(), 12);
    }
    static void log(OpenRCT2::IStream* stream, const rct_object_entry& val)
    {
        stream->WriteArray(val.name, 8);
    }
};

template<> struct DataSerializerTraits_t<ObjectEntryDescriptor>
{
    static void encode(OpenRCT2::IStream* stream, const ObjectEntryDescriptor& val)
    {
        stream->WriteValue<uint8_t>(static_cast<uint8_t>(val.Generation));
        if (val.Generation == ObjectGeneration::DAT)
        {
            DataSerializerTraits<rct_object_entry> s;
            s.encode(stream, val.Entry);
        }
        else
        {
            stream->WriteValue<uint8_t>(static_cast<uint8_t>(val.GetType()));
            stream->WriteString(val.Identifier);
        }
    }

    static void decode(OpenRCT2::IStream* stream, ObjectEntryDescriptor& val)
    {
        auto generation = static_cast<ObjectGeneration>(stream->ReadValue<uint8_t>());
        if (generation == ObjectGeneration::DAT)
        {
            DataSerializerTraits<rct_object_entry> s;
            rct_object_entry entry;
            s.decode(stream, entry);
            val = ObjectEntryDescriptor(entry);
        }
        else
        {
            auto type = static_cast<ObjectType>(stream->ReadValue<uint8_t>());
            auto identifier = stream->ReadStdString();
            val = ObjectEntryDescriptor(type, identifier);
        }
    }

    static void log(OpenRCT2::IStream* stream, const ObjectEntryDescriptor& val)
    {
        auto identifier = std::string(val.GetName());
        char msg[128] = {};
        snprintf(msg, sizeof(msg), "ObjectEntryDescriptor[%s]", identifier.c_str());
        stream->Write(msg, strlen(msg));
    }
};

template<> struct DataSerializerTraits_t<TrackDesignTrackElement>
{
    static void encode(OpenRCT2::IStream* stream, const TrackDesignTrackElement& val)
    {
        stream->Write(&val.flags);
        stream->Write(&val.type);
    }
    static void decode(OpenRCT2::IStream* stream, TrackDesignTrackElement& val)
    {
        stream->Read(&val.flags);
        stream->Read(&val.type);
    }
    static void log(OpenRCT2::IStream* stream, const TrackDesignTrackElement& val)
    {
        char msg[128] = {};
        snprintf(msg, sizeof(msg), "TrackDesignTrackElement(type = %d, flags = %d)", val.type, val.flags);
        stream->Write(msg, strlen(msg));
    }
};

template<> struct DataSerializerTraits_t<TrackDesignMazeElement>
{
    static void encode(OpenRCT2::IStream* stream, const TrackDesignMazeElement& val)
    {
        uint32_t temp = ByteSwapBE(val.all);
        stream->Write(&temp);
    }
    static void decode(OpenRCT2::IStream* stream, TrackDesignMazeElement& val)
    {
        uint32_t temp;
        stream->Read(&temp);
        val.all = ByteSwapBE(temp);
    }
    static void log(OpenRCT2::IStream* stream, const TrackDesignMazeElement& val)
    {
        char msg[128] = {};
        snprintf(msg, sizeof(msg), "TrackDesignMazeElement(all = %d)", val.all);
        stream->Write(msg, strlen(msg));
    }
};

template<> struct DataSerializerTraits_t<TrackDesignEntranceElement>
{
    static void encode(OpenRCT2::IStream* stream, const TrackDesignEntranceElement& val)
    {
        stream->Write(&val.x);
        stream->Write(&val.y);
        stream->Write(&val.z);
        stream->Write(&val.direction);
        stream->Write(&val.isExit);
    }
    static void decode(OpenRCT2::IStream* stream, TrackDesignEntranceElement& val)
    {
        stream->Read(&val.x);
        stream->Read(&val.y);
        stream->Read(&val.z);
        stream->Read(&val.direction);
        stream->Read(&val.isExit);
    }
    static void log(OpenRCT2::IStream* stream, const TrackDesignEntranceElement& val)
    {
        char msg[128] = {};
        snprintf(
            msg, sizeof(msg), "TrackDesignEntranceElement(x = %d, y = %d, z = %d, dir = %d, isExit = %d)", val.x, val.y, val.z,
            val.direction, val.isExit);
        stream->Write(msg, strlen(msg));
    }
};

template<> struct DataSerializerTraits_t<TrackDesignSceneryElement>
{
    static void encode(OpenRCT2::IStream* stream, const TrackDesignSceneryElement& val)
    {
        stream->Write(&val.loc);
        stream->Write(&val.flags);
        stream->Write(&val.primary_colour);
        stream->Write(&val.secondary_colour);
        DataSerializerTraits<ObjectEntryDescriptor> s;
        s.encode(stream, val.scenery_object);
    }
    static void decode(OpenRCT2::IStream* stream, TrackDesignSceneryElement& val)
    {
        stream->Read(&val.loc);
        stream->Read(&val.flags);
        stream->Read(&val.primary_colour);
        stream->Read(&val.secondary_colour);
        DataSerializerTraits<ObjectEntryDescriptor> s;
        s.decode(stream, val.scenery_object);
    }
    static void log(OpenRCT2::IStream* stream, const TrackDesignSceneryElement& val)
    {
        char msg[128] = {};
        snprintf(
            msg, sizeof(msg), "TrackDesignSceneryElement(x = %d, y = %d, z = %d, flags = %d, colour1 = %d, colour2 = %d)",
            val.loc.x, val.loc.y, val.loc.z, val.flags, val.primary_colour, val.secondary_colour);
        stream->Write(msg, strlen(msg));

        auto identifier = val.scenery_object.GetName();
        stream->WriteArray(identifier.data(), identifier.size());
    }
};

template<> struct DataSerializerTraits_t<rct_vehicle_colour>
{
    static void encode(OpenRCT2::IStream* stream, const rct_vehicle_colour& val)
    {
        stream->Write(&val.body_colour);
        stream->Write(&val.trim_colour);
    }
    static void decode(OpenRCT2::IStream* stream, rct_vehicle_colour& val)
    {
        stream->Read(&val.body_colour);
        stream->Read(&val.trim_colour);
    }
    static void log(OpenRCT2::IStream* stream, const rct_vehicle_colour& val)
    {
        char msg[128] = {};
        snprintf(msg, sizeof(msg), "rct_vehicle_colour(body_colour = %d, trim_colour = %d)", val.body_colour, val.trim_colour);
        stream->Write(msg, strlen(msg));
    }
};

template<> struct DataSerializerTraits_t<IntensityRange>
{
    static void encode(OpenRCT2::IStream* stream, const IntensityRange& val)
    {
        uint8_t temp = uint8_t(val);
        stream->Write(&temp);
    }
    static void decode(OpenRCT2::IStream* stream, IntensityRange& val)
    {
        auto temp = stream->ReadValue<uint8_t>();
        val = IntensityRange(temp);
    }
    static void log(OpenRCT2::IStream* stream, const IntensityRange& val)
    {
        char msg[128] = {};
        snprintf(msg, sizeof(msg), "IntensityRange(min = %d, max = %d)", val.GetMinimum(), val.GetMaximum());
        stream->Write(msg, strlen(msg));
    }
};

template<> struct DataSerializerTraits_t<PeepThought>
{
    static void encode(OpenRCT2::IStream* stream, const PeepThought& val)
    {
        stream->Write(&val.type);
        stream->Write(&val.item);
        stream->Write(&val.freshness);
        stream->Write(&val.fresh_timeout);
    }
    static void decode(OpenRCT2::IStream* stream, PeepThought& val)
    {
        stream->Read(&val.type);
        stream->Read(&val.item);
        stream->Read(&val.freshness);
        stream->Read(&val.fresh_timeout);
    }
    static void log(OpenRCT2::IStream* stream, const PeepThought& val)
    {
        char msg[128] = {};
        snprintf(
            msg, sizeof(msg), "PeepThought(type = %d, item = %u, freshness = %d, freshtimeout = %d)",
            static_cast<int32_t>(val.type), val.item, val.freshness, val.fresh_timeout);
        stream->Write(msg, strlen(msg));
    }
};

template<> struct DataSerializerTraits_t<TileCoordsXYZD>
{
    static void encode(OpenRCT2::IStream* stream, const TileCoordsXYZD& coord)
    {
        stream->WriteValue(ByteSwapBE(coord.x));
        stream->WriteValue(ByteSwapBE(coord.y));
        stream->WriteValue(ByteSwapBE(coord.z));
        stream->WriteValue(ByteSwapBE(coord.direction));
    }

    static void decode(OpenRCT2::IStream* stream, TileCoordsXYZD& coord)
    {
        auto x = ByteSwapBE(stream->ReadValue<int32_t>());
        auto y = ByteSwapBE(stream->ReadValue<int32_t>());
        auto z = ByteSwapBE(stream->ReadValue<int32_t>());
        auto d = ByteSwapBE(stream->ReadValue<Direction>());
        coord = TileCoordsXYZD{ x, y, z, d };
    }

    static void log(OpenRCT2::IStream* stream, const TileCoordsXYZD& coord)
    {
        char msg[128] = {};
        snprintf(
            msg, sizeof(msg), "TileCoordsXYZD(x = %d, y = %d, z = %d, direction = %d)", coord.x, coord.y, coord.z,
            coord.direction);
        stream->Write(msg, strlen(msg));
    }
};

template<typename T, T TNull, typename TTag> struct DataSerializerTraits_t<TIdentifier<T, TNull, TTag>>
{
    static void encode(OpenRCT2::IStream* stream, const TIdentifier<T, TNull, TTag>& id)
    {
        stream->WriteValue(ByteSwapBE(id.ToUnderlying()));
    }

    static void decode(OpenRCT2::IStream* stream, TIdentifier<T, TNull, TTag>& id)
    {
        auto temp = ByteSwapBE(stream->ReadValue<T>());
        id = TIdentifier<T, TNull, TTag>::FromUnderlying(temp);
    }

    static void log(OpenRCT2::IStream* stream, const TIdentifier<T, TNull, TTag>& id)
    {
        char msg[128] = {};
        snprintf(msg, sizeof(msg), "Id(%u)", static_cast<uint32_t>(id.ToUnderlying()));
        stream->Write(msg, strlen(msg));
    }
};
