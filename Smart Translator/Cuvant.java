import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.lang.reflect.Type;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;

public class Cuvant {
    private String word;
    private String word_en;
    private String type;
    private String []singular;
    private String []plural;
    Definitii[] definitions;

    public Cuvant(String word, String word_en, String type, String[] singular, String[] plural, Definitii[] definitions) {
        this.word = word;
        this.word_en = word_en;
        this.type = type;
        this.singular = singular;
        this.plural = plural;
        this.definitions = definitions;
    }

    public Cuvant() {

    }

    public String getWord() {
        return word;
    }

    public String getWord_en() {
        return word_en;
    }

    public String getType() {
        return type;
    }

    public String[] getSingular() {
        return singular;
    }

    public String[] getPlural() {
        return plural;
    }

    public Definitii[] getDefinitions() {
        return definitions;
    }

    public void setWord(String word) {
        this.word = word;
    }

    public void setWord_en(String word_en) {
        this.word_en = word_en;
    }

    public void setType(String type) {
        this.type = type;
    }

    public void setSingular(String[] singular) {
        this.singular = singular;
    }

    public void setPlural(String[] plural) {
        this.plural = plural;
    }

    public void setDefinitions(Definitii[] definitions) {
        this.definitions = definitions;
    }


    public static ArrayList<Cuvant> genereazaCuvinte(Path filename)
    {
        ArrayList<Cuvant> cuvinte = null;

        try {
            Gson gson = new Gson();
            Type collectionType = new TypeToken<ArrayList<Cuvant>>() {}.getType();
            cuvinte = gson.fromJson(new FileReader(String.valueOf(filename)), collectionType);
        } catch (
                FileNotFoundException ex) {
            ex.printStackTrace();
        } finally {
            ;
        }
        return cuvinte;
    }


    boolean cuvantIdentic(String nume)
    {
        return(this.getWord().equals(nume));
    }


    @Override
    public String toString() {
        return "\nCuvant: {" +
                "word='" + word + '\'' +
                ", word_en='" + word_en + '\'' +
                ", type='" + type + '\'' +
                ", singular=" + Arrays.toString(singular) +
                ", plural=" + Arrays.toString(plural) +
                ", definitions=" + Arrays.toString(definitions) +
                 + '}';
    }



}
