from queue import Queue
from threading import Thread, Event
import time
import os
import json

class ThreadPool:
    def __init__(self, data_ingestor):
        # You must implement a ThreadPool of TaskRunners
        # Your ThreadPool should check if an environment variable TP_NUM_OF_THREADS is defined
        # If the env var is defined, that is the number of threads to be used by the thread pool
        # Otherwise, you are to use what the hardware concurrency allows
        # You are free to write your implementation as you see fit, but
        # You must NOT:
        #   * create more threads than the hardware concurrency allows
        #   * recreate threads for each task
        
        CPU_CORES = 4
        # verificam daca exista variabila de mediu TP_NUM_OF_THREADS
        num_threads = os.environ.get('TP_NUM_OF_THREADS') or CPU_CORES
        
        self.data_ingestor = data_ingestor
        self.tasks_queue = Queue()  
        self.worker_threads = [TaskRunner(self.tasks_queue, self, data_ingestor) for i in range(num_threads)]
        self.start()
        self.jobs = {}

    def start(self):
        for thread in self.worker_threads:
            thread.start()

    def submit_task(self, task):
        self.tasks_queue.put(task)
        task_id = task['id']
        self.jobs[task_id] = {"status":"running"}


class TaskRunner(Thread):
    def __init__(self, tasks_queue, thread_pool, data_ingestor):
        # TODO: init necessary data structures
        super().__init__()
        self.tasks_queue = tasks_queue
        self.results_dir = 'results'
        self.thread_pool = thread_pool
        self.data_ingestor = data_ingestor

    def run(self):
        # TODO
        while True:
            # Get pending job
            task = self.tasks_queue.get()
            # Execute the job and save the result to disk
            result = self.execute_task(task)
            task_id = task["id"]
            self.thread_pool.jobs[task_id] = {"status":"done", "result":result}
            # self.save_result(task, result)
   
    def save_result(self, task, result):
        # Generate a filename based on the task identifier or any other relevant information
        filename = f"{task['id']}.json"
        # Construct the full path to save the result
        filepath = os.path.join(self.results_dir, filename)
        # Save the result as JSON to the specified filepath
        with open(filepath, 'w') as file:
            json.dump(result, file)


    def execute_task(self, task):
        survey = task['type'] 
        if survey == "global_mean":
            question = task['question']
          
            filtered_data = self.data_ingestor.data_frame[(question == self.data_ingestor.data_frame["Question"])]
                                                            
          
            average_data_value = filtered_data['Data_Value'].mean()
            return {"global_mean":average_data_value}

        elif survey == "best5":
            question = task['question']
            
            
            filtered_data = self.data_ingestor.data_frame[(question == self.data_ingestor.data_frame["Question"])]
            
       
            state_mean_data = filtered_data.groupby('LocationDesc')['Data_Value'].mean().sort_values()
            
            if question in self.data_ingestor.questions_best_is_min:
                return state_mean_data.nsmallest(5).to_dict()
            else:
                return state_mean_data.nlargest(5).to_dict()
        
        elif survey == "worst5":
            question = task['question']
         
            filtered_data = self.data_ingestor.data_frame[(question == self.data_ingestor.data_frame["Question"])]
            
            
            state_mean_data = filtered_data.groupby('LocationDesc')['Data_Value'].mean().sort_values()
            
            if not question in self.data_ingestor.questions_best_is_min:
                return state_mean_data.nsmallest(5).to_dict()
            else:
                return state_mean_data.nlargest(5).to_dict()

        elif survey == "state_mean":
            question = task['question']
            state = task['state']
          
            filtered_data = self.data_ingestor.data_frame[(question == self.data_ingestor.data_frame["Question"]) & 
                                                        (state == self.data_ingestor.data_frame["LocationDesc"])]
            state_mean_value = filtered_data['Data_Value'].mean()
            return {state:state_mean_value}
        
        elif survey == "states_mean":
            question = task['question']
            filtered_data = self.data_ingestor.data_frame[(question == self.data_ingestor.data_frame["Question"])]
            state_mean_data = filtered_data.groupby('LocationDesc')['Data_Value'].mean().sort_values()

            return state_mean_data.to_dict();
        
        return None