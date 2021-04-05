import { Injectable } from '@angular/core';
import { HttpClient, HttpEvent, HttpRequest } from '@angular/common/http';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class UploadFileService {

  constructor(private https: HttpClient) { }

  pushFileToStorage(): Observable<HttpEvent<{}>> {
    const data: FormData = new FormData();


    const newRequest = new HttpRequest('POST', '/savefile', data, {
      reportProgress: true,
      responseType: 'text'
    });

    return this.https.request(newRequest);
  }
  
  
  
  clearList(nbCl:string): Observable<HttpEvent<{}>> {
     const data: FormData = new FormData();

    data.append('s2', nbCl);

    const newRequest = new HttpRequest('POST', '/clearList', data, {
      reportProgress: true,
      responseType: 'text'
    });

    return this.https.request(newRequest);

  }
}
