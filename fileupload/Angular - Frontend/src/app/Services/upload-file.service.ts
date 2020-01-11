import { Injectable } from '@angular/core';
import { HttpClient, HttpEvent, HttpRequest } from '@angular/common/http';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class UploadFileService {

  constructor(private https: HttpClient) { }

  pushFileToStorage(file: File,file2: File): Observable<HttpEvent<{}>> {
    const data: FormData = new FormData();

    data.append('file', file);
    data.append('file2', file2);
    data.append('s2', ' bonjour');

    const newRequest = new HttpRequest('POST', 'http://localhost:8080/savefile', data, {
      reportProgress: true,
      responseType: 'text'
    });

    return this.https.request(newRequest);
  }
  
  
  download(nbCl:string): Observable<HttpEvent<{}>> {
     const data: FormData = new FormData();

    data.append('s2', nbCl);

    const newRequest = new HttpRequest('POST', 'http://localhost:8080/downloadlist', data, {
      reportProgress: true,
      responseType: 'blob'
    });

    return this.https.request(newRequest);

  }
  
  
  
  clearList(nbCl:string): Observable<HttpEvent<{}>> {
     const data: FormData = new FormData();

    data.append('s2', nbCl);

    const newRequest = new HttpRequest('POST', 'http://localhost:8080/clearList', data, {
      reportProgress: true,
      responseType: 'text'
    });

    return this.https.request(newRequest);

  }
}
