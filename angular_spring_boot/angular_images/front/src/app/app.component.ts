import { Component } from '@angular/core';
import {DomSanitizer,SafeUrl} from '@angular/platform-browser';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import {Observable} from 'rxjs';
import { HttpResponse, HttpEventType } from '@angular/common/http';
import * as FileSaver from 'file-saver';


@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
readonly httpOptions = {
  headers: new HttpHeaders({ 'Content-Type': 'application/json' })
};

  title = 'front';
  private expo : Exported = new Exported();
  private image : SafeUrl;
  private fileName='';
  private imageInput='';
  private readonly imageType : string = 'data:image/PNG;base64,';
  constructor(private http:HttpClient,private sanitizer:DomSanitizer) {

  }
  getImage(){
    this.http.post('/api/image',this.imageInput)
      .subscribe(
      (data:Exported ) =>
      {
        this.expo = data;
        this.image = this.sanitizer.bypassSecurityTrustUrl(this.imageType + data.img);
        let e:ExpFile = new ExpFile();
        e.fileName = this.fileName;
        e.bytes = data.bytes;
        this.http.post('/api/bytes',e, { headers:this.httpOptions.headers, responseType: 'blob'}).subscribe((event:Blob) => {
            FileSaver.saveAs(event, this.fileName);
               });

      }
      );
   }
}

export class Exported{
  img:string='';
  bytes:number[]=[];
}

export class ExpFile {
  fileName='';
  bytes:number[]=[];
}
