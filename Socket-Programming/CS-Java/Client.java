import java.net.*;
import java.io.*;

public class Client {
    public static void main(String[] args) {
        try {
            Socket sock = new Socket("localhost", 8888);
            PrintWriter out = new PrintWriter(sock.getOutputStream(), true);
            BufferedReader in = new BufferedReader(new InputStreamReader(sock.getInputStream()));
            BufferedReader userIn = new BufferedReader(new InputStreamReader(System.in));

            String userInput;
            while ((userInput = userIn.readLine()) != null) {
                out.println(userInput);
                System.out.println("Server: " + in.readLine());

                // Optionally handle server's response

                System.out.print("Reply: ");
            }

            out.close();
            in.close();
            userIn.close();
            sock.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
