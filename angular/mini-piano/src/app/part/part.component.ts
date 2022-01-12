import { Component, OnInit,Input } from '@angular/core';
import { Resources } from '../resources';

@Component({
  selector: 'part',
  templateUrl: './part.component.html',
  styleUrls: []
})
export class PartComponent extends Resources {
  @Input() notesOnScreen:number[]=[];
  @Input() notesColor:string[]=[];

  domColor(ind:number):string{
    if (ind < this.notesColor.length){
      return this.notesColor[ind];
    }
    return 'black';
  }
}
