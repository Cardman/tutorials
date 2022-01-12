import { Component, OnInit,Input } from '@angular/core';
import { Resources } from '../resources';

@Component({
  selector: '[notes]',
  templateUrl: './note.component.svg',
  styleUrls: []
})
export class NoteComponent extends Resources {
  @Input() pitch=this.NoteUtils.NO_NOTE;
  @Input() index=this.NoteUtils.NO_NOTE;
  @Input() colorDom='black';
  get pos():number{
    return this.index*this.NoteUtils.NOTE_SPACE;
  }
  get heightNote():number{
    return this.NoteUtils.height(this.pitch);
  }
  get diese():boolean{
    return this.NoteUtils.isDiese(this.pitch);
  }
  get off():number{
    return this.NoteUtils.isDiese(this.pitch)?this.NoteUtils.OFF_NOTE:this.NoteUtils.OFF_DIESE_NOTE;
  }
  get nbDash():number{
    return this.NoteUtils.ndDash(this.pitch);
  }
}
