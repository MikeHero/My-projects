import { Component, Input, OnInit } from '@angular/core';
import { Problem } from '../../Models/Problem';

@Component({
  selector: 'problem-card',
  templateUrl: './problem-card.component.html',
  styleUrls: ['./problem-card.component.css']
})
export class ProblemCardComponent implements OnInit {

  currentTime!: Date;
  formattedDate!: string;

  @Input() problem!: Problem;
  @Input() hideIcons!: boolean;

  constructor() {}

  ngOnInit() {
    this.updateTime();
  }

  updateTime() {
    // Assuming 'this.problem.Date' is a valid Date object or string
    this.currentTime = new Date(this.problem.Date);

    // Add 3 hours to the current time
    this.currentTime.setHours(this.currentTime.getHours() + 3);

    // Use JavaScript's toLocaleString to enforce English ('en-US') formatting
    const options: Intl.DateTimeFormatOptions = {
      weekday: 'long', // Full weekday name (e.g., Tuesday)
      year: 'numeric', // Full year
      month: 'long', // Full month name (e.g., September)
      day: 'numeric', // Day of the month
      hour: '2-digit', // 2-digit hour
      minute: '2-digit', // 2-digit minute
      second: '2-digit', // 2-digit second
      hour12: false // 24-hour format
    };

    // Format date to English locale (en-US)
    this.formattedDate = this.currentTime.toLocaleString('en-US', options);
  }
}
