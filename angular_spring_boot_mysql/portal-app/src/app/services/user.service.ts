import {Injectable} from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';

import { User,UserCriteria } from '../models/user.model';

import {Observable} from 'rxjs';


const httpOptions = {
  headers: new HttpHeaders({ 'Content-Type': 'application/json' })
};

@Injectable()
export class UserService {

  constructor(private http:HttpClient) {}

  private userUrl = '/api';

  public getUsers():Observable<User[]> {
    return this.http.get<User[]>(this.userUrl);
  }

  public getUsersBy(criteria:UserCriteria):Observable<User[]> {
    return this.http.post<User[]>(this.userUrl+"/filter", criteria);
  }

  public deleteUser(user:User):Observable<Object> {
    return this.http.delete(this.userUrl + "/"+ user.id);
  }
  public getUser(id:number):Observable<User> {
    return this.http.get<User>(this.userUrl+ "/"+ id);
  }
  public updateUser(user:User):Observable<User> {
    user.last = new Date();
    return this.http.put<User>(this.userUrl, user);
  }
  public createUser(user:User):Observable<User> {
    return this.http.post<User>(this.userUrl, user);
  }

}
