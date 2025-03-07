import { Component } from '@angular/core';
import { Tag } from '../../../shared/models/Tag';
import { FoodService } from '../../../services/food.service';

@Component({
  selector: 'app-targs',
  templateUrl: './targs.component.html',
  styleUrl: './targs.component.css'
})
export class TargsComponent {
  tags?: Tag[];

  constructor(foodService: FoodService) {
    foodService.getAllTags().subscribe(serverTags => {
      this.tags = serverTags;
    });
  }
}
