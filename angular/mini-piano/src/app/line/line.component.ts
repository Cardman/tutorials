import { Component, OnInit, Input } from '@angular/core';
import { NoteUtils } from '../note-utils';

@Component({
  selector: '[line]',
  templateUrl: './line.component.svg',
  styleUrls: []
})
export class LineComponent {
  @Input() l=0;
  @Input() y=0;
  public NoteUtils = NoteUtils;

  get coords():number{
    return NoteUtils.LINE_SPACE*this.l+this.y;
  }
}
