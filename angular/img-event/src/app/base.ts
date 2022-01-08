import { Component, OnInit } from '@angular/core';
import { Input, Output, EventEmitter } from '@angular/core';

@Component({
  template: ''
})
export class Base implements OnInit {
  @Input() nb=0;
  @Input() x=0;
  @Input() y=0;
  @Output() newItemEvent = new EventEmitter<number>();

  ngOnInit(): void {
  }

  clk(): void {
    this.newItemEvent.emit(this.nb);
  }
}
