import { Component, OnInit,HostListener } from '@angular/core';
import {DomSanitizer,SafeUrl} from '@angular/platform-browser';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import {Observable,Subscription} from 'rxjs';
import { HttpResponse, HttpEventType } from '@angular/common/http';
import * as FileSaver from 'file-saver';


@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {

  title = 'front';
  /*@HostListener('window:keydown',['$event'])
   keyDown(event:KeyboardEvent){
      if (event.preventDefault) {
	    event.preventDefault();
      }
   }*/
}

