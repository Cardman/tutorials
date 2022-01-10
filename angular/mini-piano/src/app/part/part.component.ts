import { Component, OnInit,Input } from '@angular/core';
import { NoteUtils } from '../note-utils';

@Component({
  selector: 'part',
  templateUrl: './part.component.html',
  styleUrls: []
})
export class PartComponent {
  @Input() note=-1;
  get heightNote():number{
    return NoteUtils.height(this.note);
  }
  get diese():boolean{
    return NoteUtils.isDiese(this.note);
  }
  get off():number{
    return NoteUtils.isDiese(this.note)?10:0;
  }
  get nbDash():number{
    return NoteUtils.ndDash(this.note);
  }
}
