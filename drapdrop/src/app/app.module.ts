import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import {DragDropModule} from '@angular/cdk/drag-drop';
import {ScrollingModule} from '@angular/cdk/scrolling';

import { AppComponent } from './app.component';
import { CdkVirtualScrollContextExample } from './cdk-virtual-scroll-context-example';

@NgModule({
  declarations: [
    AppComponent,
    CdkVirtualScrollContextExample
  ],
  imports: [
    BrowserModule,
    DragDropModule,ScrollingModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
