import { Component } from '@angular/core';
import {DomSanitizer} from '@angular/platform-browser';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import {Observable} from 'rxjs';
@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'front';
  private expo : Exported = new Exported();
  private image : any;
  private imageInput='';
  private readonly imageType : string = 'data:image/PNG;base64,';
  constructor(private http:HttpClient,private sanitizer:DomSanitizer) {}
  getImage(){
    this.http.post('/api/image',this.imageInput)
      .subscribe((data:Exported ) => {
      this.expo = data;
    this.image = this.sanitizer.bypassSecurityTrustUrl(this.imageType + data.img);
  })}
}

export class Exported{
  img:string='';
}
