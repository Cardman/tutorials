import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { environment } from '../../environments/environment';
//import { ErrorObservable } from 'rxjs/observable/ErrorObservable';
//import 'rxjs/add/operator/map';
//}import { map } from 'rxjs/operators';
//import 'rxjs/add/operator/catch';
//import 'rxjs/add/operator/throwError';
import { Message } from '../model/message';
import { Observable } from 'rxjs';

@Injectable()
export class SocketService {
  //url: string = "/api/socket";
  url: string = "http://localhost:8080/api/socket/send/general3";

  constructor(private http: HttpClient) { }

  post(data: Message) {
    //return this.http.post<Message>(this.url, data)
    return this.http.get<string>(this.url)
      //}.map((data: Message) => { return data; })
      //}.catch(error => {
      //}  return throwError(error);
      //})
      ;
  }
}
