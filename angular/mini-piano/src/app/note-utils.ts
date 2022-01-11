export class NoteUtils{
    static readonly NOTES_PER_OCTAVE = 12;
    static readonly LEFT = 0;
    static readonly RIGHT = 512;
    static readonly WIDTH = 512;
    static readonly LINES_NB = 5;
    static readonly RADIUS_NOTE = 8;
    static readonly LINE_SPACE = 2 * NoteUtils.RADIUS_NOTE;
    static readonly HEIGHT_LINES = (NoteUtils.LINES_NB - 1) * NoteUtils.LINE_SPACE;
    static readonly OFFSET_UPPER_LINES = 64;
    static readonly OFFSET_LOWER_LINES = NoteUtils.OFFSET_UPPER_LINES + NoteUtils.HEIGHT_LINES + 64;
    static readonly OFFSET_DO_UPP_LOW = NoteUtils.OFFSET_UPPER_LINES + NoteUtils.HEIGHT_LINES + NoteUtils.LINE_SPACE;
    static readonly OFFSET_SI_LOW_UPP = NoteUtils.OFFSET_LOWER_LINES - NoteUtils.RADIUS_NOTE;
    static readonly CENTER_NOTE = 4+NoteUtils.RADIUS_NOTE;
    static readonly VERT_BAR = NoteUtils.CENTER_NOTE+NoteUtils.RADIUS_NOTE;
    static readonly NOTE_LEFT_ROW = NoteUtils.CENTER_NOTE-NoteUtils.RADIUS_NOTE-2;
    static readonly NOTE_RIGHT_ROW = NoteUtils.CENTER_NOTE+NoteUtils.RADIUS_NOTE+8;
	static readonly NO_DASH = 0.0;
	static readonly ONE_DASH = 1.0;
	static readonly ONE_HALF_DASH_LOW = -1.5;
	static readonly ONE_HALF_DASH_UPP = 1.5;
	static readonly TWO_DASHES_LOW = -2.0;
	static readonly TWO_DASHES_UPP = 2.0;
    static readonly REGULS = [1, 3, 5, 6, 8, 10, 12];
    static readonly DIESES = [2, 4, 7, 9, 11];
    static height(note:number):number{
        let diff = NoteUtils.isDiese(note)?-1:0;
        let doUppLowPos = NoteUtils.posNoDiese(1 + 2 * NoteUtils.NOTES_PER_OCTAVE);
        let siLowUpPos = NoteUtils.posNoDiese(2 * NoteUtils.NOTES_PER_OCTAVE);
        let adj = NoteUtils.posNoDiese(note);
        if (adj >= doUppLowPos) {
            return NoteUtils.OFFSET_DO_UPP_LOW - (adj - doUppLowPos) * NoteUtils.RADIUS_NOTE;
        }
        return NoteUtils.OFFSET_SI_LOW_UPP + (siLowUpPos - adj) * NoteUtils.RADIUS_NOTE;
    }
    static posNoDiese(note:number):number{
        let nbDieses = 0;
        for (let i = 1; i <= note; i++){
            if (NoteUtils.isDiese(i)){
                nbDieses++;
            }
        }
        return note - nbDieses;
    }
    static isDiese(note:number):boolean{
        let oct = (note-1) % NoteUtils.NOTES_PER_OCTAVE + 1;
        return NoteUtils.DIESES.indexOf(oct) > -1;
    }
    static octave(note:number):number{
        for (let o = 2; o < 6; o++){
            if (note <= NoteUtils.NOTES_PER_OCTAVE * (o - 1)){
                return o;
            }
        }
        return 6;
    }
    static ndDash(note:number):number{
        if (note >= 6 && note <= 45 && note !== 25 && note !== 26){
            return NoteUtils.NO_DASH;
        }
        if (note === 5 || note === 25 || note === 26 || note == 46 || note == 47){
            return NoteUtils.ONE_DASH;
        }
        if (note === 48){
            return NoteUtils.ONE_HALF_DASH_UPP;
        }
        if (note === 3 || note == 4){
            return NoteUtils.ONE_HALF_DASH_LOW;
        }
        if (note === 1 || note === 2){
            return NoteUtils.TWO_DASHES_LOW;
        }
        return NoteUtils.TWO_DASHES_UPP;
    }
}