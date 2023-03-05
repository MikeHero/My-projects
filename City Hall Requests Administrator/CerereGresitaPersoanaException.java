public class CerereGresitaPersoanaException extends Exception{
    public CerereGresitaPersoanaException(String message) {
        super("Utilizatorul de tip persoana nu poate inainta o cerere de tip " + message);
    }
}
