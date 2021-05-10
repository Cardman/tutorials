import { Component, Input } from '@angular/core';
import { FormGroup, FormControl } from '@angular/forms';
import {TranslateService} from '@ngx-translate/core';

@Component({
  selector: 'control-messages',
  template: `
    <div *ngIf="errorMess !== null">{{errorMess}}</div>
  `
})
export class ControlMessagesComponent {
  @Input() control: FormControl;
  @Input() glob: boolean;
  constructor(private translateService:TranslateService) {}

  get errorMess():string {
    if (this.glob){
     for (let propertyName in this.control.errors) {
       if (
        this.control.errors.hasOwnProperty(propertyName)
      ) {
         return this.translateService.instant("errs."+propertyName,{nb:this.control.errors[propertyName]});
       }
     }

     return null;
    }
    for (let propertyName in this.control.errors) {
      if (
        this.control.errors.hasOwnProperty(propertyName) &&
        this.control.touched
      ) {
        return this.translateService.instant("errs."+propertyName,{nb:this.control.errors[propertyName]});
      }
    }

    return null;
  }
}