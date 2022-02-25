import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';

import {Observable} from 'rxjs';
@Injectable({
  providedIn: 'root'
})
export class OpersService {

  private userUrl = '/api';

  constructor(private http:HttpClient) {}

  public sum(a:number,b:number):Observable<number> {
    return this.http.get<number>(this.userUrl+"/0/"+a+"/"+b);
  }

  public prod(a:number,b:number):Observable<number> {
    return this.http.get<number>(this.userUrl+"/1/"+a+"/"+b);
  }
}
