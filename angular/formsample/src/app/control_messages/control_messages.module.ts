import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule,ReactiveFormsModule } from '@angular/forms';

import {HttpClientModule} from "@angular/common/http";
import {ControlMessagesComponent} from './control_messages.component';
import {TranslateService} from '@ngx-translate/core';

@NgModule({
  declarations: [
    ControlMessagesComponent
  ],
  imports: [
    BrowserModule,
    HttpClientModule,
    ReactiveFormsModule,
    FormsModule
  ],
  providers: [TranslateService],
  bootstrap: [],
  exports:[ControlMessagesComponent]
})
export class ControlMessagesModule { }
