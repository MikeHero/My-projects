import java.io.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Angajat extends Utilizator{

    String companie;


    public Angajat(String nume, String statut, String companie) {
        super(nume, statut);
        this.companie = companie;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public String getCompanie() {
        return companie;
    }

    public void setCompanie(String companie) {
        this.companie = companie;
    }
    static SimpleDateFormat formatter = new SimpleDateFormat("dd-MMM-yyyy HH:mm:ss");
    public static String getDate(Date data) {
        String output = formatter.format(data);
        return output;
    }
    @Override
    public void genereazaCerere(String[] comanda, String nume_fisier_output) throws ParseException, IOException
    {

        try
        {
            if (comanda[2].equals("inlocuire buletin") ||
                    comanda[2].equals("inlocuire carnet de sofer") ||
                    comanda[2].equals("inregistrare venit salarial")) {

                int prio = Integer.valueOf(comanda[4]);
                Date date = formatter.parse(comanda[3]);
                String dataString = getDate(date);

                String text = dataString + " - Subsemnatul " + this.getNume() + ", angajat la compania " + this.getCompanie() +
                        ", va rog sa-mi aprobati urmatoarea solicitare: " + comanda[2];
                Cerere cerereNoua = new Cerere(comanda[1], comanda[2], prio, date, text);
                this.coadaWaiting.add(cerereNoua);

            }
            else
            {
                throw new CerereGresitaAngajatException(comanda[2]);
            }
        }
        catch(CerereGresitaAngajatException ex) {
            FileWriter fw = new FileWriter(nume_fisier_output, true);
            BufferedWriter bw = new BufferedWriter(fw);
            bw.write((ex.getMessage() + '\n') );
            bw.close();
        }
    }

    @Override
    public String toString() {
        return "Angajat{" +
                "companie='" + companie + '\'' +
                ", nume='" + nume + '\'' +
                ", statut='" + statut + '\'' +
                '}';
    }
}
