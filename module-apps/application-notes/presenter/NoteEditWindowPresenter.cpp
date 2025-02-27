// Copyright (c) 2017-2021, Mudita Sp. z.o.o. All rights reserved.
// For licensing, see https://github.com/mudita/MuditaOS/LICENSE.md

#include "NoteEditWindowPresenter.hpp"

namespace app::notes
{
    namespace
    {
        struct AutoSavePolicy
        {
            bool operator()(bool isNoteEmpty) const noexcept
            {
                return !isNoteEmpty;
            }
        };
    } // namespace

    NoteEditWindowPresenter::NoteEditWindowPresenter(std::unique_ptr<AbstractNotesRepository> &&notesRepository)
        : notesRepository{std::move(notesRepository)}
    {}

    void NoteEditWindowPresenter::onNoteChanged()
    {
        noteChanged = true;
    }

    bool NoteEditWindowPresenter::isAutoSaveApproved() const noexcept
    {
        return noteChanged;
    }

    void NoteEditWindowPresenter::save(std::shared_ptr<NotesRecord> &note)
    {
        notesRepository->save(*note, [note](bool succeed, std::uint32_t noteId) {
            LOG_INFO("Note %s", succeed ? "successfully saved" : "save failed");
            if (succeed) {
                note->ID = noteId;
            }
        });
        noteChanged = false;
    }

    bool NoteCreateWindowPresenter::isAutoSaveApproved() const noexcept
    {
        AutoSavePolicy policy;
        return NoteEditWindowPresenter::isAutoSaveApproved() && policy(getView()->isNoteEmpty());
    }
} // namespace app::notes
