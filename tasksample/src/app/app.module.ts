import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppComponent } from './app.component';
import { FileUploaderComponent } from "./file-uploader.component";
import { PeopleService } from "./people.service";
import { EnemyListComponent } from "./enemy-list.component";
import { FriendListComponent } from "./friend-list.component";

@NgModule({
  declarations: [
    AppComponent,
    FileUploaderComponent,
    EnemyListComponent,
    FriendListComponent
  ],
  imports: [
    BrowserModule
  ],
  providers: [PeopleService],
  bootstrap: [AppComponent]
})
export class AppModule { }
