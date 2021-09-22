import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule,ReactiveFormsModule } from '@angular/forms';

import { AppComponent } from './app.component';
import { AppRoutingModule } from './app.routing.module';
import {HttpClient, HttpClientModule} from "@angular/common/http";
import { OpersComponent } from './opers/opers.component';
import { OpersService } from './opers.service';


@NgModule({
  declarations: [
    AppComponent,
    OpersComponent
  ],
  imports: [
    AppRoutingModule,
    BrowserModule,
    HttpClientModule,
    FormsModule,
    ReactiveFormsModule
  ],
  providers: [OpersService],
  bootstrap: [AppComponent],
  exports:[]
})
export class AppModule { }

