import { Component, OnInit } from '@angular/core';
import { interval, } from 'rxjs';
import { DatePipe } from '@angular/common';

@Component({
  selector: 'clock',
  templateUrl: './clock.component.html',
  styleUrls: ['./clock.component.css'],
  providers: [DatePipe]
})
export class ClockComponent implements OnInit {
  currentTime!: Date;
  formattedDate!: string;

  constructor(private datePipe: DatePipe) { }

  ngOnInit() {
    this.updateTime();
    interval(1000).subscribe(() => {
      this.updateTime();
    });
  }

  updateTime() {
    this.currentTime = new Date();
    const fullDate = this.datePipe.transform(this.currentTime, 'fullDate', 'ro-RO');
    const time = this.datePipe.transform(this.currentTime, 'HH:mm:ss', 'ro-RO');
    if (fullDate) {
      this.formattedDate = this.capitalizeWeekday(fullDate) + `, ${time}`;
    }
  }

  capitalizeWeekday(dateStr: string): string {
    const [weekday, ...rest] = dateStr.split(', ');
    const capitalizedWeekday = weekday.charAt(0).toUpperCase() + weekday.slice(1).toLowerCase();
    return [capitalizedWeekday, ...rest].join(', ');
  }

}
