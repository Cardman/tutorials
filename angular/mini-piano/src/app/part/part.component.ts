import { Component, OnInit,Input } from '@angular/core';

@Component({
  selector: 'part',
  templateUrl: './part.component.html',
  styleUrls: []
})
export class PartComponent {
  @Input() heightNote=-1;
  @Input() off=0;
  @Input() nbDash=0;
  @Input() diese=false;
}
