import { Component } from '@angular/core';
import {DomSanitizer,SafeUrl,SafeHtml} from '@angular/platform-browser';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent {
data: SafeHtml;
  title = 'dynamic-href';
  dynamicText='';
   constructor(private sanitizer: DomSanitizer) {}
  onClick():void{
    //style=''
	this.data = this.sanitizer.bypassSecurityTrustHtml(this.dynamicText);
  }
  goTo(re:string):void{
    document.location='#'+re;
  }
}