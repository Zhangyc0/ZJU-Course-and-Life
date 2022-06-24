public class Authenticator {
    public boolean Authenticate(Credentials credentials) {
        return DBHelper.GetAdmin(credentials);
    }
}
