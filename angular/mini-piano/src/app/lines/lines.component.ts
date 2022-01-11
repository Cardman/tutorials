import { Component, OnInit, Input } from '@angular/core';
import { Resources } from '../resources';

@Component({
  selector: '[lines]',
  templateUrl: './lines.component.svg',
  styleUrls: []
})
export class LinesComponent extends Resources {
  @Input() y=0;

}
