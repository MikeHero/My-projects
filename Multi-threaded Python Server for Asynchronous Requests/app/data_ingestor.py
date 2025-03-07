import os
import json
import csv
import pandas as pd

class DataIngestor:
    def __init__(self, csv_path: str):
        # # TODO: Read csv from csv_path
        self.csv_path = csv_path
        self.data_frame = None
        
        self.questions_best_is_min = [
            'Percent of adults aged 18 years and older who have an overweight classification',
            'Percent of adults aged 18 years and older who have obesity',
            'Percent of adults who engage in no leisure-time physical activity',
            'Percent of adults who report consuming fruit less than one time daily',
            'Percent of adults who report consuming vegetables less than one time daily'
        ]

        self.questions_best_is_max = [
            'Percent of adults who achieve at least 150 minutes a week of moderate-intensity aerobic physical activity or 75 minutes a week of vigorous-intensity aerobic activity (or an equivalent combination)',
            'Percent of adults who achieve at least 150 minutes a week of moderate-intensity aerobic physical activity or 75 minutes a week of vigorous-intensity aerobic physical activity and engage in muscle-strengthening activities on 2 or more days a week',
            'Percent of adults who achieve at least 300 minutes a week of moderate-intensity aerobic physical activity or 150 minutes a week of vigorous-intensity aerobic activity (or an equivalent combination)',
            'Percent of adults who engage in muscle-strengthening activities on 2 or more days a week',
        ]
        self.read_csv_to_dataframe()
       
    def read_csv_to_dataframe(self):
        try:
            self.data_frame = pd.read_csv(self.csv_path)
            print("CSV file loaded successfully.")
        except FileNotFoundError:
            print(f"File '{self.csv_path}' not found.")
        except Exception as e:
            print("An error occurred:", str(e))
