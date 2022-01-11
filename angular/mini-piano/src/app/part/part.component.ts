import { Component, OnInit,Input } from '@angular/core';
import { Resources } from '../resources';

@Component({
  selector: 'part',
  templateUrl: './part.component.html',
  styleUrls: []
})
export class PartComponent extends Resources {
  @Input() notesOnScreen:number[]=[];

}
