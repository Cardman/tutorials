import { Component, HostListener } from '@angular/core';
import { saveAs } from 'file-saver';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  urlAfter = '';
  readOnly = false;
  click(){
   alert(this.urlAfter);
  }
  @HostListener('window:unload',['$event'])
  unloadHandler(event){
   var blob = new Blob([''], {type: "text/plain;charset=utf-8"});
   saveAs(blob,'test.txt');
  }
  @HostListener('window:beforeunload',['$event'])
  beforeUnloadHandler(event){
   event.preventDefault();
   event.returnValue = this.urlAfter;
   this.readOnly = true;
   //window.close();
   //var blob = new Blob([JSON.stringify(window.closed)], {type: "text/plain;charset=utf-8"});
   var blob = new Blob([JSON.stringify(confirm("Do you want to leave this window?"))], {type: "text/plain;charset=utf-8"});
   saveAs(blob,'test2.txt');
   return this.urlAfter;
  }
}