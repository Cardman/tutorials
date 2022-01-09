export class NoteUtils{
    static height(note:number):number{
        const doUppLow = 144;
        const siLowUpp = 184;
        let diff = NoteUtils.isDiese(note)?-1:0;
        let doUppLowPos = NoteUtils.posNoDiese(25);
        let siLowUpPos = NoteUtils.posNoDiese(24);
        let adj = NoteUtils.posNoDiese(note);
        if (adj >= doUppLowPos) {
            return doUppLow - (adj - doUppLowPos) * 8;
        }
        return siLowUpp + (siLowUpPos - adj) * 8;
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
        let oct = (note-1) % 12 + 1;
        return oct === 2 || oct === 4 || oct === 7 || oct === 9 || oct === 11;
    }
    static octave(note:number):number{
        if (note <= 12){
            return 2;
        }
        if (note <= 24){
            return 3;
        }
        if (note <= 36){
            return 4;
        }
        if (note <= 48){
            return 5;
        }
        return 6;
    }
    static ndDash(note:number):number{
        if (note >= 6 && note <= 45 && note !== 25 && note !== 26){
            return 0;
        }
        if (note === 5 || note === 25 || note === 26 || note == 46 || note == 47){
            return 1;
        }
        if (note === 48){
            return 1.5;
        }
        if (note === 3 || note == 4){
            return -1.5;
        }
        if (note === 1 || note === 2){
            return -2;
        }
        return 2;
    }
}