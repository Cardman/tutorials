import { Component,OnInit } from '@angular/core';
import { Router,ActivatedRoute,ParamMap } from '@angular/router';
import { switchMap } from 'rxjs/operators';
import { FormBuilder, FormGroup } from '@angular/forms'

import { User } from '../models/user.model';
import { UserService } from '../services/user.service';

@Component({
  templateUrl: './edit-user-2.component.html'
})
export class EditUser2Component implements OnInit {

  userForm: FormGroup;
  id: number = 0;

  constructor(private route: ActivatedRoute,private router: Router,private formBuilder: FormBuilder, private userService: UserService) {
    this.route.paramMap.subscribe(params => {
		this.id=+params.get('id');
	  });
  }
  ngOnInit(): void {
   this.userForm = this.formBuilder.group({
      email: '',
      firstName: '',
      lastName: ''
    });
   this.userService.getUser(this.id).subscribe( data => {
          this.userForm.setValue({email:data.email,firstName:data.firstName,lastName:data.lastName});
        });
  }
  updateUser(): void {
    var user = new User();
    user.id = ""+this.id;
    user.email = this.userForm.get('email').value;
    user.firstName = this.userForm.get('firstName').value;
    user.lastName = this.userForm.get('lastName').value;
    this.userService.updateUser(user)
        .subscribe( data => {
          alert("User edited successfully.");
        });

  }

}
