export class NoteUtils{
    static readonly REGULS = [1, 3, 5, 6, 8, 10, 12];
    static readonly DIESES = [2, 4, 7, 9, 11];
    static readonly NOTES_PER_OCTAVE = NoteUtils.REGULS.length + NoteUtils.DIESES.length;
    static readonly LEFT = 0;
    static readonly RIGHT = 512;
    static readonly WIDTH = 512;
    static readonly LINES_NB = 5;
    static readonly RADIUS_NOTE = 8;
    static readonly OFF_NOTE = 10;
    static readonly LINE_SPACE = 2 * NoteUtils.RADIUS_NOTE;
    static readonly HEIGHT_LINES = (NoteUtils.LINES_NB - 1) * NoteUtils.LINE_SPACE;
    static readonly OFFSET_UPPER_LINES = 64;
    static readonly OFFSET_LOWER_LINES = NoteUtils.OFFSET_UPPER_LINES + NoteUtils.HEIGHT_LINES + 64;
    static readonly BOTTOM_LOWER_LINES = NoteUtils.OFFSET_LOWER_LINES + NoteUtils.HEIGHT_LINES;
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
	static readonly DO_POS = 1 + 2 * NoteUtils.NOTES_PER_OCTAVE;
	static readonly DO_DIESE_POS = 1 + NoteUtils.DO_POS;
	static readonly LOW_DO_POS = 1;
	static readonly LOW_DO_DIESE_POS = 1+NoteUtils.LOW_DO_POS;
	static readonly LOW_RE_POS = NoteUtils.LOW_DO_DIESE_POS+1;
	static readonly LOW_RE_DIESE_POS = 1+NoteUtils.LOW_RE_POS;
	static readonly LOW_MI_POS = NoteUtils.LOW_RE_DIESE_POS+1;
	static readonly UPP_LA_POS = NoteUtils.DO_POS + NoteUtils.NOTES_PER_OCTAVE + 9;
	static readonly UPP_LA_DIESE_POS = 1 + NoteUtils.UPP_LA_POS;
	static readonly UPP_SI_POS = NoteUtils.UPP_LA_DIESE_POS+1;
	static readonly UPP_DO_POS = NoteUtils.UPP_SI_POS+1;
	static readonly MIN_OCT = 2;
	static readonly MAX_OCT = 6;
    static height(note:number):number{
        let diff = NoteUtils.isDiese(note)?-1:0;
        let doUppLowPos = NoteUtils.posNoDiese(NoteUtils.DO_POS);
        let siLowUpPos = NoteUtils.posNoDiese(NoteUtils.DO_POS-1);
        let adj = NoteUtils.posNoDiese(note);
        if (adj >= doUppLowPos) {
            return NoteUtils.OFFSET_DO_UPP_LOW - (adj - doUppLowPos) * NoteUtils.RADIUS_NOTE;
        }
        return NoteUtils.OFFSET_SI_LOW_UPP + (siLowUpPos - adj) * NoteUtils.RADIUS_NOTE;
    }
    static posNoDiese(note:number):number{
        let nbDieses = 0;
        for (let i = NoteUtils.LOW_DO_POS; i <= note; i++){
            if (NoteUtils.isDiese(i)){
                nbDieses++;
            }
        }
        return note - nbDieses;
    }
    static isDiese(note:number):boolean{
        let oct = (note-NoteUtils.LOW_DO_POS) % NoteUtils.NOTES_PER_OCTAVE + NoteUtils.LOW_DO_POS;
        return NoteUtils.DIESES.indexOf(oct) > -1;
    }
    static octave(note:number):number{
        for (let o = NoteUtils.MIN_OCT; o < NoteUtils.MAX_OCT; o++){
            if (note < NoteUtils.LOW_DO_POS + NoteUtils.NOTES_PER_OCTAVE * (o - 1)){
                return o;
            }
        }
        return NoteUtils.MAX_OCT;
    }
    static ndDash(note:number):number{
        if (note > NoteUtils.LOW_MI_POS && note < NoteUtils.UPP_LA_POS && note !== NoteUtils.DO_POS && note !== NoteUtils.DO_DIESE_POS){
            return NoteUtils.NO_DASH;
        }
        if (note === NoteUtils.LOW_MI_POS || note === NoteUtils.DO_POS || note === NoteUtils.DO_DIESE_POS || note == NoteUtils.UPP_LA_POS || note == NoteUtils.UPP_LA_DIESE_POS){
            return NoteUtils.ONE_DASH;
        }
        if (note === NoteUtils.UPP_SI_POS){
            return NoteUtils.ONE_HALF_DASH_UPP;
        }
        if (note === NoteUtils.LOW_RE_POS || note == NoteUtils.LOW_RE_DIESE_POS){
            return NoteUtils.ONE_HALF_DASH_LOW;
        }
        if (note === NoteUtils.LOW_DO_POS || note === NoteUtils.LOW_DO_DIESE_POS){
            return NoteUtils.TWO_DASHES_LOW;
        }
        return NoteUtils.TWO_DASHES_UPP;
    }
}