import { Component } from '@angular/core';
import {SelectionListeService} from './services/selection_liste.service';
import {TranslateService} from '@ngx-translate/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'User App';
  selection_ls : string[] = [];
  constructor(selectionListeService:SelectionListeService,private translate: TranslateService){
    translate.setDefaultLang('en');
  }
  useLanguage(language: string): void {
    this.translate.use(language);
  }
  majListe(newItem: string[]) {
    this.selection_ls=newItem;
  }
}
