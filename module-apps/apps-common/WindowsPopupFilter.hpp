// Copyright (c) 2017-2021, Mudita Sp. z.o.o. All rights reserved.
// For licensing, see https://github.com/mudita/MuditaOS/LICENSE.md

#pragma once

#include <functional>

namespace gui
{
    class PopupRequestParams;
}
namespace app
{
    class WindowsStack;
}
namespace gui::popup
{
    /// This filter class is used just to filter next popup to handle if any
    /// it can and should be overriden to filter out only interesting us popups right now
    class Filter
    {
      private:
        std::function<bool(const gui::PopupRequestParams &)> appDependentFilter = nullptr;
        app::WindowsStack *stack                                                = nullptr;

      public:
        void attachWindowsStack(app::WindowsStack *stack);
        void addAppDependentFilter(std::function<bool(const gui::PopupRequestParams &)> f);
        virtual bool is_ok(const gui::PopupRequestParams &params) const;
    };
} // namespace gui::popup
