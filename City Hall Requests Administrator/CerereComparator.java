import java.util.Comparator;

public class CerereComparator implements Comparator<Cerere>{
        public int compare(Cerere c1, Cerere c2) {
            if (c1 == c2)
                return 0;
            if (c1.prioritate > c2.prioritate)
                return -1;
            if (c1.prioritate == c2.prioritate)
                return c1.getData().compareTo(c2.getData());
            return 1;
        }
}
