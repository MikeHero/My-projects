import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class Elev extends Utilizator{
    String scoala;

    public Elev(String nume, String statut, String scoala) {
        super(nume, statut);
        this.scoala = scoala;
    }

    public String getScoala() {
        return scoala;
    }

    public String getNume() {
        return nume;
    }


    // asta e formatu bun
    static SimpleDateFormat formatter = new SimpleDateFormat("dd-MMM-yyyy HH:mm:ss",Locale.ENGLISH);

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
                    comanda[2].equals("inlocuire carnet de elev"))
            {

                int prio = Integer.valueOf(comanda[4]);
                Date date = formatter.parse(comanda[3]);

                String dataString = getDate(date);

                String text = dataString + " - Subsemnatul " + this.getNume() + ", elev la scoala " +
                        this.getScoala() + ", va rog sa-mi aprobati urmatoarea solicitare: " + comanda[2];
                Cerere cerereNoua = new Cerere(comanda[1], comanda[2], prio, date, text);
                this.coadaWaiting.add(cerereNoua);

            }
            else
            {
                throw new CerereGresitaElevException(comanda[2]);
            }
        }
        catch(CerereGresitaElevException ex) {
            FileWriter fw = new FileWriter(nume_fisier_output, true);
            BufferedWriter bw = new BufferedWriter(fw);
            bw.write((ex.getMessage() + '\n') );
            bw.close();
        }
    }

    @Override
    public String toString() {
        return "Elev{" +
                "scoala='" + scoala + '\'' +
                ", nume='" + nume + '\'' +
                ", statut='" + statut + '\'' +
                '}';
    }
}
