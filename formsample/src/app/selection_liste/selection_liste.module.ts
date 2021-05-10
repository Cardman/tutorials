import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule,ReactiveFormsModule } from '@angular/forms';
import {ControlMessagesModule} from '../control_messages/control_messages.module'

import {HttpClientModule} from "@angular/common/http";
import {SelectionListeComponent} from './selection_liste.component';
import {SelectionListeEnvComponent} from './selection_liste_env.component';
import {CustomstyleDirective} from './customstyle.directive';
import {DigitcountPipe} from './digitcount.pipe';


@NgModule({
  declarations: [
    SelectionListeComponent,
    SelectionListeEnvComponent,
    CustomstyleDirective,
    DigitcountPipe
  ],
  imports: [
    BrowserModule,
    HttpClientModule,
    ReactiveFormsModule,
    FormsModule,
    ControlMessagesModule
  ],
  providers: [],
  bootstrap: [],
  exports:[SelectionListeComponent,SelectionListeEnvComponent]
})
export class SelectionListeModule { }
