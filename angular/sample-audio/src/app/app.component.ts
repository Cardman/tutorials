import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'sample-audio';
  playAudio(path:string){
    let audio = new Audio();
	audio.src = "../assets/audio/"+path;
	audio.load();
	audio.play();
  }
}
