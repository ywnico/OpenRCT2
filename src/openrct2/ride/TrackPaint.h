/*****************************************************************************
 * Copyright (c) 2014-2020 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#pragma once

#include "../common.h"
#include "../paint/Paint.h"
#include "../paint/tile_element/Paint.TileElement.h"
#include "../world/Map.h"

class StationObject;

extern const uint8_t track_map_2x2[][4];
extern const uint8_t edges_2x2[];

extern const uint8_t track_map_3x3[][9];
extern const uint8_t edges_3x3[];

extern const uint8_t track_map_4x4[][16];
extern const uint8_t edges_4x4[];

extern const uint8_t track_map_1x4[][4];

enum
{
    SPR_FLOOR_PLANKS = 3395,
    SPR_FLOOR_PLANKS_90_DEG = 3396,
    SPR_FLOOR_PLANKS_SLOPE_NE_SW = 3397,
    SPR_FLOOR_PLANKS_SLOPE_SE_NW = 3398,
    SPR_FLOOR_PLANKS_SLOPE_SW_NE = 3399,
    SPR_FLOOR_PLANKS_SLOPE_NW_SE = 3400,
    SPR_FLOOR_PLANKS_N_SEGMENT = 3401,
    SPR_FLOOR_PLANKS_E_SEGMENT = 3402,
    SPR_FLOOR_PLANKS_S_SEGMENT = 3403,
    SPR_FLOOR_PLANKS_W_SEGMENT = 3404,
    SPR_FLOOR_METAL = 14567,
    SPR_FENCE_METAL_NE = 14568,
    SPR_FENCE_METAL_SE = 14569,
    SPR_FENCE_METAL_SW = 14570,
    SPR_FENCE_METAL_NW = 14571,

    SPR_FLOOR_METAL_B = 14989,
    SPR_FENCE_METAL_B_NE = 14990,
    SPR_FENCE_METAL_B_SE = 14991,
    SPR_FENCE_METAL_B_SW = 14992,
    SPR_FENCE_METAL_B_NW = 14993,

    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_NE_SW = 16870,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_SE_NW = 16871,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_SW_SE_PART_0 = 16872,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_SW_SE_PART_1 = 16873,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_SW_SE_PART_2 = 16874,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_NW_SW_PART_0 = 16875,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_NW_SW_PART_1 = 16876,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_NW_SW_PART_2 = 16877,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_NE_NW_PART_0 = 16878,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_NE_NW_PART_1 = 16879,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_NE_NW_PART_2 = 16880,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_SE_NE_PART_0 = 16881,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_SE_NE_PART_1 = 16882,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_3_TILES_SE_NE_PART_2 = 16883,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_TO_25_DEG_UP_SW_NE = 16884,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_TO_25_DEG_UP_NW_SE = 16885,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_TO_25_DEG_UP_NE_SW = 16886,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_TO_25_DEG_UP_SE_NW = 16887,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_TO_FLAT_SW_NE = 16888,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_TO_FLAT_NW_SE = 16889,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_TO_FLAT_NE_SW = 16890,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_TO_FLAT_SE_NW = 16891,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_SW_NE = 16892,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_NW_SE = 16893,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_NE_SW = 16894,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_SE_NW = 16895,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_1_TILE_SW_NW = 16896,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_1_TILE_NW_NE = 16897,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_1_TILE_NE_SE = 16898,
    SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_QUARTER_TURN_1_TILE_SE_SW = 16899,

    SPR_FLOOR_CORK_SE_SW = 22134,
    SPR_FLOOR_CORK_SW = 22135,
    SPR_FLOOR_CORK_SE = 22136,
    SPR_FLOOR_CORK = 22137,
    SPR_FENCE_ROPE_NE = 22138,
    SPR_FENCE_ROPE_SE = 22139,
    SPR_FENCE_ROPE_SW = 22140,
    SPR_FENCE_ROPE_NW = 22141,

    SPR_STATION_PLATFORM_SW_NE = 22362,
    SPR_STATION_PLATFORM_NW_SE = 22363,
    SPR_STATION_PLATFORM_FENCED_SW_NE = 22364,
    SPR_STATION_PLATFORM_FENCED_NW_SE = 22365,
    SPR_STATION_PLATFORM_BEGIN_FENCED_SW_NE = 22366,
    SPR_STATION_PLATFORM_BEGIN_FENCED_NW_SE = 22367,
    SPR_STATION_PLATFORM_BEGIN_SW_NE = 22368,
    SPR_STATION_PLATFORM_BEGIN_NW_SE = 22369,
    SPR_STATION_FENCE_SW_NE = 22370,
    SPR_STATION_FENCE_NW_SE = 22371,
    SPR_STATION_BEGIN_ANGLE_FENCE_SW_NE = 22372,
    SPR_STATION_BEGIN_ANGLE_FENCE_NW_SE = 22373,
    SPR_STATION_FENCE_SMALL_NW_SE = 22374,
    SPR_STATION_FENCE_SMALL_SW_NE = 22375,

    SPR_STATION_PLATFORM_FENCED_END_RED_LIGHT_SW_NE = 22380,
    SPR_STATION_PLATFORM_FENCED_END_RED_LIGHT_NW_SE = 22381,
    SPR_STATION_PLATFORM_FENCED_END_GREEN_LIGHT_SW_NE = 22382,
    SPR_STATION_PLATFORM_FENCED_END_GREEN_LIGHT_NW_SE = 22383,
    SPR_STATION_LIGHT_BACK_NE_SW = 22384,
    SPR_STATION_LIGHT_BACK_NW_SE = 22385,
    SPR_STATION_LIGHT_BACK_ANGLE_FENCED_NE_SW = 22386,
    SPR_STATION_LIGHT_BACK_ANGLE_FENCED_NW_SE = 22387,
    SPR_STATION_PLATFORM_END_RED_LIGHT_SW_NE = 22388,
    SPR_STATION_PLATFORM_END_RED_LIGHT_NW_SE = 22389,
    SPR_STATION_PLATFORM_END_GREEN_LIGHT_SW_NE = 22390,
    SPR_STATION_PLATFORM_END_GREEN_LIGHT_NW_SE = 22391,
    SPR_STATION_INVERTED_FENCE_SW_NE = 22392,
    SPR_STATION_INVERTED_FENCE_NW_SE = 22393,
    SPR_STATION_INVERTED_BEGIN_ANGLE_FENCE_SW_NE = 22394,
    SPR_STATION_INVERTED_BEGIN_ANGLE_FENCE_NW_SE = 22395,
    SPR_STATION_INVERTED_LIGHT_BACK_ANGLE_FENCED_NE_SW = 22396,
    SPR_STATION_INVERTED_LIGHT_BACK_ANGLE_FENCED_NW_SE = 22397,
    SPR_STATION_INVERTED_BAR_C_SW_NE = 22398,
    SPR_STATION_INVERTED_BAR_C_NW_SE = 22399,
    SPR_STATION_INVERTED_BAR_D_SW_NE = 22400,
    SPR_STATION_INVERTED_BAR_D_NW_SE = 22401,
    SPR_STATION_INVERTED_BAR_E_SW_NE = 22402,
    SPR_STATION_INVERTED_BAR_E_NW_SE = 22403,
    SPR_STATION_PIER_EDGE_SE = 22404,
    SPR_STATION_PIER_EDGE_SW = 22405,
    SPR_STATION_PIER_EDGE_NW = 22406,
    SPR_STATION_PIER_EDGE_NE = 22407,
    SPR_STATION_PIER_EDGE_NW_FENCED = 22408,
    SPR_STATION_PIER_EDGE_NE_FENCED = 22409,
    SPR_STATION_PIER_FENCE_SE = 22410,
    SPR_STATION_PIER_FENCE_SW = 22411,
    SPR_STATION_NARROW_EDGE_SE = 22412,
    SPR_STATION_NARROW_EDGE_SW = 22413,
    SPR_STATION_NARROW_EDGE_FENCED_NW = 22414,
    SPR_STATION_NARROW_EDGE_FENCED_NE = 22415,
    SPR_STATION_NARROW_EDGE_NW = 22416,
    SPR_STATION_NARROW_EDGE_NE = 22417,
    SPR_STATION_INVERTED_BAR_F_SW_NE = 22418,
    SPR_STATION_INVERTED_BAR_F_NW_SE = 22419,
    SPR_STATION_INVERTED_BAR_0_SW_NE = 22420,
    SPR_STATION_INVERTED_BAR_0_NW_SE = 22421,
    SPR_STATION_INVERTED_BAR_A_SW_NE = 22422,
    SPR_STATION_INVERTED_BAR_A_NW_SE = 22423,
    SPR_STATION_INVERTED_BAR_B_SW_NE = 22424,
    SPR_STATION_INVERTED_BAR_B_NW_SE = 22425,
    SPR_STATION_BASE_A_SW_NE = 22426,
    SPR_STATION_BASE_A_NW_SE = 22427,
    SPR_STATION_BASE_B_SW_NE = 22428,
    SPR_STATION_BASE_B_NW_SE = 22429,
    SPR_STATION_BASE_C_SW_NE = 22430,
    SPR_STATION_BASE_C_NW_SE = 22431,
    SPR_STATION_BASE_D = 22432, // Metal plate without borders, used for some stations and for the on-ride photo segment.

    SPR_ON_RIDE_PHOTO_CAMERA_SMALL_N = 23485,
    SPR_ON_RIDE_PHOTO_CAMERA_SMALL_E = 23486,
    SPR_ON_RIDE_PHOTO_CAMERA_SMALL_S = 23487,
    SPR_ON_RIDE_PHOTO_CAMERA_SMALL_W = 23488,
    SPR_ON_RIDE_PHOTO_CAMERA_FLASH_SMALL_N = 23489,
    SPR_ON_RIDE_PHOTO_CAMERA_FLASH_SMALL_E = 23490,
    SPR_ON_RIDE_PHOTO_CAMERA_FLASH_SMALL_S = 23491,
    SPR_ON_RIDE_PHOTO_CAMERA_FLASH_SMALL_W = 23492,
    SPR_ON_RIDE_PHOTO_SIGN_SMALL_SW_NE = 23493,
    SPR_ON_RIDE_PHOTO_SIGN_SMALL_NW_SE = 23494,
    SPR_ON_RIDE_PHOTO_SIGN_SMALL_NE_SW = 23495,
    SPR_ON_RIDE_PHOTO_SIGN_SMALL_SE_NW = 23496,

    SPR_ON_RIDE_PHOTO_CAMERA_N = 25615,
    SPR_ON_RIDE_PHOTO_CAMERA_E = 25616,
    SPR_ON_RIDE_PHOTO_CAMERA_S = 25617,
    SPR_ON_RIDE_PHOTO_CAMERA_W = 25618,
    SPR_ON_RIDE_PHOTO_CAMERA_FLASH_N = 25619,
    SPR_ON_RIDE_PHOTO_CAMERA_FLASH_E = 25620,
    SPR_ON_RIDE_PHOTO_CAMERA_FLASH_S = 25621,
    SPR_ON_RIDE_PHOTO_CAMERA_FLASH_W = 25622,
    SPR_ON_RIDE_PHOTO_SIGN_SW_NE = 25623,
    SPR_ON_RIDE_PHOTO_SIGN_NW_SE = 25624,
    SPR_ON_RIDE_PHOTO_SIGN_NE_SW = 25625,
    SPR_ON_RIDE_PHOTO_SIGN_SE_NW = 25626,

    SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_SW_NE_FRAME_0 = 28865,
    SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_SW_NE_FRAME_1 = 28866,
    SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_SW_NE_FRAME_2 = 28867,
    SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_SW_NE_FRAME_3 = 28868,
    SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_NW_SE_FRAME_0 = 28869,
    SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_NW_SE_FRAME_1 = 28870,
    SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_NW_SE_FRAME_2 = 28871,
    SPR_GHOST_TRAIN_SPINNING_TUNNEL_BACK_NW_SE_FRAME_3 = 28872,
    SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_SW_NE_FRAME_0 = 28873,
    SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_SW_NE_FRAME_1 = 28874,
    SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_SW_NE_FRAME_2 = 28875,
    SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_SW_NE_FRAME_3 = 28876,
    SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_NW_SE_FRAME_0 = 28877,
    SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_NW_SE_FRAME_1 = 28878,
    SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_NW_SE_FRAME_2 = 28879,
    SPR_GHOST_TRAIN_SPINNING_TUNNEL_FRONT_NW_SE_FRAME_3 = 28880,
};

enum
{
    SCHEME_TRACK = 0,
    SCHEME_SUPPORTS = 1,
    SCHEME_MISC = 2,
    SCHEME_3 = 3,
};

enum
{
    STATION_VARIANT_BASIC,
    STATION_VARIANT_1,
    STATION_VARIANT_TALL,
};

enum
{
    MAZE_ENTRY_FLAG_0 = (1 << 0),
    MAZE_ENTRY_FLAG_1 = (1 << 1),
    MAZE_ENTRY_FLAG_2 = (1 << 2),
    MAZE_ENTRY_FLAG_3 = (1 << 3),
    MAZE_ENTRY_FLAG_4 = (1 << 4),
    MAZE_ENTRY_FLAG_5 = (1 << 5),
    MAZE_ENTRY_FLAG_6 = (1 << 6),
    MAZE_ENTRY_FLAG_7 = (1 << 7),
    MAZE_ENTRY_FLAG_8 = (1 << 8),
    MAZE_ENTRY_FLAG_9 = (1 << 9),
    MAZE_ENTRY_FLAG_10 = (1 << 10),
    MAZE_ENTRY_FLAG_11 = (1 << 11),
    MAZE_ENTRY_FLAG_12 = (1 << 12),
    MAZE_ENTRY_FLAG_13 = (1 << 13),
    MAZE_ENTRY_FLAG_14 = (1 << 14),
    MAZE_ENTRY_FLAG_15 = (1 << 15),
};

extern const uint32_t floorSpritesCork[];
extern const uint32_t floorSpritesMetal[];
extern const uint32_t floorSpritesMetalB[];

extern const uint32_t fenceSpritesRope[];
extern const uint32_t fenceSpritesMetal[];
extern const uint32_t fenceSpritesMetalB[];

extern const uint32_t trackSpritesSubmarineRideMiniHelicoptersQuarterTurn3Tiles[4][3];
extern const uint32_t trackSpritesSubmarineRideMiniHelicoptersQuarterTurn1Tile[4];

extern const uint8_t mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[];
extern const CoordsXY defaultRightQuarterTurn5TilesOffsets[4][5];
extern const CoordsXYZ defaultRightQuarterTurn5TilesBoundOffsets[4][5];
extern const CoordsXY defaultRightQuarterTurn5TilesBoundLengths[4][5];

extern const uint8_t mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[];
extern const CoordsXY defaultRightQuarterTurn3TilesOffsets[4][3];
extern const CoordsXYZ defaultRightQuarterTurn3TilesBoundOffsets[4][3];
extern const CoordsXY defaultRightQuarterTurn3TilesBoundLengths[4][3];

extern const CoordsXY defaultRightHelixUpSmallQuarterBoundLengths[4][3][2];
extern const CoordsXYZ defaultRightHelixUpSmallQuarterBoundOffsets[4][3][2];

extern const CoordsXY defaultRightHelixUpLargeQuarterBoundLengths[4][5][2];
extern const CoordsXYZ defaultRightHelixUpLargeQuarterBoundOffsets[4][5][2];

extern const CoordsXYZ defaultLeftEighthToDiagBoundOffsets[4][4];
extern const CoordsXY defaultLeftEighthToDiagBoundLengths[4][4];
extern const CoordsXYZ defaultRightEighthToDiagBoundOffsets[4][4];
extern const CoordsXY defaultRightEighthToDiagBoundLengths[4][4];
extern const int8_t defaultEighthToDiagThickness[4][4];

extern const CoordsXY defaultDiagBoundLengths[4];
extern const CoordsXY defaultDiagTileOffsets[4];

extern const uint8_t mapLeftEighthTurnToOrthogonal[5];

extern const size_t mini_golf_peep_animation_lengths[];

bool track_paint_util_has_fence(
    enum edge_t edge, const CoordsXY& position, const TrackElement& trackElement, const Ride& ride, uint8_t rotation);
void track_paint_util_paint_floor(
    paint_session& session, uint8_t edges, uint32_t colourFlags, uint16_t height, const uint32_t floorSprites[4],
    const StationObject* stationStyle);
void track_paint_util_paint_fences(
    paint_session& session, uint8_t edges, const CoordsXY& position, const TrackElement& trackElement, const Ride& ride,
    uint32_t colourFlags, uint16_t height, const uint32_t fenceSprites[4], uint8_t rotation);
bool track_paint_util_draw_station_covers(
    paint_session& session, enum edge_t edge, bool hasFence, const StationObject* stationObject, uint16_t height);
bool track_paint_util_draw_station_covers_2(
    paint_session& session, enum edge_t edge, bool hasFence, const StationObject* stationObject, uint16_t height,
    uint8_t stationVariant);
void track_paint_util_draw_narrow_station_platform(
    paint_session& session, const Ride& ride, Direction direction, int32_t height, int32_t zOffset,
    const TrackElement& trackElement);
void track_paint_util_draw_station(
    paint_session& session, const Ride& ride, Direction direction, uint16_t height, const TrackElement& trackElement);
void track_paint_util_draw_station_2(
    paint_session& session, const Ride& ride, Direction direction, uint16_t height, const TrackElement& trackElement,
    int32_t fenceOffsetA, int32_t fenceOffsetB);
void track_paint_util_draw_station_3(
    paint_session& session, const Ride& ride, Direction direction, uint16_t height, uint16_t coverHeight,
    const TrackElement& trackElement);
void track_paint_util_draw_station_inverted(
    paint_session& session, const Ride& ride, Direction direction, int32_t height, const TrackElement& trackElement,
    uint8_t stationVariant);
bool track_paint_util_should_paint_supports(const CoordsXY& position);
void track_paint_util_draw_pier(
    paint_session& session, const Ride& ride, const StationObject* stationObject, const CoordsXY& position, Direction direction,
    int32_t height, const TrackElement& trackElement, uint8_t rotation);
void track_paint_util_draw_station_metal_supports(
    paint_session& session, Direction direction, uint16_t height, uint32_t colour);
void track_paint_util_draw_station_metal_supports_2(
    paint_session& session, Direction direction, uint16_t height, uint32_t colour, uint8_t type);

void track_paint_util_right_quarter_turn_5_tiles_paint(
    paint_session& session, int8_t thickness, int16_t height, Direction direction, uint8_t trackSequence, uint32_t colourFlags,
    const uint32_t sprites[4][5], const CoordsXY offsets[4][5], const CoordsXY boundsLengths[4][5],
    const CoordsXYZ boundsOffsets[4][5]);
void track_paint_util_right_quarter_turn_5_tiles_paint_2(
    paint_session& session, int16_t height, Direction direction, uint8_t trackSequence, uint32_t colourFlags,
    const sprite_bb sprites[][5]);
void track_paint_util_right_quarter_turn_5_tiles_paint_3(
    paint_session& session, int16_t height, Direction direction, uint8_t trackSequence, uint32_t colourFlags,
    const sprite_bb sprites[][5]);
void track_paint_util_right_quarter_turn_5_tiles_tunnel(
    paint_session& session, int16_t height, Direction direction, uint8_t trackSequence, uint8_t tunnelType);
void track_paint_util_right_quarter_turn_5_tiles_wooden_supports(
    paint_session& session, int16_t height, Direction direction, uint8_t trackSequence);
void track_paint_util_right_quarter_turn_3_tiles_25_deg_up_tunnel(
    paint_session& session, int16_t height, Direction direction, uint8_t trackSequence, uint8_t tunnelType0,
    uint8_t tunnelType3);
void track_paint_util_right_quarter_turn_3_tiles_25_deg_down_tunnel(
    paint_session& session, int16_t height, Direction direction, uint8_t trackSequence, uint8_t tunnelType0,
    uint8_t tunnelType3);
void track_paint_util_right_quarter_turn_3_tiles_paint(
    paint_session& session, int8_t thickness, int16_t height, Direction direction, uint8_t trackSequence, uint32_t colourFlags,
    const uint32_t sprites[4][3], const CoordsXY offsets[4][3], const CoordsXY boundsLengths[4][3],
    const CoordsXYZ boundsOffsets[4][3]);
void track_paint_util_right_quarter_turn_3_tiles_paint_2(
    paint_session& session, int8_t thickness, int16_t height, Direction direction, uint8_t trackSequence, uint32_t colourFlags,
    const uint32_t sprites[4][3]);
void track_paint_util_right_quarter_turn_3_tiles_paint_2_with_height_offset(
    paint_session& session, int8_t thickness, int16_t height, Direction direction, uint8_t trackSequence, uint32_t colourFlags,
    const uint32_t sprites[4][3], int32_t heightOffset);
void track_paint_util_right_quarter_turn_3_tiles_paint_3(
    paint_session& session, int16_t height, Direction direction, uint8_t trackSequence, uint32_t colourFlags,
    const sprite_bb sprites[4][3]);
void track_paint_util_right_quarter_turn_3_tiles_paint_4(
    paint_session& session, int16_t height, Direction direction, uint8_t trackSequence, uint32_t colourFlags,
    const sprite_bb sprites[4][3]);
void track_paint_util_right_quarter_turn_3_tiles_tunnel(
    paint_session& session, int16_t height, Direction direction, uint8_t trackSequence, uint8_t tunnelType);
void track_paint_util_left_quarter_turn_3_tiles_paint(
    paint_session& session, int8_t thickness, int16_t height, Direction direction, uint8_t trackSequence, uint32_t colourFlags,
    const uint32_t sprites[4][3]);
void track_paint_util_left_quarter_turn_3_tiles_paint_with_height_offset(
    paint_session& session, int8_t thickness, int16_t height, Direction direction, uint8_t trackSequence, uint32_t colourFlags,
    const uint32_t sprites[4][3], int32_t heightOffset);
void track_paint_util_left_quarter_turn_3_tiles_tunnel(
    paint_session& session, int16_t height, uint8_t tunnelType, Direction direction, uint8_t trackSequence);
void track_paint_util_left_quarter_turn_1_tile_paint(
    paint_session& session, int8_t thickness, int16_t height, int16_t boundBoxZOffset, Direction direction,
    uint32_t colourFlags, const uint32_t* sprites);
void track_paint_util_spinning_tunnel_paint(paint_session& session, int8_t thickness, int16_t height, Direction direction);
void track_paint_util_onride_photo_small_paint(
    paint_session& session, Direction direction, int32_t height, const TrackElement& trackElement);
void track_paint_util_onride_photo_paint(
    paint_session& session, Direction direction, int32_t height, const TrackElement& trackElement);
void track_paint_util_right_helix_up_small_quarter_tiles_paint(
    paint_session& session, const int8_t thickness[2], int16_t height, Direction direction, uint8_t trackSequence,
    uint32_t colourFlags, const uint32_t sprites[4][3][2], const CoordsXY offsets[4][3][2],
    const CoordsXY boundsLengths[4][3][2], const CoordsXYZ boundsOffsets[4][3][2]);
void track_paint_util_right_helix_up_large_quarter_tiles_paint(
    paint_session& session, const int8_t thickness[2], int16_t height, Direction direction, uint8_t trackSequence,
    uint32_t colourFlags, const uint32_t sprites[4][5][2], const CoordsXY offsets[4][5][2],
    const CoordsXY boundsLengths[4][5][2], const CoordsXYZ boundsOffsets[4][5][2]);
void track_paint_util_eighth_to_diag_tiles_paint(
    paint_session& session, const int8_t thickness[4][4], int16_t height, Direction direction, uint8_t trackSequence,
    uint32_t colourFlags, const uint32_t sprites[4][4], const CoordsXY offsets[4][4], const CoordsXY boundsLengths[4][4],
    const CoordsXYZ boundsOffsets[4][4]);
void track_paint_util_diag_tiles_paint(
    paint_session& session, int8_t thickness, int16_t height, Direction direction, uint8_t trackSequence, uint32_t colourFlags,
    const uint32_t sprites[4], const CoordsXY offsets[4], const CoordsXY boundsLengths[4], const CoordsXYZ boundsOffsets[4]);

void track_paint_util_left_quarter_turn_1_tile_tunnel(
    paint_session& session, Direction direction, uint16_t baseHeight, int8_t startOffset, uint8_t startTunnel, int8_t endOffset,
    uint8_t endTunnel);
void track_paint_util_right_quarter_turn_1_tile_tunnel(
    paint_session& session, Direction direction, uint16_t baseHeight, int8_t startOffset, uint8_t startTunnel, int8_t endOffset,
    uint8_t endTunnel);

void track_paint_util_right_vertical_loop_segments(paint_session& session, Direction direction, uint8_t trackSequence);

void track_paint_util_left_corkscrew_up_supports(paint_session& session, Direction direction, uint16_t height);

using TRACK_PAINT_FUNCTION = void (*)(
    paint_session& session, const Ride& ride, uint8_t trackSequence, Direction direction, int32_t height,
    const TrackElement& trackElement);
using TRACK_PAINT_FUNCTION_GETTER = TRACK_PAINT_FUNCTION (*)(int32_t trackType);

TRACK_PAINT_FUNCTION get_track_paint_function_stand_up_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_suspended_swinging_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_inverted_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_junior_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_monorail(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_mini_suspended_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_miniature_railway(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_boat_hire(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_wooden_wild_mouse(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_steeplechase(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_car_ride(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_launched_freefall(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_bobsleigh_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_observation_tower(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_looping_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_dinghy_slide(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_mine_train_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_chairlift(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_corkscrew_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_maze(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_spiral_slide(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_go_karts(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_log_flume(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_river_rapids(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_dodgems(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_swinging_ship(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_swinging_inverter_ship(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_ferris_wheel(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_motionsimulator(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_3d_cinema(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_topspin(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_space_rings(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_reverse_freefall_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_lift(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_shop(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_merry_go_round(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_facility(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_twist(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_haunted_house(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_circus(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_ghost_train(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_side_friction_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_wooden_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_wild_mouse(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_multi_dimension_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_flying_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_virginia_reel(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_splash_boats(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_mini_helicopters(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_lay_down_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_suspended_monorail(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_reverser_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_heartline_twister_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_mini_golf(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_giga_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_roto_drop(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_flying_saucers(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_crooked_house(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_monorail_cycles(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_compact_inverted_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_water_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_air_powered_vertical_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_inverted_hairpin_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_magic_carpet(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_submarine_ride(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_enterprise(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_inverted_impulse_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_mini_rc(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_mine_ride(int32_t trackType);
TRACK_PAINT_FUNCTION get_track_paint_function_lim_launched_rc(int32_t trackType);
namespace HybridRC
{
    TRACK_PAINT_FUNCTION GetTrackPaintFunction(int32_t trackType);
}
namespace SingleRailRC
{
    TRACK_PAINT_FUNCTION GetTrackPaintFunction(int32_t trackType);
}
namespace AlpineRC
{
    TRACK_PAINT_FUNCTION GetTrackPaintFunction(int32_t trackType);
}
