import { Component, ElementRef, EventEmitter, Input, OnChanges, Output, ViewChild } from '@angular/core';
import {LatLng, LatLngExpression, LatLngTuple, LeafletMouseEvent, Map, Marker, icon, latLng, map, marker, tileLayer} from 'leaflet';
import { LocationService } from '../../Services/HTTP/location.service';
import { Problem } from '../../Models/Problem';

@Component({
  selector: 'map',
  templateUrl: './map.component.html',
  styleUrl: './map.component.css'
})
export class MapComponent {
                              //implements OnChanges

  private readonly MARKER_ZOOM_LEVEL = 16;
  private readonly MARKER_ICON = icon({
    iconUrl:
      'https://res.cloudinary.com/foodmine/image/upload/v1638842791/map/marker_kbua9q.png',
    iconSize: [42, 42],
    iconAnchor: [21, 42],
  });
  private readonly DEFAULT_LATLNG: LatLngTuple= [13.75, 21.62];

  
  // @Input()
  // readonly = false;

  @Input()
  latitude:number = 0;
  @Input()
  longitude:number = 0;

  @ViewChild('map', {static: true})
  mapRef!: ElementRef;

  map!: Map;
  constructor(private locationService: LocationService) { }
  
  currentMarker!:Marker;

  @Output() coordinatesChanged = new EventEmitter<{ latitude: number; longitude: number }>();


  // ngOnChanges(): void {
  //   if( !this.problem) 
  //     return ;

  //   this.initializeMap();

  //   if( this.readonly && this.addressLatLng) {
  //     this.showLocationOnReadOnlyMode();
  //   }
  // }

  // showLocationOnReadOnlyMode() {
  //   const m = this.map;
  //   this.setMarker(this.addressLatLng);
  //   m.setView(this.addressLatLng, this.MARKER_ZOOM_LEVEL);  

  //   m.dragging.disable();
  //   m.touchZoom.disable();
  //   m.doubleClickZoom.disable();
  //   m.scrollWheelZoom.disable();
  //   m.boxZoom.disable();
  //   m.keyboard.disable();
  //   m.off('click');
  //   m.tap?.disable();
  //   this.currentMarker.dragging?.disable();
  // }

  initializeMap(){
    if( this.map) 
      return ;

    this.map = map(this.mapRef.nativeElement, {
      attributionControl: false
    }).setView(this.DEFAULT_LATLNG, 1);

    
    tileLayer('https://{s}.tile.osm.org/{z}/{x}/{y}.png').addTo(this.map);
    
    this.map.on('click', (e:LeafletMouseEvent) => {
      this.setMarker(e.latlng);
    })
  }

  ngOnInit(): void{
    this.initializeMap();
  }

  findMyLocation() {
    this.locationService.getCurrentLocation().subscribe({
      next:(latlng) => {
          this.map.setView(latlng, this.MARKER_ZOOM_LEVEL)
          this.setMarker(latlng);
          console.log(latlng);
        }
      })
    
  }

  setMarker(latlng: LatLngExpression) 
  { 
    this.addressLatLng= latlng as LatLng;
    if(this.currentMarker)
    {
      this.currentMarker.setLatLng(latlng);
      return;
    }

    this.currentMarker = marker(latlng, 
    {
      draggable: true,
      icon: this.MARKER_ICON
    }).addTo(this.map);


    this.currentMarker.on('dragend', ()=> {
      this.addressLatLng = this.currentMarker.getLatLng();
    })
  }


  set addressLatLng(latlng: LatLng) {

    if( !latlng.lat.toFixed) 
      return ;

    latlng.lat = parseFloat(latlng.lat.toFixed(8));
    latlng.lng = parseFloat(latlng.lng.toFixed(8));
    this.latitude = latlng.lat;
    this.longitude = latlng.lng;
    this.coordinatesChanged.emit({ latitude: this.latitude, longitude: this.longitude });

    console.log("latitude: ",this.latitude, "longitute:", this.longitude );
  }

  // get addressLatLng(){
  //   return this.problem.addressLatLng!;
  // }

}

