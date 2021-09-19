import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import {OpersComponent} from './opers/opers.component';

const routes: Routes = [
  { path: 'opers', component: OpersComponent }

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
