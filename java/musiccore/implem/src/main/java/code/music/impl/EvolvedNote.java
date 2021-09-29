package code.music.impl;

import code.music.core.AbstractNote;
import code.music.core.MetaNote;
import code.music.enums.Gamme;
import code.util.IdMap;
import jm.music.data.Note;

public final class EvolvedNote implements AbstractNote {
    private final Note note;
    public EvolvedNote(MetaNote _meta, IdMap<Gamme,Integer> _tr) {
        double ratio_ = _meta.ratio();
        note = new Note(Math.max(Note.MIN_PITCH, _meta.pitch(_tr)), ratio_);
        note.setDuration(ratio_);
        note.setDynamic(_meta.getDynamic());
    }
    public EvolvedNote(MetaNote _meta) {
        double ratio_ = _meta.ratio();
        note = new Note(Note.REST, ratio_);
        note.setDuration(ratio_);
        note.setDynamic(_meta.getDynamic());
    }

    public Note getNote() {
        return note;
    }
}
