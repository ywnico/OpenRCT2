/*****************************************************************************
 * Copyright (c) 2014-2020 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "../../entity/EntityRegistry.h"
#include "../../interface/Viewport.h"
#include "../../paint/Paint.h"
#include "../../paint/Supports.h"
#include "../Ride.h"
#include "../RideEntry.h"
#include "../Track.h"
#include "../TrackPaint.h"
#include "../Vehicle.h"

static constexpr const uint32_t MerryGoRoundRiderOffsets[] = {
    0, 32, 64, 96, 16, 48, 80, 112,
};

static constexpr const uint16_t MerryGoRoundBreakdownVibration[] = {
    0, 1, 2, 3, 4, 3, 2, 1, 0, 0,
};

static void PaintRiders(
    paint_session& session, const Ride& ride, const rct_ride_entry& rideEntry, const Vehicle& vehicle, int32_t rotationOffset,
    const CoordsXYZ& offset, const CoordsXYZ& bbLength, const CoordsXYZ& bbOffset)
{
    if (session.DPI.zoom_level > ZoomLevel{ 0 })
        return;
    if (!(ride.lifecycle_flags & RIDE_LIFECYCLE_ON_TRACK))
        return;

    for (int32_t peep = 0; peep <= 14; peep += 2)
    {
        if (vehicle.num_peeps <= peep)
            break;

        auto imageOffset = (MerryGoRoundRiderOffsets[peep / 2] + rotationOffset) % 128;
        imageOffset -= 13;
        if (imageOffset >= 68)
            continue;

        auto imageIndex = rideEntry.Cars[0].base_image_id + 32 + imageOffset;
        auto imageId = ImageId(imageIndex, vehicle.peep_tshirt_colours[peep], vehicle.peep_tshirt_colours[peep + 1])
            .WithSkintone(vehicle.peep_skintones[peep]);
        PaintAddImageAsChild(session, imageId, offset, bbLength, bbOffset);
    }
}

static void PaintCarousel(
    paint_session& session, const Ride& ride, uint8_t direction, int8_t xOffset, int8_t yOffset, uint16_t height)
{
    height += 7;

    auto rideEntry = ride.GetRideEntry();
    if (rideEntry == nullptr)
        return;

    auto vehicle = GetEntity<Vehicle>(ride.vehicles[0]);
    if (ride.lifecycle_flags & RIDE_LIFECYCLE_ON_TRACK && vehicle != nullptr)
    {
        session.InteractionType = ViewportInteractionItem::Entity;
        session.CurrentlyDrawnEntity = vehicle;

        if (ride.lifecycle_flags & (RIDE_LIFECYCLE_BREAKDOWN_PENDING | RIDE_LIFECYCLE_BROKEN_DOWN)
            && ride.breakdown_reason_pending == BREAKDOWN_CONTROL_FAILURE && ride.breakdown_sound_modifier >= 128)
        {
            height += MerryGoRoundBreakdownVibration[(vehicle->current_time >> 1) & 7];
        }
    }

    auto rotationOffset = 0;
    if (vehicle != nullptr)
    {
        auto rotation = ((vehicle->sprite_direction >> 3) + session.CurrentRotation) << 5;
        rotationOffset = (vehicle->Pitch + rotation) % 128;
    }

    CoordsXYZ offset(xOffset, yOffset, height);
    CoordsXYZ bbLength(24, 24, 48);
    CoordsXYZ bbOffset(xOffset + 16, yOffset + 16, height);

    auto imageTemplate = ImageId(0, ride.vehicle_colours[0].Body, ride.vehicle_colours[0].Trim);
    auto imageFlags = session.TrackColours[SCHEME_MISC];
    if (imageFlags != IMAGE_TYPE_REMAP)
    {
        imageTemplate = ImageId::FromUInt32(imageFlags);
    }
    auto imageOffset = rotationOffset & 0x1F;
    auto imageId = imageTemplate.WithIndex(rideEntry->Cars[0].base_image_id + imageOffset);
    PaintAddImageAsParent(session, imageId, offset, bbLength, bbOffset);

    PaintRiders(session, ride, *rideEntry, *vehicle, rotationOffset, offset, bbLength, bbOffset);

    session.CurrentlyDrawnEntity = nullptr;
    session.InteractionType = ViewportInteractionItem::Ride;
}

static void PaintMerryGoRound(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = track_map_3x3[direction][trackSequence];

    int32_t edges = edges_3x3[trackSequence];

    wooden_a_supports_paint_setup(session, (direction & 1), 0, height, session.TrackColours[SCHEME_MISC]);

    const StationObject* stationObject = ride.GetStationObject();

    track_paint_util_paint_floor(session, edges, session.TrackColours[SCHEME_TRACK], height, floorSpritesCork, stationObject);

    track_paint_util_paint_fences(
        session, edges, session.MapPosition, trackElement, ride, session.TrackColours[SCHEME_MISC], height, fenceSpritesRope,
        session.CurrentRotation);

    switch (trackSequence)
    {
        case 1:
            PaintCarousel(session, ride, direction, 32, 32, height);
            break;
        case 3:
            PaintCarousel(session, ride, direction, 32, -32, height);
            break;
        case 5:
            PaintCarousel(session, ride, direction, 0, -32, height);
            break;
        case 6:
            PaintCarousel(session, ride, direction, -32, 32, height);
            break;
        case 7:
            PaintCarousel(session, ride, direction, -32, -32, height);
            break;
        case 8:
            PaintCarousel(session, ride, direction, -32, 0, height);
            break;
    }

    int32_t cornerSegments = 0;
    switch (trackSequence)
    {
        case 1:
            // top
            cornerSegments = SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC;
            break;
        case 3:
            // right
            cornerSegments = SEGMENT_CC | SEGMENT_BC | SEGMENT_D4;
            break;
        case 6:
            // left
            cornerSegments = SEGMENT_C8 | SEGMENT_B8 | SEGMENT_D0;
            break;
        case 7:
            // bottom
            cornerSegments = SEGMENT_D0 | SEGMENT_C0 | SEGMENT_D4;
            break;
    }

    paint_util_set_segment_support_height(session, cornerSegments, height + 2, 0x20);
    paint_util_set_segment_support_height(session, SEGMENTS_ALL & ~cornerSegments, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 64, 0x20);
}

TRACK_PAINT_FUNCTION get_track_paint_function_merry_go_round(int32_t trackType)
{
    if (trackType != TrackElemType::FlatTrack3x3)
    {
        return nullptr;
    }

    return PaintMerryGoRound;
}
