import { Component } from '@angular/core';
import {SelectionListeService} from './services/selection_liste.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'User App';
  selection_ls : string[] = [];
  constructor(selectionListeService:SelectionListeService){
    
  }
  
  majListe(newItem: string[]) {
    this.selection_ls=newItem;
  }
}
