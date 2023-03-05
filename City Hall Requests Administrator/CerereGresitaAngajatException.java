public class CerereGresitaAngajatException extends Exception {
    public CerereGresitaAngajatException(String message) {
        super("Utilizatorul de tip angajat nu poate inainta o cerere de tip " + message);
    }
}
