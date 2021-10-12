// Copyright (c) 2017-2021, Mudita Sp. z.o.o. All rights reserved.
// For licensing, see https://github.com/mudita/MuditaOS/LICENSE.md

#include "WindowsStack.hpp"
#include "WindowsFactory.hpp"
#include "windows/AppWindow.hpp"

namespace app
{
    std::map<std::string, std::unique_ptr<gui::AppWindow>>::const_iterator WindowsStack::begin() const
    {
        return std::begin(windows);
    }

    std::map<std::string, std::unique_ptr<gui::AppWindow>>::const_iterator WindowsStack::end() const
    {
        return std::end(windows);
    }

    void WindowsStack::push(const std::string &name,
                            std::unique_ptr<gui::AppWindow> window,
                            const gui::popup::Disposition &disposition)
    {
        LOG_INFO("pushing new window: %s", name.c_str());
        windows[name] = std::move(window);
        stack.push_back(WindowData(name, disposition));
    }

    gui::AppWindow *WindowsStack::get(const std::string &name) const
    {
        auto ret = windows.find(name);
        return ret == std::end(windows) ? nullptr : ret->second.get();
    }

    std::optional<WindowData> WindowsStack::getWindowData(uint32_t depth) const
    {
        if (depth >= stack.size()) {
            return std::nullopt;
        }
        return {*std::prev(stack.end(), depth + 1)};
    }

    std::optional<std::string> WindowsStack::get(uint32_t depth) const
    {
        if (auto windowData = getWindowData(depth)) {
            return {windowData->name};
        }
        return std::nullopt;
    }

    [[nodiscard]] bool WindowsStack::isEmpty() const noexcept
    {
        return stack.empty();
    }

    /// return false on pop empty
    bool WindowsStack::pop() noexcept
    {
        if (!stack.empty()) {
            stack.pop_back();
            return true;
        }
        return false;
    }

    /// TODO on close shall be handled on drops
    bool WindowsStack::popTo(const std::string &window)
    {
        auto ret = findInStack(window);
        if (ret != stack.end()) {
            LOG_INFO("---> Pop last window(s) [%d] :  %s",
                     static_cast<int>(std::distance(ret, stack.end())),
                     ret->name.c_str());
            stack.erase(std::next(ret), stack.end());
            LOG_INFO("Curent window... %s vs %s", ret->name.c_str(), stack.back().name.c_str());
            return true;
        }
        LOG_INFO("WINODW %s NOT DROPPED", window.c_str());
        return false;
    }

    bool WindowsStack::popLastWindow()
    {
        if (stack.size() == 1) {
            stack.clear();
            return true;
        }
        return false;
    }

    /// TODO on close shall be handled on drops
    /// return false on pop to non existing window
    /// THIS CAN REMOVE CURRENT WINDOW
    bool WindowsStack::drop(const std::string &window)
    {
        LOG_INFO("----------------------------------- DROPPING WINDOW %s", window.c_str());
        auto popWindow = findInStack(window);
        if (popWindow != stack.end()) {
            LOG_INFO("DROP SUCCESS %s", window.c_str());
            stack.erase(popWindow);
            return true;
        }
        LOG_INFO("DROP FAIL %s", window.c_str());
        return false;
    }

    void WindowsStack::logStack(std::ostream &out)
    {
        for (const auto &el : stack) {
            out << "logStack "
                << "name: " << el.name.c_str() << " "
                << "type: " << magic_enum::enum_name(el.disposition.windowtype) << " "
                << "popup::ID: " << magic_enum::enum_name(el.disposition.id) << " "
                << "priority: " << magic_enum::enum_name(el.disposition.priority) << " " << std::endl;
        }
    }

    bool WindowsStack::rebuildWindows(app::WindowsFactory &windowsFactory, ApplicationCommon *app)
    {
        if (windows.empty()) {
            return false;
        }
        for (auto &[name, window] : windows) {
            LOG_DEBUG("Rebuild: %s", name.c_str());
            windows[name] = windowsFactory.build(app, name);
        }
        return true;
    }

    decltype(WindowsStack::stack)::iterator WindowsStack::findInStack(const std::string &window)
    {
        return std::find_if(stack.begin(), stack.end(), [&](auto &el) { return el.name == window; });
    }

} // namespace app
