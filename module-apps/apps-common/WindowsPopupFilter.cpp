// Copyright (c) 2017-2021, Mudita Sp. z.o.o. All rights reserved.
// For licensing, see https://github.com/mudita/MuditaOS/LICENSE.md

#include "WindowsPopupFilter.hpp"
#include "WindowsStack.hpp"
#include "data/PopupRequestParams.hpp"
#include "AppWindow.hpp"

namespace gui::popup
{
    void Filter::attachWindowsStack(app::WindowsStack *stack)
    {
        this->stack = stack;
    }

    bool Filter::is_ok(const gui::PopupRequestParams &params) const
    {
        if (appDependentFilter != nullptr) {
            if (auto result = appDependentFilter(params); not result) {
                printf("--------- ignore - app dependent\n");
                return result;
            }
        }
        if (stack != nullptr) {
            auto data = stack->getWindowData(app::topWindow);
            if (not data) {
                printf("--------- ignore - no window\n");
                return true;
            }
            if ((*data).disposition.id == params.getPopupId()) {
                printf("--------- ignore - same popup id\n");
                /// its not ok to switch to popup of the same ID
                return false;
            }
            if ((*data).disposition.priority > params.getDisposition().priority) {
                printf("--------- ignore - lesser priority\n");
                /// it's not ok to switch to popup of lesser priority
                /// equal ones are fine
                return false;
            }
        }
        return true;
    }

    void Filter::addAppDependentFilter(std::function<bool(const gui::PopupRequestParams &)> f)
    {
        appDependentFilter = std::move(f);
    }

} // namespace gui::popup
