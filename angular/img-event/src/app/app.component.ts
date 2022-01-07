import { HostListener,Component } from '@angular/core';

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
  tempo=1.0;
  @HostListener('document:keydown', ['$event'])
  handleKeyDown(event: KeyboardEvent) {
    if (event.key === 'ArrowUp'){
	    if (this.tempo < 4.0){
			this.tempo *= 2.0;
		}
		return;
	} 
	if (event.key === 'ArrowDown'){
		if (this.tempo > .25){
			this.tempo /= 2.0;
		}
		return;
	} 
    
  }
}
