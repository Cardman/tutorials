import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'img-event';
  state = -1;
  onClick($event:number){
	this.state = $event;
  }
}
