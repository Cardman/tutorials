import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { UserComponent } from './user/user.component';
import {AddUserComponent} from './user/add-user.component';
import {EditUserComponent} from './user/edit-user.component';
import { User2Component } from './user2/user-2.component';
import {AddUser2Component} from './user2/add-user-2.component';
import {EditUser2Component} from './user2/edit-user-2.component';
import {SelectionListeComponent} from './selection_liste/selection_liste.component';

const routes: Routes = [
  { path: 'users', component: UserComponent },
  { path: 'add', component: AddUserComponent },
  { path: 'edit/:id', component: EditUserComponent },
  { path: 'users2', component: User2Component },
  { path: 'users2/add', component: AddUser2Component },
  { path: 'users2/:id', component: EditUser2Component },
  { path: 'selection_liste', component: SelectionListeComponent }

];

@NgModule({
  imports: [
    RouterModule.forRoot(routes)
  ],
  exports: [
    RouterModule
  ],
  declarations: []
})
export class AppRoutingModule { }
