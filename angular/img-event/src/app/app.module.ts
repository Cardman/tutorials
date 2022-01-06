import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppComponent } from './app.component';
import { ImgComponentComponent } from './img-component/img-component.component';
import { ImgComponent2Component } from './img-component2/img-component2.component';

@NgModule({
  declarations: [
    AppComponent,
	ImgComponentComponent,
	ImgComponent2Component
  ],
  imports: [
    BrowserModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
