import { Component, OnInit,HostListener,ElementRef,ViewChild } from '@angular/core';
import {DomSanitizer,SafeUrl} from '@angular/platform-browser';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import {Observable,Subscription} from 'rxjs';
import { HttpResponse, HttpEventType } from '@angular/common/http';
import * as FileSaver from 'file-saver';

export class Coords{
	x:number=0;
	y:number=0;
}

@Component({
  selector: 'image-web',
  templateUrl: './image-web.component.html',
  styleUrls: []
})
export class ImageWebComponent implements OnInit {
readonly httpOptions = {
  headers: new HttpHeaders({ 'Content-Type': 'application/json' })
};

  title = 'front';
  private image : SafeUrl;
  private square : SafeUrl;
  private images : SafeUrl[]=[];
  private fileName='';
  private imageInput='';
  private stringInput='';
  private renderedList='';
  selectedFiles: FileList;
  private readonly imageType : string = 'data:image/PNG;base64,';
  @ViewChild("scene", { static: false, read: ElementRef }) scene;
  typing:number=0;
  th:number;
  private sub2:Subscription;
  private sub3:Subscription;
  en:boolean=false;
  delta:number=0;
  v:Coords=new Coords();
  constructor(private http:HttpClient,private sanitizer:DomSanitizer,private elementRef: ElementRef) {

  }
  ngOnInit():void{
  this.sub3 = this.http.get('/api/square')
			  .subscribe(
			  (data:Exported ) =>
			  {
				this.square = this.sanitizer.bypassSecurityTrustUrl(this.imageType + data.img);
				this.sub3.unsubscribe();
				this.getImage();
			  }
			  );
 
  }
  getImage(){
	this.v.x=0;
	this.v.y=0;
    this.sub2 = this.http.post('/api/image',this.v)
      .subscribe(
      (data:Exported ) =>
      {
        this.image = this.sanitizer.bypassSecurityTrustUrl(this.imageType + data.img);
        this.sub2.unsubscribe();

      }
      );
   }
   onClick():void{
	console.log(this.scene);
	console.log(this.elementRef.nativeElement.querySelector('img'));
     //this.scene.focus();
     this.elementRef.nativeElement.querySelector('img').focus();
	 this.en = !this.en;
   }
   @HostListener('document:keydown',['$event'])
   keyDown(event:KeyboardEvent){
	if (this.typing > 0 || !this.en){
		return;
	}
	  if (event.keyCode === 37){
		this.typing = event.keyCode;
			this.v.x--;
			this.sub2 = this.http.post('/api/image',this.v)
			  .subscribe(
			  (data:Exported ) =>
			  {
				this.image = this.sanitizer.bypassSecurityTrustUrl(this.imageType + data.img);
				this.sub2.unsubscribe();
				this.move();

			  }
			  );
	  
        /*this.th = setInterval(()=>{
			if (this.typing > 0){
				return;
			}
			this.typing = event.keyCode;
			this.v.x--;
			this.sub2 = this.http.post('/api/image',this.v)
			  .subscribe(
			  (data:Exported ) =>
			  {
				this.image = this.sanitizer.bypassSecurityTrustUrl(this.imageType + data.img);
				this.sub2.unsubscribe();

			  }
			  );
		},1000);*/
	  } else if (event.keyCode === 39){
		this.typing = event.keyCode;
			this.v.x++;
			this.sub2 = this.http.post('/api/image',this.v)
			  .subscribe(
			  (data:Exported ) =>
			  {
				this.image = this.sanitizer.bypassSecurityTrustUrl(this.imageType + data.img);
				this.sub2.unsubscribe();
				this.move();

			  }
			  );
		/*this.th = setInterval(()=>{
			if (this.typing > 0){
				return;
			}
			this.typing = event.keyCode;
			this.v.x++;
			this.sub2 = this.http.post('/api/image',this.v)
			  .subscribe(
			  (data:Exported ) =>
			  {
				this.image = this.sanitizer.bypassSecurityTrustUrl(this.imageType + data.img);
				this.sub2.unsubscribe();

			  }
			  );
		},1000);*/
	  } else if (event.keyCode === 38){
		this.typing = event.keyCode;
			this.v.y--;
			this.sub2 = this.http.post('/api/image',this.v)
			  .subscribe(
			  (data:Exported ) =>
			  {
				this.image = this.sanitizer.bypassSecurityTrustUrl(this.imageType + data.img);
				this.sub2.unsubscribe();
				this.move();

			  }
			  );
	  
        /*this.th = setInterval(()=>{
			if (this.typing > 0){
				return;
			}
			this.typing = event.keyCode;
			this.v.x--;
			this.sub2 = this.http.post('/api/image',this.v)
			  .subscribe(
			  (data:Exported ) =>
			  {
				this.image = this.sanitizer.bypassSecurityTrustUrl(this.imageType + data.img);
				this.sub2.unsubscribe();

			  }
			  );
		},1000);*/
	  } else if (event.keyCode === 40){
		this.typing = event.keyCode;
			this.v.y++;
			this.sub2 = this.http.post('/api/image',this.v)
			  .subscribe(
			  (data:Exported ) =>
			  {
				this.image = this.sanitizer.bypassSecurityTrustUrl(this.imageType + data.img);
				this.sub2.unsubscribe();
				this.move();

			  }
			  );
		/*this.th = setInterval(()=>{
			if (this.typing > 0){
				return;
			}
			this.typing = event.keyCode;
			this.v.x++;
			this.sub2 = this.http.post('/api/image',this.v)
			  .subscribe(
			  (data:Exported ) =>
			  {
				this.image = this.sanitizer.bypassSecurityTrustUrl(this.imageType + data.img);
				this.sub2.unsubscribe();

			  }
			  );
		},1000);*/
	  }
	  /*if( event.stopPropagation ) {
		event.stopPropagation();
	}*/

   }
   async move(){
      for (let i = 0; i < 32; i++){
	    await delay(30);
		this.delta = 31-i;
	  }
	  this.typing = 0;
   }
   get left(){
     if (this.typing == 37){
		return this.delta;
	 }
     if (this.typing == 39){
		return -this.delta;
	 }
     return 0;
   }
   get top(){
     if (this.typing == 38){
		return this.delta;
	 }
     if (this.typing == 40){
		return -this.delta;
	 }
     return 0;
   }
   @HostListener('window:keyup',['$event'])
   keyUp(event:KeyboardEvent){
	  /*if (this.typing === 37||this.typing === 39||event.keyCode === 38||event.keyCode === 40){
		//clearInterval(this.th);
		this.typing = 0;
	  }*/
   }
}
export class Exported{
  img:string='';
  bytes:Bytes=new Bytes();
}


export class Bytes {
  array:number[]=[];
}

export function delay(ms: number) {
    return new Promise( resolve => setTimeout(resolve, ms) );
}
