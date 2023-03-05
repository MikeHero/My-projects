import java.util.Arrays;

public class Definitii extends Cuvant{
    String dict;
    String dicType;
    int year;
    String[] text;

    public Definitii(String dict, String dicType, int year, String[] text) {
        this.dict = dict;
        this.dicType = dicType;
        this.year = year;
        this.text = text;
    }

    public String getDict() {
        return dict;
    }

    public String getDicType() {
        return dicType;
    }

    public int getYear() {
        return year;
    }

    public String[] getText() {
        return text;
    }

    public void setDict(String dict) {
        this.dict = dict;
    }

    public void setDicType(String dicType) {
        this.dicType = dicType;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public void setText(String[] text) {
        this.text = text;
    }

    @Override
    public String toString() {
        return "Definitii{" +
                "dict='" + dict + '\'' +
                ", dicType='" + dicType + '\'' +
                ", year=" + year +
                ", text=" + '\'' + Arrays.toString(text)+ '\'' +
                '}';
    }
}
