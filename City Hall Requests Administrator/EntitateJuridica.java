import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class EntitateJuridica extends Utilizator {

    String companie;

    public EntitateJuridica(String nume, String statut, String companie) {
        super(nume, statut);
        this.companie = companie;
    }

    public String getNume() {
        return nume;
    }

    public String getCompanie() {
        return companie;
    }


   // static SimpleDateFormat formatter = new SimpleDateFormat("dd-MMM-yyyy HH:mm:ss");
    static SimpleDateFormat formatter = new SimpleDateFormat("dd-MMM-yyyy HH:mm:ss", Locale.ENGLISH);

    public static String getDate(Date data) {
        String output = formatter.format(data);
        return output;
    }

    @Override
    public void genereazaCerere(String[] comanda, String nume_fisier_output) throws ParseException, IOException
    {

        try
        {
            if (comanda[2].equals("creare act constitutiv") ||
                    comanda[2].equals("reinnoire autorizatie"))
            {

                int prio = Integer.valueOf(comanda[4]);
                Date date = formatter.parse(comanda[3]);
                String dataString = getDate(date);

                String text = dataString + " - Subsemnatul " + this.getCompanie() + ", reprezentant legal al companiei "
                        + this.getNume() + ", va rog sa-mi aprobati urmatoarea solicitare: " + comanda[2];
                Cerere cerereNoua = new Cerere(comanda[1], comanda[2], prio, date, text);
                this.coadaWaiting.add(cerereNoua);

            } else {
                throw new CerereGresitaEntitateJuridicaException(comanda[2]);
            }
        } catch (CerereGresitaEntitateJuridicaException ex) {
            FileWriter fw = new FileWriter(nume_fisier_output, true);
            BufferedWriter bw = new BufferedWriter(fw);
            bw.write((ex.getMessage() + '\n'));
            bw.close();
        }
    }

    @Override
    public String toString() {
        return "EntitateJuridica{" +
                "companie='" + companie + '\'' +
                ", nume='" + nume + '\'' +
                ", statut='" + statut + '\'' +
                '}';
    }
}
