import { Component } from '@angular/core';
import { PrimeCalculator } from './app.prime';
import {TranslateService} from '@ngx-translate/core';

@Component({
  selector: 'app-root',
  template: `
<app-sizer [(size)]="fontSizePx"></app-sizer>
<div [style.font-size.px]="fontSizePx">Resizable Text</div>
<app-user [user]="user">
</app-user>
<div>
   <a href="#" (click)="find10thPrimeNumber()">Click here</a> to find 10th prime number
   <div>The 10<sup>th</sup> prime number is {{ prime10 }}</div> <br/>
   <a href="#" (click)="find10000thPrimeNumber()">Click here</a> to find 10000th prime number
   <div>The 10000<sup>th</sup> prime number is {{ prime10000 }}</div>
</div>
`,
  styleUrls: ['./app.component.scss']
})
export class AppComponent {
  title = 'formsample';
  fontSizePx = 16;
  user={name:'sample',age:30}
  prime10 : number = 0;
  prime10000 : number = 0;
  constructor(private translate: TranslateService) {
        translate.setDefaultLang('en');
    }
  find10thPrimeNumber() {
      this.prime10 = PrimeCalculator.findNthPrimeNumber(10);
   }

   find10000thPrimeNumber() {
      if (typeof Worker !== 'undefined') {
         // Create a new
         const worker = new Worker('./app.worker', { type: 'module' });
         worker.onmessage = ({ data }) => {
         this.prime10000 = data;
         };
         worker.postMessage(10000);
      } else {
         // Web Workers are not supported in this environment.
         // You should add a fallback so that your program still executes correctly.
      }
   }
}
