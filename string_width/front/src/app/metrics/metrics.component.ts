import { Component,OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { Metrics } from '../models/metrics.model';
import { MetricsService } from './metrics.service';

@Component({
  templateUrl: './metrics.component.html',
  selector: 'metrics'
})
export class MetricsComponent implements OnInit {

  metrics: Metrics = new Metrics();
  result: number = 0;
  fontNames: string[] = [];

  constructor(private router: Router, private metricsService: MetricsService) {

  }

  ngOnInit() {
    this.metricsService.getFontsNames()
        .subscribe( data => {
		this.fontNames=data as string[];
        });
  }
  stringWidth(): void {
    this.metricsService.stringWidth(this.metrics)
        .subscribe( data => {
		this.result=data as number;
        });

  };

}
