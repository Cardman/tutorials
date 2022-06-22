import { Component, OnInit } from '@angular/core';
import { Input, Output, EventEmitter } from '@angular/core';
import { Resources } from './resources';

@Component({
  template: '',
  styleUrls: []
})
export class Base extends Resources implements OnInit {
  @Input() nb=0;
  @Input() x=0;
  @Input() y=0;
  @Output() newItemEvent = new EventEmitter<number>();
  @Input() keyPressed: {[name:number]:boolean}={};

  ngOnInit(): void {
  }

  get pressed():boolean{
    return this.keyPressed[this.nb+15] === true;
  }
  clk(): void {
    this.newItemEvent.emit(this.nb);
  }
}
