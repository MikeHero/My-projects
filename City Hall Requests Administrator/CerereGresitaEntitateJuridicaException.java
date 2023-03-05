public class CerereGresitaEntitateJuridicaException extends Exception{
    public CerereGresitaEntitateJuridicaException(String message) {
        super("Utilizatorul de tip entitate juridica nu poate inainta o cerere de tip " + message);
    }
}
