import java.io.File;;
import java.nio.file.Paths;
import java.util.ArrayList;


public class Dictionar {

    ArrayList<Cuvant> dictionar ;
    ArrayList <String> Limbi = new ArrayList<String>();

    public Dictionar() {
        dictionar = new ArrayList<Cuvant>();
    }

    ArrayList<Cuvant> initializeazaDictionar()
    {
        try {
            File folder = new File("folder_de_intrare");
            File[] listOfFiles = folder.listFiles();
            // se inumara fisierele dinauntrul folderului

            ArrayList<Cuvant> List2 = new ArrayList<Cuvant>();
            for (int i = 0; i < listOfFiles.length; i++) {
                int dim_init = dictionar.size();
                File file = listOfFiles[i];
                List2 = Cuvant.genereazaCuvinte(Paths.get(String.valueOf(file)));

                /* pentru fiecare fisier adaugam lista de cuvinte in ArrayList */
                dictionar.addAll(List2);
                int dim_finala = dictionar.size();
                /* pentru fiecare lista de cuvinte adaugam limba in care sunt */
                String fileName= new String();
                fileName = file.getName();
                String language = new String();
                language = "" + fileName.charAt(0) + fileName.charAt(1);    // primele 2 caractere si obtinem fr / ro
                //System.out.println(language);
                for(int j = dim_init; j < dim_finala; j++)
                {
                    Limbi.add(language);
                }


            }

        } catch (Exception e) {e.printStackTrace();}
        return dictionar;
    }

    void printeazaDictionar()
    {
        if (dictionar == null)
        {
            System.out.println("Lista e vida");
        }
        else
        {
            System.out.println(dictionar);
            System.out.println("**************************************************");
        }
    }

    void printeazaLimbaCuvDinDictionar()
    {
        if(Limbi == null)
        {
            System.out.println("Lista de limba e vida");
        }
        else
        {
            System.out.println(Limbi);
            System.out.println("**************************************************");
        }
    }

    boolean addWord(Cuvant word, String language)
    {
        boolean rez = true;
        boolean nu_exista = false;
        int contor = 0;
        String nume_word = word.getWord();
        for( Cuvant i : dictionar)
        {
            /* Cuvantul de adaugat exista deja, intoarcem false */
            if( i.cuvantIdentic(nume_word) == true && language.equals(Limbi.get(contor)) )
            {
                System.out.println("Cuvantul exista deja in dictionarul cu aceasta limba");
                rez = false;
                break;
            }
            contor++;
        }
        if(rez == true )
        {
            nu_exista = true; /* adaugam */
            dictionar.add(word);
            Limbi.add(language);
        }
        return rez;
    }

    /* Intoarce true dacă s-a sters cuvântul în dicționar sau false dacă nu există cuvântul în dicționar*/

    boolean removeWord(String word, String language)
    {
        if( dictionar.isEmpty())
        {
            System.out.println("Dictionar vid");return false;
        }
        int contor = 0;
        for( Cuvant i : dictionar)
        {
            /* Daca gasim cuvantul, il eliminam din dictionar si intoarcem true */

            if( i.cuvantIdentic(word) && language.equals(Limbi.get(contor)) ) //Daca gasim cuvantul din limba respectiva
            {
                Limbi.remove(contor);
                dictionar.remove(i);

                return true;
            }
            contor++;
        }

        System.out.println("Cuvantul nu exista in dictionar, deci nu poate fi sters");

        return false;
    }

    // intoarce false dacă există o definiție din același dicționar
    boolean addDefinitionForWord(String word, String language, Definitii definition)
    {
        int contor = 0;
        Definitii []definitii = new Definitii[1];
        definitii[0] = definition;
        for(Cuvant i : dictionar)
        {
            if(i.cuvantIdentic(word) && language.equals(Limbi.get(contor)) )
            {
                if (i.getDefinitions() == null)
                {
                    i.setDefinitions(definitii);
                    return true;
                }
                else
                {
                    /*exista deja o definitie din acelasi dictionar */
                    System.out.println("Exista deja o definitie din acelasi dictionar, nu pot adauga alta");
                    return false;
                }
            }
            contor++;
        }
        return false;
    }
    //Intoarce true dacă s-a șters definiția sau false dacă nu există o definiție din dicționarul primit ca parametru
    boolean removeDefinition(String word, String language, String dictionary)
    {

        for( Cuvant i : dictionar)
        {
            if( i.cuvantIdentic(word))
            {
                int contor = 0;
                int contor2 = 0;
                int gasit = 0;
                Definitii[] def = i.getDefinitions();
                for( Definitii def_v : def )
                {
                    if( def_v.getDict().equals(dictionary))
                    {
                        gasit = 1;      /* trebuie exclusa fix definitia def_v din vector */
                        break;
                    }
                    contor++;
                }
                if( gasit ==1 )
                {
                    Definitii []def2 = new Definitii[def.length];
                    for( Definitii def_v : def)
                    {
                        if(contor != contor2)
                        {
                            def2[contor2]=def_v;
                        }
                        contor2++;
                    }
                    i.setDefinitions(def2);
                    return true;
                }

            }
        }
        return false;
    }


    String translateWord(String word, String fromLanguage, String toLanguage)
    {
        int contor = 0;
        String rez = new String();
        String nume_en = new String();
        int gasit_traducere = 0;

        for(Cuvant i : dictionar)
        {
            if( i.cuvantIdentic(word) && fromLanguage.equals(Limbi.get(contor))  )
            {
                nume_en = i.getWord_en();
                break;
            }
            contor++;
        }
        contor = 0;

        for(Cuvant i : dictionar)
        {
            if( i.getWord_en().equals(nume_en) && toLanguage.equals(Limbi.get(contor)) )
            {
                rez = i.getWord();
                gasit_traducere = 1;
                break;
            }
            contor++;
        }
        if(gasit_traducere == 0)
        {
            System.out.println("Nu exista in dictionar aparitie in 2 limbi a cuvantului, deci nu il pot traduce");
        }

        return rez;

    }


    String translateSentence(String sentence, String fromLanguage, String toLanguage)
    {
        String result = new String();
        String[] cuvant = new String[40];
        result="";


        cuvant = sentence.split(" ");
        for( String index : cuvant )
        {
            int contor = 0;
            String rez = new String();
            String nume_en = new String();

            for(Cuvant i : dictionar)
            {
                if( i.cuvantIdentic(index) && fromLanguage.equals(Limbi.get(contor))  )
                {
                    nume_en = i.getWord_en();
                    break;
                }
                contor++;
            }
            contor = 0;

            for(Cuvant i : dictionar)
            {
                if( i.getWord_en().equals(nume_en) && toLanguage.equals(Limbi.get(contor)) )
                {
                    rez = i.getWord();
                    if(result == "")
                        result = result.concat(rez);
                    else
                    {
                        result = result.concat(" "+rez);
                    }

                }
                contor++;
            }
        }

        return result;
    }






}


