import { Component,HostListener,OnInit } from '@angular/core';
import { Resources } from './resources';
import { saveAs } from 'file-saver';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent extends Resources implements OnInit {
  title = 'mini-piano';
  lastNote = '';
  notesOnScreen:number[]=[];
  notesParts:number[]=[];
  tempo=1.0;
  choice = 0;
  enabledChoice = false;
  diffs:number[][]=[];
  notesColor:string[]=[];
  expNotes:number[]=[];
  indexTestedNote = 0;
  nbCorrect = 0;
  nbFalse = 0;

  ngOnInit(): void {
    this.diffs.push(this.NoteUtils.REGULS.map(n => n + this.NoteUtils.NOTES_PER_OCTAVE*2));
    let comp:number[]=[];
    for (let o = 0; o < 4; o++){
      for (let n of this.NoteUtils.REGULS.map(n => n + this.NoteUtils.NOTES_PER_OCTAVE*o)){
        comp.push(n);
      }
    }
    comp.push(this.NoteUtils.UPP_DO_POS);
    this.diffs.push(comp);
    let all:number[]=[];
    for (let n = this.NoteUtils.LOW_DO_POS; n <= this.NoteUtils.UPP_DO_POS; n++){
      all.push(n);
    }
    this.diffs.push(all);
  }
  onClick($event:number){
    if (this.enabledChoice) {
		return;
	}
	if (this.choice >= 1) {
		let expNote = this.expNotes[this.indexTestedNote];
		if (expNote === $event){
			this.nbCorrect++;
		} else {
			this.nbFalse++;
		}
		this.lastNote = this.NoteUtils.str($event);
		this.notesColor.push(this.NoteUtils.color(expNote,$event));
		if (this.indexTestedNote + 1 < this.expNotes.length){
			this.indexTestedNote++;
			this.notesOnScreen.push(this.expNotes[this.indexTestedNote]);
		} else {
			this.enabledChoice = true;
		}
		return;
	}
    let audio = new Audio();
	audio.src = "../assets/sounds/"+($event+15)+".wav";
	audio.load();
	audio.play();
	if (this.notesOnScreen.length >= 16){
		this.notesOnScreen = [];
	}
	this.lastNote = this.NoteUtils.str($event);
	this.notesOnScreen.push($event);
	this.notesParts.push($event);
  }
  res():void{
     if (this.choice >= 1) {
		return;
	 }
     this.notesOnScreen = [];
     this.notesParts = [];
  }
  chg():void{
     this.notesOnScreen = [];
     this.notesParts = [];
	 this.notesColor=[];
     this.enabledChoice = !this.enabledChoice;
     if (!this.enabledChoice){
         if (this.choice >= 1) {
			this.expNotes=[];
			this.indexTestedNote=0;
			this.nbCorrect=0;
			this.nbFalse=0;
			let lsQuiz = this.diffs[this.choice - 1];
			for (let it = 0; it < this.NoteUtils.NB_ANS; it++){
				let editInd = Math.floor(Math.random()*lsQuiz.length);
				this.expNotes.push(lsQuiz[editInd]);
			}
			let expNote = this.expNotes[this.indexTestedNote];
			this.notesOnScreen.push(expNote);
		 }
     }
  }
  saveLast():void{
     if (this.choice >= 1) {
		return;
	 }
    let lines = '';
	let nbRows = Math.floor(this.notesParts.length/16)+1;
	if (this.notesParts.length % 16 === 0){
		nbRows--;
	}
	for (let r = 0; r < nbRows; r++){
		for (let i = 0; i < 5; i++){
			lines+=`<path d="M 0 ${this.boundUpp(i)+r*320} L 512 ${this.boundUpp(i)+r*320}" stroke="black" fill="transparent"/>`;
		}
		for (let i = 0; i < 5; i++){
			lines+=`<path d="M 0 ${this.boundLow(i)+r*320} L 512 ${this.boundLow(i)+r*320}" stroke="black" fill="transparent"/>`;
		}
		lines += `<path d="M ${this.NoteUtils.LEFT} ${this.NoteUtils.OFFSET_UPPER_LINES+r*320} L ${this.NoteUtils.LEFT} ${this.NoteUtils.BOTTOM_LOWER_LINES+r*320}" stroke="black" fill="transparent"/>`;
	}
	let svgFile = `<svg>`;
	svgFile += lines;
	for (let r = 0; r < nbRows; r++){
		for (let n = 0; n < 16; n++){
			let ind = r * 16 + n;
			if (ind >= this.notesParts.length){
				continue;
			}
			let ab = ind % 16;
			let real = r;
			let note = this.notesParts[ind];
			let diese = this.NoteUtils.isDiese(note);
			let heightNote = this.NoteUtils.height(note);
			let nbDash = this.NoteUtils.ndDash(note);
			let off = this.NoteUtils.isDiese(note)?10:0;
			if (diese){
				svgFile += `<text x="${ab*this.NoteUtils.NOTE_SPACE}" y="${heightNote+real*320}">#</text>`;
			}
			if(nbDash===1){
				svgFile += `<path d="M ${2+ab*this.NoteUtils.NOTE_SPACE+off} ${heightNote+real*320} L ${28+ab*this.NoteUtils.NOTE_SPACE+off} ${heightNote+real*320}" stroke="black" fill="transparent"/>`;
			}
			if(nbDash===1.5){
				svgFile += `<path d="M ${2+ab*this.NoteUtils.NOTE_SPACE+off} ${heightNote+8+real*320} L ${28+ab*this.NoteUtils.NOTE_SPACE+off} ${heightNote+8+real*320}" stroke="black" fill="transparent"/>`;
			}
			if(nbDash===-1.5){
				svgFile += `<path d="M ${2+ab*this.NoteUtils.NOTE_SPACE+off} ${heightNote-8+real*320} L ${28+ab*this.NoteUtils.NOTE_SPACE+off} ${heightNote-8+real*320}" stroke="black" fill="transparent"/>`;
			}
			if(nbDash===-2){
				svgFile += `<path d="M ${2+ab*this.NoteUtils.NOTE_SPACE+off} ${heightNote+real*320} L ${28+ab*this.NoteUtils.NOTE_SPACE+off} ${heightNote+real*320}" stroke="black" fill="transparent"/>`;
				svgFile += `<path d="M ${2+ab*this.NoteUtils.NOTE_SPACE+off} ${heightNote-16+real*320} L ${28+ab*this.NoteUtils.NOTE_SPACE+off} ${heightNote-16+real*320}" stroke="black" fill="transparent"/>`;
			}
			if(nbDash===2){
				svgFile += `<path d="M ${2+ab*this.NoteUtils.NOTE_SPACE+off} ${heightNote+real*320} L ${28+ab*this.NoteUtils.NOTE_SPACE+off} ${heightNote+real*320}" stroke="black" fill="transparent"/>`;
				svgFile += `<path d="M ${2+ab*this.NoteUtils.NOTE_SPACE+off} ${heightNote+16+real*320} L ${28+ab*this.NoteUtils.NOTE_SPACE+off} ${heightNote+16+real*320}" stroke="black" fill="transparent"/>`;
			}
			svgFile += `<circle cx="${12+ab*this.NoteUtils.NOTE_SPACE+off}" cy="${heightNote+real*320}" r="8"/>`;
			svgFile += `<path d="M ${20+ab*this.NoteUtils.NOTE_SPACE+off} ${heightNote+real*320} L ${20+ab*this.NoteUtils.NOTE_SPACE+off} ${heightNote-32+real*320}" stroke="black" fill="transparent"/>`;
		}
	}
	svgFile += `</svg>`;
	if (this.notesParts.length){
	  var blob = new Blob([`<svg xmlns="http://www.w3.org/2000/svg" xmlns:_xmlns="xmlns">`+svgFile+`</svg>`], {type: "text/plain;charset=utf-8"});
	  saveAs(blob,'partition.svg');
	}
  }
  boundUpp(i:number):number{
     return i*this.NoteUtils.LINE_SPACE+64;
  }
  boundLow(i:number):number{
     return i*this.NoteUtils.LINE_SPACE+192;
  }
  svgNote(note:number,lines:string):string{
	if (note < 0){
		return "";
	}
	let diese = this.NoteUtils.isDiese(note);
	let heightNote = this.NoteUtils.height(note);
	let nbDash = this.NoteUtils.ndDash(note);
	let off = this.NoteUtils.isDiese(note)?10:0;
	let svgFile = `<svg width="40" height="320">`;
	svgFile += lines;
	if (diese){
		svgFile += `<text x="0" y="${heightNote}">#</text>`;
	}
	if(nbDash===1){
		svgFile += `<path d="M ${2+off} ${heightNote} L ${28+off} ${heightNote}" stroke="black" fill="transparent"/>`;
	}
	if(nbDash===1.5){
		svgFile += `<path d="M ${2+off} ${heightNote+8} L ${28+off} ${heightNote+8}" stroke="black" fill="transparent"/>`;
	}
	if(nbDash===-1.5){
		svgFile += `<path d="M ${2+off} ${heightNote-8} L ${28+off} ${heightNote-8}" stroke="black" fill="transparent"/>`;
	}
	if(nbDash===-2){
		svgFile += `<path d="M ${2+off} ${heightNote} L ${28+off} ${heightNote}" stroke="black" fill="transparent"/>`;
		svgFile += `<path d="M ${2+off} ${heightNote-16} L ${28+off} ${heightNote-16}" stroke="black" fill="transparent"/>`;
	}
	if(nbDash===2){
		svgFile += `<path d="M ${2+off} ${heightNote} L ${28+off} ${heightNote}" stroke="black" fill="transparent"/>`;
		svgFile += `<path d="M ${2+off} ${heightNote+16} L ${28+off} ${heightNote+16}" stroke="black" fill="transparent"/>`;
	}
	svgFile += `<circle cx="${12+off}" cy="${heightNote}" r="8"/>`;
	svgFile += `<path d="M ${20+off} ${heightNote} L ${20+off} ${heightNote-32}" stroke="black" fill="transparent"/>`;
	svgFile += `</svg>`;
	return svgFile;

}
  @HostListener('document:keydown', ['$event'])
  handleKeyDown(event: KeyboardEvent) {
    if (event.key === 'ArrowUp'){
	    if (this.tempo < 4.0){
			this.tempo *= 2.0;
		}
		return;
	} 
	if (event.key === 'ArrowDown'){
		if (this.tempo > .25){
			this.tempo /= 2.0;
		}
		return;
	} 
    
  }
}
