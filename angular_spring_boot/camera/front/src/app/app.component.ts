import { Component, OnInit,HostListener } from '@angular/core';
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
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {
readonly httpOptions = {
  headers: new HttpHeaders({ 'Content-Type': 'application/json' })
};

  title = 'front';
  private image : SafeUrl;
  private images : SafeUrl[]=[];
  private fileName='';
  private imageInput='';
  private stringInput='';
  private renderedList='';
  selectedFiles: FileList;
  private readonly imageType : string = 'data:image/PNG;base64,';
  typing:number=0;
  th:number;
  private sub2:Subscription;
  v:Coords=new Coords();
  constructor(private http:HttpClient,private sanitizer:DomSanitizer) {

  }
  ngOnInit():void{
  this.getImage();
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
   @HostListener('window:keydown',['$event'])
   keyDown(event:KeyboardEvent){
	if (this.typing > 0){
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
				(async () => { 
					await delay(100);
				})();
				this.typing = 0;

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
				(async () => { 
					await delay(100);
				})();
				this.typing = 0;

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
				(async () => { 
					await delay(100);
				})();
				this.typing = 0;

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
				(async () => { 
					await delay(100);
				})();
				this.typing = 0;

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
