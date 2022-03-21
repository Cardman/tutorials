import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { User,UserCriteria,UserCriteria3 } from '../models/user.model';
import { UserService } from '../services/user.service';
import * as moment from 'moment';

@Component({
  selector: 'app-user',
  templateUrl: './user.component.html',
  styles: []
})
export class UserComponent implements OnInit {

  users: User[];
  firstName : string = '';
  lastName : string = '';
  email : string = '';
  last : Date = null;
  range : string = '';

  constructor(private router: Router, private userService: UserService) {

  }

  ngOnInit() {
    this.userService.getUsers()
      .subscribe( data => {
        this.users = data;
      });
  };
  parseDate(dateString: string): Date {
    if (dateString) {
        //return moment(dateString,'yyyy-MM-dd HH:mm:ss').toDate();
        /*let d = new Date(dateString);
        return new Date(d.getTime() + d.getTimezoneOffset() * 60000);*/
        return new Date(dateString);
    }
    return null;
}
  getUsersBy(): void {
    let criteria:UserCriteria = new UserCriteria();
    criteria.firstName = this.firstName;
    criteria.lastName = this.lastName;
    criteria.email = this.email;
    criteria.last = this.last;
    this.userService.getUsersBy(criteria)
      .subscribe( data => {
        this.users = data;
      });
  };
  
  getUsersBy2():void {
    let criteria:UserCriteria3 = new UserCriteria3();
    if (this.range.trim() === ","){
        criteria.onlyNullFlag = true;
    } else {
        let parts = this.range.trim().split(",");
        if (parts.length === 2){
         criteria.begin = this.parseDate2(parts[0]);
         criteria.end = this.parseDate2(parts[1]);
        }
        
    }
    console.log(JSON.stringify(criteria));
    this.userService.getUsersBy2(criteria)
      .subscribe( data => {
        this.users = data;
      });
  }
  parseDate2(part:string):Date{
    if (part.trim().length === 0){
       return null;
    }
    try {
     let parts = part.trim().split("/").map(p => p.trim());
     let res = new Date(Date.UTC(parseInt(parts[0]),parseInt(parts[1])-1,parseInt(parts[2])));
     if (isNaN(res.getTime())){
         return null;
     }
     return res;
    }catch(e){
     return null;
    }
  }
  deleteUser(user: User): void {
    this.userService.deleteUser(user)
      .subscribe( data => {
        this.users = this.users.filter(u => u !== user);
      })
  };

}


