public class User {
    private static String name;
    private static String username;
    private static String dbPassword;
    private static String adminPassword;

    public User(String name, String username, String dbPassword) {
        User.name = name;
        User.username = username;
        User.dbPassword = dbPassword;
    }

    public User() {
        User.name = "";
        User.username = "";
        User.dbPassword = "";
    }

    public static String getName() {
        return User.name;
    }

    public static void setName(String name) {
        User.name = name;
    }

    public static String getUsername() {
        return username;
    }

    public static void setUsername(String username) {
        User.username = username;
    }

    public static String getDbPassword() {
        return dbPassword;
    }

    public static void setDbPassword(String dbPassword) {
        User.dbPassword = dbPassword;
    }

    public static String getAdminPassword() {
        return User.adminPassword;
    }

    public static void setAdminPassword(String adminPassword) {
        User.adminPassword = adminPassword;
    }

    public boolean isEmpty() {
        return User.username.isEmpty();
    }
}
