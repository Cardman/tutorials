import { Component, OnDestroy } from '@angular/core';
import { Subject, Subscription, Observable } from 'rxjs';
import { interval, of } from 'rxjs';
import { throttleTime } from 'rxjs/operators';

// Import the application components and services.
import { FileUploaderComponent } from "./file-uploader.component";
import { FileAddEvent } from "./file-add-event";

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent implements OnDestroy {
  title = 'tasksample';

  monobs = of(0);

  statut = 0;
  st = true;
  
  secondes: number = 0;
  counterSubscription: Subscription;
  list = "friends";
   showList( newList:string ):void {

		this.list = newList;

	}

  onStart():void{

    this.st = false;


  }
  // I handle the fileAdd event on the uploader and determine if the given file
	// can be added to the upload queue. The default behavior is that all files will
	// be allowed unless explicitly prevented.
	public handleFileAdd( event: FileAddEvent ) : void {

		var isPngFile = /\.(png)$/i.test( event.file.name );

		// If the dropped file is a PNG, prevent it from being added to the uploader.
		// Since the uploader isn't controlled by a one-way data flow of files, we do
		// this by preventing the default behavior on the given event object.
		isPngFile && event.preventDefault();

	}
  onStop():void{

    if (this.counterSubscription) {
     this.st = true;
    }
  }
  ngOnDestroy():void{

    if (this.counterSubscription) {
     this.counterSubscription.unsubscribe();
    }
  }
}
