import { Component,ElementRef,OnDestroy } from '@angular/core';
import { HttpResponse, HttpEventType } from '@angular/common/http';
import { UploadFileService } from './Services/upload-file.service';

import { ViewChild } from '@angular/core';

import * as FileSaver from 'file-saver';
import * as Stomp from 'stompjs';
import * as SockJS from 'sockjs-client';

import { Subject } from 'rxjs';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnDestroy {
  serverUrl = '/socket'
  title = 'File-Upload-Save';
  stompClient;
  subGlobal: Subject<any> = null;

  progress: { percentage: number } = { percentage: 0 };
  saved = false;
  enViewFile = false;
  nbCls: string[] = []
  messages: string[] = []


  constructor(private uploadService: UploadFileService){
   this.initializeWebSocketConnection();
  }

  
  upload() {

    this.uploadService.pushFileToStorage().subscribe(event => {
      if (event.type === HttpEventType.UploadProgress) {
      } else if (event instanceof HttpResponse) {
        this.nbCls.push((event as HttpResponse<string>).body)
		this.saved = true;
		this.enViewFile = true;
      }
    

      }
    );
  }
  
  initializeWebSocketConnection() {
    let ws = new SockJS(this.serverUrl);
    this.stompClient = Stomp.over(ws);
    let that = this;
    this.stompClient.connect({}, function (frame) {
      that.openGlobalSocket();
    });
  }
  openGlobalSocket() {
    this.subGlobal = this.stompClient.subscribe("/socket-publisher", (message) => {
      this.handleResult(message);
    });
  }
  reset(nbCl: string){
	
    this.uploadService.clearList(nbCl).subscribe(event => {
		if (event instanceof HttpResponse) {
			var len = this.nbCls.length;
			for (var i = 0; i < len; i++){
				if (this.nbCls[i] === nbCl){
					this.nbCls.splice(i,1);
					break;
				}
			}
			this.saved = false;
			this.enViewFile = false;
		}
	});
  }
  handleResult(message){
    if (message.body) {
      this.messages.push(message.body);
    }
  }
  ngOnDestroy(){
	if (this.stompClient){
		this.stompClient.disconnect();
	}
    if (this.subGlobal){
		this.subGlobal.unsubscribe();
	}
  }
}
