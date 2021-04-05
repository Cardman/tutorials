import { Component, OnInit, OnDestroy } from '@angular/core';
import { PeopleService } from "./people.service";
import { Subject, Subscription, Observable } from 'rxjs';
import {Person} from './person.model';

@Component({
	selector: "enemy-list",
	template:
	`
		<h2>
			Enemies
		</h2>
		<p *ngIf="! enemies">
			<em>Loading...</em>
		</p>
		<div *ngIf="enemies">
			<p>
				Oh chickens, you have {{ enemies.length }} enemies!
			</p>
			<ul>
				<li *ngFor="let enemy of enemies">
					{{ enemy.name }}
				</li>
			</ul>
		</div>
	`
})
export class EnemyListComponent implements OnInit,OnDestroy{
	peopleSubscription:Subscription;
	enemies:Person[];
	constructor(private peopleService:PeopleService){}
	ngOnInit():void{
		this.peopleSubscription = this.peopleService.getEnemies()
		.subscribe(
			enemies => {
		  this.enemies = enemies;
		  },
			(error) => {

				console.error( "Error in getEnemies():", error );
				alert( "Oops: We couldn't load enemy data." );

			},
			()=> {

				console.debug( "Completed getEnemies()." );

			}
		);
	}
	ngOnDestroy():void {

		console.warn( "Destroying friend-list" );
		console.info( "Canceling any hot Rx subscriptions." );

		// If the component had a chance to initiate the request for 
		// friend data, we need "cancel" the sequence. What we don't want
		// is something like the Error handler to show an Alert() modal
		// after the component has been destroyed (at least not in our 
		// particular use-case). When we unsubscribe, it will prevent 
		// the Value, Error, and Complete handlers from being invoked.
		// Even if the sequence had already completed, this will be safe
		// to call.
		if (this. peopleSubscription ) {

			this.peopleSubscription.unsubscribe();
			
		}

	}
}