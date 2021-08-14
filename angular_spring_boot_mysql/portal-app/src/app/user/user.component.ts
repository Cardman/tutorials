import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { User,UserCriteria } from '../models/user.model';
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
  deleteUser(user: User): void {
    this.userService.deleteUser(user)
      .subscribe( data => {
        this.users = this.users.filter(u => u !== user);
      })
  };

}


