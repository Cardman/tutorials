import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule,ReactiveFormsModule } from '@angular/forms';

import {HttpClientModule} from "@angular/common/http";
import {SelecteurComponent} from './selecteur.component';

@NgModule({
  declarations: [
    SelecteurComponent
  ],
  imports: [
    BrowserModule,
    HttpClientModule,
    ReactiveFormsModule,
    FormsModule
  ],
  providers: [],
  bootstrap: [],
  exports:[SelecteurComponent]
})
export class SelecteurModule { }
