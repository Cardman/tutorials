import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule,ReactiveFormsModule } from '@angular/forms';
import {SelecteurModule} from './selecteur/selecteur.module'
import {SelectionListeModule} from './selection_liste/selection_liste.module'

import { AppComponent } from './app.component';
import { UserComponent } from './user/user.component';
import { User2Component } from './user2/user-2.component';
import { AppRoutingModule } from './app.routing.module';
import {UserService} from './services/user.service';
import {SelectionListeService} from './services/selection_liste.service';
import {HttpClientModule} from "@angular/common/http";
import {AddUserComponent} from './user/add-user.component';
import {EditUserComponent} from './user/edit-user.component';
import {AddUser2Component} from './user2/add-user-2.component';
import {EditUser2Component} from './user2/edit-user-2.component';

@NgModule({
  declarations: [
    AppComponent,
    UserComponent,
    AddUserComponent,
    EditUserComponent,
    User2Component,
    AddUser2Component,
    EditUser2Component
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    HttpClientModule,
    FormsModule,
    ReactiveFormsModule,
    SelecteurModule,
    SelectionListeModule
  ],
  providers: [UserService,SelectionListeService],
  bootstrap: [AppComponent],
  exports:[]
})
export class AppModule { }
