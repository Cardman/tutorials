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

  selectedFiles: FileList;
  selectedFiles2: FileList;
  currentFileUpload: File;
  currentFileUpload2: File;
  progress: { percentage: number } = { percentage: 0 };
  selectedFile : File= null;
  selectedFile2 : File= null;
  changeImage = false;
  changeImage2 = false;
  saved = false;
  enFirst = true;
  enSecond = true;
  enViewFile = false;
  
  nbCl = '0';

  @ViewChild('myInput1', {static: false})
myInputVariable1: ElementRef;

@ViewChild('myInput2', {static: false})
myInputVariable2: ElementRef;

  constructor(private uploadService: UploadFileService){}

  downloadFile(){

    this.uploadService.download(this.nbCl).subscribe(event => {
		if (event instanceof HttpResponse) {
			const blob = (event as HttpResponse<Blob>).body;
  FileSaver.saveAs(blob, 'files.txt');
			this.enViewFile = false;
		}
	});
  }

  change($event:Event) {
    this.changeImage = true;
  }

  changedImage(event:Event) {
    this.selectedFile = event.target.files[0];
  }

  change2($event:Event) {
    this.changeImage2 = true;
  }

  changedImage2(event:Event) {
    this.selectedFile2 = event.target.files[0];
  }
  
  upload() {
    this.progress.percentage = 0;

    this.currentFileUpload = this.selectedFiles.item(0);
    this.currentFileUpload2 = this.selectedFiles2.item(0);
    this.uploadService.pushFileToStorage(this.currentFileUpload,this.currentFileUpload2).subscribe(event => {
      if (event.type === HttpEventType.UploadProgress) {
        this.progress.percentage = Math.round(100 * event.loaded / event.total);
      } else if (event instanceof HttpResponse) {
        this.nbCl = (event as HttpResponse<string>).body;
		this.saved = true;
		this.enFirst = false;
		this.enSecond = false;
		this.enViewFile = true;
       //alert('File Successfully Uploaded '+(event as HttpResponse<string>).body);  
    this.currentFileUpload = null;
    this.currentFileUpload2 = null;
	this.myInputVariable1.nativeElement.value = "";
	this.myInputVariable2.nativeElement.value = "";
      }
    

    this.selectedFiles = undefined;
    this.selectedFiles2 = undefined;
      }
    );
  }
  reset(){
	
    this.uploadService.clearList(this.nbCl).subscribe(event => {
		if (event instanceof HttpResponse) {
			this.saved = false;
			this.enFirst = true;
			this.enSecond = true;
			this.enViewFile = false;
		}
	});
  }

  selectFile(event:Event) {
    this.selectedFiles = event.target.files;
  }

  selectFile2(event:Event) {
    this.selectedFiles2 = event.target.files;
  }
}
