import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FlyoutModule } from 'ngx-flyout';

import { AppRoutingModule } from './app-routing.module';
import {TranslateLoader, TranslateModule} from '@ngx-translate/core';
import {TranslateHttpLoader} from '@ngx-translate/http-loader';
import {HttpClient, HttpClientModule} from '@angular/common/http';
import { SelectionListeModule } from './selection_liste/selection_liste.module';
import { AppComponent } from './app.component';
import { AppUserComponent } from './app-user.component';
import { SizerComponent } from './sizer.component';

@NgModule({
  declarations: [
    AppComponent,
    AppUserComponent,
    SizerComponent
  ],
  imports: [
    BrowserModule,
    FlyoutModule,
    AppRoutingModule,
    SelectionListeModule,
        TranslateModule.forRoot({
            loader: {
                provide: TranslateLoader,
                useFactory: HttpLoaderFactory,
                deps: [HttpClient]
            }
        })
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }

// required for AOT compilation
export function HttpLoaderFactory(http: HttpClient): TranslateHttpLoader {
    return new TranslateHttpLoader(http);
}