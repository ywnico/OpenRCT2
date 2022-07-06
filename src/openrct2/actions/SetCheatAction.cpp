/*****************************************************************************
 * Copyright (c) 2014-2020 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "SetCheatAction.h"

#include "../Cheats.h"
#include "../Context.h"
#include "../GameState.h"
#include "../config/Config.h"
#include "../core/String.hpp"
#include "../drawing/Drawing.h"
#include "../entity/Duck.h"
#include "../entity/EntityRegistry.h"
#include "../entity/Staff.h"
#include "../localisation/Localisation.h"
#include "../localisation/StringIds.h"
#include "../network/network.h"
#include "../ride/Ride.h"
#include "../ride/Vehicle.h"
#include "../scenario/Scenario.h"
#include "../ui/UiContext.h"
#include "../util/Util.h"
#include "../windows/Intent.h"
#include "../world/Banner.h"
#include "../world/Climate.h"
#include "../world/Footpath.h"
#include "../world/Location.hpp"
#include "../world/Map.h"
#include "../world/Park.h"
#include "../world/Scenery.h"
#include "../world/Surface.h"
#include "ParkSetLoanAction.h"
#include "ParkSetParameterAction.h"

using ParametersRange = std::pair<std::pair<int32_t, int32_t>, std::pair<int32_t, int32_t>>;

SetCheatAction::SetCheatAction(CheatType cheatType, int32_t param1, int32_t param2)
    : _cheatType(static_cast<int32_t>(cheatType))
    , _param1(param1)
    , _param2(param2)
{
}

void SetCheatAction::AcceptParameters(GameActionParameterVisitor& visitor)
{
    visitor.Visit("type", _cheatType);
    visitor.Visit("param1", _param1);
    visitor.Visit("param2", _param2);
}

uint16_t SetCheatAction::GetActionFlags() const
{
    return GameAction::GetActionFlags() | GameActions::Flags::AllowWhilePaused;
}

void SetCheatAction::Serialise(DataSerialiser& stream)
{
    GameAction::Serialise(stream);
    stream << DS_TAG(_cheatType) << DS_TAG(_param1) << DS_TAG(_param2);
}

GameActions::Result SetCheatAction::Query() const
{
    if (static_cast<uint32_t>(_cheatType) >= static_cast<uint32_t>(CheatType::Count))
    {
        GameActions::Result(GameActions::Status::InvalidParameters, STR_NONE, STR_NONE);
    }

    ParametersRange validRange = GetParameterRange(static_cast<CheatType>(_cheatType.id));

    if (_param1 < validRange.first.first || _param1 > validRange.first.second)
    {
        GameActions::Result(GameActions::Status::InvalidParameters, STR_NONE, STR_NONE);
    }
    if (_param2 < validRange.second.first || _param2 > validRange.second.second)
    {
        GameActions::Result(GameActions::Status::InvalidParameters, STR_NONE, STR_NONE);
    }

    return GameActions::Result();
}

GameActions::Result SetCheatAction::Execute() const
{
    switch (static_cast<CheatType>(_cheatType.id))
    {
        case CheatType::SandboxMode:
            gCheatsSandboxMode = _param1 != 0;
            window_invalidate_by_class(WC_MAP);
            window_invalidate_by_class(WC_FOOTPATH);
            break;
        case CheatType::DisableClearanceChecks:
            gCheatsDisableClearanceChecks = _param1 != 0;
            // Required to update the clearance checks overlay on the Cheats button.
            window_invalidate_by_class(WC_TOP_TOOLBAR);
            break;
        case CheatType::DisableSupportLimits:
            gCheatsDisableSupportLimits = _param1 != 0;
            break;
        case CheatType::ShowAllOperatingModes:
            gCheatsShowAllOperatingModes = _param1 != 0;
            break;
        case CheatType::ShowVehiclesFromOtherTrackTypes:
            gCheatsShowVehiclesFromOtherTrackTypes = _param1 != 0;
            break;
        case CheatType::FastLiftHill:
            gCheatsUnlockOperatingLimits = _param1 != 0;
            break;
        case CheatType::DisableBrakesFailure:
            gCheatsDisableBrakesFailure = _param1 != 0;
            break;
        case CheatType::DisableAllBreakdowns:
            gCheatsDisableAllBreakdowns = _param1 != 0;
            break;
        case CheatType::DisableTrainLengthLimit:
            gCheatsDisableTrainLengthLimit = _param1 != 0;
            break;
        case CheatType::EnableChainLiftOnAllTrack:
            gCheatsEnableChainLiftOnAllTrack = _param1 != 0;
            break;
        case CheatType::BuildInPauseMode:
            gCheatsBuildInPauseMode = _param1 != 0;
            break;
        case CheatType::IgnoreRideIntensity:
            gCheatsIgnoreRideIntensity = _param1 != 0;
            break;
        case CheatType::DisableVandalism:
            gCheatsDisableVandalism = _param1 != 0;
            break;
        case CheatType::DisableLittering:
            gCheatsDisableLittering = _param1 != 0;
            break;
        case CheatType::NoMoney:
            SetScenarioNoMoney(_param1 != 0);
            break;
        case CheatType::AddMoney:
            AddMoney(_param1);
            break;
        case CheatType::SetMoney:
            SetMoney(_param1);
            break;
        case CheatType::ClearLoan:
            ClearLoan();
            break;
        case CheatType::SetGuestParameter:
            SetGuestParameter(_param1, _param2);
            break;
        case CheatType::GenerateGuests:
            GenerateGuests(_param1);
            break;
        case CheatType::RemoveAllGuests:
            RemoveAllGuests();
            break;
        case CheatType::GiveAllGuests:
            GiveObjectToGuests(_param1);
            break;
        case CheatType::SetGrassLength:
            SetGrassLength(_param1);
            break;
        case CheatType::WaterPlants:
            WaterPlants();
            break;
        case CheatType::FixVandalism:
            FixVandalism();
            break;
        case CheatType::RemoveLitter:
            RemoveLitter();
            break;
        case CheatType::DisablePlantAging:
            gCheatsDisablePlantAging = _param1 != 0;
            break;
        case CheatType::SetStaffSpeed:
            SetStaffSpeed(_param1);
            break;
        case CheatType::RenewRides:
            RenewRides();
            break;
        case CheatType::MakeDestructible:
            MakeDestructible();
            break;
        case CheatType::FixRides:
            FixBrokenRides();
            break;
        case CheatType::ResetCrashStatus:
            ResetRideCrashStatus();
            break;
        case CheatType::TenMinuteInspections:
            Set10MinuteInspection();
            break;
        case CheatType::WinScenario:
            scenario_success();
            break;
        case CheatType::ForceWeather:
            // Todo - make sure this is safe
            climate_force_weather(WeatherType{ static_cast<uint8_t>(_param1) });
            break;
        case CheatType::FreezeWeather:
            gCheatsFreezeWeather = _param1 != 0;
            break;
        case CheatType::NeverEndingMarketing:
            gCheatsNeverendingMarketing = _param1 != 0;
            break;
        case CheatType::OpenClosePark:
            ParkSetOpen(!park_is_open());
            break;
        case CheatType::HaveFun:
            gScenarioObjective.Type = OBJECTIVE_HAVE_FUN;
            break;
        case CheatType::SetForcedParkRating:
            set_forced_park_rating(_param1);
            break;
        case CheatType::AllowArbitraryRideTypeChanges:
            gCheatsAllowArbitraryRideTypeChanges = _param1 != 0;
            window_invalidate_by_class(WC_RIDE);
            break;
        case CheatType::OwnAllLand:
            OwnAllLand();
            break;
        case CheatType::DisableRideValueAging:
            gCheatsDisableRideValueAging = _param1 != 0;
            break;
        case CheatType::IgnoreResearchStatus:
            gCheatsIgnoreResearchStatus = _param1 != 0;
            break;
        case CheatType::EnableAllDrawableTrackPieces:
            gCheatsEnableAllDrawableTrackPieces = _param1 != 0;
            break;
        case CheatType::CreateDucks:
            CreateDucks(_param1);
            break;
        case CheatType::RemoveDucks:
            Duck::RemoveAll();
            break;
        case CheatType::AllowTrackPlaceInvalidHeights:
            gCheatsAllowTrackPlaceInvalidHeights = _param1 != 0;
            break;
        default:
        {
            log_error("Unabled cheat: %d", _cheatType.id);
            GameActions::Result(GameActions::Status::InvalidParameters, STR_NONE, STR_NONE);
        }
        break;
    }

    if (network_get_mode() == NETWORK_MODE_NONE)
    {
        config_save_default();
    }

    window_invalidate_by_class(WC_CHEATS);
    return GameActions::Result();
}

ParametersRange SetCheatAction::GetParameterRange(CheatType cheatType) const
{
    switch (static_cast<CheatType>(_cheatType.id))
    {
        case CheatType::SandboxMode:
            [[fallthrough]];
        case CheatType::DisableClearanceChecks:
            [[fallthrough]];
        case CheatType::DisableSupportLimits:
            [[fallthrough]];
        case CheatType::ShowAllOperatingModes:
            [[fallthrough]];
        case CheatType::ShowVehiclesFromOtherTrackTypes:
            [[fallthrough]];
        case CheatType::FastLiftHill:
            [[fallthrough]];
        case CheatType::DisableBrakesFailure:
            [[fallthrough]];
        case CheatType::DisableAllBreakdowns:
            [[fallthrough]];
        case CheatType::DisableTrainLengthLimit:
            [[fallthrough]];
        case CheatType::EnableChainLiftOnAllTrack:
            [[fallthrough]];
        case CheatType::BuildInPauseMode:
            [[fallthrough]];
        case CheatType::IgnoreRideIntensity:
            [[fallthrough]];
        case CheatType::DisableVandalism:
            [[fallthrough]];
        case CheatType::DisableLittering:
            [[fallthrough]];
        case CheatType::NoMoney:
            [[fallthrough]];
        case CheatType::DisablePlantAging:
            [[fallthrough]];
        case CheatType::FreezeWeather:
            [[fallthrough]];
        case CheatType::NeverEndingMarketing:
            [[fallthrough]];
        case CheatType::AllowArbitraryRideTypeChanges:
            [[fallthrough]];
        case CheatType::DisableRideValueAging:
            [[fallthrough]];
        case CheatType::IgnoreResearchStatus:
            [[fallthrough]];
        case CheatType::EnableAllDrawableTrackPieces:
            [[fallthrough]];
        case CheatType::OpenClosePark:
            return { { 0, 1 }, { 0, 0 } };
        case CheatType::AddMoney:
            [[fallthrough]];
        case CheatType::SetMoney:
            return { { std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max() }, { 0, 0 } };
        case CheatType::SetGuestParameter:
            switch (_param1)
            {
                case GUEST_PARAMETER_HAPPINESS:
                    return { { GUEST_PARAMETER_HAPPINESS, GUEST_PARAMETER_PREFERRED_RIDE_INTENSITY },
                             { 0, PEEP_MAX_HAPPINESS } };
                case GUEST_PARAMETER_ENERGY:
                    return { { GUEST_PARAMETER_HAPPINESS, GUEST_PARAMETER_PREFERRED_RIDE_INTENSITY },
                             { PEEP_MIN_ENERGY, PEEP_MAX_ENERGY } };
                case GUEST_PARAMETER_HUNGER:
                    return { { GUEST_PARAMETER_HAPPINESS, GUEST_PARAMETER_PREFERRED_RIDE_INTENSITY }, { 0, PEEP_MAX_HUNGER } };
                case GUEST_PARAMETER_THIRST:
                    return { { GUEST_PARAMETER_HAPPINESS, GUEST_PARAMETER_PREFERRED_RIDE_INTENSITY }, { 0, PEEP_MAX_THIRST } };
                case GUEST_PARAMETER_NAUSEA:
                    return { { GUEST_PARAMETER_HAPPINESS, GUEST_PARAMETER_PREFERRED_RIDE_INTENSITY }, { 0, PEEP_MAX_NAUSEA } };
                case GUEST_PARAMETER_NAUSEA_TOLERANCE:
                    return { { GUEST_PARAMETER_HAPPINESS, GUEST_PARAMETER_PREFERRED_RIDE_INTENSITY },
                             { EnumValue(PeepNauseaTolerance::None), EnumValue(PeepNauseaTolerance::High) } };
                case GUEST_PARAMETER_TOILET:
                    return { { GUEST_PARAMETER_HAPPINESS, GUEST_PARAMETER_PREFERRED_RIDE_INTENSITY }, { 0, PEEP_MAX_TOILET } };
                case GUEST_PARAMETER_PREFERRED_RIDE_INTENSITY:
                    return { { GUEST_PARAMETER_HAPPINESS, GUEST_PARAMETER_PREFERRED_RIDE_INTENSITY }, { 0, 255 } };
                default:
                    return { { 0, 0 }, { 0, 0 } };
            }
        case CheatType::GenerateGuests:
            return { { 1, 10000 }, { 0, 0 } };
        case CheatType::GiveAllGuests:
            return { { OBJECT_MONEY, OBJECT_UMBRELLA }, { 0, 0 } };
        case CheatType::SetGrassLength:
            return { { 0, 7 }, { 0, 0 } };
        case CheatType::SetStaffSpeed:
            return { { 0, 255 }, { 0, 0 } };
        case CheatType::ForceWeather:
            return { { 0, EnumValue(WeatherType::Count) - 1 }, { 0, 0 } };
        case CheatType::SetForcedParkRating:
            return { { 0, 999 }, { 0, 0 } };
        case CheatType::CreateDucks:
            return { { 0, 100 }, { 0, 0 } };
        default:
            return { { 0, 0 }, { 0, 0 } };
    }
}

void SetCheatAction::SetGrassLength(int32_t length) const
{
    for (int32_t y = 0; y < MAXIMUM_MAP_SIZE_TECHNICAL; y++)
    {
        for (int32_t x = 0; x < MAXIMUM_MAP_SIZE_TECHNICAL; x++)
        {
            auto surfaceElement = map_get_surface_element_at(TileCoordsXY{ x, y }.ToCoordsXY());
            if (surfaceElement == nullptr)
                continue;

            if (surfaceElement != nullptr && (surfaceElement->GetOwnership() & OWNERSHIP_OWNED)
                && surfaceElement->GetWaterHeight() == 0 && surfaceElement->CanGrassGrow())
            {
                surfaceElement->SetGrassLength(length);
            }
        }
    }

    gfx_invalidate_screen();
}

void SetCheatAction::WaterPlants() const
{
    tile_element_iterator it;

    tile_element_iterator_begin(&it);
    do
    {
        if (it.element->GetType() == TileElementType::SmallScenery)
        {
            it.element->AsSmallScenery()->SetAge(0);
        }
    } while (tile_element_iterator_next(&it));

    gfx_invalidate_screen();
}

void SetCheatAction::FixVandalism() const
{
    tile_element_iterator it;

    tile_element_iterator_begin(&it);
    do
    {
        if (it.element->GetType() != TileElementType::Path)
            continue;

        if (!(it.element)->AsPath()->HasAddition())
            continue;

        it.element->AsPath()->SetIsBroken(false);
    } while (tile_element_iterator_next(&it));

    gfx_invalidate_screen();
}

void SetCheatAction::RemoveLitter() const
{
    for (auto litter : EntityList<Litter>())
    {
        EntityRemove(litter);
    }

    tile_element_iterator it{};
    tile_element_iterator_begin(&it);
    do
    {
        if (it.element->GetType() != TileElementType::Path)
            continue;

        auto* path = it.element->AsPath();
        if (!path->HasAddition())
            continue;

        auto* pathBitEntry = path->GetAdditionEntry();
        if (pathBitEntry != nullptr && pathBitEntry->flags & PATH_BIT_FLAG_IS_BIN)
            path->SetAdditionStatus(0xFF);

    } while (tile_element_iterator_next(&it));

    gfx_invalidate_screen();
}

void SetCheatAction::FixBrokenRides() const
{
    for (auto& ride : GetRideManager())
    {
        if ((ride.mechanic_status != RIDE_MECHANIC_STATUS_FIXING)
            && (ride.lifecycle_flags & (RIDE_LIFECYCLE_BREAKDOWN_PENDING | RIDE_LIFECYCLE_BROKEN_DOWN)))
        {
            auto mechanic = ride_get_assigned_mechanic(&ride);
            if (mechanic != nullptr)
            {
                mechanic->RemoveFromRide();
            }

            ride_fix_breakdown(&ride, 0);
            ride.window_invalidate_flags |= RIDE_INVALIDATE_RIDE_MAIN | RIDE_INVALIDATE_RIDE_LIST;
        }
    }
}

void SetCheatAction::RenewRides() const
{
    for (auto& ride : GetRideManager())
    {
        ride.Renew();
    }
    window_invalidate_by_class(WC_RIDE);
}

void SetCheatAction::MakeDestructible() const
{
    for (auto& ride : GetRideManager())
    {
        ride.lifecycle_flags &= ~RIDE_LIFECYCLE_INDESTRUCTIBLE;
        ride.lifecycle_flags &= ~RIDE_LIFECYCLE_INDESTRUCTIBLE_TRACK;
    }
    window_invalidate_by_class(WC_RIDE);
}

void SetCheatAction::ResetRideCrashStatus() const
{
    for (auto& ride : GetRideManager())
    {
        // Reset crash status and history
        ride.lifecycle_flags &= ~RIDE_LIFECYCLE_CRASHED;
        ride.last_crash_type = RIDE_CRASH_TYPE_NONE;
    }
    window_invalidate_by_class(WC_RIDE);
}

void SetCheatAction::Set10MinuteInspection() const
{
    for (auto& ride : GetRideManager())
    {
        // Set inspection interval to 10 minutes
        ride.inspection_interval = RIDE_INSPECTION_EVERY_10_MINUTES;
    }
    window_invalidate_by_class(WC_RIDE);
}

void SetCheatAction::SetScenarioNoMoney(bool enabled) const
{
    if (enabled)
    {
        gParkFlags |= PARK_FLAGS_NO_MONEY;
    }
    else
    {
        gParkFlags &= ~PARK_FLAGS_NO_MONEY;
    }
    // Invalidate all windows that have anything to do with finance
    window_invalidate_by_class(WC_RIDE);
    window_invalidate_by_class(WC_PEEP);
    window_invalidate_by_class(WC_PARK_INFORMATION);
    window_invalidate_by_class(WC_FINANCES);
    window_invalidate_by_class(WC_BOTTOM_TOOLBAR);
    window_invalidate_by_class(WC_TOP_TOOLBAR);
    window_invalidate_by_class(WC_CHEATS);
}

void SetCheatAction::SetMoney(money32 amount) const
{
    gCash = amount;

    window_invalidate_by_class(WC_FINANCES);
    window_invalidate_by_class(WC_BOTTOM_TOOLBAR);
}

void SetCheatAction::AddMoney(money32 amount) const
{
    gCash = add_clamp_money32(gCash, amount);

    window_invalidate_by_class(WC_FINANCES);
    window_invalidate_by_class(WC_BOTTOM_TOOLBAR);
}

void SetCheatAction::ClearLoan() const
{
    // First give money
    AddMoney(gBankLoan);

    // Then pay the loan
    auto gameAction = ParkSetLoanAction(0.00_GBP);
    GameActions::ExecuteNested(&gameAction);
}

void SetCheatAction::GenerateGuests(int32_t count) const
{
    auto& park = OpenRCT2::GetContext()->GetGameState()->GetPark();
    for (int32_t i = 0; i < count; i++)
    {
        park.GenerateGuest();
    }
    window_invalidate_by_class(WC_BOTTOM_TOOLBAR);
}

void SetCheatAction::SetGuestParameter(int32_t parameter, int32_t value) const
{
    for (auto peep : EntityList<Guest>())
    {
        switch (parameter)
        {
            case GUEST_PARAMETER_HAPPINESS:
                peep->Happiness = value;
                peep->HappinessTarget = value;
                // Clear the 'red-faced with anger' status if we're making the guest happy
                if (value > 0)
                {
                    peep->PeepFlags &= ~PEEP_FLAGS_ANGRY;
                    peep->Angriness = 0;
                }
                break;
            case GUEST_PARAMETER_ENERGY:
                peep->Energy = value;
                peep->EnergyTarget = value;
                break;
            case GUEST_PARAMETER_HUNGER:
                peep->Hunger = value;
                break;
            case GUEST_PARAMETER_THIRST:
                peep->Thirst = value;
                break;
            case GUEST_PARAMETER_NAUSEA:
                peep->Nausea = value;
                peep->NauseaTarget = value;
                break;
            case GUEST_PARAMETER_NAUSEA_TOLERANCE:
                peep->NauseaTolerance = static_cast<PeepNauseaTolerance>(value);
                break;
            case GUEST_PARAMETER_TOILET:
                peep->Toilet = value;
                break;
            case GUEST_PARAMETER_PREFERRED_RIDE_INTENSITY:
                peep->Intensity = IntensityRange(value, 15);
                break;
        }
        peep->UpdateSpriteType();
    }
}

void SetCheatAction::GiveObjectToGuests(int32_t object) const
{
    for (auto peep : EntityList<Guest>())
    {
        switch (object)
        {
            case OBJECT_MONEY:
                peep->CashInPocket = 1000.00_GBP;
                break;
            case OBJECT_PARK_MAP:
                peep->GiveItem(ShopItem::Map);
                break;
            case OBJECT_BALLOON:
                peep->GiveItem(ShopItem::Balloon);
                peep->BalloonColour = scenario_rand_max(COLOUR_COUNT - 1);
                peep->UpdateSpriteType();
                break;
            case OBJECT_UMBRELLA:
                peep->GiveItem(ShopItem::Umbrella);
                peep->UmbrellaColour = scenario_rand_max(COLOUR_COUNT - 1);
                peep->UpdateSpriteType();
                break;
        }
    }
    window_invalidate_by_class(WC_PEEP);
}

void SetCheatAction::RemoveAllGuests() const
{
    for (auto& ride : GetRideManager())
    {
        ride.num_riders = 0;

        for (auto& station : ride.GetStations())
        {
            station.QueueLength = 0;
            station.LastPeepInQueue = EntityId::GetNull();
        }

        for (auto trainIndex : ride.vehicles)
        {
            for (Vehicle* vehicle = TryGetEntity<Vehicle>(trainIndex); vehicle != nullptr;
                 vehicle = TryGetEntity<Vehicle>(vehicle->next_vehicle_on_train))
            {
                for (auto& peepInTrainIndex : vehicle->peep)
                {
                    auto peep = TryGetEntity<Guest>(peepInTrainIndex);
                    if (peep != nullptr)
                    {
                        if ((peep->State == PeepState::OnRide && peep->RideSubState == PeepRideSubState::OnRide)
                            || (peep->State == PeepState::LeavingRide && peep->RideSubState == PeepRideSubState::LeaveVehicle))
                        {
                            vehicle->ApplyMass(-peep->Mass);
                        }
                    }
                    peepInTrainIndex = EntityId::GetNull();
                }

                vehicle->num_peeps = 0;
                vehicle->next_free_seat = 0;
            }
        }
    }

    // Do not use the FOR_ALL_PEEPS macro for this as next sprite index
    // will be fetched on a deleted guest.
    for (auto guest : EntityList<Guest>())
    {
        guest->Remove();
    }

    window_invalidate_by_class(WC_RIDE);
    gfx_invalidate_screen();
}

void SetCheatAction::SetStaffSpeed(uint8_t value) const
{
    for (auto peep : EntityList<Staff>())
    {
        peep->Energy = value;
        peep->EnergyTarget = value;
    }
}

void SetCheatAction::OwnAllLand() const
{
    const auto min = CoordsXY{ COORDS_XY_STEP, COORDS_XY_STEP };
    const auto max = GetMapSizeUnits() - CoordsXY{ COORDS_XY_STEP, COORDS_XY_STEP };

    for (CoordsXY coords = min; coords.y <= max.y; coords.y += COORDS_XY_STEP)
    {
        for (coords.x = min.x; coords.x <= max.x; coords.x += COORDS_XY_STEP)
        {
            auto* surfaceElement = map_get_surface_element_at(coords);
            if (surfaceElement == nullptr)
                continue;

            // Ignore already owned tiles.
            if (surfaceElement->GetOwnership() & OWNERSHIP_OWNED)
                continue;

            int32_t baseZ = surfaceElement->GetBaseZ();
            int32_t destOwnership = check_max_allowable_land_rights_for_tile({ coords, baseZ });

            // only own tiles that were not set to 0
            if (destOwnership != OWNERSHIP_UNOWNED)
            {
                surfaceElement->SetOwnership(destOwnership);
                update_park_fences_around_tile(coords);
                map_invalidate_tile({ coords, baseZ, baseZ + 16 });
            }
        }
    }

    // Completely unown peep spawn points
    for (const auto& spawn : gPeepSpawns)
    {
        auto* surfaceElement = map_get_surface_element_at(spawn);
        if (surfaceElement != nullptr)
        {
            surfaceElement->SetOwnership(OWNERSHIP_UNOWNED);
            update_park_fences_around_tile(spawn);
            uint16_t baseZ = surfaceElement->GetBaseZ();
            map_invalidate_tile({ spawn, baseZ, baseZ + 16 });
        }
    }

    map_count_remaining_land_rights();
}

void SetCheatAction::ParkSetOpen(bool isOpen) const
{
    auto parkSetParameter = ParkSetParameterAction(isOpen ? ParkParameter::Open : ParkParameter::Close);
    GameActions::ExecuteNested(&parkSetParameter);
}

void SetCheatAction::CreateDucks(int count) const
{
    for (int i = 0; i < count; i++)
    {
        // 100 attempts at finding some water to create a few ducks at
        for (int32_t attempts = 0; attempts < 100; attempts++)
        {
            if (scenario_create_ducks())
                break;
        }
    }
}
