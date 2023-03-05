public class CerereGresitaPensionarException extends Exception {
    public CerereGresitaPensionarException(String message) {
        super("Utilizatorul de tip pensionar nu poate inainta o cerere de tip " + message);
    }
}
