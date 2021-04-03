import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { User } from '../models/user.model';
import { UserService } from '../services/user.service';
import { FormBuilder, FormGroup } from '@angular/forms'

@Component({
  templateUrl: './add-user-2.component.html'
})
export class AddUser2Component implements OnInit {

  userForm: FormGroup;

  constructor(private router: Router, private formBuilder: FormBuilder, private userService: UserService) {

  }
  ngOnInit(): void {
   this.userForm = this.formBuilder.group({
      email: '',
      firstName: '',
      lastName: ''
    });
  }
  createUser(): void {
    var user = new User();
    user.email = this.userForm.get('email').value;
    user.firstName = this.userForm.get('firstName').value;
    user.lastName = this.userForm.get('lastName').value;
    this.userService.createUser(user)
        .subscribe( data => {
          alert("User created successfully.");
        });

  }

}
