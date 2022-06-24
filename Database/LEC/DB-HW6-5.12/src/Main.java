import javax.swing.plaf.ColorUIResource;
import java.awt.*;
import java.io.File;
import java.util.Scanner;

public class Main {
    public static User authenticatedUser = new User();
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        boolean newConnection = false;
        String username = "";
        String password = "";
        String dbName = "";

        String response = "";
        boolean done = false;
        while (!done) {
            System.out.println("Do you need to setup a database? (yes/no)");
            response = scanner.nextLine();
            if (response.equals("yes")) {
                newConnection = true;
                System.out.println("MySQL username:");
                User.setUsername(scanner.nextLine());
                System.out.println("MySQL password:");
                User.setDbPassword(scanner.nextLine());
                System.out.println("Create database name:");
                dbName = scanner.nextLine();
                done = true;
            } else if (response.equals("no")) {
                System.out.println("MySQL username:");
                User.setUsername(scanner.nextLine());
                System.out.println("MySQL password:");
                User.setDbPassword(scanner.nextLine());
                System.out.println("Database name:");
                dbName = scanner.nextLine();
                // Verify the local MySQL instance has user with credentials and db exists.
                if(!DBHelper.DBExists(dbName)) {
                    System.out.println("Database doesn't exist or credentials are invalid.");
                    continue;
                }
                done = true;
            } else {
                System.out.println("Invalid response. Try again.");
            }

        }

        String dbFile = null;

        if (newConnection) {
            dbFile = PickFile();
        }

        // Initialize database connection
        DBHelper dbHelper = new DBHelper(dbFile, dbName);

        done = false;
        while (!done) {
            System.out.println("Do you want to seed database from file? (yes/no)");
            response = scanner.nextLine();

            if (response.equals("yes")) {
                String seedFile = PickFile();
                dbHelper.SeedDatabase(seedFile);
                done = true;
            } else if (response.equals("no")) {
                done = true;
            } else {
                System.out.println("Invalid Response. Try Again.");
            }
        }


        UserPrompts userPrompts = new UserPrompts();

        // A little help
        System.out.println("Username: admin\nPassword: admin");

        while (authenticatedUser.isEmpty()) {
            // Prompt user for credentials
            Credentials credentials = userPrompts.GetCredentials();

            // Authenticate user
            Authenticator authenticator = new Authenticator();

            if (authenticator.Authenticate(credentials)) {
                System.out.println("User authenticated");
            } else {
                System.out.println("Unauthorized");
            }
        }

        userPrompts.Search();
    }

    public static String PickFile() {
        FileDialog dialog = new FileDialog((Frame) null, "Select MySQL Database File");
        dialog.setMode(FileDialog.LOAD);
        dialog.setVisible(true);
        return dialog.getDirectory() + dialog.getFile();
    }
}
