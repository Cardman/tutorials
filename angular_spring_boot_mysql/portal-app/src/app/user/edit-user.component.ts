import { Component,OnInit } from '@angular/core';
import { Router,ActivatedRoute,ParamMap } from '@angular/router';
import { switchMap } from 'rxjs/operators';

import { User } from '../models/user.model';
import { UserService } from '../services/user.service';

@Component({
  templateUrl: './edit-user.component.html'
})
export class EditUserComponent implements OnInit {

  user: User = null;
  id: number = 0;

  constructor(private route: ActivatedRoute,private router: Router, private userService: UserService) {
    this.route.paramMap.subscribe(params => {
		this.id=+params.get('id');
	  });
  }
  ngOnInit() {
   this.userService.getUser(this.id).subscribe( data => {
          this.user = data;
        });
}
  updateUser(): void {
    this.userService.updateUser(this.user)
        .subscribe( data => {
          alert("User edited successfully.");
        });

  };

}
