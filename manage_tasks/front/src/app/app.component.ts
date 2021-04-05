import { Component,ElementRef } from '@angular/core';
import { HttpResponse, HttpEventType } from '@angular/common/http';
import { UploadFileService } from './Services/upload-file.service';

import { ViewChild } from '@angular/core';

import * as FileSaver from 'file-saver';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'File-Upload-Save';

  progress: { percentage: number } = { percentage: 0 };
  saved = false;
  enViewFile = false;
  
  nbCl = '0';


  constructor(private uploadService: UploadFileService){}


  
  upload() {

    this.uploadService.pushFileToStorage().subscribe(event => {
      if (event.type === HttpEventType.UploadProgress) {
      } else if (event instanceof HttpResponse) {
        this.nbCl = (event as HttpResponse<string>).body;
		this.saved = true;
		this.enViewFile = true;
       //alert('File Successfully Uploaded '+(event as HttpResponse<string>).body);  
      }
    

      }
    );
  }
  reset(){
	
    this.uploadService.clearList(this.nbCl).subscribe(event => {
		if (event instanceof HttpResponse) {
			this.saved = false;
			this.enViewFile = false;
		}
	});
  }

}
