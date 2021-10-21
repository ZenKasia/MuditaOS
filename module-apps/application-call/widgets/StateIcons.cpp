// Copyright (c) 2017-2021, Mudita Sp. z.o.o. All rights reserved.
// For licensing, see https://github.com/mudita/MuditaOS/LICENSE.md

#include "CallAppStyle.hpp"
#include "StateIcons.hpp"

namespace gui
{
    namespace
    {
        constexpr auto muteImg       = "microphone_on";
        constexpr auto mutedImg      = "microphone_off";
        constexpr auto muteStr       = "app_call_mute";
        constexpr auto mutedStr      = "app_call_muted";
        constexpr auto speakerImg    = "speaker_off";
        constexpr auto speakerOnImg  = "speaker_on";
        constexpr auto speakerStr    = "app_call_speaker";
        constexpr auto speakerOnStr  = "app_call_speaker_on";

        const StateIcon<MicrophoneIconState>::IconMap microphoneIconMap = {
            {MicrophoneIconState::MUTE, {muteImg, muteStr}}, {MicrophoneIconState::MUTED, {mutedImg, mutedStr}}};
        const StateIcon<SpeakerIconState>::IconMap speakerIconMap = {
            {SpeakerIconState::SPEAKER, {speakerImg, speakerStr}},
            {SpeakerIconState::SPEAKERON, {speakerOnImg, speakerOnStr}}};
    } // namespace

    MicrophoneIcon::MicrophoneIcon(Item *parent)
        : StateIcon(parent, MicrophoneIconState::MUTE, microphoneIconMap, gui::ImageTypeSpecifier::W_M)
    {}

    SpeakerIcon::SpeakerIcon(Item *parent)
        : StateIcon(parent, SpeakerIconState::SPEAKER, speakerIconMap, gui::ImageTypeSpecifier::W_M)
    {}

} // namespace gui
