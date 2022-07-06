/*****************************************************************************
 * Copyright (c) 2014-2020 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include <openrct2-ui/interface/Viewport.h>
#include <openrct2-ui/interface/Widget.h>
#include <openrct2-ui/windows/Window.h>
#include <openrct2/Context.h>
#include <openrct2/config/Config.h>
#include <openrct2/localisation/StringIds.h>
#include <openrct2/world/Footpath.h>

// clang-format off
static rct_widget _mainWidgets[] = {
    MakeWidget({0, 0}, {0, 0}, WindowWidgetType::Viewport, WindowColour::Primary, STR_VIEWPORT),
    WIDGETS_END,
};
// clang-format on

class MainWindow final : public Window
{
public:
    void OnOpen() override
    {
        _mainWidgets[0].right = width;
        _mainWidgets[0].bottom = height;
        widgets = _mainWidgets;

        viewport_create(this, windowPos, width, height, Focus(CoordsXYZ(0x0FFF, 0x0FFF, 0)));
        if (viewport != nullptr)
        {
            SetViewportFlags();
        }
        gCurrentRotation = 0;
        gShowGridLinesRefCount = 0;
        gShowLandRightsRefCount = 0;
        gShowConstuctionRightsRefCount = 0;
        WindowFootpathResetSelectedPath();
    }

    void OnDraw(rct_drawpixelinfo& dpi) override
    {
        viewport_render(&dpi, viewport, { { dpi.x, dpi.y }, { dpi.x + dpi.width, dpi.y + dpi.height } });
    }

private:
    void SetViewportFlags()
    {
        viewport->flags |= VIEWPORT_FLAG_SOUND_ON;
        if (gConfigGeneral.invisible_rides)
            viewport->flags |= VIEWPORT_FLAG_INVISIBLE_RIDES;
        if (gConfigGeneral.invisible_vehicles)
            viewport->flags |= VIEWPORT_FLAG_INVISIBLE_VEHICLES;
        if (gConfigGeneral.invisible_trees)
            viewport->flags |= VIEWPORT_FLAG_INVISIBLE_VEGETATION;
        if (gConfigGeneral.invisible_scenery)
            viewport->flags |= VIEWPORT_FLAG_INVISIBLE_SCENERY;
        if (gConfigGeneral.invisible_paths)
            viewport->flags |= VIEWPORT_FLAG_INVISIBLE_PATHS;
        if (gConfigGeneral.invisible_supports)
            viewport->flags |= VIEWPORT_FLAG_INVISIBLE_SUPPORTS;
    }
};

/**
 * Creates the main window that holds the main viewport.
 *  rct2: 0x0066B3E8
 */
rct_window* WindowMainOpen()
{
    return WindowCreate<MainWindow>(WC_MAIN_WINDOW, { 0, 0 }, context_get_width(), context_get_height(), WF_STICK_TO_BACK);
}
