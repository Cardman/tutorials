import { Component, OnInit,Input } from '@angular/core';
import { Resources } from '../resources';

@Component({
  selector: 'part',
  templateUrl: './part.component.html',
  styleUrls: []
})
export class PartComponent extends Resources {
  @Input() note=this.NoteUtils.NO_NOTE;
  get heightNote():number{
    return this.NoteUtils.height(this.note);
  }
  get diese():boolean{
    return this.NoteUtils.isDiese(this.note);
  }
  get off():number{
    return this.NoteUtils.isDiese(this.note)?this.NoteUtils.OFF_NOTE:this.NoteUtils.OFF_DIESE_NOTE;
  }
  get nbDash():number{
    return this.NoteUtils.ndDash(this.note);
  }
}
