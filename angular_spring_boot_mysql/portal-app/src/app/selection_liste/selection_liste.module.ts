import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule,ReactiveFormsModule } from '@angular/forms';
import {ControlMessagesModule} from '../control_messages/control_messages.module'

import {HttpClientModule} from "@angular/common/http";
import {SelectionListeComponent} from './selection_liste.component';
import {SelectionListeService} from '../services/selection_liste.service';


@NgModule({
  declarations: [
    SelectionListeComponent
  ],
  imports: [
    BrowserModule,
    HttpClientModule,
    ReactiveFormsModule,
    FormsModule,
    ControlMessagesModule
  ],
  providers: [SelectionListeService],
  bootstrap: [],
  exports:[SelectionListeComponent]
})
export class SelectionListeModule { }
