import { Component } from '@angular/core';
import { NoteUtils } from './note-utils';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'mini-piano';
  state = -1;
  octave = -1;
  heightNote = -1;
  off=0;
  nbDash=0;
  diese = '';
  onClick($event:number){
  let audio = new Audio();
	audio.src = "../assets/sounds/"+($event+15)+".wav";
	audio.load();
	audio.play();
	this.state = $event;
	this.octave = NoteUtils.octave($event);
	this.diese = NoteUtils.isDiese($event)?'#':'';
	this.off = NoteUtils.isDiese($event)?10:0;
	this.heightNote = NoteUtils.height($event);
	this.nbDash = NoteUtils.ndDash($event);
  }
}
