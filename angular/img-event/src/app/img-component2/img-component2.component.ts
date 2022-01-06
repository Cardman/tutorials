import { Component, OnInit } from '@angular/core';
import { Input, Output, EventEmitter } from '@angular/core';

@Component({
  selector: '[svgpath4]',
  templateUrl: './img-component2.component.svg',
  styleUrls: ['./img-component2.component.css']
})
export class ImgComponent2Component implements OnInit {
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
