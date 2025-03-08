import { LatLng } from "leaflet";

export class Problem{
    id!: number;
    Title!: string;
    Description!: string;
    Location!: string;
    Latitude?: number;
    Longitude?: number;
    addressLatLng?: LatLng;
    Priority!: boolean;
    Solved!: boolean;
    Date!: Date;
    ImageURL?: string;
}