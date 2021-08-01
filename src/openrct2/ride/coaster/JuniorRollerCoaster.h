/*****************************************************************************
 * Copyright (c) 2014-2020 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#ifndef _JUNIOR_ROLLER_COASTER_H
#define _JUNIOR_ROLLER_COASTER_H

#include "../../common.h"
#include "../../paint/tile_element/Paint.TileElement.h"

enum class JuniorRcChainType : uint8_t
{
    None,
    FrictionWheels,
    ChainLift,
};

struct Ride;

void junior_rc_paint_station(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, uint8_t rideType);

void junior_rc_paint_track_flat(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_25_deg_up(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_60_deg_up(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_flat_to_25_deg_up(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_25_deg_up_to_60_deg_up(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_60_deg_up_to_25_deg_up(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_25_deg_up_to_flat(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);

void junior_rc_paint_track_left_quarter_turn_5_tiles_25_deg_up(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_right_quarter_turn_5_tiles_25_deg_up(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);

void junior_rc_paint_track_right_quarter_turn_3_tiles_25_deg_up(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_right_quarter_turn_3_tiles_25_deg_down(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);

void junior_rc_paint_track_diag_flat(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_diag_25_deg_up(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_diag_60_deg_up(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_diag_flat_to_25_deg_up(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_diag_flat_to_60_deg_up(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_diag_25_deg_up_to_60_deg_up(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_diag_60_deg_up_to_25_deg_up(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_diag_25_deg_up_to_flat(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_diag_60_deg_up_to_flat(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_diag_25_deg_down(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_diag_60_deg_down(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_diag_flat_to_25_deg_down(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_diag_flat_to_60_deg_down(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_diag_25_deg_down_to_60_deg_down(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_diag_60_deg_down_to_25_deg_down(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_diag_25_deg_down_to_flat(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);
void junior_rc_paint_track_diag_60_deg_down_to_flat(
    paint_session* session, const Ride* ride, uint8_t trackSequence, uint8_t direction, uint16_t height,
    const TileElement* tileElement, JuniorRcChainType chainType);

#endif // _JUNIOR_ROLLER_COASTER_H
