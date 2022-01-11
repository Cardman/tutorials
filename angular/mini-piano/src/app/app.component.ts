import { Component,HostListener } from '@angular/core';
import { NoteUtils } from './note-utils';
import { saveAs } from 'file-saver';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'mini-piano';
  state = -1;
  octave = -1;
  tempo=1.0;
  saveLines:boolean = false;
  onClick($event:number){
    let audio = new Audio();
	audio.src = "../assets/sounds/"+($event+15)+".wav";
	audio.load();
	audio.play();
	this.state = $event;
	this.octave = NoteUtils.octave($event);
  }
  saveLast():void{
    let lines = '';
	if (this.saveLines){
		lines += `<svg>`;
		for (let i = 0; i < 5; i++){
			lines+=`<path d="M 0 ${AppComponent.boundUpp(i)} L 40 ${AppComponent.boundUpp(i)}" stroke="black" fill="transparent"/>`;
		}
		for (let i = 0; i < 5; i++){
			lines+=`<path d="M 0 ${AppComponent.boundLow(i)} L 40 ${AppComponent.boundLow(i)}" stroke="black" fill="transparent"/>`;
		}
		lines += `</svg>`;
	
	}
	let res = AppComponent.svgNote(this.state,lines);
	if (res){
	  var blob = new Blob([`<svg xmlns="http://www.w3.org/2000/svg" xmlns:_xmlns="xmlns">`+res+`</svg>`], {type: "text/plain;charset=utf-8"});
	  saveAs(blob,this.state+'.svg');
	}
  }
  static boundUpp(i:number):number{
     return i*NoteUtils.LINE_SPACE+64;
  }
  static boundLow(i:number):number{
     return i*NoteUtils.LINE_SPACE+192;
  }
  static svgNote(note:number,lines:string):string{
	if (note < 0){
		return "";
	}
	let diese = NoteUtils.isDiese(note);
	let heightNote = NoteUtils.height(note);
	let nbDash = NoteUtils.ndDash(note);
	let off = NoteUtils.isDiese(note)?10:0;
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
