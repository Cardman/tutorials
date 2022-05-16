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
  private images : SafeUrl[]=[];
  private fileName='';
  private imageInput='';
  private stringInput='';
  private renderedList='';
  selectedFiles: FileList;
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
            const a = document.createElement('a')
            const objectUrl = URL.createObjectURL(event)
            a.href = objectUrl
            a.download = this.fileName;
            a.click();
            URL.revokeObjectURL(objectUrl);
               });

      }
      );
   }
   selectFiles(event:any) {
     this.selectedFiles = event.target.files;
     console.log(event.target.files);
   }
   useFiles(){

      const len = this.selectedFiles.length;
      this.images = [];
      for (let i = 0; i < len; i++) {
         const data: FormData = new FormData();
         let sel: File = this.selectedFiles[i];
             data.append('file', sel);
         this.http.post('/api/files',data)
                      .subscribe(
                      (data:ExportedDecode[] ) =>
                      {
                        data.forEach(e => {
                          this.images.push(this.sanitizer.bypassSecurityTrustUrl(this.imageType + e.exported.img));
                          let ex:ExpFile = new ExpFile();
                          ex.fileName = sel.name.replace('.png','.txt');
                          ex.bytes = e.decode;
                          this.http.post('/api/bytes',ex, { headers:this.httpOptions.headers, responseType: 'blob'}).subscribe((event:Blob) => {
                                      const a = document.createElement('a')
                                      const objectUrl = URL.createObjectURL(event)
                                      a.href = objectUrl
                                      a.download = sel.name.replace('.png','.txt');
                                      a.click();
                                      URL.revokeObjectURL(objectUrl);
                                         });
                        });
                      }
                      )
      }
   }
   strInput(){
     let db = new DoubledList();
     db.str.push(this.stringInput);
     this.http.post('/api/doubledlist',db)
           .subscribe(
           (data:DoubledList ) =>{
             this.renderedList = data.str[0]+data.str[1];
           }
           );
   }
}
export class ExportedDecode{
  decode:Bytes=new Bytes();
  exported:Exported=new Exported();
}
export class Exported{
  img:string='';
  bytes:Bytes=new Bytes();
}

export class ExpFile {
  fileName='';
  bytes:Bytes=new Bytes();
}

export class Bytes {
  array:number[]=[];
}

export class DoubledList {
  str:string[]=[];
}
