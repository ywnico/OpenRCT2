/*****************************************************************************
 * Copyright (c) 2022 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#pragma once

#ifdef ENABLE_SCRIPTING

#    include "../../../world/TileElement.h"
#    include "../../Duktape.hpp"

#    include <cstdint>
#    include <string>

namespace OpenRCT2::Scripting
{
    class ScTrackSegment
    {
    private:
        track_type_t _type;

    public:
        ScTrackSegment(track_type_t type);

        static void Register(duk_context* ctx);

    private:
        int32_t type_get() const;
        std::string description_get() const;
        int32_t beginZ_get() const;
        int32_t beginDirection_get() const;
        int32_t beginAngle_get() const;
        int32_t beginBank_get() const;
        int32_t endX_get() const;
        int32_t endY_get() const;
        int32_t endZ_get() const;
        int32_t endDirection_get() const;
        int32_t endAngle_get() const;
        int32_t endBank_get() const;
        int32_t length_get() const;
        DukValue elements_get() const;
    };

} // namespace OpenRCT2::Scripting

#endif
