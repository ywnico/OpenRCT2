/*****************************************************************************
 * Copyright (c) 2014-2020 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "../../config/Config.h"
#include "../../drawing/Drawing.h"
#include "../../interface/Viewport.h"
#include "../../paint/Paint.h"
#include "../../paint/Supports.h"
#include "../../paint/tile_element/Paint.Surface.h"
#include "../../paint/tile_element/Paint.TileElement.h"
#include "../../sprites.h"
#include "../../world/Map.h"
#include "../RideData.h"
#include "../TrackData.h"
#include "../TrackPaint.h"

struct sprite_bb_2
{
    uint32_t sprite_id_a;
    uint32_t sprite_id_b;
    CoordsXYZ offset;
    CoordsXYZ bb_offset;
    CoordsXYZ bb_size;
};

enum
{
    SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_SW_NE = 23497,
    SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_NW_SE = 23498,
    SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_NE_SW = 23499,
    SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_SE_NW = 23500,
    SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_SW_NE = 23501,
    SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_NW_SE = 23502,
    SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_NE_SW = 23503,
    SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_SE_NW = 23504,
    SPR_WOODEN_RC_LEFT_BANK_SW_NE = 23505,
    SPR_WOODEN_RC_LEFT_BANK_NW_SE = 23506,
    SPR_WOODEN_RC_LEFT_BANK_NE_SW = 23507,
    SPR_WOODEN_RC_LEFT_BANK_SE_NW = 23508,
    SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_SW_NE = 23509,
    SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_NW_SE = 23510,
    SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_NE_SW = 23511,
    SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_SE_NW = 23512,
    SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_SW_NE = 23513,
    SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_NW_SE = 23514,
    SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_NE_SW = 23515,
    SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_SE_NW = 23516,
    SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_SW_NE = 23517,
    SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_NW_SE = 23518,
    SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_NE_SW = 23519,
    SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_SE_NW = 23520,
    SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_SW_NE = 23521,
    SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_NW_SE = 23522,
    SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_NE_SW = 23523,
    SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_SE_NW = 23524,
    SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_FRONT_NW_SE = 23525,
    SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_FRONT_SE_NW = 23526,
    SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_FRONT_NE_SW = 23527,
    SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_FRONT_NW_SE = 23528,
    SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_FRONT_NE_SW = 23529,
    SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_FRONT_NW_SE = 23530,
    SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_FRONT_NE_SW = 23531,
    SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_FRONT_NW_SE = 23532,
    SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_FRONT_NE_SW = 23533,
    SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_FRONT_NW_SE = 23534,
    SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_FRONT_NE_SW = 23535,
    SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_FRONT_SW_NE = 23536,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_SW_NE = 23537,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_NW_SE = 23538,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_NE_SW = 23539,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_SE_NW = 23540,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_SW_NE = 23541,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_NW_SE = 23542,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_NE_SW = 23543,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_SE_NW = 23544,
    SPR_WOODEN_RC_25_DEG_SW_NE = 23545,
    SPR_WOODEN_RC_25_DEG_NW_SE = 23546,
    SPR_WOODEN_RC_25_DEG_NE_SW = 23547,
    SPR_WOODEN_RC_25_DEG_SE_NW = 23548,
    SPR_WOODEN_RC_25_DEG_TO_60_DEG_SW_NE = 23549,
    SPR_WOODEN_RC_25_DEG_TO_60_DEG_FRONT_NW_SE = 23550,
    SPR_WOODEN_RC_25_DEG_TO_60_DEG_NW_SE = 23551,
    SPR_WOODEN_RC_25_DEG_TO_60_DEG_FRONT_NE_SW = 23552,
    SPR_WOODEN_RC_25_DEG_TO_60_DEG_NE_SW = 23553,
    SPR_WOODEN_RC_25_DEG_TO_60_DEG_SE_NW = 23554,
    SPR_WOODEN_RC_60_DEG_TO_25_DEG_SW_NE = 23555,
    SPR_WOODEN_RC_60_DEG_TO_25_DEG_FRONT_NW_SE = 23556,
    SPR_WOODEN_RC_60_DEG_TO_25_DEG_NW_SE = 23557,
    SPR_WOODEN_RC_60_DEG_TO_25_DEG_FRONT_NE_SW = 23558,
    SPR_WOODEN_RC_60_DEG_TO_25_DEG_NE_SW = 23559,
    SPR_WOODEN_RC_60_DEG_TO_25_DEG_SE_NW = 23560,
    SPR_WOODEN_RC_60_DEG_SW_NE = 23561,
    SPR_WOODEN_RC_60_DEG_CHAIN_SW_NE = 23561,
    SPR_WOODEN_RC_60_DEG_NW_SE = 23562,
    SPR_WOODEN_RC_60_DEG_CHAIN_NW_SE = 23562,
    SPR_WOODEN_RC_60_DEG_NE_SW = 23563,
    SPR_WOODEN_RC_60_DEG_CHAIN_NE_SW = 23563,
    SPR_WOODEN_RC_60_DEG_SE_NW = 23564,
    SPR_WOODEN_RC_60_DEG_CHAIN_SE_NW = 23564,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_FRONT_NW_SE = 23565,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_FRONT_NE_SW = 23566,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_FRONT_NW_SE = 23567,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_FRONT_NE_SW = 23568,
    SPR_WOODEN_RC_25_DEG_FRONT_NW_SE = 23569,
    SPR_WOODEN_RC_60_DEG_FRONT_NW_SE = 23569,
    SPR_WOODEN_RC_25_DEG_FRONT_NE_SW = 23570,
    SPR_WOODEN_RC_60_DEG_FRONT_NE_SW = 23570,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_SW_NE = 23571,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_NW_SE = 23572,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_NE_SW = 23573,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_SE_NW = 23574,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_SW_NE = 23575,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_NW_SE = 23576,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_NE_SW = 23577,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_SE_NW = 23578,
    SPR_WOODEN_RC_25_DEG_CHAIN_SW_NE = 23579,
    SPR_WOODEN_RC_25_DEG_CHAIN_NW_SE = 23580,
    SPR_WOODEN_RC_25_DEG_CHAIN_NE_SW = 23581,
    SPR_WOODEN_RC_25_DEG_CHAIN_SE_NW = 23582,

    SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_FRONT_NW_SE = 23599,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_FRONT_NE_SW = 23600,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_FRONT_NW_SE = 23601,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_FRONT_NE_SW = 23602,
    SPR_WOODEN_RC_25_DEG_CHAIN_FRONT_NW_SE = 23603,
    SPR_WOODEN_RC_60_DEG_CHAIN_FRONT_NW_SE = 23603,
    SPR_WOODEN_RC_25_DEG_CHAIN_FRONT_NE_SW = 23604,
    SPR_WOODEN_RC_60_DEG_CHAIN_FRONT_NE_SW = 23604,
    SPR_WOODEN_RC_QUARTER_TURN_5_SW_SE_SEQ_0 = 23605,
    SPR_WOODEN_RC_QUARTER_TURN_5_SW_SE_SEQ_2 = 23606,
    SPR_WOODEN_RC_QUARTER_TURN_5_SW_SE_SEQ_3 = 23607,
    SPR_WOODEN_RC_QUARTER_TURN_5_SW_SE_SEQ_5 = 23608,
    SPR_WOODEN_RC_QUARTER_TURN_5_SW_SE_SEQ_6 = 23609,
    SPR_WOODEN_RC_QUARTER_TURN_5_NW_SW_SEQ_0 = 23610,
    SPR_WOODEN_RC_QUARTER_TURN_5_NW_SW_SEQ_2 = 23611,
    SPR_WOODEN_RC_QUARTER_TURN_5_NW_SW_SEQ_3 = 23612,
    SPR_WOODEN_RC_QUARTER_TURN_5_NW_SW_SEQ_5 = 23613,
    SPR_WOODEN_RC_QUARTER_TURN_5_NW_SW_SEQ_6 = 23614,
    SPR_WOODEN_RC_QUARTER_TURN_5_NE_NW_SEQ_0 = 23615,
    SPR_WOODEN_RC_QUARTER_TURN_5_NE_NW_SEQ_2 = 23616,
    SPR_WOODEN_RC_QUARTER_TURN_5_NE_NW_SEQ_3 = 23617,
    SPR_WOODEN_RC_QUARTER_TURN_5_NE_NW_SEQ_5 = 23618,
    SPR_WOODEN_RC_QUARTER_TURN_5_NE_NW_SEQ_6 = 23619,
    SPR_WOODEN_RC_QUARTER_TURN_5_SE_NE_SEQ_0 = 23620,
    SPR_WOODEN_RC_QUARTER_TURN_5_SE_NE_SEQ_2 = 23621,
    SPR_WOODEN_RC_QUARTER_TURN_5_SE_NE_SEQ_3 = 23622,
    SPR_WOODEN_RC_QUARTER_TURN_5_SE_NE_SEQ_5 = 23623,
    SPR_WOODEN_RC_QUARTER_TURN_5_SE_NE_SEQ_6 = 23624,
    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_SW_SE_SEQ_0 = 23625,
    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_SW_SE_SEQ_2 = 23626,
    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_SW_SE_SEQ_3 = 23627,
    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_SW_SE_SEQ_5 = 23628,
    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_SW_SE_SEQ_6 = 23629,
    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_NE_NW_SEQ_0 = 23630,
    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_NE_NW_SEQ_2 = 23631,
    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_NE_NW_SEQ_3 = 23632,
    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_NE_NW_SEQ_5 = 23633,
    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_NE_NW_SEQ_6 = 23634,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SW_SE_SEQ_0 = 23635,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SW_SE_SEQ_2 = 23636,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SW_SE_SEQ_3 = 23637,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SW_SE_SEQ_5 = 23638,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SW_SE_SEQ_6 = 23639,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NW_SW_SEQ_0 = 23640,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NW_SW_SEQ_2 = 23641,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NW_SW_SEQ_3 = 23642,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NW_SW_SEQ_5 = 23643,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NW_SW_SEQ_6 = 23644,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NE_NW_SEQ_0 = 23645,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NE_NW_SEQ_2 = 23646,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NE_NW_SEQ_3 = 23647,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NE_NW_SEQ_5 = 23648,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NE_NW_SEQ_6 = 23649,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SE_NE_SEQ_0 = 23650,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SE_NE_SEQ_2 = 23651,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SE_NE_SEQ_3 = 23652,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SE_NE_SEQ_5 = 23653,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SE_NE_SEQ_6 = 23654,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_SW_SE_SEQ_0 = 23655,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_SW_SE_SEQ_2 = 23656,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_SW_SE_SEQ_3 = 23657,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_SW_SE_SEQ_5 = 23658,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_SW_SE_SEQ_6 = 23659,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_NE_NW_SEQ_0 = 23660,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_NE_NW_SEQ_2 = 23661,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_NE_NW_SEQ_3 = 23662,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_NE_NW_SEQ_5 = 23663,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_NE_NW_SEQ_6 = 23664,

    SPR_WOODEN_RC_FLAT_CHAIN_SW_NE = 23749,
    SPR_WOODEN_RC_FLAT_CHAIN_NW_SE = 23750,
    SPR_WOODEN_RC_FLAT_CHAIN_NE_SW = 23751,
    SPR_WOODEN_RC_FLAT_CHAIN_SE_NW = 23752,
    SPR_WOODEN_RC_FLAT_SW_NE = 23753,
    SPR_WOODEN_RC_FLAT_NW_SE = 23754,
    SPR_WOODEN_RC_BRAKES_SW_NE = 23755,
    SPR_WOODEN_RC_BRAKES_NW_SE = 23756,
    SPR_WOODEN_RC_BLOCK_BRAKES_SW_NE_OPEN = 23757,
    SPR_WOODEN_RC_BLOCK_BRAKES_NW_SE_OPEN = 23758,
    SPR_WOODEN_RC_BLOCK_BRAKES_SW_NE_CLOSED = 23759,
    SPR_WOODEN_RC_BLOCK_BRAKES_NW_SE_CLOSED = 23760,

    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_0 = 23841,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_1 = 23842,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_2 = 23843,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_3 = 23844,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_4 = 23845,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_5 = 23846,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_6 = 23847,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_7 = 23848,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_8 = 23849,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_9 = 23850,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_10 = 23851,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_11 = 23852,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_12 = 23853,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_13 = 23854,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_14 = 23855,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_15 = 23856,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_16 = 23857,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_17 = 23858,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_18 = 23859,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_19 = 23860,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_20 = 23861,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_21 = 23862,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_22 = 23863,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_23 = 23864,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_24 = 23865,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_25 = 23866,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_26 = 23867,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_27 = 23868,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_28 = 23869,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_29 = 23870,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_30 = 23871,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_31 = 23872,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_32 = 23873,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_33 = 23874,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_34 = 23875,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_35 = 23876,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_36 = 23877,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_37 = 23878,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_38 = 23879,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_39 = 23880,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_40 = 23881,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_41 = 23882,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_42 = 23883,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_43 = 23884,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_44 = 23885,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_45 = 23886,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_46 = 23887,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_47 = 23888,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_48 = 23889,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_49 = 23890,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_50 = 23891,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_51 = 23892,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_52 = 23893,
    SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_53 = 23894,

    SPR_WOODEN_RC_STATION_SW_NE = 23973,
    SPR_WOODEN_RC_STATION_NW_SE = 23974,

    SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_RAILS_SW_NE = 24363,
    SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_RAILS_NW_SE = 24364,
    SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_RAILS_NE_SW = 24365,
    SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_RAILS_SE_NW = 24366,
    SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_RAILS_SW_NE = 24367,
    SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_RAILS_NW_SE = 24368,
    SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_RAILS_NE_SW = 24369,
    SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_RAILS_SE_NW = 24370,
    SPR_WOODEN_RC_LEFT_BANK_RAILS_SW_NE = 24371,
    SPR_WOODEN_RC_LEFT_BANK_RAILS_NW_SE = 24372,
    SPR_WOODEN_RC_LEFT_BANK_RAILS_NE_SW = 24373,
    SPR_WOODEN_RC_LEFT_BANK_RAILS_SE_NW = 24374,
    SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_RAILS_SW_NE = 24375,
    SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_RAILS_NW_SE = 24376,
    SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_RAILS_NE_SW = 24377,
    SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_RAILS_SE_NW = 24378,
    SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_RAILS_SW_NE = 24379,
    SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_RAILS_NW_SE = 24380,
    SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_RAILS_NE_SW = 24381,
    SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_RAILS_SE_NW = 24382,
    SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_RAILS_SW_NE = 24383,
    SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_RAILS_NW_SE = 24384,
    SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_RAILS_NE_SW = 24385,
    SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_RAILS_SE_NW = 24386,
    SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_RAILS_SW_NE = 24387,
    SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_RAILS_NW_SE = 24388,
    SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_RAILS_NE_SW = 24389,
    SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_RAILS_SE_NW = 24390,
    SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_RAILS_FRONT_NW_SE = 24391,
    SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_RAILS_FRONT_SE_NW = 24392,
    SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_RAILS_FRONT_NE_SW = 24393,
    SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_RAILS_FRONT_NW_SE = 24394,
    SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_RAILS_FRONT_NE_SW = 24395,
    SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_RAILS_FRONT_NW_SE = 24396,
    SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_RAILS_FRONT_NE_SW = 24397,
    SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_RAILS_FRONT_NW_SE = 24398,
    SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_RAILS_FRONT_NE_SW = 24399,
    SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_RAILS_FRONT_NW_SE = 24400,
    SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_RAILS_FRONT_NE_SW = 24401,
    SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_RAILS_FRONT_SW_NE = 24402,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_RAILS_SW_NE = 24403,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_RAILS_NW_SE = 24404,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_RAILS_NE_SW = 24405,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_RAILS_SE_NW = 24406,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_RAILS_SW_NE = 24407,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_RAILS_NW_SE = 24408,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_RAILS_NE_SW = 24409,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_RAILS_SE_NW = 24410,
    SPR_WOODEN_RC_25_DEG_RAILS_SW_NE = 24411,
    SPR_WOODEN_RC_25_DEG_RAILS_NW_SE = 24412,
    SPR_WOODEN_RC_25_DEG_RAILS_NE_SW = 24413,
    SPR_WOODEN_RC_25_DEG_RAILS_SE_NW = 24414,
    SPR_WOODEN_RC_25_DEG_TO_60_DEG_RAILS_SW_NE = 24415,
    SPR_WOODEN_RC_25_DEG_TO_60_DEG_RAILS_FRONT_NW_SE = 24416,
    SPR_WOODEN_RC_25_DEG_TO_60_DEG_RAILS_NW_SE = 24417,
    SPR_WOODEN_RC_25_DEG_TO_60_DEG_RAILS_FRONT_NE_SW = 24418,
    SPR_WOODEN_RC_25_DEG_TO_60_DEG_RAILS_NE_SW = 24419,
    SPR_WOODEN_RC_25_DEG_TO_60_DEG_RAILS_SE_NW = 24420,
    SPR_WOODEN_RC_60_DEG_TO_25_DEG_RAILS_SW_NE = 24421,
    SPR_WOODEN_RC_60_DEG_TO_25_DEG_RAILS_FRONT_NW_SE = 24422,
    SPR_WOODEN_RC_60_DEG_TO_25_DEG_RAILS_NW_SE = 24423,
    SPR_WOODEN_RC_60_DEG_TO_25_DEG_RAILS_FRONT_NE_SW = 24424,
    SPR_WOODEN_RC_60_DEG_TO_25_DEG_RAILS_NE_SW = 24425,
    SPR_WOODEN_RC_60_DEG_TO_25_DEG_RAILS_SE_NW = 24426,
    SPR_WOODEN_RC_60_DEG_RAILS_SW_NE = 24427,
    SPR_WOODEN_RC_60_DEG_CHAIN_RAILS_SW_NE = 24427,
    SPR_WOODEN_RC_60_DEG_RAILS_NW_SE = 24428,
    SPR_WOODEN_RC_60_DEG_CHAIN_RAILS_NW_SE = 24428,
    SPR_WOODEN_RC_60_DEG_RAILS_NE_SW = 24429,
    SPR_WOODEN_RC_60_DEG_CHAIN_RAILS_NE_SW = 24429,
    SPR_WOODEN_RC_60_DEG_RAILS_SE_NW = 24430,
    SPR_WOODEN_RC_60_DEG_CHAIN_RAILS_SE_NW = 24430,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_RAILS_FRONT_NW_SE = 24431,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_RAILS_FRONT_NE_SW = 24432,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_RAILS_FRONT_NW_SE = 24433,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_RAILS_FRONT_NE_SW = 24434,
    SPR_WOODEN_RC_25_DEG_RAILS_FRONT_NW_SE = 24435,
    SPR_WOODEN_RC_60_DEG_RAILS_FRONT_NW_SE = 24435,
    SPR_WOODEN_RC_25_DEG_RAILS_FRONT_NE_SW = 24436,
    SPR_WOODEN_RC_60_DEG_RAILS_FRONT_NE_SW = 24436,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_RAILS_SW_NE = 24437,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_RAILS_NW_SE = 24438,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_RAILS_NE_SW = 24439,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_RAILS_SE_NW = 24440,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_RAILS_SW_NE = 24441,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_RAILS_NW_SE = 24442,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_RAILS_NE_SW = 24443,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_RAILS_SE_NW = 24444,
    SPR_WOODEN_RC_25_DEG_CHAIN_RAILS_SW_NE = 24445,
    SPR_WOODEN_RC_25_DEG_CHAIN_RAILS_NW_SE = 24446,
    SPR_WOODEN_RC_25_DEG_CHAIN_RAILS_NE_SW = 24447,
    SPR_WOODEN_RC_25_DEG_CHAIN_RAILS_SE_NW = 24448,

    SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_RAILS_FRONT_NW_SE = 24465,
    SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_RAILS_FRONT_NE_SW = 24466,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_RAILS_FRONT_NW_SE = 24467,
    SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_RAILS_FRONT_NE_SW = 24468,
    SPR_WOODEN_RC_25_DEG_CHAIN_RAILS_FRONT_NW_SE = 24469,
    SPR_WOODEN_RC_60_DEG_CHAIN_RAILS_FRONT_NW_SE = 24469,
    SPR_WOODEN_RC_25_DEG_CHAIN_RAILS_FRONT_NE_SW = 24470,
    SPR_WOODEN_RC_60_DEG_CHAIN_RAILS_FRONT_NE_SW = 24470,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SW_SE_SEQ_0 = 24471,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SW_SE_SEQ_2 = 24472,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SW_SE_SEQ_3 = 24473,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SW_SE_SEQ_5 = 24474,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SW_SE_SEQ_6 = 24475,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NW_SW_SEQ_0 = 24476,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NW_SW_SEQ_2 = 24477,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NW_SW_SEQ_3 = 24478,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NW_SW_SEQ_5 = 24479,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NW_SW_SEQ_6 = 24480,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NE_NW_SEQ_0 = 24481,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NE_NW_SEQ_2 = 24482,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NE_NW_SEQ_3 = 24483,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NE_NW_SEQ_5 = 24484,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NE_NW_SEQ_6 = 24485,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SE_NE_SEQ_0 = 24486,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SE_NE_SEQ_2 = 24487,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SE_NE_SEQ_3 = 24488,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SE_NE_SEQ_5 = 24489,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SE_NE_SEQ_6 = 24490,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_0 = 24491,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_2 = 24492,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_3 = 24493,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_5 = 24494,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_6 = 24495,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_0 = 24496,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_2 = 24497,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_3 = 24498,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_5 = 24499,
    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_6 = 24500,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SW_SE_SEQ_0 = 24501,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SW_SE_SEQ_2 = 24502,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SW_SE_SEQ_3 = 24503,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SW_SE_SEQ_5 = 24504,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SW_SE_SEQ_6 = 24505,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NW_SW_SEQ_0 = 24506,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NW_SW_SEQ_2 = 24507,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NW_SW_SEQ_3 = 24508,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NW_SW_SEQ_5 = 24509,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NW_SW_SEQ_6 = 24510,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NE_NW_SEQ_0 = 24511,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NE_NW_SEQ_2 = 24512,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NE_NW_SEQ_3 = 24513,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NE_NW_SEQ_5 = 24514,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NE_NW_SEQ_6 = 24515,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SE_NE_SEQ_0 = 24516,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SE_NE_SEQ_2 = 24517,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SE_NE_SEQ_3 = 24518,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SE_NE_SEQ_5 = 24519,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SE_NE_SEQ_6 = 24520,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_0 = 24521,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_2 = 24522,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_3 = 24523,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_5 = 24524,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_6 = 24525,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_0 = 24526,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_2 = 24527,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_3 = 24528,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_5 = 24529,
    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_6 = 24530,

    SPR_WOODEN_RC_FLAT_CHAIN_RAILS_SW_NE = 24615,
    SPR_WOODEN_RC_FLAT_CHAIN_RAILS_NW_SE = 24616,
    SPR_WOODEN_RC_FLAT_CHAIN_RAILS_NE_SW = 24617,
    SPR_WOODEN_RC_FLAT_CHAIN_RAILS_SE_NW = 24618,
    SPR_WOODEN_RC_FLAT_RAILS_SW_NE = 24619,
    SPR_WOODEN_RC_FLAT_RAILS_NW_SE = 24620,
    SPR_WOODEN_RC_BRAKES_RAILS_SW_NE = 24621,
    SPR_WOODEN_RC_BRAKES_RAILS_NW_SE = 24622,
    SPR_WOODEN_RC_BLOCK_BRAKES_RAILS_SW_NE = 24623,
    SPR_WOODEN_RC_BLOCK_BRAKES_RAILS_NW_SE = 24624,

    SPR_WOODEN_RC_STATION_RAILS_SW_NE = 24839,
    SPR_WOODEN_RC_STATION_RAILS_NW_SE = 24840,
};

static constexpr const uint32_t _wooden_rc_block_brakes_image_ids[4][3] = {
    { SPR_WOODEN_RC_BLOCK_BRAKES_SW_NE_OPEN, SPR_WOODEN_RC_BLOCK_BRAKES_SW_NE_CLOSED, SPR_WOODEN_RC_BLOCK_BRAKES_RAILS_SW_NE },
    { SPR_WOODEN_RC_BLOCK_BRAKES_NW_SE_OPEN, SPR_WOODEN_RC_BLOCK_BRAKES_NW_SE_CLOSED, SPR_WOODEN_RC_BLOCK_BRAKES_RAILS_NW_SE },
    { SPR_WOODEN_RC_BLOCK_BRAKES_SW_NE_OPEN, SPR_WOODEN_RC_BLOCK_BRAKES_SW_NE_CLOSED, SPR_WOODEN_RC_BLOCK_BRAKES_RAILS_SW_NE },
    { SPR_WOODEN_RC_BLOCK_BRAKES_NW_SE_OPEN, SPR_WOODEN_RC_BLOCK_BRAKES_NW_SE_CLOSED, SPR_WOODEN_RC_BLOCK_BRAKES_RAILS_NW_SE },
};

static uint32_t wooden_rc_get_track_colour(paint_session& session)
{
    return (session.TrackColours[SCHEME_TRACK] & ~0xF80000) | session.TrackColours[SCHEME_SUPPORTS];
}

static uint32_t wooden_rc_get_rails_colour(paint_session& session)
{
    return session.TrackColours[SCHEME_TRACK];
}

static paint_struct* wooden_rc_track_paint(
    paint_session& session, uint32_t imageIdTrack, uint32_t imageIdRails, uint8_t direction, int8_t x_offset, int8_t y_offset,
    int16_t bound_box_length_x, int16_t bound_box_length_y, int8_t bound_box_length_z, int16_t z_offset,
    int16_t bound_box_offset_x, int16_t bound_box_offset_y, int16_t bound_box_offset_z)
{
    uint32_t imageId = imageIdTrack | wooden_rc_get_track_colour(session);
    uint32_t railsImageId = imageIdRails | wooden_rc_get_rails_colour(session);

    PaintAddImageAsParentRotated(
        session, direction, imageId, { x_offset, y_offset, z_offset },
        { bound_box_length_x, bound_box_length_y, bound_box_length_z },
        { bound_box_offset_x, bound_box_offset_y, bound_box_offset_z });
    return PaintAddImageAsChildRotated(
        session, direction, railsImageId, { x_offset, y_offset, z_offset },
        { bound_box_length_x, bound_box_length_y, bound_box_length_z },
        { bound_box_offset_x, bound_box_offset_y, bound_box_offset_z });
}

static void wooden_rc_track_paint_bb(paint_session& session, const sprite_bb_2* bb, int16_t height)
{
    if (bb->sprite_id_a == 0)
        return;

    uint32_t imageId = bb->sprite_id_a | wooden_rc_get_track_colour(session);
    uint32_t railsImageId = bb->sprite_id_b | wooden_rc_get_rails_colour(session);

    PaintAddImageAsParent(
        session, imageId, { bb->offset.x, bb->offset.y, height + bb->offset.z },
        { bb->bb_size.x, bb->bb_size.y, bb->bb_size.z }, { bb->bb_offset.x, bb->bb_offset.y, height + bb->bb_offset.z });
    PaintAddImageAsChild(
        session, railsImageId, { static_cast<int8_t>(bb->offset.x), static_cast<int8_t>(bb->offset.y), height + bb->offset.z },
        { bb->bb_size.x, bb->bb_size.y, static_cast<int8_t>(bb->bb_size.z) },
        { bb->bb_offset.x, bb->bb_offset.y, height + bb->bb_offset.z });
}

/** rct2: 0x008AC568 */
static void wooden_rc_track_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const uint32_t imageIds[4][2] = {
        { SPR_WOODEN_RC_FLAT_SW_NE, SPR_WOODEN_RC_FLAT_CHAIN_SW_NE },
        { SPR_WOODEN_RC_FLAT_NW_SE, SPR_WOODEN_RC_FLAT_CHAIN_NW_SE },
        { SPR_WOODEN_RC_FLAT_SW_NE, SPR_WOODEN_RC_FLAT_CHAIN_NE_SW },
        { SPR_WOODEN_RC_FLAT_NW_SE, SPR_WOODEN_RC_FLAT_CHAIN_SE_NW },
    };
    static constexpr const uint32_t railsImageIds[4][2] = {
        { SPR_WOODEN_RC_FLAT_RAILS_SW_NE, SPR_WOODEN_RC_FLAT_CHAIN_RAILS_SW_NE },
        { SPR_WOODEN_RC_FLAT_RAILS_NW_SE, SPR_WOODEN_RC_FLAT_CHAIN_RAILS_NW_SE },
        { SPR_WOODEN_RC_FLAT_RAILS_SW_NE, SPR_WOODEN_RC_FLAT_CHAIN_RAILS_NE_SW },
        { SPR_WOODEN_RC_FLAT_RAILS_NW_SE, SPR_WOODEN_RC_FLAT_CHAIN_RAILS_SE_NW },
    };

    uint8_t isChained = trackElement.HasChain() ? 1 : 0;
    wooden_rc_track_paint(
        session, imageIds[direction][isChained], railsImageIds[direction][isChained], direction, 0, 2, 32, 25, 2, height, 0, 3,
        height);
    wooden_a_supports_paint_setup(session, direction & 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
    paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 32, 0x20);
}

static void wooden_rc_track_station(
    paint_session& session, const Ride& ride, [[maybe_unused]] uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const uint32_t stationImageIds[4][2] = {
        { SPR_WOODEN_RC_STATION_SW_NE, SPR_WOODEN_RC_STATION_RAILS_SW_NE },
        { SPR_WOODEN_RC_STATION_NW_SE, SPR_WOODEN_RC_STATION_RAILS_NW_SE },
        { SPR_WOODEN_RC_STATION_SW_NE, SPR_WOODEN_RC_STATION_RAILS_SW_NE },
        { SPR_WOODEN_RC_STATION_NW_SE, SPR_WOODEN_RC_STATION_RAILS_NW_SE },
    };

    int32_t trackType = trackElement.GetTrackType();
    if (trackType == TrackElemType::EndStation)
    {
        const auto brakeImg = trackElement.BlockBrakeClosed() ? _wooden_rc_block_brakes_image_ids[direction][1]
                                                              : _wooden_rc_block_brakes_image_ids[direction][0];
        wooden_rc_track_paint(
            session, brakeImg, _wooden_rc_block_brakes_image_ids[direction][2], direction, 0, 2, 32, 27, 2, height, 0, 2,
            height);
    }
    else
    {
        wooden_rc_track_paint(
            session, stationImageIds[direction][0], stationImageIds[direction][1], direction, 0, 2, 32, 27, 2, height, 0, 2,
            height);
    }
    wooden_a_supports_paint_setup(session, direction & 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
    track_paint_util_draw_station_2(session, ride, direction, height, trackElement, 9, 11);
    paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 32, 0x20);
}

/** rct2: 0x008AC578 */
static void wooden_rc_track_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const uint32_t imageIds[2][4][4] = {
        {
            {
                SPR_WOODEN_RC_25_DEG_SW_NE,
                SPR_WOODEN_RC_25_DEG_RAILS_SW_NE,
                0,
                0,
            },
            {
                SPR_WOODEN_RC_25_DEG_NW_SE,
                SPR_WOODEN_RC_25_DEG_RAILS_NW_SE,
                SPR_WOODEN_RC_25_DEG_FRONT_NW_SE,
                SPR_WOODEN_RC_25_DEG_RAILS_FRONT_NW_SE,
            },
            {
                SPR_WOODEN_RC_25_DEG_NE_SW,
                SPR_WOODEN_RC_25_DEG_RAILS_NE_SW,
                SPR_WOODEN_RC_25_DEG_FRONT_NE_SW,
                SPR_WOODEN_RC_25_DEG_RAILS_FRONT_NE_SW,
            },
            {
                SPR_WOODEN_RC_25_DEG_SE_NW,
                SPR_WOODEN_RC_25_DEG_RAILS_SE_NW,
                0,
                0,
            },
        },
        {
            {
                SPR_WOODEN_RC_25_DEG_CHAIN_SW_NE,
                SPR_WOODEN_RC_25_DEG_CHAIN_RAILS_SW_NE,
                0,
                0,
            },
            {
                SPR_WOODEN_RC_25_DEG_CHAIN_NW_SE,
                SPR_WOODEN_RC_25_DEG_CHAIN_RAILS_NW_SE,
                SPR_WOODEN_RC_25_DEG_CHAIN_FRONT_NW_SE,
                SPR_WOODEN_RC_25_DEG_CHAIN_RAILS_FRONT_NW_SE,
            },
            {
                SPR_WOODEN_RC_25_DEG_CHAIN_NE_SW,
                SPR_WOODEN_RC_25_DEG_CHAIN_RAILS_NE_SW,
                SPR_WOODEN_RC_25_DEG_CHAIN_FRONT_NE_SW,
                SPR_WOODEN_RC_25_DEG_CHAIN_RAILS_FRONT_NE_SW,
            },
            {
                SPR_WOODEN_RC_25_DEG_CHAIN_SE_NW,
                SPR_WOODEN_RC_25_DEG_CHAIN_RAILS_SE_NW,
                0,
                0,
            },
        },
    };

    uint8_t isChained = trackElement.HasChain() ? 1 : 0;
    wooden_rc_track_paint(
        session, imageIds[isChained][direction][0], imageIds[isChained][direction][1], direction, 0, 0, 32, 25, 2, height, 0, 3,
        height);
    if (direction == 1 || direction == 2)
    {
        wooden_rc_track_paint(
            session, imageIds[isChained][direction][2], imageIds[isChained][direction][3], direction, 0, 0, 32, 1, 9, height, 0,
            26, height + 5);
    }
    wooden_a_supports_paint_setup(session, direction & 1, 9 + direction, height, session.TrackColours[SCHEME_SUPPORTS]);

    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height + 8, TUNNEL_SQUARE_8);
    }

    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 56, 0x20);
}

/** rct2: 0x008AC588 */
static void wooden_rc_track_60_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const uint32_t imageIds[4][2] = {
        { SPR_WOODEN_RC_60_DEG_SW_NE, SPR_WOODEN_RC_60_DEG_RAILS_SW_NE },
        { SPR_WOODEN_RC_60_DEG_NW_SE, SPR_WOODEN_RC_60_DEG_RAILS_NW_SE },
        { SPR_WOODEN_RC_60_DEG_NE_SW, SPR_WOODEN_RC_60_DEG_RAILS_NE_SW },
        { SPR_WOODEN_RC_60_DEG_SE_NW, SPR_WOODEN_RC_60_DEG_RAILS_SE_NW },
    };

    if (direction == 0 || direction == 3)
    {
        wooden_rc_track_paint(
            session, imageIds[direction][0], imageIds[direction][1], direction, 0, 0, 32, 25, 2, height, 0, 3, height);
    }
    else
    {
        session.WoodenSupportsPrependTo = wooden_rc_track_paint(
            session, imageIds[direction][0], imageIds[direction][1], direction, 0, 0, 2, 24, 93, height, 28, 4, height - 16);
    }
    wooden_a_supports_paint_setup(session, direction & 1, 21 + direction, height, session.TrackColours[SCHEME_SUPPORTS]);

    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height + 56, TUNNEL_SQUARE_8);
    }

    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 104, 0x20);
}

/** rct2: 0x008AC598 */
static void wooden_rc_track_flat_to_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const uint32_t imageIds[2][4][4] = {
        {
            {
                SPR_WOODEN_RC_FLAT_TO_25_DEG_SW_NE,
                SPR_WOODEN_RC_FLAT_TO_25_DEG_RAILS_SW_NE,
                0,
                0,
            },
            {
                SPR_WOODEN_RC_FLAT_TO_25_DEG_NW_SE,
                SPR_WOODEN_RC_FLAT_TO_25_DEG_RAILS_NW_SE,
                SPR_WOODEN_RC_FLAT_TO_25_DEG_FRONT_NW_SE,
                SPR_WOODEN_RC_FLAT_TO_25_DEG_RAILS_FRONT_NW_SE,
            },
            {
                SPR_WOODEN_RC_FLAT_TO_25_DEG_NE_SW,
                SPR_WOODEN_RC_FLAT_TO_25_DEG_RAILS_NE_SW,
                SPR_WOODEN_RC_FLAT_TO_25_DEG_FRONT_NE_SW,
                SPR_WOODEN_RC_FLAT_TO_25_DEG_RAILS_FRONT_NE_SW,
            },
            {
                SPR_WOODEN_RC_FLAT_TO_25_DEG_SE_NW,
                SPR_WOODEN_RC_FLAT_TO_25_DEG_RAILS_SE_NW,
                0,
                0,
            },
        },
        {
            {
                SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_SW_NE,
                SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_RAILS_SW_NE,
                0,
                0,
            },
            {
                SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_NW_SE,
                SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_RAILS_NW_SE,
                SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_FRONT_NW_SE,
                SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_RAILS_FRONT_NW_SE,
            },
            {
                SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_NE_SW,
                SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_RAILS_NE_SW,
                SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_FRONT_NE_SW,
                SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_RAILS_FRONT_NE_SW,
            },
            {
                SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_SE_NW,
                SPR_WOODEN_RC_FLAT_TO_25_DEG_CHAIN_RAILS_SE_NW,
                0,
                0,
            },
        },
    };

    uint8_t isChained = trackElement.HasChain() ? 1 : 0;
    wooden_rc_track_paint(
        session, imageIds[isChained][direction][0], imageIds[isChained][direction][1], direction, 0, 0, 32, 25, 2, height, 0, 3,
        height);
    if (direction == 1 || direction == 2)
    {
        wooden_rc_track_paint(
            session, imageIds[isChained][direction][2], imageIds[isChained][direction][3], direction, 0, 0, 32, 1, 9, height, 0,
            26, height + 5);
    }
    wooden_a_supports_paint_setup(session, direction & 1, 1 + direction, height, session.TrackColours[SCHEME_SUPPORTS]);

    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_8);
    }

    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 48, 0x20);
}

/** rct2: 0x008AC5A8 */
static void wooden_rc_track_25_deg_up_to_60_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const uint32_t imageIds[4][4] = {
        {
            SPR_WOODEN_RC_25_DEG_TO_60_DEG_SW_NE,
            SPR_WOODEN_RC_25_DEG_TO_60_DEG_RAILS_SW_NE,
            0,
            0,
        },
        {
            SPR_WOODEN_RC_25_DEG_TO_60_DEG_NW_SE,
            SPR_WOODEN_RC_25_DEG_TO_60_DEG_RAILS_NW_SE,
            SPR_WOODEN_RC_25_DEG_TO_60_DEG_FRONT_NW_SE,
            SPR_WOODEN_RC_25_DEG_TO_60_DEG_RAILS_FRONT_NW_SE,
        },
        {
            SPR_WOODEN_RC_25_DEG_TO_60_DEG_NE_SW,
            SPR_WOODEN_RC_25_DEG_TO_60_DEG_RAILS_NE_SW,
            SPR_WOODEN_RC_25_DEG_TO_60_DEG_FRONT_NE_SW,
            SPR_WOODEN_RC_25_DEG_TO_60_DEG_RAILS_FRONT_NE_SW,
        },
        {
            SPR_WOODEN_RC_25_DEG_TO_60_DEG_SE_NW,
            SPR_WOODEN_RC_25_DEG_TO_60_DEG_RAILS_SE_NW,
            0,
            0,
        },
    };

    if (direction == 0 || direction == 3)
    {
        wooden_rc_track_paint(
            session, imageIds[direction][0], imageIds[direction][1], direction, 0, 0, 32, 25, 2, height, 0, 3, height);
    }
    else
    {
        session.WoodenSupportsPrependTo = wooden_rc_track_paint(
            session, imageIds[direction][0], imageIds[direction][1], direction, 0, 0, 2, 24, 43, height, 28, 4, height + 2);
        wooden_rc_track_paint(
            session, imageIds[direction][2], imageIds[direction][3], direction, 0, 0, 32, 2, 43, height, 0, 4, height);
    }
    wooden_a_supports_paint_setup(session, direction & 1, 13 + direction, height, session.TrackColours[SCHEME_SUPPORTS]);

    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height + 24, TUNNEL_SQUARE_8);
    }

    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 72, 0x20);
}

/** rct2: 0x008AC5B8 */
static void wooden_rc_track_60_deg_up_to_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const uint32_t imageIds[4][4] = {
        {
            SPR_WOODEN_RC_60_DEG_TO_25_DEG_SW_NE,
            SPR_WOODEN_RC_60_DEG_TO_25_DEG_RAILS_SW_NE,
            0,
            0,
        },
        {
            SPR_WOODEN_RC_60_DEG_TO_25_DEG_NW_SE,
            SPR_WOODEN_RC_60_DEG_TO_25_DEG_RAILS_NW_SE,
            SPR_WOODEN_RC_60_DEG_TO_25_DEG_FRONT_NW_SE,
            SPR_WOODEN_RC_60_DEG_TO_25_DEG_RAILS_FRONT_NW_SE,
        },
        {
            SPR_WOODEN_RC_60_DEG_TO_25_DEG_NE_SW,
            SPR_WOODEN_RC_60_DEG_TO_25_DEG_RAILS_NE_SW,
            SPR_WOODEN_RC_60_DEG_TO_25_DEG_FRONT_NE_SW,
            SPR_WOODEN_RC_60_DEG_TO_25_DEG_RAILS_FRONT_NE_SW,
        },
        {
            SPR_WOODEN_RC_60_DEG_TO_25_DEG_SE_NW,
            SPR_WOODEN_RC_60_DEG_TO_25_DEG_RAILS_SE_NW,
            0,
            0,
        },
    };

    if (direction == 0 || direction == 3)
    {
        wooden_rc_track_paint(
            session, imageIds[direction][0], imageIds[direction][1], direction, 0, 0, 32, 25, 2, height, 0, 3, height);
    }
    else
    {
        session.WoodenSupportsPrependTo = wooden_rc_track_paint(
            session, imageIds[direction][0], imageIds[direction][1], direction, 0, 0, 24, 1, 61, height, 4, 28, height - 16);
        wooden_rc_track_paint(
            session, imageIds[direction][2], imageIds[direction][3], direction, 0, 0, 32, 2, 43, height, 0, 4, height);
    }
    wooden_a_supports_paint_setup(session, direction & 1, 17 + direction, height, session.TrackColours[SCHEME_SUPPORTS]);

    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height + 24, TUNNEL_SQUARE_8);
    }

    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 72, 0x20);
}

/** rct2: 0x008AC5C8 */
static void wooden_rc_track_25_deg_up_to_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const uint32_t imageIds[2][4][4] = {
        {
            {
                SPR_WOODEN_RC_25_DEG_TO_FLAT_SW_NE,
                SPR_WOODEN_RC_25_DEG_TO_FLAT_RAILS_SW_NE,
                0,
                0,
            },
            {
                SPR_WOODEN_RC_25_DEG_TO_FLAT_NW_SE,
                SPR_WOODEN_RC_25_DEG_TO_FLAT_RAILS_NW_SE,
                SPR_WOODEN_RC_25_DEG_TO_FLAT_FRONT_NW_SE,
                SPR_WOODEN_RC_25_DEG_TO_FLAT_RAILS_FRONT_NW_SE,
            },
            {
                SPR_WOODEN_RC_25_DEG_TO_FLAT_NE_SW,
                SPR_WOODEN_RC_25_DEG_TO_FLAT_RAILS_NE_SW,
                SPR_WOODEN_RC_25_DEG_TO_FLAT_FRONT_NE_SW,
                SPR_WOODEN_RC_25_DEG_TO_FLAT_RAILS_FRONT_NE_SW,
            },
            {
                SPR_WOODEN_RC_25_DEG_TO_FLAT_SE_NW,
                SPR_WOODEN_RC_25_DEG_TO_FLAT_RAILS_SE_NW,
                0,
                0,
            },
        },
        {
            {
                SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_SW_NE,
                SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_RAILS_SW_NE,
                0,
                0,
            },
            {
                SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_NW_SE,
                SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_RAILS_NW_SE,
                SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_FRONT_NW_SE,
                SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_RAILS_FRONT_NW_SE,
            },
            {
                SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_NE_SW,
                SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_RAILS_NE_SW,
                SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_FRONT_NE_SW,
                SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_RAILS_FRONT_NE_SW,
            },
            {
                SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_SE_NW,
                SPR_WOODEN_RC_25_DEG_TO_FLAT_CHAIN_RAILS_SE_NW,
                0,
                0,
            },
        },
    };

    uint8_t isChained = trackElement.HasChain() ? 1 : 0;
    wooden_rc_track_paint(
        session, imageIds[isChained][direction][0], imageIds[isChained][direction][1], direction, 0, 0, 32, 25, 2, height, 0, 3,
        height);
    if (direction == 1 || direction == 2)
    {
        wooden_rc_track_paint(
            session, imageIds[isChained][direction][2], imageIds[isChained][direction][3], direction, 0, 0, 32, 1, 9, height, 0,
            26, height + 5);
    }
    wooden_a_supports_paint_setup(session, direction & 1, 5 + direction, height, session.TrackColours[SCHEME_SUPPORTS]);

    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_FLAT);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height + 8, TUNNEL_14);
    }

    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 40, 0x20);
}

/** rct2: 0x008AC5D8 */
static void wooden_rc_track_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_25_deg_up(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008AC5E8 */
static void wooden_rc_track_60_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_60_deg_up(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008AC5F8 */
static void wooden_rc_track_flat_to_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_25_deg_up_to_flat(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008AC608 */
static void wooden_rc_track_25_deg_down_to_60_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_60_deg_up_to_25_deg_up(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008AC618 */
static void wooden_rc_track_60_deg_down_to_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_25_deg_up_to_60_deg_up(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008AC628 */
static void wooden_rc_track_25_deg_down_to_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_flat_to_25_deg_up(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

static void wooden_rc_track_right_quarter_turn_5(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const sprite_bb_2 imageIds[2][4][7] = {
        {
            {
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_SW_SE_SEQ_0,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SW_SE_SEQ_0,
                    { 0, 2, 0 },
                    { 0, 2, 0 },
                    { 32, 32, 2 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_SW_SE_SEQ_2,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SW_SE_SEQ_2,
                    { 0, 16, 0 },
                    { 0, 16, 0 },
                    { 32, 16, 2 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_SW_SE_SEQ_3,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SW_SE_SEQ_3,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 16, 16, 2 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_SW_SE_SEQ_5,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SW_SE_SEQ_5,
                    { 16, 0, 0 },
                    { 16, 0, 0 },
                    { 16, 32, 2 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_SW_SE_SEQ_6,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SW_SE_SEQ_6,
                    { 2, 0, 0 },
                    { 2, 0, 0 },
                    { 32, 32, 2 },
                },
            },
            {
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_NW_SW_SEQ_0,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NW_SW_SEQ_0,
                    { 2, 0, 0 },
                    { 2, 0, 0 },
                    { 32, 32, 2 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_NW_SW_SEQ_2,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NW_SW_SEQ_2,
                    { 16, 0, 0 },
                    { 16, 0, 0 },
                    { 16, 34, 2 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_NW_SW_SEQ_3,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NW_SW_SEQ_3,
                    { 0, 16, 0 },
                    { 0, 16, 0 },
                    { 16, 16, 2 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_NW_SW_SEQ_5,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NW_SW_SEQ_5,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 32, 16, 2 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_NW_SW_SEQ_6,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NW_SW_SEQ_6,
                    { 0, 2, 0 },
                    { 0, 2, 0 },
                    { 32, 27, 2 },
                },
            },
            {
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_NE_NW_SEQ_0,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NE_NW_SEQ_0,
                    { 0, 2, 0 },
                    { 0, 2, 0 },
                    { 32, 27, 2 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_NE_NW_SEQ_2,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NE_NW_SEQ_2,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 32, 16, 2 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_NE_NW_SEQ_3,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NE_NW_SEQ_3,
                    { 16, 16, 0 },
                    { 16, 16, 0 },
                    { 16, 16, 2 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_NE_NW_SEQ_5,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NE_NW_SEQ_5,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 16, 32, 2 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_NE_NW_SEQ_6,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_NE_NW_SEQ_6,
                    { 2, 0, 0 },
                    { 2, 0, 0 },
                    { 27, 32, 2 },
                },
            },
            {
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_SE_NE_SEQ_0,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SE_NE_SEQ_0,
                    { 2, 0, 0 },
                    { 2, 0, 0 },
                    { 27, 32, 2 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_SE_NE_SEQ_2,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SE_NE_SEQ_2,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 16, 32, 2 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_SE_NE_SEQ_3,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SE_NE_SEQ_3,
                    { 16, 0, 0 },
                    { 16, 0, 0 },
                    { 16, 16, 2 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_SE_NE_SEQ_5,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SE_NE_SEQ_5,
                    { 0, 16, 0 },
                    { 0, 16, 0 },
                    { 32, 16, 2 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_SE_NE_SEQ_6,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_SE_NE_SEQ_6,
                    { 0, 2, 0 },
                    { 0, 2, 0 },
                    { 32, 32, 2 },
                },
            },
        },
        {
            {
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_SW_SE_SEQ_0,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_0,
                    { 0, 2, 0 },
                    { 0, 2, 27 },
                    { 32, 32, 0 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_SW_SE_SEQ_2,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_2,
                    { 0, 16, 0 },
                    { 0, 16, 27 },
                    { 32, 16, 0 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_SW_SE_SEQ_3,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_3,
                    { 0, 0, 0 },
                    { 0, 0, 27 },
                    { 16, 16, 0 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_SW_SE_SEQ_5,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_5,
                    { 16, 0, 0 },
                    { 16, 0, 27 },
                    { 16, 32, 0 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_SW_SE_SEQ_6,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_6,
                    { 2, 0, 0 },
                    { 2, 0, 27 },
                    { 32, 32, 0 },
                },
            },
            {
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
            },
            {
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_NE_NW_SEQ_0,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_0,
                    { 0, 2, 0 },
                    { 0, 2, 27 },
                    { 32, 27, 0 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_NE_NW_SEQ_2,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_2,
                    { 0, 0, 0 },
                    { 0, 0, 27 },
                    { 32, 16, 0 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_NE_NW_SEQ_3,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_3,
                    { 16, 16, 0 },
                    { 16, 16, 27 },
                    { 16, 16, 0 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_NE_NW_SEQ_5,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_5,
                    { 0, 0, 0 },
                    { 0, 0, 27 },
                    { 16, 32, 0 },
                },
                {
                    SPR_WOODEN_RC_QUARTER_TURN_5_FRONT_NE_NW_SEQ_6,
                    SPR_WOODEN_RC_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_6,
                    { 2, 0, 0 },
                    { 2, 0, 27 },
                    { 27, 32, 0 },
                },
            },
            {
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
            },
        },
    };
    static int8_t supportType[4][7] = {
        { 0, -1, 4, 2, -1, 4, 1 },
        { 1, -1, 5, 3, -1, 5, 0 },
        { 0, -1, 2, 4, -1, 2, 1 },
        { 1, -1, 3, 5, -1, 3, 0 },
    };

    wooden_rc_track_paint_bb(session, &imageIds[0][direction][trackSequence], height);
    wooden_rc_track_paint_bb(session, &imageIds[1][direction][trackSequence], height);
    track_paint_util_right_quarter_turn_5_tiles_tunnel(session, height, direction, trackSequence, TUNNEL_SQUARE_FLAT);

    if (supportType[direction][trackSequence] != -1)
    {
        wooden_a_supports_paint_setup(
            session, supportType[direction][trackSequence], 0, height, session.TrackColours[SCHEME_SUPPORTS]);
    }

    int32_t blockedSegments = 0;
    switch (trackSequence)
    {
        case 0:
            blockedSegments = SEGMENTS_ALL;
            break;
        case 1:
            blockedSegments = SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC;
            break;
        case 2:
            blockedSegments = SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4;
            break;
        case 3:
            blockedSegments = SEGMENT_B4 | SEGMENT_B8 | SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0
                | SEGMENT_D4;
            break;
        case 4:
            blockedSegments = SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC;
            break;
        case 5:
            blockedSegments = SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4;
            break;
        case 6:
            blockedSegments = SEGMENT_B4 | SEGMENT_B8 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC
                | SEGMENT_D0 | SEGMENT_D4;
            break;
    }
    paint_util_set_segment_support_height(session, paint_util_rotate_segments(blockedSegments, direction), 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 32, 0x20);
}

static void wooden_rc_track_left_quarter_turn_5(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    wooden_rc_track_right_quarter_turn_5(session, ride, trackSequence, (direction + 1) & 3, height, trackElement);
}

/** rct2: 0x008AC658 */
static void wooden_rc_track_flat_to_left_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const uint32_t imageIds[4][4] = {
        {
            SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_SW_NE,
            SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_RAILS_SW_NE,
            0,
            0,
        },
        {
            SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_NW_SE,
            SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_RAILS_NW_SE,
            SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_FRONT_NW_SE,
            SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_RAILS_FRONT_NW_SE,
        },
        {
            SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_NE_SW,
            SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_RAILS_NE_SW,
            0,
            0,
        },
        {
            SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_SE_NW,
            SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_RAILS_SE_NW,
            SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_FRONT_SE_NW,
            SPR_WOODEN_RC_FLAT_TO_LEFT_BANK_RAILS_FRONT_SE_NW,
        },
    };

    wooden_rc_track_paint(
        session, imageIds[direction][0], imageIds[direction][1], direction, 0, 0, 32, 25, 2, height, 0, 3, height);
    if (direction == 1 || direction == 3)
    {
        wooden_rc_track_paint(
            session, imageIds[direction][2], imageIds[direction][3], direction, 0, 0, 32, 1, 9, height, 0, 26, height + 5);
    }
    wooden_a_supports_paint_setup(session, direction & 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
    paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 32, 0x20);
}

/** rct2: 0x008AC668 */
static void wooden_rc_track_flat_to_right_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const uint32_t imageIds[4][4] = {
        {
            SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_SW_NE,
            SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_RAILS_SW_NE,
            SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_FRONT_SW_NE,
            SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_RAILS_FRONT_SW_NE,
        },
        {
            SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_NW_SE,
            SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_RAILS_NW_SE,
            0,
            0,
        },
        {
            SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_NE_SW,
            SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_RAILS_NE_SW,
            SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_FRONT_NE_SW,
            SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_RAILS_FRONT_NE_SW,
        },
        {
            SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_SE_NW,
            SPR_WOODEN_RC_FLAT_TO_RIGHT_BANK_RAILS_SE_NW,
            0,
            0,
        },
    };

    wooden_rc_track_paint(
        session, imageIds[direction][0], imageIds[direction][1], direction, 0, 0, 32, 25, 2, height, 0, 3, height);
    if (direction == 0 || direction == 2)
    {
        wooden_rc_track_paint(
            session, imageIds[direction][2], imageIds[direction][3], direction, 0, 0, 32, 1, 9, height, 0, 26, height + 5);
    }
    wooden_a_supports_paint_setup(session, direction & 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
    paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 32, 0x20);
}

/** rct2: 0x008AC678 */
static void wooden_rc_track_left_bank_to_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_flat_to_right_bank(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008AC688 */
static void wooden_rc_track_right_bank_to_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_flat_to_left_bank(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

static void wooden_rc_track_banked_right_quarter_turn_5(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const sprite_bb_2 imageIds[2][4][7] = {
        {
            {
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SW_SE_SEQ_0,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SW_SE_SEQ_0,
                    { 0, 0, 0 },
                    { 0, 2, 0 },
                    { 32, 32, 2 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SW_SE_SEQ_2,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SW_SE_SEQ_2,
                    { 0, 0, 0 },
                    { 0, 16, 0 },
                    { 32, 16, 2 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SW_SE_SEQ_3,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SW_SE_SEQ_3,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 16, 16, 2 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SW_SE_SEQ_5,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SW_SE_SEQ_5,
                    { 0, 0, 0 },
                    { 16, 0, 0 },
                    { 16, 32, 2 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SW_SE_SEQ_6,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SW_SE_SEQ_6,
                    { 0, 0, 0 },
                    { 2, 0, 0 },
                    { 32, 32, 2 },
                },
            },
            {
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NW_SW_SEQ_0,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NW_SW_SEQ_0,
                    { 0, 0, 0 },
                    { 2, 0, 0 },
                    { 32, 32, 2 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NW_SW_SEQ_2,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NW_SW_SEQ_2,
                    { 0, 0, 0 },
                    { 16, 0, 0 },
                    { 16, 32, 2 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NW_SW_SEQ_3,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NW_SW_SEQ_3,
                    { 0, 0, 0 },
                    { 0, 16, 0 },
                    { 16, 16, 2 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NW_SW_SEQ_5,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NW_SW_SEQ_5,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 32, 16, 2 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NW_SW_SEQ_6,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NW_SW_SEQ_6,
                    { 0, 0, 0 },
                    { 0, 2, 0 },
                    { 32, 27, 2 },
                },
            },
            {
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NE_NW_SEQ_0,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NE_NW_SEQ_0,
                    { 0, 0, 0 },
                    { 0, 2, 0 },
                    { 32, 27, 2 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NE_NW_SEQ_2,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NE_NW_SEQ_2,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 32, 16, 2 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NE_NW_SEQ_3,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NE_NW_SEQ_3,
                    { 0, 0, 0 },
                    { 16, 16, 0 },
                    { 16, 16, 2 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NE_NW_SEQ_5,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NE_NW_SEQ_5,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 16, 32, 2 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_NE_NW_SEQ_6,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_NE_NW_SEQ_6,
                    { 0, 0, 0 },
                    { 2, 0, 0 },
                    { 27, 32, 2 },
                },
            },
            {
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SE_NE_SEQ_0,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SE_NE_SEQ_0,
                    { 0, 0, 0 },
                    { 2, 0, 0 },
                    { 27, 32, 2 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SE_NE_SEQ_2,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SE_NE_SEQ_2,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 16, 32, 2 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SE_NE_SEQ_3,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SE_NE_SEQ_3,
                    { 0, 0, 0 },
                    { 16, 0, 0 },
                    { 16, 16, 2 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SE_NE_SEQ_5,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SE_NE_SEQ_5,
                    { 0, 0, 0 },
                    { 0, 16, 0 },
                    { 32, 16, 2 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_SE_NE_SEQ_6,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_SE_NE_SEQ_6,
                    { 0, 0, 0 },
                    { 0, 2, 0 },
                    { 32, 32, 2 },
                },
            },
        },
        {
            {
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_SW_SE_SEQ_0,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_0,
                    { 0, 0, 0 },
                    { 0, 2, 27 },
                    { 32, 32, 0 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_SW_SE_SEQ_2,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_2,
                    { 0, 0, 0 },
                    { 0, 16, 27 },
                    { 32, 16, 0 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_SW_SE_SEQ_3,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_3,
                    { 0, 0, 0 },
                    { 0, 0, 27 },
                    { 16, 16, 0 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_SW_SE_SEQ_5,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_5,
                    { 0, 0, 0 },
                    { 16, 0, 27 },
                    { 16, 32, 0 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_SW_SE_SEQ_6,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_SW_SE_SEQ_6,
                    { 0, 0, 0 },
                    { 2, 0, 27 },
                    { 32, 32, 0 },
                },
            },
            {
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
            },
            {
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_NE_NW_SEQ_0,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_0,
                    { 0, 0, 0 },
                    { 0, 2, 27 },
                    { 32, 27, 0 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_NE_NW_SEQ_2,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_2,
                    { 0, 0, 0 },
                    { 0, 0, 27 },
                    { 32, 16, 0 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_NE_NW_SEQ_3,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_3,
                    { 0, 0, 0 },
                    { 16, 16, 27 },
                    { 16, 16, 0 },
                },
                {
                    0,
                    0,
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                    { 0, 0, 0 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_NE_NW_SEQ_5,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_5,
                    { 0, 0, 0 },
                    { 0, 0, 27 },
                    { 16, 32, 0 },
                },
                {
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_FRONT_NE_NW_SEQ_6,
                    SPR_WOODEN_RC_BANKED_QUARTER_TURN_5_RAILS_FRONT_NE_NW_SEQ_6,
                    { 0, 0, 0 },
                    { 2, 0, 27 },
                    { 27, 32, 0 },
                },
            },
            {
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
                { 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
            },
        },
    };
    static int8_t supportType[4][7] = {
        { 0, -1, 4, 2, -1, 4, 1 },
        { 1, -1, 5, 3, -1, 5, 0 },
        { 0, -1, 2, 4, -1, 2, 1 },
        { 1, -1, 3, 5, -1, 3, 0 },
    };

    wooden_rc_track_paint_bb(session, &imageIds[0][direction][trackSequence], height);
    wooden_rc_track_paint_bb(session, &imageIds[1][direction][trackSequence], height);
    track_paint_util_right_quarter_turn_5_tiles_tunnel(session, height, direction, trackSequence, TUNNEL_SQUARE_FLAT);

    if (supportType[direction][trackSequence] != -1)
    {
        wooden_a_supports_paint_setup(
            session, supportType[direction][trackSequence], 0, height, session.TrackColours[SCHEME_SUPPORTS]);
    }

    int32_t blockedSegments = 0;
    switch (trackSequence)
    {
        case 0:
            blockedSegments = SEGMENTS_ALL;
            break;
        case 1:
            blockedSegments = SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC;
            break;
        case 2:
            blockedSegments = SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4;
            break;
        case 3:
            blockedSegments = SEGMENT_B4 | SEGMENT_B8 | SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0
                | SEGMENT_D4;
            break;
        case 4:
            blockedSegments = SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC;
            break;
        case 5:
            blockedSegments = SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4;
            break;
        case 6:
            blockedSegments = SEGMENT_B4 | SEGMENT_B8 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC
                | SEGMENT_D0 | SEGMENT_D4;
            break;
    }
    paint_util_set_segment_support_height(session, paint_util_rotate_segments(blockedSegments, direction), 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 32, 0x20);
}

static void wooden_rc_track_banked_left_quarter_turn_5(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    wooden_rc_track_banked_right_quarter_turn_5(session, ride, trackSequence, (direction + 1) & 3, height, trackElement);
}

/** rct2: 0x008AC6B8 */
static void wooden_rc_track_left_bank_to_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const uint32_t imageIds[4][4] = {
        {
            SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_SW_NE,
            SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_RAILS_SW_NE,
            0,
            0,
        },
        {
            SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_NW_SE,
            SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_RAILS_NW_SE,
            SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_FRONT_NW_SE,
            SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_RAILS_FRONT_NW_SE,
        },
        {
            SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_NE_SW,
            SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_RAILS_NE_SW,
            SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_FRONT_NE_SW,
            SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_RAILS_FRONT_NE_SW,
        },
        {
            SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_SE_NW,
            SPR_WOODEN_RC_LEFT_BANK_TO_25_DEG_RAILS_SE_NW,
            0,
            0,
        },
    };

    wooden_rc_track_paint(
        session, imageIds[direction][0], imageIds[direction][1], direction, 0, 0, 32, 25, 2, height, 0, 3, height);
    if (direction == 1 || direction == 2)
    {
        wooden_rc_track_paint(
            session, imageIds[direction][2], imageIds[direction][3], direction, 0, 0, 32, 1, 9, height, 0, 26, height + 5);
    }
    wooden_a_supports_paint_setup(session, direction & 1, 1 + direction, height, session.TrackColours[SCHEME_SUPPORTS]);
    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_8);
    }
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 48, 0x20);
}

/** rct2: 0x008AC6C8 */
static void wooden_rc_track_right_bank_to_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const uint32_t imageIds[4][4] = {
        {
            SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_SW_NE,
            SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_RAILS_SW_NE,
            0,
            0,
        },
        {
            SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_NW_SE,
            SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_RAILS_NW_SE,
            SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_FRONT_NW_SE,
            SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_RAILS_FRONT_NW_SE,
        },
        {
            SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_NE_SW,
            SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_RAILS_NE_SW,
            SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_FRONT_NE_SW,
            SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_RAILS_FRONT_NE_SW,
        },
        {
            SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_SE_NW,
            SPR_WOODEN_RC_RIGHT_BANK_TO_25_DEG_RAILS_SE_NW,
            0,
            0,
        },
    };

    wooden_rc_track_paint(
        session, imageIds[direction][0], imageIds[direction][1], direction, 0, 0, 32, 25, 2, height, 0, 3, height);
    if (direction == 1 || direction == 2)
    {
        wooden_rc_track_paint(
            session, imageIds[direction][2], imageIds[direction][3], direction, 0, 0, 32, 1, 9, height, 0, 26, height + 5);
    }
    wooden_a_supports_paint_setup(session, direction & 1, 1 + direction, height, session.TrackColours[SCHEME_SUPPORTS]);
    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_8);
    }
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 48, 0x20);
}

/** rct2: 0x008AC6D8 */
static void wooden_rc_track_25_deg_up_to_left_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const uint32_t imageIds[4][4] = {
        {
            SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_SW_NE,
            SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_RAILS_SW_NE,
            0,
            0,
        },
        {
            SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_NW_SE,
            SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_RAILS_NW_SE,
            SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_FRONT_NW_SE,
            SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_RAILS_FRONT_NW_SE,
        },
        {
            SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_NE_SW,
            SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_RAILS_NE_SW,
            SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_FRONT_NE_SW,
            SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_RAILS_FRONT_NE_SW,
        },
        {
            SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_SE_NW,
            SPR_WOODEN_RC_25_DEG_TO_LEFT_BANK_RAILS_SE_NW,
            0,
            0,
        },
    };

    wooden_rc_track_paint(
        session, imageIds[direction][0], imageIds[direction][1], direction, 0, 0, 32, 25, 2, height, 0, 3, height);
    if (direction == 1 || direction == 2)
    {
        wooden_rc_track_paint(
            session, imageIds[direction][2], imageIds[direction][3], direction, 0, 0, 32, 1, 9, height, 0, 26, height + 5);
    }
    wooden_a_supports_paint_setup(session, direction & 1, 5 + direction, height, session.TrackColours[SCHEME_SUPPORTS]);
    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_FLAT);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height + 8, TUNNEL_14);
    }
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 40, 0x20);
}

/** rct2: 0x008AC6E8 */
static void wooden_rc_track_25_deg_up_to_right_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const uint32_t imageIds[4][4] = {
        {
            SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_SW_NE,
            SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_RAILS_SW_NE,
            0,
            0,
        },
        {
            SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_NW_SE,
            SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_RAILS_NW_SE,
            SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_FRONT_NW_SE,
            SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_RAILS_FRONT_NW_SE,
        },
        {
            SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_NE_SW,
            SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_RAILS_NE_SW,
            SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_FRONT_NE_SW,
            SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_RAILS_FRONT_NE_SW,
        },
        {
            SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_SE_NW,
            SPR_WOODEN_RC_25_DEG_TO_RIGHT_BANK_RAILS_SE_NW,
            0,
            0,
        },
    };

    wooden_rc_track_paint(
        session, imageIds[direction][0], imageIds[direction][1], direction, 0, 0, 32, 25, 2, height, 0, 3, height);
    if (direction == 1 || direction == 2)
    {
        wooden_rc_track_paint(
            session, imageIds[direction][2], imageIds[direction][3], direction, 0, 0, 32, 1, 9, height, 0, 26, height + 5);
    }
    wooden_a_supports_paint_setup(session, direction & 1, 5 + direction, height, session.TrackColours[SCHEME_SUPPORTS]);
    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_FLAT);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height + 8, TUNNEL_14);
    }
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 40, 0x20);
}

/** rct2: 0x008AC6F8 */
static void wooden_rc_track_left_bank_to_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_25_deg_up_to_right_bank(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008AC708 */
static void wooden_rc_track_right_bank_to_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_25_deg_up_to_left_bank(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008AC718 */
static void wooden_rc_track_25_deg_down_to_left_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_right_bank_to_25_deg_up(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008AC728 */
static void wooden_rc_track_25_deg_down_to_right_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_left_bank_to_25_deg_up(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008AC738 */
static void wooden_rc_track_left_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const uint32_t imageIds[4][2] = {
        { SPR_WOODEN_RC_LEFT_BANK_SW_NE, SPR_WOODEN_RC_LEFT_BANK_RAILS_SW_NE },
        { SPR_WOODEN_RC_LEFT_BANK_NW_SE, SPR_WOODEN_RC_LEFT_BANK_RAILS_NW_SE },
        { SPR_WOODEN_RC_LEFT_BANK_NE_SW, SPR_WOODEN_RC_LEFT_BANK_RAILS_NE_SW },
        { SPR_WOODEN_RC_LEFT_BANK_SE_NW, SPR_WOODEN_RC_LEFT_BANK_RAILS_SE_NW },
    };

    wooden_rc_track_paint(
        session, imageIds[direction][0], imageIds[direction][1], direction, 0, 0, 32, 25, 2, height, 0, 3, height);
    wooden_a_supports_paint_setup(session, direction & 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
    paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 32, 0x20);
}

/** rct2: 0x008AC748 */
static void wooden_rc_track_right_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_left_bank(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008AC758 */
static void wooden_rc_track_left_quarter_turn_5_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23781, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24647, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    wooden_a_supports_paint_setup(session, 0, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23786, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24652, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23812, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24678, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 67 });
                    wooden_a_supports_paint_setup(session, 1, 10, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23791, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24657, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    wooden_a_supports_paint_setup(session, 0, 11, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23796, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24662, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    wooden_a_supports_paint_setup(session, 1, 12, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 1:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_BC | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23782, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24648, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23787, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24653, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23813, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24679, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23792, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24658, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23797, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24663, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23819, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24685, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23783, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24649, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23788, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24654, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23814, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 59 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24680, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 59 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23793, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24659, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23798, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24664, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23820, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 59 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24686, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 59 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B4 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4,
                    direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 64, 0x20);
            break;
        case 4:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_BC | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23784, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24650, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23789, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24655, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23815, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24681, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23794, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24660, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23817, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24683, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23799, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24665, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23821, { 0, 0, height }, { 16, 32, 0 },
                        { 16, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24687, { 0, 0, height }, { 16, 32, 0 },
                        { 16, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23785, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24651, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    wooden_a_supports_paint_setup(session, 1, 12, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23790, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24656, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23816, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24682, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 0, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23795, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24661, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23818, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24684, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 1, 10, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23800, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24666, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23822, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24688, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 0, 11, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 2:
                    paint_util_push_tunnel_right(session, height + 8, TUNNEL_SQUARE_8);
                    break;
                case 3:
                    paint_util_push_tunnel_left(session, height + 8, TUNNEL_SQUARE_8);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
    }
}

/** rct2: 0x008AC768 */
static void wooden_rc_track_right_quarter_turn_5_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23761, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24627, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    wooden_a_supports_paint_setup(session, 0, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23766, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24632, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    wooden_a_supports_paint_setup(session, 1, 10, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23771, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24637, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23807, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24673, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 67 });
                    wooden_a_supports_paint_setup(session, 0, 11, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23776, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24642, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    wooden_a_supports_paint_setup(session, 1, 12, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 1:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23762, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24628, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23801, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24667, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23767, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24633, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23772, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24638, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23808, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24674, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23777, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24643, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23763, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24629, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23802, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 59 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24668, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 59 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23768, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24634, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23773, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24639, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23809, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 59 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24675, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 59 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23778, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24644, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B4 | SEGMENT_B8 | SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4,
                    direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 64, 0x20);
            break;
        case 4:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23764, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24630, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23803, { 0, 0, height }, { 16, 32, 0 },
                        { 16, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24669, { 0, 0, height }, { 16, 32, 0 },
                        { 16, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23769, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24635, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23805, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24671, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23774, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24640, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23810, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24676, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23779, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24645, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23765, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24631, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23804, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24670, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 1, 10, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23770, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24636, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23806, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24672, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 0, 11, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23775, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24641, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23811, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24677, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 1, 12, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23780, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24646, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    wooden_a_supports_paint_setup(session, 0, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 0:
                    paint_util_push_tunnel_right(session, height + 8, TUNNEL_SQUARE_8);
                    break;
                case 1:
                    paint_util_push_tunnel_left(session, height + 8, TUNNEL_SQUARE_8);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
    }
}

/** rct2: 0x008AC778 */
static void wooden_rc_track_left_quarter_turn_5_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    wooden_rc_track_right_quarter_turn_5_25_deg_up(session, ride, trackSequence, (direction + 1) & 3, height, trackElement);
}

/** rct2: 0x008AC788 */
static void wooden_rc_track_right_quarter_turn_5_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    wooden_rc_track_left_quarter_turn_5_25_deg_up(session, ride, trackSequence, (direction - 1) & 3, height, trackElement);
}

/** rct2: 0x008AC798 */
static void wooden_rc_track_s_bend_left(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23725, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24591, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23729, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24595, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23741, { 0, 0, height }, { 32, 25, 0 },
                        { 0, 3, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24607, { 0, 0, height }, { 32, 25, 0 },
                        { 0, 3, height + 27 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23728, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24594, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23732, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24598, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23744, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24610, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 27 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23726, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24592, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23730, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24596, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23742, { 0, 0, height }, { 32, 26, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24608, { 0, 0, height }, { 32, 26, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23727, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24593, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23731, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24597, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23743, { 0, 0, height }, { 32, 26, 0 },
                        { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24609, { 0, 0, height }, { 32, 26, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23727, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24593, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23731, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24597, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23743, { 0, 0, height }, { 32, 26, 0 },
                        { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24609, { 0, 0, height }, { 32, 26, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23726, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24592, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23730, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24596, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23742, { 0, 0, height }, { 32, 26, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24608, { 0, 0, height }, { 32, 26, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23728, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24594, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23732, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24598, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23744, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24610, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 27 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23725, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24591, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23729, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24595, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23741, { 0, 0, height }, { 32, 25, 0 },
                        { 0, 3, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24607, { 0, 0, height }, { 32, 25, 0 },
                        { 0, 3, height + 27 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 1:
                    paint_util_push_tunnel_right(session, height, TUNNEL_SQUARE_FLAT);
                    break;
                case 2:
                    paint_util_push_tunnel_left(session, height, TUNNEL_SQUARE_FLAT);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008AC7A8 */
static void wooden_rc_track_s_bend_right(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23733, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24599, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23745, { 0, 0, height }, { 32, 25, 0 },
                        { 0, 3, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24611, { 0, 0, height }, { 32, 25, 0 },
                        { 0, 3, height + 27 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23737, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24603, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23736, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24602, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23748, { 0, 0, height }, { 32, 25, 0 },
                        { 0, 3, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24614, { 0, 0, height }, { 32, 25, 0 },
                        { 0, 3, height + 27 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23740, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24606, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23734, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24600, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23746, { 0, 0, height }, { 32, 26, 0 },
                        { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24612, { 0, 0, height }, { 32, 26, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23738, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24604, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23735, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24601, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23747, { 0, 0, height }, { 32, 26, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24613, { 0, 0, height }, { 32, 26, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23739, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24605, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23735, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24601, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23747, { 0, 0, height }, { 32, 26, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24613, { 0, 0, height }, { 32, 26, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23739, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24605, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23734, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24600, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23746, { 0, 0, height }, { 32, 26, 0 },
                        { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24612, { 0, 0, height }, { 32, 26, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23738, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24604, { 0, 0, height }, { 32, 26, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23736, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24602, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23748, { 0, 0, height }, { 32, 25, 0 },
                        { 0, 3, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24614, { 0, 0, height }, { 32, 25, 0 },
                        { 0, 3, height + 27 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23740, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24606, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23733, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24599, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23745, { 0, 0, height }, { 32, 25, 0 },
                        { 0, 3, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24611, { 0, 0, height }, { 32, 25, 0 },
                        { 0, 3, height + 27 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23737, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24603, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 1:
                    paint_util_push_tunnel_right(session, height, TUNNEL_SQUARE_FLAT);
                    break;
                case 2:
                    paint_util_push_tunnel_left(session, height, TUNNEL_SQUARE_FLAT);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008ACE18 */
static void wooden_rc_track_left_vertical_loop(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23453, { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23461, { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23460, { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23468, { 0, 6, height }, { 32, 20, 7 });
                    break;
            }
            metal_a_supports_paint_setup(session, METAL_SUPPORTS_BOXED, 4, 8, height, session.TrackColours[SCHEME_SUPPORTS]);
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23454, { 0, 0, height }, { 32, 26, 3 });
                    metal_a_supports_paint_setup(
                        session, METAL_SUPPORTS_BOXED, 4, 20, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23462, { 0, 14, height }, { 32, 2, 63 });
                    metal_a_supports_paint_setup(
                        session, METAL_SUPPORTS_BOXED, 4, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23459, { 0, 6, height }, { 32, 26, 3 });
                    metal_a_supports_paint_setup(
                        session, METAL_SUPPORTS_BOXED, 4, 16, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23467, { 0, 6, height }, { 32, 26, 3 });
                    metal_a_supports_paint_setup(
                        session, METAL_SUPPORTS_BOXED, 4, 16, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23455, { 16, 0, height }, { 5, 16, 119 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23463, { 12, 0, height }, { 3, 16, 119 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23458, { 10, 16, height }, { 4, 16, 119 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23466, { 16, 16, height }, { 4, 16, 119 });
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 168, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23456, { 0, 0, height + 32 }, { 32, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23464, { 0, 0, height + 32 }, { 32, 16, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23457, { 0, 16, height + 32 }, { 32, 16, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23465, { 0, 16, height + 32 }, { 32, 16, 3 });
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 4:
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 5:
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23457, { 0, 16, height + 32 }, { 32, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23465, { 0, 16, height + 32 }, { 32, 16, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23456, { 0, 0, height + 32 }, { 32, 16, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23464, { 0, 0, height + 32 }, { 32, 16, 3 });
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 7:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23458, { 10, 16, height }, { 4, 16, 119 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23466, { 16, 16, height }, { 4, 16, 119 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23455, { 16, 0, height }, { 5, 16, 119 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23463, { 12, 0, height }, { 3, 16, 119 });
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 168, 0x20);
            break;
        case 8:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23459, { 0, 6, height }, { 32, 26, 3 });
                    metal_a_supports_paint_setup(
                        session, METAL_SUPPORTS_BOXED, 4, 16, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23467, { 0, 6, height }, { 32, 26, 3 });
                    metal_a_supports_paint_setup(
                        session, METAL_SUPPORTS_BOXED, 4, 16, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23454, { 0, 0, height }, { 32, 26, 3 });
                    metal_a_supports_paint_setup(
                        session, METAL_SUPPORTS_BOXED, 4, 20, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23462, { 0, 14, height }, { 32, 2, 63 });
                    metal_a_supports_paint_setup(
                        session, METAL_SUPPORTS_BOXED, 4, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 9:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23460, { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23468, { 0, 6, height }, { 32, 20, 7 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23453, { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23461, { 0, 6, height }, { 32, 20, 3 });
                    break;
            }
            metal_a_supports_paint_setup(session, METAL_SUPPORTS_BOXED, 4, 8, height, session.TrackColours[SCHEME_SUPPORTS]);
            switch (direction)
            {
                case 1:
                    paint_util_push_tunnel_right(session, height - 8, TUNNEL_SQUARE_7);
                    break;
                case 2:
                    paint_util_push_tunnel_left(session, height - 8, TUNNEL_SQUARE_7);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
    }
}

/** rct2: 0x008ACE28 */
static void wooden_rc_track_right_vertical_loop(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23484, { 0, 6, height }, { 32, 20, 7 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23476, { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23477, { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23469, { 0, 6, height }, { 32, 20, 3 });
                    break;
            }
            metal_a_supports_paint_setup(session, METAL_SUPPORTS_BOXED, 4, 8, height, session.TrackColours[SCHEME_SUPPORTS]);
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
            }
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23483, { 0, 6, height }, { 32, 26, 3 });
                    metal_a_supports_paint_setup(
                        session, METAL_SUPPORTS_BOXED, 4, 16, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23475, { 0, 6, height }, { 32, 26, 3 });
                    metal_a_supports_paint_setup(
                        session, METAL_SUPPORTS_BOXED, 4, 16, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23478, { 0, 14, height }, { 32, 2, 63 });
                    metal_a_supports_paint_setup(
                        session, METAL_SUPPORTS_BOXED, 4, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23470, { 0, 0, height }, { 32, 26, 3 });
                    metal_a_supports_paint_setup(
                        session, METAL_SUPPORTS_BOXED, 4, 20, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23482, { 16, 16, height }, { 4, 16, 119 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23474, { 10, 16, height }, { 4, 16, 119 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23479, { 12, 0, height }, { 3, 16, 119 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23471, { 16, 0, height }, { 5, 16, 119 });
                    break;
            }
            paint_util_set_general_support_height(session, height + 168, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23481, { 0, 16, height + 32 }, { 32, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23473, { 0, 16, height + 32 }, { 32, 16, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23480, { 0, 0, height + 32 }, { 32, 16, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23472, { 0, 0, height + 32 }, { 32, 16, 3 });
                    break;
            }
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 4:
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 5:
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23480, { 0, 0, height + 32 }, { 32, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23472, { 0, 0, height + 32 }, { 32, 16, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23481, { 0, 16, height + 32 }, { 32, 16, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23473, { 0, 16, height + 32 }, { 32, 16, 3 });
                    break;
            }
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 7:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23479, { 12, 0, height }, { 3, 16, 119 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23471, { 16, 0, height }, { 5, 16, 119 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23482, { 16, 16, height }, { 4, 16, 119 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23474, { 10, 16, height }, { 4, 16, 119 });
                    break;
            }
            paint_util_set_general_support_height(session, height + 168, 0x20);
            break;
        case 8:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23478, { 0, 14, height }, { 32, 2, 63 });
                    metal_a_supports_paint_setup(
                        session, METAL_SUPPORTS_BOXED, 4, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23470, { 0, 0, height }, { 32, 26, 3 });
                    metal_a_supports_paint_setup(
                        session, METAL_SUPPORTS_BOXED, 4, 20, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23483, { 0, 6, height }, { 32, 26, 3 });
                    metal_a_supports_paint_setup(
                        session, METAL_SUPPORTS_BOXED, 4, 16, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23475, { 0, 6, height }, { 32, 26, 3 });
                    metal_a_supports_paint_setup(
                        session, METAL_SUPPORTS_BOXED, 4, 16, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 9:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23477, { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23469, { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23484, { 0, 6, height }, { 32, 20, 7 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 23476, { 0, 6, height }, { 32, 20, 3 });
                    break;
            }
            metal_a_supports_paint_setup(session, METAL_SUPPORTS_BOXED, 4, 8, height, session.TrackColours[SCHEME_SUPPORTS]);
            switch (direction)
            {
                case 1:
                    paint_util_push_tunnel_right(session, height - 8, TUNNEL_SQUARE_7);
                    break;
                case 2:
                    paint_util_push_tunnel_left(session, height - 8, TUNNEL_SQUARE_7);
                    break;
            }
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
    }

    track_paint_util_right_vertical_loop_segments(session, direction, trackSequence);
}

/** rct2: 0x008AC7E8 */
static void wooden_rc_track_left_quarter_turn_3(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23828, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24694, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23831, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24697, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23840, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24706, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23834, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24700, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23825, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24691, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23837, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24703, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23827, { 16, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24693, { 16, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23830, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24696, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23839, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24705, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23833, { 0, 16, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24699, { 0, 16, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23824, { 16, 16, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24690, { 16, 16, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23836, { 16, 16, height }, { 16, 16, 0 },
                        { 16, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24702, { 16, 16, height }, { 16, 16, 0 },
                        { 16, 16, height + 27 });
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23826, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24692, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23829, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24695, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23838, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24704, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23832, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24698, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23823, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24689, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23835, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24701, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 2:
                    paint_util_push_tunnel_right(session, height, TUNNEL_SQUARE_FLAT);
                    break;
                case 3:
                    paint_util_push_tunnel_left(session, height, TUNNEL_SQUARE_FLAT);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008AC7F8 */
static void wooden_rc_track_right_quarter_turn_3(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
    wooden_rc_track_left_quarter_turn_3(session, ride, trackSequence, (direction - 1) & 3, height, trackElement);
}

/** rct2: 0x008AC808 */
static void wooden_rc_track_left_quarter_turn_3_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_5,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24712, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_8,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24715, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_17,
                        { 0, 0, height }, { 32, 20, 0 }, { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24724, { 0, 0, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_11,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24718, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_2,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24709, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_14,
                        { 0, 0, height }, { 32, 20, 0 }, { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24721, { 0, 0, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_4,
                        { 0, 0, height }, { 16, 16, 2 }, { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24711, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_7,
                        { 0, 0, height }, { 16, 16, 2 }, { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24714, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_16,
                        { 0, 0, height }, { 16, 16, 0 }, { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24723, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_10,
                        { 0, 0, height }, { 16, 16, 2 }, { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24717, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_1,
                        { 0, 0, height }, { 16, 16, 2 }, { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24708, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_13,
                        { 0, 0, height }, { 16, 16, 0 }, { 16, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24720, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 27 });
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_3,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24710, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_6,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24713, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_15,
                        { 0, 0, height }, { 20, 32, 0 }, { 6, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24722, { 0, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_9,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24716, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_0,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24707, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_12,
                        { 0, 0, height }, { 20, 32, 0 }, { 6, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24719, { 0, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 2:
                    paint_util_push_tunnel_right(session, height, TUNNEL_SQUARE_FLAT);
                    break;
                case 3:
                    paint_util_push_tunnel_left(session, height, TUNNEL_SQUARE_FLAT);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008AC818 */
static void wooden_rc_track_right_quarter_turn_3_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
    wooden_rc_track_left_quarter_turn_3_bank(session, ride, trackSequence, (direction - 1) & 3, height, trackElement);
}

/** rct2: 0x008AC828 */
static void wooden_rc_track_left_quarter_turn_3_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23906, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24772, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23908, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24774, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23919, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24785, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23910, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24776, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23904, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24770, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23917, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24783, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 1:
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 2:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23905, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24771, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23907, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24773, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23918, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24784, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23909, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24775, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23920, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24786, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23903, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24769, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23916, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24782, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 2:
                    paint_util_push_tunnel_right(session, height + 8, TUNNEL_SQUARE_8);
                    break;
                case 3:
                    paint_util_push_tunnel_left(session, height + 8, TUNNEL_SQUARE_8);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
    }
}

/** rct2: 0x008AC838 */
static void wooden_rc_track_right_quarter_turn_3_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23895, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24761, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23911, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24777, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23897, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24763, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23899, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24765, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23914, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24780, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23901, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24767, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 1:
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 2:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23896, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24762, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23912, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24778, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23898, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24764, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23913, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24779, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23900, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24766, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23915, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24781, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23902, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24768, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 0:
                    paint_util_push_tunnel_right(session, height + 8, TUNNEL_SQUARE_8);
                    break;
                case 1:
                    paint_util_push_tunnel_left(session, height + 8, TUNNEL_SQUARE_8);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
    }
}

/** rct2: 0x008AC848 */
static void wooden_rc_track_left_quarter_turn_3_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
    wooden_rc_track_right_quarter_turn_3_25_deg_up(session, ride, trackSequence, (direction + 1) & 3, height, trackElement);
}

/** rct2: 0x008AC858 */
static void wooden_rc_track_right_quarter_turn_3_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
    wooden_rc_track_left_quarter_turn_3_25_deg_up(session, ride, trackSequence, (direction - 1) & 3, height, trackElement);
}

/** rct2: 0x008ACAB8 */
static void wooden_rc_track_left_half_banked_helix_up_small(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_41,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24748, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_44,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24751, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_53,
                        { 0, 0, height }, { 32, 20, 0 }, { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24760, { 0, 0, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_47,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24754, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_38,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24745, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_50,
                        { 0, 0, height }, { 32, 20, 0 }, { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24757, { 0, 0, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_D4, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_40,
                        { 0, 0, height }, { 16, 16, 2 }, { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24747, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_43,
                        { 0, 0, height }, { 16, 16, 2 }, { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24750, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_52,
                        { 0, 0, height }, { 16, 16, 0 }, { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24759, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_46,
                        { 0, 0, height }, { 16, 16, 2 }, { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24753, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_37,
                        { 0, 0, height }, { 16, 16, 2 }, { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24744, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_49,
                        { 0, 0, height }, { 16, 16, 0 }, { 16, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24756, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 27 });
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_39,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24746, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_42,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24749, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_51,
                        { 0, 0, height }, { 20, 32, 0 }, { 6, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24758, { 0, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_45,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24752, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_36,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24743, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_48,
                        { 0, 0, height }, { 20, 32, 0 }, { 6, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24755, { 0, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 2:
                    paint_util_push_tunnel_right(session, height + 8, TUNNEL_SQUARE_FLAT);
                    break;
                case 3:
                    paint_util_push_tunnel_left(session, height + 8, TUNNEL_SQUARE_FLAT);
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_BC | SEGMENT_CC, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_38,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24745, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_50,
                        { 0, 0, height }, { 20, 32, 0 }, { 6, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24757, { 0, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_41,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24748, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_44,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24751, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_53,
                        { 0, 0, height }, { 20, 32, 0 }, { 6, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24760, { 0, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_47,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24754, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 0:
                    paint_util_push_tunnel_right(session, height, TUNNEL_SQUARE_FLAT);
                    break;
                case 1:
                    paint_util_push_tunnel_left(session, height, TUNNEL_SQUARE_FLAT);
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_CC, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_37,
                        { 0, 0, height }, { 16, 16, 2 }, { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24744, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_49,
                        { 0, 0, height }, { 16, 16, 0 }, { 16, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24756, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 27 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_40,
                        { 0, 0, height }, { 16, 16, 2 }, { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24747, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_43,
                        { 0, 0, height }, { 16, 16, 2 }, { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24750, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_52,
                        { 0, 0, height }, { 16, 16, 0 }, { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24759, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_46,
                        { 0, 0, height }, { 16, 16, 2 }, { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24753, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 7:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_36,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24743, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_48,
                        { 0, 0, height }, { 32, 20, 0 }, { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24755, { 0, 0, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_39,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24746, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_42,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24749, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_51,
                        { 0, 0, height }, { 32, 20, 0 }, { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24758, { 0, 0, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_45,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24752, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height + 8, TUNNEL_SQUARE_FLAT);
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C8, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008ACAC8 */
static void wooden_rc_track_right_half_banked_helix_up_small(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_18,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24725, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_30,
                        { 0, 0, height }, { 32, 20, 0 }, { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24737, { 0, 0, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_21,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24728, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_24,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24731, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_33,
                        { 0, 0, height }, { 32, 20, 0 }, { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24740, { 0, 0, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_27,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24734, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C8, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_19,
                        { 0, 0, height }, { 16, 16, 2 }, { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24726, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_31,
                        { 0, 0, height }, { 16, 16, 0 }, { 16, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24738, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 27 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_22,
                        { 0, 0, height }, { 16, 16, 2 }, { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24729, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_25,
                        { 0, 0, height }, { 16, 16, 2 }, { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24732, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_34,
                        { 0, 0, height }, { 16, 16, 0 }, { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24741, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_28,
                        { 0, 0, height }, { 16, 16, 2 }, { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24735, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_20,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24727, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_32,
                        { 0, 0, height }, { 20, 32, 0 }, { 6, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24739, { 0, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_23,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24730, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_26,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24733, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_35,
                        { 0, 0, height }, { 20, 32, 0 }, { 6, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24742, { 0, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_29,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24736, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 0:
                    paint_util_push_tunnel_right(session, height + 8, TUNNEL_SQUARE_FLAT);
                    break;
                case 1:
                    paint_util_push_tunnel_left(session, height + 8, TUNNEL_SQUARE_FLAT);
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_CC, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_21,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24728, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_24,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24731, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_33,
                        { 0, 0, height }, { 20, 32, 0 }, { 6, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24740, { 0, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_27,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24734, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_18,
                        { 0, 0, height }, { 20, 32, 2 }, { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24725, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_30,
                        { 0, 0, height }, { 20, 32, 0 }, { 6, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24737, { 0, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 2:
                    paint_util_push_tunnel_right(session, height, TUNNEL_SQUARE_FLAT);
                    break;
                case 3:
                    paint_util_push_tunnel_left(session, height, TUNNEL_SQUARE_FLAT);
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_BC | SEGMENT_CC, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_22,
                        { 0, 0, height }, { 16, 16, 2 }, { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24729, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_25,
                        { 0, 0, height }, { 16, 16, 2 }, { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24732, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_34,
                        { 0, 0, height }, { 16, 16, 0 }, { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24741, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_28,
                        { 0, 0, height }, { 16, 16, 2 }, { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24735, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23860, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24726, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_31,
                        { 0, 0, height }, { 16, 16, 0 }, { 16, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24738, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 27 });
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 7:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_23,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24730, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_26,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24733, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_35,
                        { 0, 0, height }, { 32, 20, 0 }, { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24742, { 0, 0, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_29,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24736, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_20,
                        { 0, 0, height }, { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24727, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | SPR_WOODEN_RC_SMALL_RIGHT_BANKED_TURN_32,
                        { 0, 0, height }, { 32, 20, 0 }, { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24739, { 0, 0, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height + 8, TUNNEL_SQUARE_FLAT);
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_D4, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008ACAD8 */
static void wooden_rc_track_left_half_banked_helix_down_small(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    if (trackSequence >= 4)
    {
        trackSequence -= 4;
        direction = (direction - 1) & 3;
    }
    trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
    wooden_rc_track_right_half_banked_helix_up_small(session, ride, trackSequence, (direction + 1) & 3, height, trackElement);
}

/** rct2: 0x008ACAE8 */
static void wooden_rc_track_right_half_banked_helix_down_small(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    if (trackSequence >= 4)
    {
        trackSequence -= 4;
        direction = (direction + 1) & 3;
    }
    trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
    wooden_rc_track_left_half_banked_helix_up_small(session, ride, trackSequence, (direction - 1) & 3, height, trackElement);
}

/** rct2: 0x008ACAF8 */
static void wooden_rc_track_left_half_banked_helix_up_large(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23704, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24570, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23709, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24575, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23724, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24590, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 27 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23714, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24580, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23699, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24565, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23719, { 0, 0, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24585, { 0, 0, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_D4, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_BC | SEGMENT_CC | SEGMENT_D4, direction), 48, 0x20);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23703, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24569, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23708, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24574, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23723, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24589, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23713, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24579, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23698, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24564, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23718, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24584, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23702, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24568, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23707, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24573, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23722, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 29 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24588, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 29 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23712, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24578, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23697, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24563, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23717, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24583, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C0 | SEGMENT_C8 | SEGMENT_D0, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 4:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_BC | SEGMENT_CC | SEGMENT_D4, direction), 48, 0x20);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23701, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24567, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23706, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24572, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23721, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 33 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24587, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 33 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23711, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24577, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23696, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24562, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23716, { 0, 0, height }, { 16, 32, 0 },
                        { 16, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24582, { 0, 0, height }, { 16, 32, 0 },
                        { 16, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23700, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24566, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23705, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24571, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23720, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 33 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24586, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 33 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23710, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24576, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23695, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24561, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23715, { 0, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24581, { 0, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 2:
                    paint_util_push_tunnel_right(session, height + 8, TUNNEL_SQUARE_FLAT);
                    break;
                case 3:
                    paint_util_push_tunnel_left(session, height + 8, TUNNEL_SQUARE_FLAT);
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_BC | SEGMENT_CC, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 7:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23699, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24565, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23719, { 0, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24585, { 0, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23704, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24570, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23709, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24575, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23724, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24590, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23714, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24580, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 0:
                    paint_util_push_tunnel_right(session, height, TUNNEL_SQUARE_FLAT);
                    break;
                case 1:
                    paint_util_push_tunnel_left(session, height, TUNNEL_SQUARE_FLAT);
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_CC, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 8:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC, direction), 48, 0x20);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 9:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23698, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24564, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23718, { 0, 0, height }, { 16, 32, 0 },
                        { 16, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24584, { 0, 0, height }, { 16, 32, 0 },
                        { 16, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23703, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24569, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23708, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24574, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23723, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24589, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23713, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24579, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 10:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23697, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24563, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23717, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24583, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23702, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24568, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23707, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24573, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23722, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 29 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24588, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 29 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23712, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24578, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_BC | SEGMENT_D0 | SEGMENT_D4, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 11:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC, direction), 48, 0x20);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 12:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23696, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24562, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23716, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24582, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23701, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24567, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23706, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24572, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23721, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 33 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24587, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 33 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23711, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24577, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 13:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23695, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24561, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23715, { 0, 0, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24581, { 0, 0, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23700, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24566, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23705, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24571, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23720, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 33 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24586, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 33 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23710, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24576, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height + 8, TUNNEL_SQUARE_FLAT);
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C8, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008ACB08 */
static void wooden_rc_track_right_half_banked_helix_up_large(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23665, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24531, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23685, { 0, 0, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24551, { 0, 0, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23670, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24536, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23675, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24541, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23690, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24556, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 27 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23680, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24546, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C8, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC, direction), 48, 0x20);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23666, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24532, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23686, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24552, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23671, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24537, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23676, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24542, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23691, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24557, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23681, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24547, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23667, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24533, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23687, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24553, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23672, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24538, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23677, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24543, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23692, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 29 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24558, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 29 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23682, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24548, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_BC | SEGMENT_D0 | SEGMENT_D4, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 4:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC, direction), 48, 0x20);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23668, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24534, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23688, { 0, 0, height }, { 16, 32, 0 },
                        { 16, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24554, { 0, 0, height }, { 16, 32, 0 },
                        { 16, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23673, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24539, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23678, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24544, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23693, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 33 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24559, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 33 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23683, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24549, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23669, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24535, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23689, { 0, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24555, { 0, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23674, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24540, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23679, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24545, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23694, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 33 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24560, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 33 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23684, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24550, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 0:
                    paint_util_push_tunnel_right(session, height + 8, TUNNEL_SQUARE_FLAT);
                    break;
                case 1:
                    paint_util_push_tunnel_left(session, height + 8, TUNNEL_SQUARE_FLAT);
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_CC, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 7:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23670, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24536, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23675, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24541, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23690, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24556, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23680, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24546, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23665, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24531, { 0, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23685, { 0, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24551, { 0, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 2:
                    paint_util_push_tunnel_right(session, height, TUNNEL_SQUARE_FLAT);
                    break;
                case 3:
                    paint_util_push_tunnel_left(session, height, TUNNEL_SQUARE_FLAT);
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_B8 | SEGMENT_BC | SEGMENT_CC, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 8:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_BC | SEGMENT_CC | SEGMENT_D4, direction), 48, 0x20);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 9:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23671, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24537, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23676, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24542, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23691, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24557, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23681, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24547, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23666, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24532, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23686, { 0, 0, height }, { 16, 32, 0 },
                        { 16, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24552, { 0, 0, height }, { 16, 32, 0 },
                        { 16, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 10:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23672, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24538, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23677, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24543, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23692, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 29 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24558, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 29 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23682, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24548, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23667, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24533, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23687, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24553, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C0 | SEGMENT_C8 | SEGMENT_D0, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_BC | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 11:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_BC | SEGMENT_CC | SEGMENT_D4, direction), 48, 0x20);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 12:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23673, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24539, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23678, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24544, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23693, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 33 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24559, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 33 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23683, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24549, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23668, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24534, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23688, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24554, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 13:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23674, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24540, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23679, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24545, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23694, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 33 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24560, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 33 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23684, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24550, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23669, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24535, { 0, 0, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23689, { 0, 0, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24555, { 0, 0, height }, { 32, 20, 0 },
                        { 0, 6, height + 27 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height + 8, TUNNEL_SQUARE_FLAT);
            }
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_D4, direction), 48, 0x20);
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008ACB18 */
static void wooden_rc_track_left_half_banked_helix_down_large(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    if (trackSequence >= 7)
    {
        trackSequence -= 7;
        direction = (direction - 1) & 3;
    }
    trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    wooden_rc_track_right_half_banked_helix_up_large(session, ride, trackSequence, (direction + 1) & 3, height, trackElement);
}

/** rct2: 0x008ACB28 */
static void wooden_rc_track_right_half_banked_helix_down_large(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    if (trackSequence >= 7)
    {
        trackSequence -= 7;
        direction = (direction + 1) & 3;
    }
    trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    wooden_rc_track_left_half_banked_helix_up_large(session, ride, trackSequence, (direction - 1) & 3, height, trackElement);
}

/** rct2: 0x008ACB98 */
static void wooden_rc_track_left_quarter_turn_1_60_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24209, { 0, 0, height }, { 28, 28, 3 },
                { 2, 2, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25075, { 0, 0, height }, { 28, 28, 3 },
                { 2, 2, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24217, { 0, 0, height }, { 28, 28, 1 },
                { 2, 2, height + 99 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25083, { 0, 0, height }, { 28, 28, 1 },
                { 2, 2, height + 99 });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24210, { 0, 0, height }, { 28, 28, 3 },
                { 2, 2, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25076, { 0, 0, height }, { 28, 28, 3 },
                { 2, 2, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24218, { 0, 0, height }, { 28, 28, 1 },
                { 2, 2, height + 99 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25084, { 0, 0, height }, { 28, 28, 1 },
                { 2, 2, height + 99 });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24211, { 0, 0, height }, { 28, 28, 3 },
                { 2, 2, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25077, { 0, 0, height }, { 28, 28, 3 },
                { 2, 2, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24219, { 0, 0, height }, { 28, 28, 1 },
                { 2, 2, height + 99 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25085, { 0, 0, height }, { 28, 28, 1 },
                { 2, 2, height + 99 });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24212, { 0, 0, height }, { 28, 28, 3 },
                { 2, 2, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25078, { 0, 0, height }, { 28, 28, 3 },
                { 2, 2, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24220, { 0, 0, height }, { 28, 28, 1 },
                { 2, 2, height + 99 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25086, { 0, 0, height }, { 28, 28, 1 },
                { 2, 2, height + 99 });
            break;
    }
    track_paint_util_left_quarter_turn_1_tile_tunnel(session, direction, height, -8, TUNNEL_SQUARE_7, +56, TUNNEL_SQUARE_8);
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 104, 0x20);
}

/** rct2: 0x008ACB78 */
static void wooden_rc_track_right_quarter_turn_1_60_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24213, { 0, 0, height }, { 28, 28, 3 },
                { 2, 2, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25079, { 0, 0, height }, { 28, 28, 3 },
                { 2, 2, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24221, { 0, 0, height }, { 28, 28, 1 },
                { 2, 2, height + 99 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25087, { 0, 0, height }, { 28, 28, 1 },
                { 2, 2, height + 99 });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24214, { 0, 0, height }, { 28, 28, 3 },
                { 2, 2, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25080, { 0, 0, height }, { 28, 28, 3 },
                { 2, 2, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24222, { 0, 0, height }, { 28, 28, 1 },
                { 2, 2, height + 99 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25088, { 0, 0, height }, { 28, 28, 1 },
                { 2, 2, height + 99 });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24215, { 0, 0, height }, { 28, 28, 3 },
                { 2, 2, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25081, { 0, 0, height }, { 28, 28, 3 },
                { 2, 2, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24223, { 0, 0, height }, { 28, 28, 1 },
                { 2, 2, height + 99 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25089, { 0, 0, height }, { 28, 28, 1 },
                { 2, 2, height + 99 });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24216, { 0, 0, height }, { 28, 28, 3 },
                { 2, 2, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25082, { 0, 0, height }, { 28, 28, 3 },
                { 2, 2, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24224, { 0, 0, height }, { 28, 28, 1 },
                { 2, 2, height + 99 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25090, { 0, 0, height }, { 28, 28, 1 },
                { 2, 2, height + 99 });
            break;
    }
    track_paint_util_right_quarter_turn_1_tile_tunnel(session, direction, height, -8, TUNNEL_SQUARE_7, +56, TUNNEL_SQUARE_8);
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 104, 0x20);
}

/** rct2: 0x008ACB88 */
static void wooden_rc_track_left_quarter_turn_1_60_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_right_quarter_turn_1_60_deg_up(session, ride, trackSequence, (direction + 1) & 3, height, trackElement);
}

/** rct2: 0x008ACBA8 */
static void wooden_rc_track_right_quarter_turn_1_60_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_left_quarter_turn_1_60_deg_up(session, ride, trackSequence, (direction - 1) & 3, height, trackElement);
}

/** rct2: 0x008AC868 */
static void wooden_rc_track_brakes(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const uint32_t imageIds[4][2] = {
        { SPR_WOODEN_RC_BRAKES_SW_NE, SPR_WOODEN_RC_BRAKES_RAILS_SW_NE },
        { SPR_WOODEN_RC_BRAKES_NW_SE, SPR_WOODEN_RC_BRAKES_RAILS_NW_SE },
        { SPR_WOODEN_RC_BRAKES_SW_NE, SPR_WOODEN_RC_BRAKES_RAILS_SW_NE },
        { SPR_WOODEN_RC_BRAKES_NW_SE, SPR_WOODEN_RC_BRAKES_RAILS_NW_SE },
    };

    wooden_rc_track_paint(
        session, imageIds[direction][0], imageIds[direction][1], direction, 0, 2, 32, 25, 2, height, 0, 3, height);
    wooden_a_supports_paint_setup(session, direction & 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
    paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 32, 0x20);
}

/** rct2: 0x008ACC78 */
static void wooden_rc_track_25_deg_up_left_banked(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24249, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25115, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 0, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24250, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25116, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24257, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25123, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 1, 10, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24251, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25117, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24258, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25124, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 0, 11, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24252, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25118, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 1, 12, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
    }
    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height + 8, TUNNEL_SQUARE_8);
    }
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 56, 0x20);
}

/** rct2: 0x008ACC88 */
static void wooden_rc_track_25_deg_up_right_banked(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24253, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25119, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 0, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24254, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25120, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24259, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25125, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 1, 10, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24255, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25121, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24260, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25126, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 0, 11, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24256, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25122, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 1, 12, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
    }
    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height + 8, TUNNEL_SQUARE_8);
    }
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 56, 0x20);
}

/** rct2: 0x008AC878 */
static void wooden_rc_track_on_ride_photo(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 23753, { 0, 2, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 24619, { 0, 2, height }, { 32, 25, 2 },
                { 0, 3, height });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 23754, { 0, 2, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 24620, { 0, 2, height }, { 32, 25, 2 },
                { 0, 3, height });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 23753, { 0, 2, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 24619, { 0, 2, height }, { 32, 25, 2 },
                { 0, 3, height });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 23754, { 0, 2, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 24620, { 0, 2, height }, { 32, 25, 2 },
                { 0, 3, height });
            break;
    }
    wooden_a_supports_paint_setup(session, direction & 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
    track_paint_util_onride_photo_small_paint(session, direction, height + 16, trackElement);
    paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_INVERTED_9);
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 48, 0x20);
}

/** rct2: 0x008ACC98 */
static void wooden_rc_track_25_deg_down_left_banked(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_25_deg_up_right_banked(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008ACCA8 */
static void wooden_rc_track_25_deg_down_right_banked(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_25_deg_up_left_banked(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008ACE08 */
static void wooden_rc_track_water_splash(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    const bool transparent = gConfigGeneral.transparent_water || (session.ViewFlags & VIEWPORT_FLAG_UNDERGROUND_INSIDE);
    const uint32_t waterOverlay = transparent ? SPR_WATER_OVERLAY : SPR_RCT1_WATER_OVERLAY;

    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23989, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24855, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x61000000 | SPR_WATER_MASK, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x00000000 | waterOverlay, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 23997, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24863, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23993, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24859, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23990, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24856, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x61000000 | SPR_WATER_MASK, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x00000000 | waterOverlay, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 23998, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24864, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23994, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24860, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23987, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24853, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x61000000 | SPR_WATER_MASK, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x00000000 | waterOverlay, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 23995, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24861, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23991, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24857, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23988, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24854, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x61000000 | SPR_WATER_MASK, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x00000000 | waterOverlay, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 23996, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24862, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23992, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24858, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    break;
            }
            wooden_a_supports_paint_setup(session, direction & 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
            paint_util_push_tunnel_rotated(session, direction, height + 16, TUNNEL_SQUARE_FLAT);
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23977, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24843, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x61000000 | SPR_WATER_MASK, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x00000000 | waterOverlay, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 23985, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24851, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23981, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24847, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23978, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24844, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x61000000 | SPR_WATER_MASK, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x00000000 | waterOverlay, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 23986, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24852, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23982, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24848, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23975, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24841, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x61000000 | SPR_WATER_MASK, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x00000000 | waterOverlay, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 23983, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24849, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23979, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24845, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23976, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24842, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x61000000 | SPR_WATER_MASK, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x00000000 | waterOverlay, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 23984, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24850, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23980, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24846, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    break;
            }
            wooden_a_supports_paint_setup(session, direction & 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23999, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24865, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x61000000 | SPR_WATER_MASK, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x00000000 | waterOverlay, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24003, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24869, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24001, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24867, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    break;
                case 1:
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24000, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24866, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x61000000 | SPR_WATER_MASK, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x00000000 | waterOverlay, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24004, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24870, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24002, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24868, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    break;
            }
            wooden_a_supports_paint_setup(session, direction & 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23975, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24841, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x61000000 | SPR_WATER_MASK, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x00000000 | waterOverlay, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 23983, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24849, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23979, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24845, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23976, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24842, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x61000000 | SPR_WATER_MASK, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x00000000 | waterOverlay, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 23984, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24850, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23980, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24846, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23977, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24843, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x61000000 | SPR_WATER_MASK, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x00000000 | waterOverlay, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 23985, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24851, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23981, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24847, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23978, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24844, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x61000000 | SPR_WATER_MASK, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x00000000 | waterOverlay, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 23986, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24852, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23982, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24848, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    break;
            }
            wooden_a_supports_paint_setup(session, direction & 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23987, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24853, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x61000000 | SPR_WATER_MASK, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x00000000 | waterOverlay, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 23995, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24861, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23991, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24857, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23988, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24854, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x61000000 | SPR_WATER_MASK, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x00000000 | waterOverlay, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 23996, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24862, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23992, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24858, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23989, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24855, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x61000000 | SPR_WATER_MASK, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x00000000 | waterOverlay, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 23997, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24863, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23993, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24859, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23990, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24856, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x61000000 | SPR_WATER_MASK, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, 0x00000000 | waterOverlay, { 0, 0, height + 16 }, { 32, 25, 2 },
                        { 0, 3, height + 16 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 23998, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_SUPPORTS] | 24864, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23994, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24860, { 0, 0, height }, { 32, 25, 2 },
                        { 0, 3, height });
                    break;
            }
            wooden_a_supports_paint_setup(session, direction & 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
            paint_util_push_tunnel_rotated(session, direction, height + 16, TUNNEL_SQUARE_FLAT);
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
    }
}

/** rct2: 0x008AC958 */
static void wooden_rc_track_left_eighth_to_diag(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24137, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25003, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24141, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25007, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24153, { 0, 0, height }, { 32, 32, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25019, { 0, 0, height }, { 32, 32, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24145, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25011, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24149, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25015, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24157, { 0, 0, height }, { 32, 32, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25023, { 0, 0, height }, { 32, 32, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24138, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25004, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24142, { 0, 0, height }, { 34, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25008, { 0, 0, height }, { 34, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24154, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25020, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24146, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25012, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24150, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25016, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24158, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25024, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 27 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24139, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25005, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24143, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25009, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24155, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25021, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24147, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25013, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24151, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25017, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24159, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25025, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24140, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25006, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24144, { 0, 0, height }, { 16, 18, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25010, { 0, 0, height }, { 16, 18, 2 },
                        { 0, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24156, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25022, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 16, height + 27 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24148, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25014, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24152, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25018, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24160, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25026, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 0, height + 27 });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008AC968 */
static void wooden_rc_track_right_eighth_to_diag(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24113, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24979, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24129, { 0, 0, height }, { 32, 32, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24995, { 0, 0, height }, { 32, 32, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24117, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24983, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24121, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24987, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24133, { 0, 0, height }, { 32, 32, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24999, { 0, 0, height }, { 32, 32, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24125, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24991, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24114, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24980, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24130, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24996, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 27 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24118, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24984, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24122, { 0, 0, height }, { 34, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24988, { 0, 0, height }, { 34, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24134, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25000, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24126, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24992, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24115, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24981, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24131, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24997, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24119, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24985, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24123, { 0, 0, height }, { 28, 28, 2 },
                        { 4, 4, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24989, { 0, 0, height }, { 28, 28, 2 },
                        { 4, 4, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24135, { 0, 0, height }, { 28, 28, 0 },
                        { 4, 4, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25001, { 0, 0, height }, { 28, 28, 0 },
                        { 4, 4, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24127, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24993, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24116, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24982, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24132, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24998, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 0, height + 27 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24120, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24986, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24124, { 0, 0, height }, { 16, 18, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24990, { 0, 0, height }, { 16, 18, 2 },
                        { 0, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24136, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25002, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 16, height + 27 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24128, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24994, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008AC978 */
static void wooden_rc_track_left_eighth_to_orthogonal(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
    wooden_rc_track_right_eighth_to_diag(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008AC988 */
static void wooden_rc_track_right_eighth_to_orthogonal(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
    wooden_rc_track_left_eighth_to_diag(session, ride, trackSequence, (direction + 3) & 3, height, trackElement);
}

/** rct2: 0x008AC998 */
static void wooden_rc_track_left_eighth_bank_to_diag(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24185, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25051, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24189, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25055, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24201, { 0, 0, height }, { 32, 32, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25067, { 0, 0, height }, { 32, 32, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24193, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25059, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24197, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25063, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24205, { 0, 0, height }, { 32, 32, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25071, { 0, 0, height }, { 32, 32, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24186, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25052, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24190, { 0, 0, height }, { 34, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25056, { 0, 0, height }, { 34, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24202, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25068, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24194, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25060, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24198, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25064, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24206, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25072, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 27 });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24187, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25053, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24191, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25057, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24203, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25069, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24195, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25061, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24199, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25065, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24207, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25073, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24188, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25054, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24192, { 0, 0, height }, { 16, 18, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25058, { 0, 0, height }, { 16, 18, 2 },
                        { 0, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24204, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25070, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 16, height + 27 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24196, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25062, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24200, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25066, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24208, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25074, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 0, height + 27 });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008AC9A8 */
static void wooden_rc_track_right_eighth_bank_to_diag(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24161, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25027, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24177, { 0, 0, height }, { 32, 32, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25043, { 0, 0, height }, { 32, 32, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24165, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25031, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24169, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25035, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24181, { 0, 0, height }, { 32, 32, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25047, { 0, 0, height }, { 32, 32, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24173, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25039, { 0, 0, height }, { 32, 32, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24162, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25028, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24178, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25044, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 27 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24166, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25032, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24170, { 0, 0, height }, { 34, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25036, { 0, 0, height }, { 34, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24182, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25048, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 0, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24174, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25040, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24163, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25029, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24179, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25045, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24167, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25033, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24171, { 0, 0, height }, { 28, 28, 2 },
                        { 4, 4, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25037, { 0, 0, height }, { 28, 28, 2 },
                        { 4, 4, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24183, { 0, 0, height }, { 28, 28, 0 },
                        { 4, 4, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25049, { 0, 0, height }, { 28, 28, 0 },
                        { 4, 4, height + 27 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24175, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25041, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24164, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25030, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24180, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 0, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25046, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 0, height + 27 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24168, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25034, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24172, { 0, 0, height }, { 16, 18, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25038, { 0, 0, height }, { 16, 18, 2 },
                        { 0, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24184, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25050, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 16, height + 27 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24176, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25042, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008AC9B8 */
static void wooden_rc_track_left_eighth_bank_to_orthogonal(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
    wooden_rc_track_right_eighth_bank_to_diag(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008AC9C8 */
static void wooden_rc_track_right_eighth_bank_to_orthogonal(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
    wooden_rc_track_left_eighth_bank_to_diag(session, ride, trackSequence, (direction + 3) & 3, height, trackElement);
}

/** rct2: 0x008AC888 */
static void wooden_rc_track_diag_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24050, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24916, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24008, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24874, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24047, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24913, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24051, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 27 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24917, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 27 });
                        wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24005, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24871, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24009, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 27 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24875, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 27 });
                        wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 0:
                        wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24049, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24915, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24052, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 27 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24918, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 27 });
                        wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24007, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24873, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24010, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 27 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24876, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 27 });
                        wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24048, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24914, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24006, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24872, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008AC8B8 */
static void wooden_rc_track_diag_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24068, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24934, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24026, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24892, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 1:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24065, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24931, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24069, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 43 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24935, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 43 });
                        wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24023, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24889, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24027, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 43 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24893, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 43 });
                        wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 2:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 0:
                        wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24067, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24933, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24070, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 43 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24936, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 43 });
                        wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24025, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24891, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24028, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 43 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24894, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 43 });
                        wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 3:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24066, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24932, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24024, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24890, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
    }
}

/** rct2: 0x008AC8E8 */
static void wooden_rc_track_diag_60_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24044, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24910, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 104, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24041, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24907, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24045, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 91 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24911, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 91 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 104, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24043, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24909, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24046, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 91 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24912, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 91 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 104, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24042, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24908, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 104, 0x20);
            break;
    }
}

/** rct2: 0x008AC898 */
static void wooden_rc_track_diag_flat_to_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24056, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24922, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24014, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24880, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 1:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24053, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24919, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24057, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24923, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24011, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24877, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24015, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24881, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 2:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 0:
                        wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24055, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24921, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24058, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24924, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24013, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24879, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24016, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24882, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 3:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24054, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24920, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24012, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24878, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
    }
}

/** rct2: 0x008AC8C8 */
static void wooden_rc_track_diag_25_deg_up_to_60_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24032, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24898, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24029, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24895, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24033, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 59 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24899, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 59 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24031, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24897, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24034, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 59 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24900, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 59 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24030, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24896, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
    }
}

/** rct2: 0x008AC8D8 */
static void wooden_rc_track_diag_60_deg_up_to_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24038, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24904, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24035, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24901, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24039, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 59 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24905, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 59 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24037, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24903, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24040, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 59 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24906, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 59 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24036, { -16, -16, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24902, { -16, -16, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
    }
}

/** rct2: 0x008AC8A8 */
static void wooden_rc_track_diag_25_deg_up_to_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24062, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24928, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24020, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24886, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 1:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24059, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24925, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24063, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24929, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24017, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24883, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24021, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24887, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 2:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 0:
                        wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24061, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24927, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24064, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24930, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24019, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24885, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24022, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24888, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 3:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24060, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24926, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24018, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24884, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
    }
}

/** rct2: 0x008AC918 */
static void wooden_rc_track_diag_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24066, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24932, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24024, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24890, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 1:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24067, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24933, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24070, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 43 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24936, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 43 });
                        wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24025, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24891, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24028, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 43 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24894, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 43 });
                        wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 2:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 0:
                        wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24065, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24931, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24069, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 43 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24935, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 43 });
                        wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24023, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24889, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24027, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 43 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24893, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 43 });
                        wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 3:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24068, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24934, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24026, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24892, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
    }
}

/** rct2: 0x008AC948 */
static void wooden_rc_track_diag_60_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24042, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24908, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 104, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24043, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24909, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24046, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 91 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24912, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 91 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 104, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24041, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24907, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24045, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 91 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24911, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 91 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 104, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24044, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24910, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 104, 0x20);
            break;
    }
}

/** rct2: 0x008AC8F8 */
static void wooden_rc_track_diag_flat_to_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24060, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24926, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24018, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24884, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            break;
        case 1:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24061, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24927, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24064, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24930, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24019, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24885, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24022, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24888, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            break;
        case 2:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 0:
                        wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24059, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24925, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24063, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24929, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24017, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24883, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24021, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24887, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            break;
        case 3:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24062, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24928, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24020, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24886, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            break;
    }

    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 56, 0x20);
}

/** rct2: 0x008AC928 */
static void wooden_rc_track_diag_25_deg_down_to_60_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24036, { -16, -16, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24902, { -16, -16, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24037, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24903, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24040, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 59 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24906, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 59 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24035, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24901, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24039, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 59 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24905, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 59 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24038, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24904, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
    }
}

/** rct2: 0x008AC938 */
static void wooden_rc_track_diag_60_deg_down_to_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24030, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24896, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24031, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24897, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24034, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 59 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24900, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 59 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24029, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24895, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24033, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 59 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24899, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 59 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24032, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24898, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
    }
}

/** rct2: 0x008AC908 */
static void wooden_rc_track_diag_25_deg_down_to_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24054, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24920, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24012, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24878, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 1:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24055, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24921, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24058, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24924, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24013, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24879, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24016, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24882, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 2:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 0:
                        wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24053, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24919, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24057, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24923, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 1:
                        wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24011, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24877, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24015, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24881, { -16, -16, height },
                            { 32, 32, 0 }, { -16, -16, height + 35 });
                        wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                    case 3:
                        wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 3:
            if (trackElement.HasChain())
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24056, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24922, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, wooden_rc_get_track_colour(session) | 24014, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        PaintAddImageAsChildRotated(
                            session, direction, wooden_rc_get_rails_colour(session) | 24880, { -16, -16, height },
                            { 32, 32, 2 }, { -16, -16, height });
                        break;
                }
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
    }
}

/** rct2: 0x008ACA18 */
static void wooden_rc_track_diag_flat_to_left_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24080, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24946, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24077, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24943, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24081, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24947, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24079, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24945, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24082, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24948, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24078, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24944, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008AC9F8 */
static void wooden_rc_track_diag_flat_to_right_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24086, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24952, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24083, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24949, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24087, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24953, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24085, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24951, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24088, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24954, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24084, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24950, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008ACA08 */
static void wooden_rc_track_diag_left_bank_to_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24084, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24950, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24085, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24951, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24088, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24954, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24083, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24949, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24087, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24953, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24086, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24952, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008ACA28 */
static void wooden_rc_track_diag_right_bank_to_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24078, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24944, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24079, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24945, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24082, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24948, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24077, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24943, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24081, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24947, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24080, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24946, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008ACA58 */
static void wooden_rc_track_diag_left_bank_to_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24104, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24970, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24101, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24967, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24105, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24971, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24103, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24969, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24106, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24972, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24102, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24968, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
    }
}

/** rct2: 0x008ACA68 */
static void wooden_rc_track_diag_right_bank_to_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24110, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24976, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24107, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24973, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24111, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24977, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24109, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24975, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24112, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24978, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24108, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24974, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
    }
}

/** rct2: 0x008ACA38 */
static void wooden_rc_track_diag_25_deg_up_to_left_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24092, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24958, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24089, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24955, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24093, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24959, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24091, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24957, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24094, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24960, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24090, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24956, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
    }
}

/** rct2: 0x008ACA48 */
static void wooden_rc_track_diag_25_deg_up_to_right_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24098, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24964, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24095, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24961, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24099, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24965, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24097, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24963, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24100, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24966, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24096, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24962, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
    }
}

/** rct2: 0x008ACA78 */
static void wooden_rc_track_diag_left_bank_to_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24096, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24962, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24097, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24963, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24100, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24966, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24095, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24961, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24099, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24965, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24098, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24964, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            break;
    }

    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 56, 0x20);
}

/** rct2: 0x008ACA88 */
static void wooden_rc_track_diag_right_bank_to_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24090, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24956, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24091, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24957, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24094, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24960, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_b_supports_paint_setup(session, 4, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_b_supports_paint_setup(session, 5, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24089, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24955, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24093, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24959, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    wooden_b_supports_paint_setup(session, 2, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_b_supports_paint_setup(session, 3, 0, height + 16, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24092, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24958, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            break;
    }

    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 56, 0x20);
}

/** rct2: 0x008ACA98 */
static void wooden_rc_track_diag_25_deg_down_to_left_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24108, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24974, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24109, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24975, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24112, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24978, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24107, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24973, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24111, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24977, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24110, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24976, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
    }
}

/** rct2: 0x008ACAA8 */
static void wooden_rc_track_diag_25_deg_down_to_right_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24102, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24968, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24103, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24969, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24106, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24972, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24101, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24967, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24105, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24971, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 35 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24104, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24970, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
    }
}

/** rct2: 0x008AC9D8 */
static void wooden_rc_track_diag_left_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24074, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24940, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24071, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24937, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24075, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24941, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24073, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24939, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24076, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24942, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24072, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24938, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008AC9E8 */
static void wooden_rc_track_diag_right_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24072, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24938, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24073, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24939, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24076, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24942, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24071, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24937, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24075, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24941, { -16, -16, height }, { 32, 32, 0 },
                        { -16, -16, height + 27 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24074, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24940, { -16, -16, height }, { 32, 32, 2 },
                        { -16, -16, height });
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x008ACB38 */
static void wooden_rc_track_left_bank_to_left_quarter_turn_3_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23958, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24824, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23960, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24826, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23971, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24837, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23962, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24828, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23956, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24822, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23969, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24835, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 64, 0x20);
            break;
        case 1:
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 2:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23957, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24823, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23959, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24825, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23970, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24836, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23961, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24827, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23972, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24838, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23955, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24821, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23968, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24834, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 2:
                    paint_util_push_tunnel_right(session, height, TUNNEL_SQUARE_8);
                    break;
                case 3:
                    paint_util_push_tunnel_left(session, height, TUNNEL_SQUARE_8);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 64, 0x20);
            break;
    }
}

/** rct2: 0x008ACB48 */
static void wooden_rc_track_right_bank_to_right_quarter_turn_3_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23947, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24813, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23963, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24829, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23949, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24815, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23951, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24817, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23966, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24832, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23953, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24819, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 64, 0x20);
            break;
        case 1:
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 2:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23948, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24814, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23964, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24830, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23950, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24816, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23965, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24831, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23952, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24818, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23967, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24833, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23954, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24820, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 0:
                    paint_util_push_tunnel_right(session, height, TUNNEL_SQUARE_8);
                    break;
                case 1:
                    paint_util_push_tunnel_left(session, height, TUNNEL_SQUARE_8);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 64, 0x20);
            break;
    }
}

/** rct2: 0x008ACB58 */
static void wooden_rc_track_left_quarter_turn_3_25_deg_down_to_left_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23950, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24816, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23965, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24831, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23952, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24818, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23967, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24833, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23954, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24820, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23948, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24814, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23964, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24830, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_8);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 64, 0x20);
            break;
        case 1:
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 2:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23949, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24815, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23951, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24817, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23966, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24832, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23953, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24819, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23947, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24813, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23963, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24829, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 2:
                    paint_util_push_tunnel_right(session, height, TUNNEL_SQUARE_FLAT);
                    break;
                case 3:
                    paint_util_push_tunnel_left(session, height, TUNNEL_SQUARE_FLAT);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 64, 0x20);
            break;
    }
}

/** rct2: 0x008ACB68 */
static void wooden_rc_track_right_quarter_turn_3_25_deg_down_to_right_bank(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23955, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24821, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23968, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24834, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23957, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24823, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23959, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24825, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23970, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24836, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23961, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24827, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23972, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24838, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_8);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 64, 0x20);
            break;
        case 1:
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 2:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 48, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23956, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24822, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23969, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24835, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23958, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24824, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23960, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24826, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23971, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24837, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23962, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24828, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 0:
                    paint_util_push_tunnel_right(session, height, TUNNEL_SQUARE_FLAT);
                    break;
                case 1:
                    paint_util_push_tunnel_left(session, height, TUNNEL_SQUARE_FLAT);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 64, 0x20);
            break;
    }
}

/** rct2: 0x008ACDF8 */
static void wooden_rc_track_block_brakes(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    const auto brakeImg = trackElement.BlockBrakeClosed() ? _wooden_rc_block_brakes_image_ids[direction][1]
                                                          : _wooden_rc_block_brakes_image_ids[direction][0];
    wooden_rc_track_paint(
        session, brakeImg, _wooden_rc_block_brakes_image_ids[direction][2], direction, 0, 2, 32, 25, 2, height, 0, 3, height);
    wooden_a_supports_paint_setup(session, direction & 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
    paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 32, 0x20);
}

/** rct2: 0x008ACCB8 */
static void wooden_rc_track_left_banked_quarter_turn_3_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23932, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24798, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23934, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24800, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23945, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24811, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23936, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24802, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23930, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24796, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23943, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24809, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 1:
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 2:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23931, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24797, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23933, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24799, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23944, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24810, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23935, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24801, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23946, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24812, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23929, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24795, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23942, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24808, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 2:
                    paint_util_push_tunnel_right(session, height + 8, TUNNEL_SQUARE_8);
                    break;
                case 3:
                    paint_util_push_tunnel_left(session, height + 8, TUNNEL_SQUARE_8);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
    }
}

/** rct2: 0x008ACCC8 */
static void wooden_rc_track_right_banked_quarter_turn_3_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23921, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24787, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23937, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24803, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23923, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24789, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23925, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24791, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23940, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24806, { 0, 6, height }, { 32, 20, 0 },
                        { 0, 6, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23927, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24793, { 0, 6, height }, { 32, 20, 2 },
                        { 0, 6, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 1:
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 2:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_C0 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_D4, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 56, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23922, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24788, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23938, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24804, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23924, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24790, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23939, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24805, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23926, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24792, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23941, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24807, { 6, 0, height }, { 20, 32, 0 },
                        { 6, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 23928, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 24794, { 6, 0, height }, { 20, 32, 2 },
                        { 6, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 0:
                    paint_util_push_tunnel_right(session, height + 8, TUNNEL_SQUARE_8);
                    break;
                case 1:
                    paint_util_push_tunnel_left(session, height + 8, TUNNEL_SQUARE_8);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
    }
}

/** rct2: 0x008ACCD8 */
static void wooden_rc_track_left_banked_quarter_turn_3_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
    wooden_rc_track_right_banked_quarter_turn_3_25_deg_up(
        session, ride, trackSequence, (direction + 1) & 3, height, trackElement);
}

/** rct2: 0x008ACCE8 */
static void wooden_rc_track_right_banked_quarter_turn_3_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = mapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
    wooden_rc_track_left_banked_quarter_turn_3_25_deg_up(
        session, ride, trackSequence, (direction - 1) & 3, height, trackElement);
}

/** rct2: 0x008ACC38 */
static void wooden_rc_track_left_banked_quarter_turn_5_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24321, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25187, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    wooden_a_supports_paint_setup(session, 0, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24326, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25192, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24352, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25218, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 67 });
                    wooden_a_supports_paint_setup(session, 1, 10, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24331, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25197, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    wooden_a_supports_paint_setup(session, 0, 11, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24336, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25202, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    wooden_a_supports_paint_setup(session, 1, 12, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 1:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_BC | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24322, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25188, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24327, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25193, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24353, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25219, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24332, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25198, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24337, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25203, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24359, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25225, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B4 | SEGMENT_B8 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24323, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25189, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24328, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25194, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24354, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 59 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25220, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 59 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24333, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25199, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24338, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25204, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24360, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 59 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25226, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 59 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B4 | SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4,
                    direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 64, 0x20);
            break;
        case 4:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_BC | SEGMENT_CC | SEGMENT_D4, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24324, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25190, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24329, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25195, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24355, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25221, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24334, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25200, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24357, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25223, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24339, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25205, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24361, { 0, 0, height }, { 16, 32, 0 },
                        { 16, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25227, { 0, 0, height }, { 16, 32, 0 },
                        { 16, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24325, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25191, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    wooden_a_supports_paint_setup(session, 1, 12, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24330, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25196, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24356, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25222, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 0, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24335, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25201, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24358, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25224, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 1, 10, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24340, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25206, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24362, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25228, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 0, 11, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 2:
                    paint_util_push_tunnel_right(session, height + 8, TUNNEL_SQUARE_8);
                    break;
                case 3:
                    paint_util_push_tunnel_left(session, height + 8, TUNNEL_SQUARE_8);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
    }
}

/** rct2: 0x008ACC48 */
static void wooden_rc_track_right_banked_quarter_turn_5_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24301, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25167, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    wooden_a_supports_paint_setup(session, 0, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24306, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25172, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    wooden_a_supports_paint_setup(session, 1, 10, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24311, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25177, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24347, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25213, { 0, 0, height }, { 32, 27, 0 },
                        { 0, 2, height + 67 });
                    wooden_a_supports_paint_setup(session, 0, 11, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24316, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25182, { 0, 0, height }, { 32, 27, 2 },
                        { 0, 2, height });
                    wooden_a_supports_paint_setup(session, 1, 12, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 1:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24302, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25168, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24341, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25207, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 16, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24307, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25173, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24312, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25178, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24348, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25214, { 0, 0, height }, { 32, 16, 0 },
                        { 0, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24317, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25183, { 0, 0, height }, { 32, 16, 2 },
                        { 0, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_BC | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24303, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25169, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24342, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 59 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25208, { 0, 0, height }, { 16, 16, 0 },
                        { 0, 0, height + 59 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24308, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25174, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24313, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25179, { 0, 0, height }, { 16, 16, 2 },
                        { 16, 16, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24349, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 59 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25215, { 0, 0, height }, { 16, 16, 0 },
                        { 16, 16, height + 59 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24318, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25184, { 0, 0, height }, { 16, 16, 2 },
                        { 0, 16, height });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B4 | SEGMENT_B8 | SEGMENT_BC | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_CC | SEGMENT_D0 | SEGMENT_D4,
                    direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 64, 0x20);
            break;
        case 4:
            paint_util_set_segment_support_height(
                session, paint_util_rotate_segments(SEGMENT_B4 | SEGMENT_C8 | SEGMENT_CC, direction), 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24304, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25170, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24343, { 0, 0, height }, { 16, 32, 0 },
                        { 16, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25209, { 0, 0, height }, { 16, 32, 0 },
                        { 16, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 4, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24309, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25175, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24345, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25211, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 5, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24314, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25180, { 0, 0, height }, { 16, 32, 2 },
                        { 0, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24350, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25216, { 0, 0, height }, { 16, 32, 0 },
                        { 0, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 2, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24319, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25185, { 0, 0, height }, { 16, 32, 2 },
                        { 16, 0, height });
                    wooden_a_supports_paint_setup(session, 3, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            paint_util_set_segment_support_height(
                session,
                paint_util_rotate_segments(
                    SEGMENT_B8 | SEGMENT_C0 | SEGMENT_C4 | SEGMENT_C8 | SEGMENT_D0 | SEGMENT_D4, direction),
                0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24305, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25171, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24344, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25210, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 1, 10, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24310, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25176, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24346, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25212, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 0, 11, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24315, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25181, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24351, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25217, { 0, 0, height }, { 27, 32, 0 },
                        { 2, 0, height + 67 });
                    wooden_a_supports_paint_setup(session, 1, 12, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, wooden_rc_get_track_colour(session) | 24320, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    PaintAddImageAsChildRotated(
                        session, direction, wooden_rc_get_rails_colour(session) | 25186, { 0, 0, height }, { 27, 32, 2 },
                        { 2, 0, height });
                    wooden_a_supports_paint_setup(session, 0, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            switch (direction)
            {
                case 0:
                    paint_util_push_tunnel_right(session, height + 8, TUNNEL_SQUARE_8);
                    break;
                case 1:
                    paint_util_push_tunnel_left(session, height + 8, TUNNEL_SQUARE_8);
                    break;
            }
            paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
            paint_util_set_general_support_height(session, height + 72, 0x20);
            break;
    }
}

/** rct2: 0x008ACC58 */
static void wooden_rc_track_left_banked_quarter_turn_5_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    wooden_rc_track_right_banked_quarter_turn_5_25_deg_up(
        session, ride, trackSequence, (direction + 1) & 3, height, trackElement);
}

/** rct2: 0x008ACC68 */
static void wooden_rc_track_right_banked_quarter_turn_5_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = mapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    wooden_rc_track_left_banked_quarter_turn_5_25_deg_up(
        session, ride, trackSequence, (direction - 1) & 3, height, trackElement);
}

/** rct2: 0x008ACCF8 */
static void wooden_rc_track_25_deg_up_to_left_banked_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24261, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25127, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 0, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24262, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25128, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 1, 10, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24263, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25129, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 0, 11, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24264, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25130, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 1, 12, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
    }
    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height + 8, TUNNEL_SQUARE_8);
    }
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 56, 0x20);
}

/** rct2: 0x008ACD08 */
static void wooden_rc_track_25_deg_up_to_right_banked_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24265, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25131, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 0, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24266, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25132, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 1, 10, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24267, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25133, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 0, 11, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24268, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25134, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 1, 12, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
    }
    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height + 8, TUNNEL_SQUARE_8);
    }
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 56, 0x20);
}

/** rct2: 0x008ACD18 */
static void wooden_rc_track_left_banked_25_deg_up_to_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24269, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25135, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 0, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24270, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25136, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 1, 10, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24271, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25137, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 0, 11, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24272, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25138, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 1, 12, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
    }
    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height + 8, TUNNEL_SQUARE_8);
    }
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 56, 0x20);
}

/** rct2: 0x008ACD28 */
static void wooden_rc_track_right_banked_25_deg_up_to_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24273, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25139, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 0, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24274, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25140, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 1, 10, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24275, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25141, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 0, 11, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24276, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25142, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 1, 12, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
    }
    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_7);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height + 8, TUNNEL_SQUARE_8);
    }
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 56, 0x20);
}

/** rct2: 0x008ACD38 */
static void wooden_rc_track_25_deg_down_to_left_banked_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_right_banked_25_deg_up_to_25_deg_up(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008ACD48 */
static void wooden_rc_track_25_deg_down_to_right_banked_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_left_banked_25_deg_up_to_25_deg_up(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008ACD58 */
static void wooden_rc_track_left_banked_25_deg_down_to_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_25_deg_up_to_right_banked_25_deg_up(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008ACD68 */
static void wooden_rc_track_right_banked_25_deg_down_to_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_25_deg_up_to_left_banked_25_deg_up(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008ACD78 */
static void wooden_rc_track_left_banked_flat_to_left_banked_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24277, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25143, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 0, 1, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24278, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25144, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24293, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25159, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 1, 2, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24279, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25145, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24294, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25160, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 0, 3, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24280, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25146, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 1, 4, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
    }
    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_8);
    }
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 48, 0x20);
}

/** rct2: 0x008ACD88 */
static void wooden_rc_track_right_banked_flat_to_right_banked_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24281, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25147, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 0, 1, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24282, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25148, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24295, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25161, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 1, 2, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24283, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25149, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24296, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25162, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 0, 3, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24284, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25150, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 1, 4, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
    }
    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_8);
    }
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 48, 0x20);
}

/** rct2: 0x008ACD98 */
static void wooden_rc_track_left_banked_25_deg_up_to_left_banked_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24285, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25151, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 0, 5, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24286, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25152, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24297, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25163, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 1, 6, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24287, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25153, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24298, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25164, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 0, 7, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24288, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25154, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 1, 8, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
    }
    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_FLAT);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height + 8, TUNNEL_14);
    }
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 40, 0x20);
}

/** rct2: 0x008ACDA8 */
static void wooden_rc_track_right_banked_25_deg_up_to_right_banked_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24289, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25155, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 0, 5, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24290, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25156, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24299, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25165, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 1, 6, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24291, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25157, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24300, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25166, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 0, 7, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24292, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25158, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 1, 8, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
    }
    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_FLAT);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height + 8, TUNNEL_14);
    }
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 40, 0x20);
}

/** rct2: 0x008ACDB8 */
static void wooden_rc_track_left_banked_flat_to_left_banked_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_right_banked_25_deg_up_to_right_banked_flat(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008ACDC8 */
static void wooden_rc_track_right_banked_flat_to_right_banked_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_left_banked_25_deg_up_to_left_banked_flat(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008ACDD8 */
static void wooden_rc_track_left_banked_25_deg_down_to_left_banked_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_right_banked_flat_to_right_banked_25_deg_up(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008ACDE8 */
static void wooden_rc_track_right_banked_25_deg_down_to_right_banked_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_left_banked_flat_to_left_banked_25_deg_up(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008ACBB8 */
static void wooden_rc_track_flat_to_left_banked_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24225, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25091, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 0, 1, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24226, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25092, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24241, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25107, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 1, 2, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24227, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25093, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24242, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25108, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 0, 3, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24228, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25094, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 1, 4, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
    }
    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_8);
    }
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 48, 0x20);
}

/** rct2: 0x008ACBC8 */
static void wooden_rc_track_flat_to_right_banked_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24229, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25095, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 0, 1, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24230, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25096, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24243, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25109, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 1, 2, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24231, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25097, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24244, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25110, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 0, 3, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24232, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25098, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 1, 4, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
    }
    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_8);
    }
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 48, 0x20);
}

/** rct2: 0x008ACBD8 */
static void wooden_rc_track_left_banked_25_deg_up_to_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24233, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25099, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 0, 5, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24234, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25100, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24245, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25111, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 1, 6, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24235, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25101, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24246, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25112, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 0, 7, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24236, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25102, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 1, 8, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
    }
    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_FLAT);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height + 8, TUNNEL_14);
    }
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 40, 0x20);
}

/** rct2: 0x008ACBE8 */
static void wooden_rc_track_right_banked_25_deg_up_to_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24237, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25103, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 0, 5, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24238, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25104, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24247, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25113, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 1, 6, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24239, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25105, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24248, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25114, { 0, 0, height }, { 32, 1, 9 },
                { 0, 26, height + 5 });
            wooden_a_supports_paint_setup(session, 0, 7, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, wooden_rc_get_track_colour(session) | 24240, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            PaintAddImageAsChildRotated(
                session, direction, wooden_rc_get_rails_colour(session) | 25106, { 0, 0, height }, { 32, 25, 2 },
                { 0, 3, height });
            wooden_a_supports_paint_setup(session, 1, 8, height, session.TrackColours[SCHEME_SUPPORTS]);
            break;
    }
    if (direction == 0 || direction == 3)
    {
        paint_util_push_tunnel_rotated(session, direction, height - 8, TUNNEL_SQUARE_FLAT);
    }
    else
    {
        paint_util_push_tunnel_rotated(session, direction, height + 8, TUNNEL_14);
    }
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 40, 0x20);
}

/** rct2: 0x008ACBF8 */
static void wooden_rc_track_flat_to_left_banked_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_right_banked_25_deg_up_to_flat(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008ACC08 */
static void wooden_rc_track_flat_to_right_banked_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_left_banked_25_deg_up_to_flat(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008ACC18 */
static void wooden_rc_track_left_banked_25_deg_down_to_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_flat_to_right_banked_25_deg_up(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008ACC28 */
static void wooden_rc_track_right_banked_25_deg_down_to_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    wooden_rc_track_flat_to_left_banked_25_deg_up(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

static void wooden_rc_track_booster(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const uint32_t imageIds[4] = {
        SPR_G2_WOODEN_RC_BOOSTER_SW_NE,
        SPR_G2_WOODEN_RC_BOOSTER_NW_SE,
        SPR_G2_WOODEN_RC_BOOSTER_SW_NE,
        SPR_G2_WOODEN_RC_BOOSTER_NW_SE,
    };
    static constexpr const uint32_t railsImageIds[4] = {
        SPR_WOODEN_RC_FLAT_CHAIN_RAILS_SW_NE,
        SPR_WOODEN_RC_FLAT_CHAIN_RAILS_NW_SE,
        SPR_WOODEN_RC_FLAT_CHAIN_RAILS_NE_SW,
        SPR_WOODEN_RC_FLAT_CHAIN_RAILS_SE_NW,
    };

    wooden_rc_track_paint(
        session, imageIds[direction], railsImageIds[direction], direction, 0, 2, 32, 25, 2, height, 0, 3, height);
    wooden_a_supports_paint_setup(session, direction & 1, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
    paint_util_push_tunnel_rotated(session, direction, height, TUNNEL_SQUARE_FLAT);
    paint_util_set_segment_support_height(session, SEGMENTS_ALL, 0xFFFF, 0);
    paint_util_set_general_support_height(session, height + 32, 0x20);
}

TRACK_PAINT_FUNCTION get_track_paint_function_wooden_rc(int32_t trackType)
{
    switch (trackType)
    {
        case TrackElemType::Flat:
            return wooden_rc_track_flat;
        case TrackElemType::EndStation:
        case TrackElemType::BeginStation:
        case TrackElemType::MiddleStation:
            return wooden_rc_track_station;
        case TrackElemType::Up25:
            return wooden_rc_track_25_deg_up;
        case TrackElemType::Up60:
            return wooden_rc_track_60_deg_up;
        case TrackElemType::FlatToUp25:
            return wooden_rc_track_flat_to_25_deg_up;
        case TrackElemType::Up25ToUp60:
            return wooden_rc_track_25_deg_up_to_60_deg_up;
        case TrackElemType::Up60ToUp25:
            return wooden_rc_track_60_deg_up_to_25_deg_up;
        case TrackElemType::Up25ToFlat:
            return wooden_rc_track_25_deg_up_to_flat;
        case TrackElemType::Down25:
            return wooden_rc_track_25_deg_down;
        case TrackElemType::Down60:
            return wooden_rc_track_60_deg_down;
        case TrackElemType::FlatToDown25:
            return wooden_rc_track_flat_to_25_deg_down;
        case TrackElemType::Down25ToDown60:
            return wooden_rc_track_25_deg_down_to_60_deg_down;
        case TrackElemType::Down60ToDown25:
            return wooden_rc_track_60_deg_down_to_25_deg_down;
        case TrackElemType::Down25ToFlat:
            return wooden_rc_track_25_deg_down_to_flat;
        case TrackElemType::LeftQuarterTurn5Tiles:
            return wooden_rc_track_left_quarter_turn_5;
        case TrackElemType::RightQuarterTurn5Tiles:
            return wooden_rc_track_right_quarter_turn_5;
        case TrackElemType::FlatToLeftBank:
            return wooden_rc_track_flat_to_left_bank;
        case TrackElemType::FlatToRightBank:
            return wooden_rc_track_flat_to_right_bank;
        case TrackElemType::LeftBankToFlat:
            return wooden_rc_track_left_bank_to_flat;
        case TrackElemType::RightBankToFlat:
            return wooden_rc_track_right_bank_to_flat;
        case TrackElemType::BankedLeftQuarterTurn5Tiles:
            return wooden_rc_track_banked_left_quarter_turn_5;
        case TrackElemType::BankedRightQuarterTurn5Tiles:
            return wooden_rc_track_banked_right_quarter_turn_5;
        case TrackElemType::LeftBankToUp25:
            return wooden_rc_track_left_bank_to_25_deg_up;
        case TrackElemType::RightBankToUp25:
            return wooden_rc_track_right_bank_to_25_deg_up;
        case TrackElemType::Up25ToLeftBank:
            return wooden_rc_track_25_deg_up_to_left_bank;
        case TrackElemType::Up25ToRightBank:
            return wooden_rc_track_25_deg_up_to_right_bank;
        case TrackElemType::LeftBankToDown25:
            return wooden_rc_track_left_bank_to_25_deg_down;
        case TrackElemType::RightBankToDown25:
            return wooden_rc_track_right_bank_to_25_deg_down;
        case TrackElemType::Down25ToLeftBank:
            return wooden_rc_track_25_deg_down_to_left_bank;
        case TrackElemType::Down25ToRightBank:
            return wooden_rc_track_25_deg_down_to_right_bank;
        case TrackElemType::LeftBank:
            return wooden_rc_track_left_bank;
        case TrackElemType::RightBank:
            return wooden_rc_track_right_bank;
        case TrackElemType::LeftQuarterTurn5TilesUp25:
            return wooden_rc_track_left_quarter_turn_5_25_deg_up;
        case TrackElemType::RightQuarterTurn5TilesUp25:
            return wooden_rc_track_right_quarter_turn_5_25_deg_up;
        case TrackElemType::LeftQuarterTurn5TilesDown25:
            return wooden_rc_track_left_quarter_turn_5_25_deg_down;
        case TrackElemType::RightQuarterTurn5TilesDown25:
            return wooden_rc_track_right_quarter_turn_5_25_deg_down;
        case TrackElemType::SBendLeft:
            return wooden_rc_track_s_bend_left;
        case TrackElemType::SBendRight:
            return wooden_rc_track_s_bend_right;
        case TrackElemType::LeftVerticalLoop:
            return wooden_rc_track_left_vertical_loop;
        case TrackElemType::RightVerticalLoop:
            return wooden_rc_track_right_vertical_loop;
        case TrackElemType::LeftQuarterTurn3Tiles:
            return wooden_rc_track_left_quarter_turn_3;
        case TrackElemType::RightQuarterTurn3Tiles:
            return wooden_rc_track_right_quarter_turn_3;
        case TrackElemType::LeftBankedQuarterTurn3Tiles:
            return wooden_rc_track_left_quarter_turn_3_bank;
        case TrackElemType::RightBankedQuarterTurn3Tiles:
            return wooden_rc_track_right_quarter_turn_3_bank;
        case TrackElemType::LeftQuarterTurn3TilesUp25:
            return wooden_rc_track_left_quarter_turn_3_25_deg_up;
        case TrackElemType::RightQuarterTurn3TilesUp25:
            return wooden_rc_track_right_quarter_turn_3_25_deg_up;
        case TrackElemType::LeftQuarterTurn3TilesDown25:
            return wooden_rc_track_left_quarter_turn_3_25_deg_down;
        case TrackElemType::RightQuarterTurn3TilesDown25:
            return wooden_rc_track_right_quarter_turn_3_25_deg_down;
        case TrackElemType::LeftHalfBankedHelixUpSmall:
            return wooden_rc_track_left_half_banked_helix_up_small;
        case TrackElemType::RightHalfBankedHelixUpSmall:
            return wooden_rc_track_right_half_banked_helix_up_small;
        case TrackElemType::LeftHalfBankedHelixDownSmall:
            return wooden_rc_track_left_half_banked_helix_down_small;
        case TrackElemType::RightHalfBankedHelixDownSmall:
            return wooden_rc_track_right_half_banked_helix_down_small;
        case TrackElemType::LeftHalfBankedHelixUpLarge:
            return wooden_rc_track_left_half_banked_helix_up_large;
        case TrackElemType::RightHalfBankedHelixUpLarge:
            return wooden_rc_track_right_half_banked_helix_up_large;
        case TrackElemType::LeftHalfBankedHelixDownLarge:
            return wooden_rc_track_left_half_banked_helix_down_large;
        case TrackElemType::RightHalfBankedHelixDownLarge:
            return wooden_rc_track_right_half_banked_helix_down_large;
        case TrackElemType::LeftQuarterTurn1TileUp60:
            return wooden_rc_track_left_quarter_turn_1_60_deg_up;
        case TrackElemType::RightQuarterTurn1TileUp60:
            return wooden_rc_track_right_quarter_turn_1_60_deg_up;
        case TrackElemType::LeftQuarterTurn1TileDown60:
            return wooden_rc_track_left_quarter_turn_1_60_deg_down;
        case TrackElemType::RightQuarterTurn1TileDown60:
            return wooden_rc_track_right_quarter_turn_1_60_deg_down;
        case TrackElemType::Brakes:
            return wooden_rc_track_brakes;
        case TrackElemType::Up25LeftBanked:
            return wooden_rc_track_25_deg_up_left_banked;
        case TrackElemType::Up25RightBanked:
            return wooden_rc_track_25_deg_up_right_banked;
        case TrackElemType::OnRidePhoto:
            return wooden_rc_track_on_ride_photo;
        case TrackElemType::Down25LeftBanked:
            return wooden_rc_track_25_deg_down_left_banked;
        case TrackElemType::Down25RightBanked:
            return wooden_rc_track_25_deg_down_right_banked;
        case TrackElemType::Watersplash:
            return wooden_rc_track_water_splash;
        case TrackElemType::LeftEighthToDiag:
            return wooden_rc_track_left_eighth_to_diag;
        case TrackElemType::RightEighthToDiag:
            return wooden_rc_track_right_eighth_to_diag;
        case TrackElemType::LeftEighthToOrthogonal:
            return wooden_rc_track_left_eighth_to_orthogonal;
        case TrackElemType::RightEighthToOrthogonal:
            return wooden_rc_track_right_eighth_to_orthogonal;
        case TrackElemType::LeftEighthBankToDiag:
            return wooden_rc_track_left_eighth_bank_to_diag;
        case TrackElemType::RightEighthBankToDiag:
            return wooden_rc_track_right_eighth_bank_to_diag;
        case TrackElemType::LeftEighthBankToOrthogonal:
            return wooden_rc_track_left_eighth_bank_to_orthogonal;
        case TrackElemType::RightEighthBankToOrthogonal:
            return wooden_rc_track_right_eighth_bank_to_orthogonal;
        case TrackElemType::DiagFlat:
            return wooden_rc_track_diag_flat;
        case TrackElemType::DiagUp25:
            return wooden_rc_track_diag_25_deg_up;
        case TrackElemType::DiagUp60:
            return wooden_rc_track_diag_60_deg_up;
        case TrackElemType::DiagFlatToUp25:
            return wooden_rc_track_diag_flat_to_25_deg_up;
        case TrackElemType::DiagUp25ToUp60:
            return wooden_rc_track_diag_25_deg_up_to_60_deg_up;
        case TrackElemType::DiagUp60ToUp25:
            return wooden_rc_track_diag_60_deg_up_to_25_deg_up;
        case TrackElemType::DiagUp25ToFlat:
            return wooden_rc_track_diag_25_deg_up_to_flat;
        case TrackElemType::DiagDown25:
            return wooden_rc_track_diag_25_deg_down;
        case TrackElemType::DiagDown60:
            return wooden_rc_track_diag_60_deg_down;
        case TrackElemType::DiagFlatToDown25:
            return wooden_rc_track_diag_flat_to_25_deg_down;
        case TrackElemType::DiagDown25ToDown60:
            return wooden_rc_track_diag_25_deg_down_to_60_deg_down;
        case TrackElemType::DiagDown60ToDown25:
            return wooden_rc_track_diag_60_deg_down_to_25_deg_down;
        case TrackElemType::DiagDown25ToFlat:
            return wooden_rc_track_diag_25_deg_down_to_flat;
        case TrackElemType::DiagFlatToLeftBank:
            return wooden_rc_track_diag_flat_to_left_bank;
        case TrackElemType::DiagFlatToRightBank:
            return wooden_rc_track_diag_flat_to_right_bank;
        case TrackElemType::DiagLeftBankToFlat:
            return wooden_rc_track_diag_left_bank_to_flat;
        case TrackElemType::DiagRightBankToFlat:
            return wooden_rc_track_diag_right_bank_to_flat;
        case TrackElemType::DiagLeftBankToUp25:
            return wooden_rc_track_diag_left_bank_to_25_deg_up;
        case TrackElemType::DiagRightBankToUp25:
            return wooden_rc_track_diag_right_bank_to_25_deg_up;
        case TrackElemType::DiagUp25ToLeftBank:
            return wooden_rc_track_diag_25_deg_up_to_left_bank;
        case TrackElemType::DiagUp25ToRightBank:
            return wooden_rc_track_diag_25_deg_up_to_right_bank;
        case TrackElemType::DiagLeftBankToDown25:
            return wooden_rc_track_diag_left_bank_to_25_deg_down;
        case TrackElemType::DiagRightBankToDown25:
            return wooden_rc_track_diag_right_bank_to_25_deg_down;
        case TrackElemType::DiagDown25ToLeftBank:
            return wooden_rc_track_diag_25_deg_down_to_left_bank;
        case TrackElemType::DiagDown25ToRightBank:
            return wooden_rc_track_diag_25_deg_down_to_right_bank;
        case TrackElemType::DiagLeftBank:
            return wooden_rc_track_diag_left_bank;
        case TrackElemType::DiagRightBank:
            return wooden_rc_track_diag_right_bank;
        case TrackElemType::LeftBankToLeftQuarterTurn3TilesUp25:
            return wooden_rc_track_left_bank_to_left_quarter_turn_3_25_deg_up;
        case TrackElemType::RightBankToRightQuarterTurn3TilesUp25:
            return wooden_rc_track_right_bank_to_right_quarter_turn_3_25_deg_up;
        case TrackElemType::LeftQuarterTurn3TilesDown25ToLeftBank:
            return wooden_rc_track_left_quarter_turn_3_25_deg_down_to_left_bank;
        case TrackElemType::RightQuarterTurn3TilesDown25ToRightBank:
            return wooden_rc_track_right_quarter_turn_3_25_deg_down_to_right_bank;
        case TrackElemType::BlockBrakes:
            return wooden_rc_track_block_brakes;
        case TrackElemType::LeftBankedQuarterTurn3TileUp25:
            return wooden_rc_track_left_banked_quarter_turn_3_25_deg_up;
        case TrackElemType::RightBankedQuarterTurn3TileUp25:
            return wooden_rc_track_right_banked_quarter_turn_3_25_deg_up;
        case TrackElemType::LeftBankedQuarterTurn3TileDown25:
            return wooden_rc_track_left_banked_quarter_turn_3_25_deg_down;
        case TrackElemType::RightBankedQuarterTurn3TileDown25:
            return wooden_rc_track_right_banked_quarter_turn_3_25_deg_down;
        case TrackElemType::LeftBankedQuarterTurn5TileUp25:
            return wooden_rc_track_left_banked_quarter_turn_5_25_deg_up;
        case TrackElemType::RightBankedQuarterTurn5TileUp25:
            return wooden_rc_track_right_banked_quarter_turn_5_25_deg_up;
        case TrackElemType::LeftBankedQuarterTurn5TileDown25:
            return wooden_rc_track_left_banked_quarter_turn_5_25_deg_down;
        case TrackElemType::RightBankedQuarterTurn5TileDown25:
            return wooden_rc_track_right_banked_quarter_turn_5_25_deg_down;
        case TrackElemType::Up25ToLeftBankedUp25:
            return wooden_rc_track_25_deg_up_to_left_banked_25_deg_up;
        case TrackElemType::Up25ToRightBankedUp25:
            return wooden_rc_track_25_deg_up_to_right_banked_25_deg_up;
        case TrackElemType::LeftBankedUp25ToUp25:
            return wooden_rc_track_left_banked_25_deg_up_to_25_deg_up;
        case TrackElemType::RightBankedUp25ToUp25:
            return wooden_rc_track_right_banked_25_deg_up_to_25_deg_up;
        case TrackElemType::Down25ToLeftBankedDown25:
            return wooden_rc_track_25_deg_down_to_left_banked_25_deg_down;
        case TrackElemType::Down25ToRightBankedDown25:
            return wooden_rc_track_25_deg_down_to_right_banked_25_deg_down;
        case TrackElemType::LeftBankedDown25ToDown25:
            return wooden_rc_track_left_banked_25_deg_down_to_25_deg_down;
        case TrackElemType::RightBankedDown25ToDown25:
            return wooden_rc_track_right_banked_25_deg_down_to_25_deg_down;
        case TrackElemType::LeftBankedFlatToLeftBankedUp25:
            return wooden_rc_track_left_banked_flat_to_left_banked_25_deg_up;
        case TrackElemType::RightBankedFlatToRightBankedUp25:
            return wooden_rc_track_right_banked_flat_to_right_banked_25_deg_up;
        case TrackElemType::LeftBankedUp25ToLeftBankedFlat:
            return wooden_rc_track_left_banked_25_deg_up_to_left_banked_flat;
        case TrackElemType::RightBankedUp25ToRightBankedFlat:
            return wooden_rc_track_right_banked_25_deg_up_to_right_banked_flat;
        case TrackElemType::LeftBankedFlatToLeftBankedDown25:
            return wooden_rc_track_left_banked_flat_to_left_banked_25_deg_down;
        case TrackElemType::RightBankedFlatToRightBankedDown25:
            return wooden_rc_track_right_banked_flat_to_right_banked_25_deg_down;
        case TrackElemType::LeftBankedDown25ToLeftBankedFlat:
            return wooden_rc_track_left_banked_25_deg_down_to_left_banked_flat;
        case TrackElemType::RightBankedDown25ToRightBankedFlat:
            return wooden_rc_track_right_banked_25_deg_down_to_right_banked_flat;
        case TrackElemType::FlatToLeftBankedUp25:
            return wooden_rc_track_flat_to_left_banked_25_deg_up;
        case TrackElemType::FlatToRightBankedUp25:
            return wooden_rc_track_flat_to_right_banked_25_deg_up;
        case TrackElemType::LeftBankedUp25ToFlat:
            return wooden_rc_track_left_banked_25_deg_up_to_flat;
        case TrackElemType::RightBankedUp25ToFlat:
            return wooden_rc_track_right_banked_25_deg_up_to_flat;
        case TrackElemType::FlatToLeftBankedDown25:
            return wooden_rc_track_flat_to_left_banked_25_deg_down;
        case TrackElemType::FlatToRightBankedDown25:
            return wooden_rc_track_flat_to_right_banked_25_deg_down;
        case TrackElemType::LeftBankedDown25ToFlat:
            return wooden_rc_track_left_banked_25_deg_down_to_flat;
        case TrackElemType::RightBankedDown25ToFlat:
            return wooden_rc_track_right_banked_25_deg_down_to_flat;
        case TrackElemType::Booster:
            return wooden_rc_track_booster;
    }
    return nullptr;
}
