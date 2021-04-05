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
  nbCls: string[] = []
  nbCl = '0';


  constructor(private uploadService: UploadFileService){}


  
  upload() {

    this.uploadService.pushFileToStorage().subscribe(event => {
      if (event.type === HttpEventType.UploadProgress) {
      } else if (event instanceof HttpResponse) {
        this.nbCl = (event as HttpResponse<string>).body;
		this.nbCls.push((event as HttpResponse<string>).body)
		this.saved = true;
		this.enViewFile = true;
       //alert('File Successfully Uploaded '+(event as HttpResponse<string>).body);  
      }
    

      }
    );
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

}
