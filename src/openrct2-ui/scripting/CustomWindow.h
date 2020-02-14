/*****************************************************************************
 * Copyright (c) 2014-2018 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "../interface/Window.h"

#include <string>

namespace OpenRCT2::Ui::Windows
{
    void UpdateWidgetText(rct_window* w, rct_widgetindex widget, const std::string& value);
}
