import { Component, OnInit, EventEmitter, Output } from '@angular/core';

@Component({
  selector: 'selection_liste_env',
  templateUrl: './selection_liste_env.component.html',
  styleUrls: []
})
export class SelectionListeEnvComponent {
  digits : number = 100; 
  @Output() selection_ls : string[] = [];
  @Output() selection_ls2 : string[] = [];
  @Output() closeFyout = new EventEmitter<boolean>();
  majListe(newItem: string[]) {
    this.selection_ls=newItem;
  }
  majListe2(newItem: string[]) {
    this.selection_ls2=newItem;
  }
  onCloseFlyout():void {
    this.closeFyout.emit(false);
  }
}