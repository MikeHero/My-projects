    In rezolvarea acestei teme m-am folosit de laboratorul de inmultire a matricelor:
https://ocw.cs.pub.ro/courses/asc/laboratoare/09.

    (A_t x B + B x A) x B_t

    Am spart operatia de mai sus pe bucati si am comentat la fiecare bucata de cod care fragment 
din operatie mare a fost executat. De exemplu mai intai se face (A_t x B), apoi (B x A), apoi am
insumat cele doua, iar la final, rezultatul l-am inmultit cu B_t si se obtine raspunsul dorit
pentru calculul nostru.
    

solver_neopt.c
    - cel mai brut mod cu putinta de a face calculul; "de mana", dupa cum s-a dorit.
    - Avem functii suficient de descriptive prin denumire si comentarii, avem:
    transpune_matrice, transpune_matrice_triunghiulara, inmultire_matrice( folosita ultima inainte
    de rezultatul final), inmultire_matrice_triunghiulara_inferior_cu_matrice( e folosita pentru 
    A_t x B); inmultire_matr_cu_matrice_triung_sup se ocupa de "B x A". Toti acesti pasi sunt 
    apelati pe rand, secvential, in functia calculeaza(). Matricele intermediare sunt alocate, 
    dar li se da free la final.

solver_blas.c
    - cea mai rapida metoda de a face acest calcul
    - se initializeaza rezultatul final cu zero
    - am urmat acelasi curs de actiune ca mai sus, de etapizare in calcul, in pasi
    - aici pentru ordinea parametrilor am citit documentatia, si tot la operatiile de mai sus se reduce
    - declaram matricele auxiliare pe care le eliberam la final
    - se folosesc doar functiile de biblioteca blas inmultire de matrice triunghiulara
        cu un alt fel de matrice oarecare, de inmultire matrice cu matrice, de adunare de matrice;

solver_opt.c
    - felul sistematic de a imparti calculul in mare in etape mai mici, ramane neschimbat; optimizarea
        provine strict din cod, este drumul de la neoptimizat -> spre optimizat.
    - Pentru setul de calcule da, timpul de executie s-a redus cu peste 60%
    - Categoric se va tine cont ca A are elemente nule, calcule care nu mai trebuie sa fie facute, 
        din ratiuni de a castiga timp.
    - Pe masura ce optimizam fiecare inmultire din formulare mare, fiecare suma, observam cum scade 
        timpul de executie de la 23s, la 20s, de la 20s la 16s, mai schimbam ordinea intr-un for 
        i,j,k -> i-k-j, iar se micsora timpul si in cele din urma, trecem la pointer, la register si
        ajungem la timpul mult dorit. Optimzari succesive pana la performanta dorita. 
        De mentionat ca al nostru cod devine mai greu lizibil pe masura ce il optimizam mai mult si mai
        greu de debug-at.
        (exemplu loop unrolling -> scade timpul cu 20%)
    - Cand inmultim 2 matrice vom pastra un pointer catre linia primeia si coloana celei de-a doua
    - declaram variabilele folosite cu register; reduce costul accesului la memorie ca timp, reduce
        cache miss-urile.
    - cand avem 3 for-uri imbricate, in cel mai de jos, nu se mai adauga mereu la un element din
    matrice, ci se pastreaza intr-o variabila declarata register, acea variabila contorizeaza 
    toate adunarile, iar la final asignarea se face o singura data cand elementul din matrice rezultatul
    ia valoarea intregii sume ( asa evitam un posibil cache miss)
    - legat de functia inmultire_matr, pointerul pe linie creste din 1, in 1 sa ne deplasam pe liniile
    matricei Deinmulit, iar pointerul pe coloana pentru matricea inmultitor creste din n in n ca sa
    simulam deplasarea pe coloana.
    - numele sugestive ale functiilor s-au pastrat.
    - la functia de adunare matrice avem pointeri catre result, termen1, termen2 care
        (*result = *termen1 + *termen2), creste fiecare cu cate unul, se faciliteaza accesul la
        memorie ca nu mai avem result[i][j].
    - se va tine cont si de ordinea optima ca timp al inmultirii matricelor expusa si in laborator
        => k-i-j si i-k-j ar trebui sa aiba cele mai bune performante
    - evitam deferentierea a[i][j]

cachegrind:
    - Asignarea din cea mai de jos bucla cu index k, intr-un for este inlocuita 
    "[i * n + j] = valoare" de un pointer *poitner = valoare, scutim calcului i*n, pentru toata durata
    buclei in functie de k, pentru care i*n ramane constat, este preferabil sa folosim un pointer.
    - instructiunile sunt mai putine, dupa cum se poate observa din fisierele .cache, de la neoptimizat
    spre optimizat o scadere a numarului de la 3,631,972,640 -> 1,899,186,254.
    - se detecteaza constantele din bucle si nu le mai recalculam la fiecare pas, nu ii mai reinitializam
        si doar adunam cu 1.
        de exemplu: *pb = b + i *n
    - declarand cu register, reducem cache miss
    
