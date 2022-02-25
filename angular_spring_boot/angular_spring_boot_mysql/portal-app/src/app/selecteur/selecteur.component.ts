import { Component, OnInit } from '@angular/core';

import { User } from '../models/user.model';

@Component({
  selector: 'monselecteur',
  templateUrl: './selecteur.component.html',
  styleUrls: []
})
export class SelecteurComponent implements OnInit {

  users: User[] = [];

  constructor() {

  }

  ngOnInit() {
    var user = new User();
    user.id=`${Math.floor(Math.random()*256)}`
    user.firstName = 'Premier';
    user.lastName = 'Dernier';
    user.email = 'Mail';
    this.users.push(user);
  };


}


