/*****************************************************************************
 * Copyright (c) 2014-2021 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#pragma once

#include "../rct2/DATLimits.h"
#include "RideColour.h"
#include "ShopItem.h"
#include "VehicleColour.h"
#include "VehicleEntry.h"

#include <cstdint>

// Set to 255 on all tracked ride entries
static uint8_t constexpr NoFlatRideCars = 0xFF;

struct RideNaming
{
    rct_string_id Name;
    rct_string_id Description;
};

struct track_colour_preset_list
{
    uint8_t count;
    TrackColour list[256];
};

struct vehicle_colour_preset_list
{
    uint8_t count;
    VehicleColour list[256];
};

/**
 * Ride type structure.
 */
struct rct_ride_entry
{
    RideNaming naming;
    // The first three images are previews. They correspond to the ride_type[] array.
    uint32_t images_offset;
    uint32_t flags;
    uint8_t ride_type[RCT2::ObjectLimits::MaxRideTypesPerRideEntry];
    uint8_t min_cars_in_train;
    uint8_t max_cars_in_train;
    uint8_t cars_per_flat_ride;
    // Number of cars that can't hold passengers
    uint8_t zero_cars;
    // The index to the vehicle type displayed in the vehicle tab.
    uint8_t TabCar;
    uint8_t DefaultCar;
    // Convert from first - fourth car to vehicle structure
    uint8_t FrontCar;
    uint8_t SecondCar;
    uint8_t RearCar;
    uint8_t ThirdCar;
    uint8_t BuildMenuPriority;
    CarEntry Cars[RCT2::ObjectLimits::MaxCarTypesPerRideEntry];
    vehicle_colour_preset_list* vehicle_preset_list;
    int8_t excitement_multiplier;
    int8_t intensity_multiplier;
    int8_t nausea_multiplier;
    uint8_t max_height;
    ShopItem shop_item[RCT2::ObjectLimits::MaxShopItemsPerRideEntry];
    rct_string_id capacity;
    void* obj;

    const CarEntry* GetCar(size_t id) const
    {
        if (id < std::size(Cars))
        {
            return &Cars[id];
        }
        return nullptr;
    }

    const CarEntry* GetDefaultCar() const
    {
        return GetCar(DefaultCar);
    }
};

void set_vehicle_type_image_max_sizes(CarEntry* vehicle_type, int32_t num_images);
RideNaming get_ride_naming(const uint8_t rideType, rct_ride_entry* rideEntry);
