Multi-threaded Python Server for Asynchronous Requests
	
	This software was coded in Python. It is an implementation of a server which runs on a thread pool
system to facilitate the requests of multiple users at the same time, based on preprocessing the "csv" 
format data with the help of the Pandas library.


-----------------------------------------------------------------------------------------------------------

	Salut! M-am folosit de pandas ca sa citesc continutul fisierului csv. La initializare se verifica 
daca exista directorul results, daca nu va fi creat. Pe forum s-a specificat ca checkerul va avea 
variabila de mediu, daca nu vom folosi puterea de paralelizare a masinii gazda. Ma folosesc de Queue care
are calitatea de a fi ThreadSafe. Threadurile mele partajeaza o coada comuna de taskuri pe care le rezolva. 
	Cand un task este introdus in coada, el devine ca status running, cand este finalizat se adauga 
intr-o coada speciala, de taskuri finalizate.
	Executia unui task poate fi asemanata cu un switch, in functie de tipul taskului, implementat prin 
if-else-uri. Pe langa task, cand il adaug in coada, se va retine si tipul acestui task, daca este best5, 
daca este get_mean etc, alaturi de ID-ul acestuia. ID-urile se incrementeaza la fiecare task nou aduagat. 
Cand execut un task, verific tipul acestui task si fiecare tip are o logica diferita, un fel specific de 
a filtra si a folosi datele furnizate de fisierul csv. 
	Ca template pentru structura unui ThreadPool, am citit comentariile de pe forum prin care se preciza
asemanator ca un pseudocod cam ce implementare ar trebui sa aiba, "dupa cum s-a discutat si la APD" :).

Metode de testare manuala:
- dupa ce am implementat best5 am folosit curl in terminal

curl -X POST   http://localhost:5000/api/best5   -H 'Content-Type: application/json'   -d '{
    "question": "Percent of adults aged 18 years and older who have an overweight classification"

curl -X GET   http://localhost:5000/api/get_results/1
{"data":{"Arkansas":32.99516129032258,"District of Columbia":30.746875,"Kentucky":33.071641791044776,"Missouri":32.76268656716418,"Vermont":33.118181818181824},"status":"done"}

