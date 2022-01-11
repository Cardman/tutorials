import { Component, OnInit,Input } from '@angular/core';
import { NoteUtils } from '../note-utils';
import { Resources } from '../resources';

@Component({
  selector: 'part',
  templateUrl: './part.component.html',
  styleUrls: []
})
export class PartComponent extends Resources {
  @Input() note=-1;
  get heightNote():number{
    return this.NoteUtils.height(this.note);
  }
  get diese():boolean{
    return this.NoteUtils.isDiese(this.note);
  }
  get off():number{
    return this.NoteUtils.isDiese(this.note)?10:0;
  }
  get nbDash():number{
    return this.NoteUtils.ndDash(this.note);
  }
}
