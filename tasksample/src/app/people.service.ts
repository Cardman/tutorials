
import { Subject, Subscription, Observable } from 'rxjs';
import {Injectable} from '@angular/core';
import { interval, timer,of} from 'rxjs';

import { catchError,delay,map } from 'rxjs/operators';
import {Person} from './person.model';

@Injectable({providedIn:'root'})
export class PeopleService{
	simulatedNetworkLatency = ( 2 * 1000 );

	// I return the collection of enemies (as a stream).
	getEnemies():Observable<Person[]> {

		// NOTE: This will throw an error "in the future" after the 
		// simulated network activity has completed. 
		return timer( this.simulatedNetworkLatency ).
		pipe(map(x => {throw new Error( "Server Error" );}));


	}


	// I return the collection of friends (as a stream).
	getFriends():Observable<Person[]> {

		var friends = [
			new Person(
				1,
				"Sarah"
			),
			new Person(
				2,
				"Kim"
			),
			new Person(
				3,
				"Joanna"
			)
		];
		return of(friends).pipe(delay(this.simulatedNetworkLatency));

	}
}