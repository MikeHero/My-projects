import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Date;
import java.util.PriorityQueue;

public abstract class Utilizator {
    String nume;
    String statut;
    PriorityQueue<Cerere> coadaWaiting = new PriorityQueue<>();
    PriorityQueue<Cerere> coadaFinalized = new PriorityQueue<>();
    public Utilizator(String nume, String statut) {
        this.nume = nume;
        this.statut = statut;
    }

    public String getNume() {
        return nume;
    }

    public String getStatut() {
        return statut;
    }

    public PriorityQueue<Cerere> getCoadaWaiting() {
        return coadaWaiting;
    }

    public void setCoadaWaiting(PriorityQueue<Cerere> coadaWaiting) {
        this.coadaWaiting = coadaWaiting;
    }

    void afiseazaCoadaWaiting(ArrayList<String> display) throws IOException {

        PriorityQueue<Cerere> coadaWaitingCopie = new PriorityQueue<>();

        display.add(this.getNume() + " - cereri in asteptare:"+'\n');

        // scot un element din coada, il afisez, il pun in coada auxiliara
        while(this.coadaWaiting.isEmpty() == false )
        {
            coadaWaitingCopie.add(coadaWaiting.peek());
            display.add(this.coadaWaiting.peek().getText() + '\n');
            this.coadaWaiting.remove();
        }

        // cu ajutorul cozii auxiliare refac coada initiala, dupa ce am afisat elementele
        while(coadaWaitingCopie.isEmpty() == false)
        {
            this.coadaWaiting.add(coadaWaitingCopie.peek());
            coadaWaitingCopie.remove();
        }

    }


    void afiseazaCoadaFinalized(ArrayList<String> display) throws IOException {

        PriorityQueue<Cerere> coadaFinalizedCopie = new PriorityQueue<>();

        display.add(this.getNume() + " - cereri in finalizate:"+'\n');

        // scot un element din coada, il afisez, il pun in coada auxiliara
        while(this.coadaFinalized.isEmpty() == false )
        {
            coadaFinalizedCopie.add(coadaFinalized.peek());
            display.add(this.coadaFinalized.peek().getText() + '\n');
            this.coadaFinalized.remove();
        }

        // cu ajutorul cozii auxiliare refac coada initiala, dupa ce am afisat elementele
        while(coadaFinalizedCopie.isEmpty() == false)
        {
            this.coadaFinalized.add(coadaFinalizedCopie.peek());
            coadaFinalizedCopie.remove();
        }

    }

    void eliminaCoadaWaiting(Date data)
    {
        PriorityQueue<Cerere> coadaWaitingCopie = new PriorityQueue<>();
        while(this.coadaWaiting.isEmpty() == false )
        {
            // pe cea cu data specificata o elimin, pe aia nu o adaug
            if(coadaWaiting.peek().getData().compareTo(data) != 0 )
                coadaWaitingCopie.add(coadaWaiting.peek());
            this.coadaWaiting.remove();
        }

        // cu ajutorul cozii auxiliare refac coada initiala, dupa ce am afisat elementele
        while(coadaWaitingCopie.isEmpty() == false)
        {
            this.coadaWaiting.add(coadaWaitingCopie.peek());
            coadaWaitingCopie.remove();
        }

    }

    public abstract void genereazaCerere(String[] comanda, String nume_fisier_output)
            throws ParseException, IOException;
}
