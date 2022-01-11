import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { FormsModule } from '@angular/forms'; 

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { LeftKeyComponent } from './left-key/left-key.component';
import { RightKeyComponent } from './right-key/right-key.component';
import { CenterKeyComponent } from './center-key/center-key.component';
import { BlackKeyComponent } from './black-key/black-key.component';
import { UpperKeyComponent } from './upper-key/upper-key.component';
import { LineComponent } from './line/line.component';
import { LinesComponent } from './lines/lines.component';
import { PartComponent } from './part/part.component';

@NgModule({
  declarations: [
    LeftKeyComponent,
    RightKeyComponent,
    CenterKeyComponent,
    BlackKeyComponent,
    UpperKeyComponent,
    LineComponent,
    LinesComponent,
    PartComponent,
    AppComponent
  ],
  imports: [
    BrowserModule,
    FormsModule,
    AppRoutingModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
