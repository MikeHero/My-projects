public class CerereGresitaElevException extends  Exception{

    public CerereGresitaElevException(String message) {
        super("Utilizatorul de tip elev nu poate inainta o cerere de tip " + message);
    }
}
