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
#include "../../object/StationObject.h"
#include "../../paint/Paint.h"
#include "../../paint/Supports.h"
#include "../Ride.h"
#include "../RideEntry.h"
#include "../Track.h"
#include "../TrackPaint.h"
#include "../Vehicle.h"

enum class Plane
{
    Back,
    Front,
};

enum
{
    SPR_MAGIC_CARPET_FRAME_NW = 22002,
    SPR_MAGIC_CARPET_FRAME_SE = 22003,
    SPR_MAGIC_CARPET_FRAME_NE = 22004,
    SPR_MAGIC_CARPET_FRAME_SW = 22005,
    SPR_MAGIC_CARPET_PENDULUM_NW = 22006,
    SPR_MAGIC_CARPET_PENDULUM_NE = 22038,
    SPR_MAGIC_CARPET_PENDULUM_SE = 22070,
    SPR_MAGIC_CARPET_PENDULUM_SW = 22102,
};

struct bound_box
{
    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;
};

static constexpr const int16_t MagicCarpetOscillationZ[] = {
    -2, -1, 1, 5, 10, 16, 23, 30, 37, 45, 52, 59, 65, 70, 74, 76, 77, 76, 74, 70, 65, 59, 52, 45, 37, 30, 23, 16, 10, 5, 1, -1,
};

static constexpr const int8_t MagicCarpetOscillationXY[] = {
    0, 6,  12,  18,  23,  27,  30,  31,  32,  31,  30,  27,  23,  18,  12,  6,
    0, -5, -11, -17, -22, -26, -29, -30, -31, -30, -29, -26, -22, -17, -11, -5,
};

static constexpr const bound_box MagicCarpetBounds[] = {
    { 0, 8, 32, 16 },
    { 8, 0, 16, 32 },
    { 0, 8, 32, 16 },
    { 8, 0, 16, 32 },
};

static ImageIndex GetMagicCarpetFrameImage(Plane plane, Direction direction)
{
    if (direction & 1)
    {
        return plane == Plane::Back ? SPR_MAGIC_CARPET_FRAME_NE : SPR_MAGIC_CARPET_FRAME_SW;
    }
    else
    {
        return plane == Plane::Back ? SPR_MAGIC_CARPET_FRAME_NW : SPR_MAGIC_CARPET_FRAME_SE;
    }
}

static ImageIndex GetMagicCarpetPendulumImage(Plane plane, Direction direction, int32_t swing)
{
    ImageIndex imageIndex;
    if (direction & 1)
    {
        imageIndex = plane == Plane::Back ? SPR_MAGIC_CARPET_PENDULUM_NE : SPR_MAGIC_CARPET_PENDULUM_SW;
    }
    else
    {
        imageIndex = plane == Plane::Back ? SPR_MAGIC_CARPET_PENDULUM_NW : SPR_MAGIC_CARPET_PENDULUM_SE;
    }
    if (direction & 2)
    {
        imageIndex += (0 - swing) & 31;
    }
    else
    {
        imageIndex += swing;
    }
    return imageIndex;
}

static Vehicle* GetFirstVehicle(const Ride& ride)
{
    if (ride.lifecycle_flags & RIDE_LIFECYCLE_ON_TRACK)
    {
        return GetEntity<Vehicle>(ride.vehicles[0]);
    }
    return nullptr;
}

static void PaintMagicCarpetRiders(
    paint_session& session, const rct_ride_entry& rideEntry, const Vehicle& vehicle, Direction direction,
    const CoordsXYZ& offset, const CoordsXYZ& bbOffset, const CoordsXYZ& bbSize)
{
    if (session.DPI.zoom_level > ZoomLevel{ 1 })
        return;

    auto baseImageIndex = rideEntry.Cars[0].base_image_id + 4 + direction;
    for (uint8_t peepIndex = 0; peepIndex < vehicle.num_peeps; peepIndex += 2)
    {
        auto imageIndex = baseImageIndex + (peepIndex * 2);
        auto imageId = ImageId(
            imageIndex, vehicle.peep_tshirt_colours[peepIndex + 0], vehicle.peep_tshirt_colours[peepIndex + 1])
            .WithSkintone(vehicle.peep_skintones[peepIndex + 0]);
        PaintAddImageAsChild(session, imageId, offset, bbSize, bbOffset);
    }
}

static void PaintMagicCarpetFrame(
    paint_session& session, Plane plane, Direction direction, const CoordsXYZ& offset, const CoordsXYZ& bbOffset,
    const CoordsXYZ& bbSize)
{
    auto imageIndex = GetMagicCarpetFrameImage(plane, direction);
    auto imageTemplate = ImageId::FromUInt32(session.TrackColours[SCHEME_TRACK]);
    auto imageId = imageTemplate.WithIndex(imageIndex);
    if (plane == Plane::Back)
    {
        PaintAddImageAsParent(session, imageId, offset, bbSize, bbOffset);
    }
    else
    {
        PaintAddImageAsChild(session, imageId, offset, bbSize, bbOffset);
    }
}

static void PaintMagicCarpetPendulum(
    paint_session& session, Plane plane, int32_t swing, Direction direction, const CoordsXYZ& offset, const CoordsXYZ& bbOffset,
    const CoordsXYZ& bbSize)
{
    auto imageIndex = GetMagicCarpetPendulumImage(plane, direction, swing);
    auto imageTemplate = ImageId::FromUInt32(session.TrackColours[SCHEME_TRACK]);
    auto imageId = imageTemplate.WithIndex(imageIndex);
    PaintAddImageAsChild(session, imageId, offset, bbSize, bbOffset);
}

static void PaintMagicCarpetVehicle(
    paint_session& session, const Ride& ride, uint8_t direction, int32_t swing, CoordsXYZ offset, const CoordsXYZ& bbOffset,
    const CoordsXYZ& bbSize)
{
    const auto* rideEntry = ride.GetRideEntry();
    if (rideEntry == nullptr)
        return;

    auto directionalOffset = MagicCarpetOscillationXY[swing];
    switch (direction)
    {
        case 0:
            offset.x -= directionalOffset;
            break;
        case 1:
            offset.y += directionalOffset;
            break;
        case 2:
            offset.x += directionalOffset;
            break;
        case 3:
            offset.y -= directionalOffset;
            break;
    }
    offset.z += MagicCarpetOscillationZ[swing];

    // Vehicle
    auto imageTemplate = ImageId(0, ride.vehicle_colours[0].Body, ride.vehicle_colours[0].Trim);
    auto imageFlags = session.TrackColours[SCHEME_MISC];
    if (imageFlags != IMAGE_TYPE_REMAP)
    {
        imageTemplate = ImageId::FromUInt32(imageFlags);
    }
    auto vehicleImageIndex = rideEntry->Cars[0].base_image_id + direction;
    PaintAddImageAsChild(session, imageTemplate.WithIndex(vehicleImageIndex), offset, bbSize, bbOffset);

    auto* vehicle = GetFirstVehicle(ride);
    if (vehicle != nullptr)
    {
        PaintMagicCarpetRiders(session, *rideEntry, *vehicle, direction, offset, bbOffset, bbSize);
    }
}

static void PaintMagicCarpetStructure(
    paint_session& session, const Ride& ride, uint8_t direction, int8_t axisOffset, uint16_t height)
{
    auto swing = 0;
    auto* vehicle = GetFirstVehicle(ride);
    if (vehicle != nullptr)
    {
        swing = vehicle->Pitch;
        session.InteractionType = ViewportInteractionItem::Entity;
        session.CurrentlyDrawnEntity = vehicle;
    }

    bound_box bb = MagicCarpetBounds[direction];
    CoordsXYZ offset, bbOffset, bbSize;
    offset.x = (direction & 1) ? 0 : axisOffset;
    offset.y = (direction & 1) ? axisOffset : 0;
    offset.z = height + 7;
    bbOffset.x = bb.x;
    bbOffset.y = bb.y;
    bbOffset.z = height + 7;
    bbSize.x = bb.width;
    bbSize.y = bb.height;
    bbSize.z = 127;

    PaintMagicCarpetFrame(session, Plane::Back, direction, offset, bbOffset, bbSize);
    PaintMagicCarpetPendulum(session, Plane::Back, swing, direction, offset, bbOffset, bbSize);
    PaintMagicCarpetVehicle(session, ride, direction, swing, offset, bbOffset, bbSize);
    PaintMagicCarpetPendulum(session, Plane::Front, swing, direction, offset, bbOffset, bbSize);
    PaintMagicCarpetFrame(session, Plane::Front, direction, offset, bbOffset, bbSize);

    session.CurrentlyDrawnEntity = nullptr;
    session.InteractionType = ViewportInteractionItem::Ride;
}

static void PaintMagicCarpet(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    uint8_t relativeTrackSequence = track_map_1x4[direction][trackSequence];

    // The end tiles do not have a platform
    switch (relativeTrackSequence)
    {
        case 0:
        case 2:
            if (direction & 1)
            {
                metal_a_supports_paint_setup(
                    session, METAL_SUPPORTS_TUBES, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                metal_a_supports_paint_setup(
                    session, METAL_SUPPORTS_TUBES, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
            }
            else
            {
                metal_a_supports_paint_setup(
                    session, METAL_SUPPORTS_TUBES, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                metal_a_supports_paint_setup(
                    session, METAL_SUPPORTS_TUBES, 8, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
            }
            const StationObject* stationObject = ride.GetStationObject();

            if (stationObject != nullptr && !(stationObject->Flags & STATION_OBJECT_FLAGS::NO_PLATFORMS))
            {
                uint32_t imageId = SPR_STATION_BASE_D | session.TrackColours[SCHEME_SUPPORTS];
                PaintAddImageAsParent(session, imageId, { 0, 0, height }, { 32, 32, 1 });
            }
            break;
    }

    switch (relativeTrackSequence)
    {
        case 3:
            PaintMagicCarpetStructure(session, ride, direction, -48, height);
            break;
        case 0:
            PaintMagicCarpetStructure(session, ride, direction, -16, height);
            break;
        case 2:
            PaintMagicCarpetStructure(session, ride, direction, 16, height);
            break;
        case 1:
            PaintMagicCarpetStructure(session, ride, direction, 48, height);
            break;
    }

    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 176, 0x20);
}

TRACK_PAINT_FUNCTION get_track_paint_function_magic_carpet(int32_t trackType)
{
    switch (trackType)
    {
        case TrackElemType::FlatTrack1x4A:
            return PaintMagicCarpet;
    }
    return nullptr;
}
