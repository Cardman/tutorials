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
  url: string = "/api/socket";

  constructor(private http: HttpClient) { }

  post(data: Message) {
    return this.http.post<Message>(this.url, data)
      //}.map((data: Message) => { return data; })
      //}.catch(error => {
      //}  return throwError(error);
      //})
      ;
  }
}
