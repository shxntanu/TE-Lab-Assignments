import java.net.*;
import java.util.*;
import java.io.*;

class RequestHandler extends Thread {
    PrintWriter out;
    Scanner in;
    Socket sock;
    public RequestHandler(Socket s){
        try{
            sock = s;
            out = new PrintWriter(sock.getOutputStream(), true);
            in = new Scanner(sock.getInputStream());
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    public void run(){
        try{
            if(in.hasNextLine()){
                System.out.println("Client: " + in.nextLine());
            }
            Scanner temp = new Scanner(System.in);

            System.out.print("Reply: ");
            String replString = temp.nextLine();
            out.println(replString);

            out.close();
            sock.close();
        } catch(Exception e){
            e.printStackTrace();
        }
    }
}

public class S{
    public static void main(String [] args) {
        try(ServerSocket serverSocket = new ServerSocket(21)){
            while(true){
                Socket sock = serverSocket.accept();
                Thread newConvo = new RequestHandler(sock);
                newConvo.start();
            }
        } catch(Exception e) {
            e.printStackTrace();
        }
    }
}
