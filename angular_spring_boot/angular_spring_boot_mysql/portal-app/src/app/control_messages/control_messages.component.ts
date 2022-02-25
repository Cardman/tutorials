import { Component, Input } from '@angular/core';
import { FormGroup, FormControl } from '@angular/forms';

@Component({
  selector: 'control-messages',
  template: `
    <div *ngIf="errorMess !== null">{{errorMess}}</div>
  `
})
export class ControlMessagesComponent {
  @Input() control: FormControl;
  @Input() glob: boolean;
  constructor() {}

  get errorMess():string {
    if (this.glob){
     for (let propertyName in this.control.errors) {
       if (
        this.control.errors.hasOwnProperty(propertyName)
      ) {
         return propertyName+':'+this.control.errors[propertyName];
       }
     }

     return null;
    }
    for (let propertyName in this.control.errors) {
      if (
        this.control.errors.hasOwnProperty(propertyName) &&
        this.control.touched
      ) {
        return propertyName+':'+this.control.errors[propertyName];
      }
    }

    return null;
  }
}