import java.net.*;
import java.io.*;

class RequestHandler extends Thread {
    PrintWriter out;
    BufferedReader in;
    Socket sock;

    public RequestHandler(Socket s) {
        try {
            sock = s;
            out = new PrintWriter(sock.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(sock.getInputStream()));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void run() {
        try {
            String clientMessage;
            while ((clientMessage = in.readLine()) != null) {
                System.out.println("Client: " + clientMessage);

                // Process client's message if needed

                System.out.print("Reply: ");
                BufferedReader temp = new BufferedReader(new InputStreamReader(System.in));
                String reply = temp.readLine();
                out.println(reply);
            }
            out.close();
            sock.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

public class Server {
    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(8888)) {
            while (true) {
                Socket sock = serverSocket.accept();
                Thread newConvo = new RequestHandler(sock);
                newConvo.start();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
