import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import {MetricsComponent} from './metrics/metrics.component';

const routes: Routes = [
  { path: 'add', component: MetricsComponent }
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
