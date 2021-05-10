import { Component, Input } from '@angular/core';

@Component(
{selector:'app-user',
templateUrl:'./app-user.component.html'
})
export class AppUserComponent{
@Input()user;
  selection_ls : string[] = [];
  selection_ls2 : string[] = [];
  private openFlyout: boolean = false;
 
  private toggleSidebar() {
    this.openFlyout = !this.openFlyout;
  }
  majListe(newItem: string[]) {
    this.selection_ls=newItem;
  }
  majListe2(newItem: string[]) {
    this.selection_ls2=newItem;
  }
  fermer(status: boolean) {
    this.openFlyout = false;
  }
}
if (typeof Worker !== 'undefined') {
  // Create a new
  const worker = new Worker('./app.worker', { type: 'module' });
  worker.onmessage = ({ data }) => {
    console.log(`page got message: ${data}`);
  };
  worker.postMessage('hello');
} else {
  // Web Workers are not supported in this environment.
  // You should add a fallback so that your program still executes correctly.
}