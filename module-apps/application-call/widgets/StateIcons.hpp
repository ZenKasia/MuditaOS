// Copyright (c) 2017-2021, Mudita Sp. z.o.o. All rights reserved.
// For licensing, see https://github.com/mudita/MuditaOS/LICENSE.md

#pragma once

#include "StateIcon.hpp"

#include <cstdint>

namespace gui
{
    enum class MicrophoneIconState
    {
        MUTE,
        MUTED
    };

    class MicrophoneIcon : public StateIcon<MicrophoneIconState>
    {
      public:
        MicrophoneIcon() = delete;
        MicrophoneIcon(Item *parent);
    };

    enum class SpeakerIconState
    {
        SPEAKER,
        SPEAKERON
    };

    class SpeakerIcon : public StateIcon<SpeakerIconState>
    {
      public:
        SpeakerIcon() = delete;
        SpeakerIcon(Item *parent);
    };
} // namespace gui
