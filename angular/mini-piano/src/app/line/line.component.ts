import { Component, OnInit, Input } from '@angular/core';
import { Resources } from '../resources';

@Component({
  selector: '[line]',
  templateUrl: './line.component.svg',
  styleUrls: []
})
export class LineComponent extends Resources{
  @Input() l=0;
  @Input() y=0;

  get coords():number{
    return this.NoteUtils.LINE_SPACE*this.l+this.y;
  }
}
