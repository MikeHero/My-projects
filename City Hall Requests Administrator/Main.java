
import jdk.jshell.execution.Util;

import javax.xml.crypto.Data;
import java.io.*;
import java.lang.reflect.Array;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.PriorityQueue;
import java.util.Set;

public class Main {

    public enum Cereri{
        inlocuire_buletin,
        inregistrare_venit_salarial,
        inlocuire_carnet_de_sofer,
        inlocuire_carnet_de_elev,
        creare_act_constitutiv,
        reinnoire_autorizatie,
        inregistrare_cupoane_de_pensie,
    }

    static int gaseste(String nume, ArrayList<Utilizator> v)
    {
        for(Utilizator aux: v)
            if(nume.equals(aux.getNume()))
                return v.indexOf(aux);
        return -1;
    }

    static int gasesteStatut(String statut, ArrayList<Utilizator> v)
    {
        for(Utilizator aux: v)
            if(statut.equals(aux.getStatut()))
                return v.indexOf(aux);
        return -1;
    }

    static void unifica(String statut, ArrayList<Utilizator> v,  PriorityQueue<Cerere> coadaWaitingGlobal)
    {
        for (Utilizator aux : v)
        {
            if(statut.equals(aux.getStatut()))
                coadaWaitingGlobal.addAll(aux.getCoadaWaiting());
        }

    }

    static void afisare(String statut, PriorityQueue<Cerere> coadaWaitingGlobal, String nume_fisier_output) throws IOException {

        FileWriter fw = new FileWriter(nume_fisier_output, true);
        BufferedWriter bw = new BufferedWriter(fw);

        bw.write(statut  + " - cereri in birou:"+'\n');

        // scot un element din coada, il afisez, il pun in coada auxiliara
        if (coadaWaitingGlobal != null) {
            while (coadaWaitingGlobal.isEmpty() == false) {
                bw.write( coadaWaitingGlobal.peek().getPrioritate() + " - "
                        +coadaWaitingGlobal.peek().getText() + '\n');
                coadaWaitingGlobal.remove();
            }
        }

        bw.close();
    }

    static void solutioneaza(Date data,  ArrayList<Utilizator> v)
    {
        for(Utilizator aux : v)
        {
            PriorityQueue<Cerere> coadaWaitingCopie = new PriorityQueue<>();
            while (aux.coadaWaiting.isEmpty() == false)
            {
                // pe cea cu data specificata o elimin, pe aia nu o adaug
                if (aux.getCoadaWaiting().peek().getData().compareTo(data) != 0)
                    coadaWaitingCopie.add(aux.getCoadaWaiting().peek());
                else
                    aux.coadaFinalized.add(aux.getCoadaWaiting().peek());

                aux.getCoadaWaiting().remove();


            }

            // cu ajutorul cozii auxiliare refac coada initiala, dupa ce am afisat elementele
            while (coadaWaitingCopie.isEmpty() == false) {
                aux.getCoadaWaiting().add(coadaWaitingCopie.peek());
                coadaWaitingCopie.remove();
            }
        }

    }

    static SimpleDateFormat formatter = new SimpleDateFormat("dd-MMM-yyyy HH:mm:ss");
    public static String genereazaData(Date data) {
        String output = formatter.format(data);
        return output;
    }

    public static void main(String[] args)  {

        try
        {
            String nume_fisier_input = "resources/input/" + args[0];
            String nume_fisier_output = "resources/output/" + args[0];

            // ne asiguram ca fisierul de output e gol
            new FileWriter(nume_fisier_output, false).close();

            ArrayList<Utilizator> v = new ArrayList<Utilizator>();
            ArrayList<String> display = new ArrayList<>();
            ArrayList<Functionar> birou = new ArrayList<>();




            BufferedReader br = new BufferedReader(new FileReader(nume_fisier_input));
            String buff = " ";
            while (buff != null) {
                buff = br.readLine();
                if (buff == null)
                    break;

                String[] comanda = buff.split(";");
                for (int i = 0; i < comanda.length; i++)
                    comanda[i] = comanda[i].strip();
                if (comanda[0].equals("adauga_utilizator")) {
                    // trebuie sa adaugam un angajat
                    if (comanda[1].equals("angajat")) {
                        Angajat angajat = new Angajat(comanda[2], comanda[1], comanda[3]);
                        v.add(angajat);
                    }
                    // trebuie sa adaugam un elev
                    else if(comanda[1].equals("elev")) {
                        Elev elev = new Elev(comanda[2], comanda[1], comanda[3]);
                        v.add(elev);
                    }
                    // trebuie sa adaugam un pensionar
                    else if(comanda[1].equals("pensionar"))
                    {
                        Pensionar pensionar = new Pensionar(comanda[2], comanda[1]);
                        v.add(pensionar);
                    }
                    else if(comanda[1].equals("entitate juridica"))
                    {
                        EntitateJuridica entitateJuridica = new EntitateJuridica(comanda[2], comanda[1], comanda[3]);
                        v.add(entitateJuridica);
                    }
                    else if(comanda[1].equals("persoana"))
                    {
                        Persoana persoana = new Persoana((comanda[2]), comanda[1]);
                        v.add(persoana);
                    }

                } else if (comanda[0].equals("cerere_noua")) {
                    // indexul din arraylist la care se afla utilizatorul mentionat in cerere
                    int index = gaseste(comanda[1], v);
                    v.get(index).genereazaCerere(comanda, nume_fisier_output);

                } else if (comanda[0].equals("afiseaza_cereri_in_asteptare")) {
                    int index = gaseste(comanda[1], v);
                    v.get(index).afiseazaCoadaWaiting(display);
                } else if(comanda[0].equals("retrage_cerere")) {
                    int index = gaseste((comanda[1]), v);

                    // obtinem data -> din string
                    SimpleDateFormat formatter = new SimpleDateFormat("dd-MMM-yyyy HH:mm:ss");
                    Date date = formatter.parse(comanda[2]);
                    v.get(index).eliminaCoadaWaiting(date);
                }
                else if (comanda[0].equals("afiseaza_cereri"))
                {
                    PriorityQueue coadaWaitingGlobal = new PriorityQueue<>(new CerereComparator());
                    unifica(comanda[1], v, coadaWaitingGlobal);
                    afisare(comanda[1], coadaWaitingGlobal, nume_fisier_output );
                }
                else if( comanda[0].equals("adauga_functionar"))
                {
                    Functionar functionar = new Functionar(comanda[2], comanda[1]);
                    birou.add(functionar);
                }
                else if(comanda[0].equals("rezolva_cerere"))
                {
                    PriorityQueue coadaWaitingGlobal = new PriorityQueue<>(new CerereComparator());
                    unifica(comanda[1], v, coadaWaitingGlobal);
                    Cerere c = (Cerere) coadaWaitingGlobal.peek();
                    Date de_eliminat = c.getData();
                    solutioneaza(de_eliminat, v);
                    String nume_fisier_output_functionar = "resources/output/"+ comanda[2] +".txt";

                    FileWriter fw = new FileWriter(nume_fisier_output_functionar, true);
                    BufferedWriter bw = new BufferedWriter(fw);

                    bw.write(genereazaData(c.getData()) + " - " + c.getNume() + '\n' );

                    bw.close();
                }
                else if(comanda[0].equals("afiseaza_cereri_finalizate"))
                {
                    int index = gaseste(comanda[1], v);
                    v.get(index).afiseazaCoadaFinalized(display);
                }

            }
            br.close();

            FileWriter fw = new FileWriter(nume_fisier_output, true);
            BufferedWriter bw = new BufferedWriter(fw);
            while (display.isEmpty() == false)
            {
                bw.write(display.get(0));
                display.remove(0);
            }
            bw.close();
        }
        catch (IOException ex)
        {
            ;
        }
        catch(ParseException ex)
        {
            ;
        }









    }
}
