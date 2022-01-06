import { Component, OnInit } from '@angular/core';
import { Input, Output, EventEmitter } from '@angular/core';

@Component({
  selector: '[svgpath2]',
  templateUrl: './img-component.component.svg',
  styleUrls: ['./img-component.component.css']
})
export class ImgComponentComponent implements OnInit {
  @Input() nb=0;
  @Input() x=0;
  @Input() y=0;
  @Output() newItemEvent = new EventEmitter<number>();
  constructor() { }

  ngOnInit(): void {
  }

  clk(): void {
    this.newItemEvent.emit(this.nb);
  }
}
