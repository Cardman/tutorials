import { Component, OnInit, Input } from '@angular/core';

@Component({
  selector: '[lines]',
  templateUrl: './lines.component.svg',
  styleUrls: []
})
export class LinesComponent {
  @Input() y=0;

}
