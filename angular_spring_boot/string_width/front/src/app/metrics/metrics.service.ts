import {Injectable} from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';

import { Metrics } from '../models/metrics.model';

import {Observable} from 'rxjs';


const httpOptions = {
  headers: new HttpHeaders({ 'Content-Type': 'application/json' })
};

@Injectable()
export class MetricsService {

  constructor(private http:HttpClient) {}

  private metricsUrl = '/api';

  public getFontsNames():Observable<any> {
    return this.http.get<any>(this.metricsUrl);
  }

  public stringWidth(metrics:Metrics):Observable<any> {
    return this.http.post<Metrics>(this.metricsUrl, metrics);
  }
  public stringDim(metrics:Metrics):Observable<any> {
    return this.http.post<Metrics>(this.metricsUrl+"/dim", metrics);
  }

}
