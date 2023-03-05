public class Test {
    public static void main(String[] args) {

        try
        {
            Dictionar d = new Dictionar();
            d.initializeazaDictionar();
            System.out.println("Dictionar initial: ");
            d.printeazaDictionar();
            System.out.println("Limba cuvintelor din dictionar, in ordine este: ");

            /* Functie care intoarce un vector cu Limbile in care sunt cuvintele in dictionar */
            d.printeazaLimbaCuvDinDictionar();


            /* campuri cuvant */
            String word = "cal";
            String word_en = "horse";
            String type = "noun";
            String []singular = new String[1];  singular[0] = "cal";
            String []plural = new String[1];    plural[0]="cai";

            /* campuri definitie */
            String dict = "Dicționar de sinonime";
            String dict_type = "synonyms";
            int year = 2012 ;
            String []text = new String[2];
            text[0] = "Animal domestic erbivor, cu copita nedespicată, folosit la călărie și la tracțiune";
            text[1] = "Cel mai rapid";

            /* cream definitia cuvantului */
            Definitii[] def = new Definitii[1];
            def[0] = new Definitii(dict, dict_type, year, text);

            /* cream cuvantul de adaugat*/
            Cuvant cuv = new Cuvant(word, word_en, type, singular, plural, def);


            /*d.addWord(cuv,"ro");
            System.out.println("Dictionar dupa add");
            d.printeazaDictionar();
            d.printeazaLimbaCuvDinDictionar();*/

            //d.addWord(cuv,"fr");
            //System.out.println("Dictionar dupa al doilea add");
            //d.printeazaDictionar();
            //d.printeazaLimbaCuvDinDictionar();

            /*d.removeWord("cal", "ro");
            System.out.println("Dictionar dupa remove cuv cal");
            d.printeazaDictionar();
            d.printeazaLimbaCuvDinDictionar();*/

            /*d.removeWord("chat","fr");
            System.out.println("Dictionar dupa remove cuv chat");
            d.printeazaDictionar();
            d.printeazaLimbaCuvDinDictionar();*/


            /*d.removeWord("poiana","ro");
            System.out.println("Dictionar dupa ce am incercat remove cuv poiana");
            d.printeazaDictionar();
            d.printeazaLimbaCuvDinDictionar();*/

            /* Testam translateWord */
            /*System.out.println(d.translateWord("pisică", "ro","fr"));
            System.out.println(d.translateWord("chat", "fr","ro"));*/

            //Test removeDefinition
            /*d.removeDefinition("câine", "ro", "Dicționar de sinonime" );
            d.printeazaDictionar();*/

            // TransalateSentence
            /*
            word = "joc";
            word_en = "game";
            type = "noun";
            singular[0] = "joc";
            plural[0]="jocuri";
            Cuvant cuv2 = new Cuvant(word, word_en, type, singular, plural, def); // reciclam def de mai sus
            d.addWord(cuv2, "ro");
            d.printeazaDictionar();
            String rezultat =new String();
            System.out.println("Traducem folosind dictionarul propozitia: \"pisica joc\"");
            System.out.println(d.translateSentence("pisică joc","ro","fr"));
            System.out.println(d.translateSentence("chat jeu","fr","ro"));*/


        }
        catch(Exception e){e.printStackTrace();}


    }
}
