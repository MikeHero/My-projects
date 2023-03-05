import java.util.Comparator;
import java.util.Date;

public class Cerere implements Comparable {
    String nume;
    String solicitare;
    int prioritate;
    Date data;
    String text;


    public Cerere(String nume, String solicitare, int prioritate, Date data, String text) {
        this.nume = nume;
        this.solicitare = solicitare;
        this.prioritate = prioritate;
        this.data = data;
        this.text = text;
    }

    public String getText() {
        return text;
    }

    public Date getData() {
        return data;
    }

    public int getPrioritate()
    {
        return this.prioritate;
    }

    public String getNume()
    {
        return this.nume;
    }

    public int compareTo(Object o) {
        if (this == (Cerere) o)
            return 0;
        // if( this.prioritate > ((Cerere)o).prioritate)
        //    return -1;
        //if( this.prioritate == ((Cerere)o).prioritate)
        return this.data.compareTo(((Cerere) o).data);
        //return 1;
    }

}
