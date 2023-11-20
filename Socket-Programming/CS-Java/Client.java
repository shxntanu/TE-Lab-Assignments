import java.net.*;
import java.io.*;
import java.util.*;

public class C{
    public static void main(String [] args){
        try{
            while(true){
                Socket sock = new Socket("localhost", 21);
                PrintWriter out = new PrintWriter(sock.getOutputStream(), true);
                Scanner in = new Scanner(sock.getInputStream());

                System.out.print("Reply: ");
                Scanner temp = new Scanner(System.in);
                String reply;
                reply = temp.nextLine();
                
                out.println(reply);
                System.out.println("Server: " + in.nextLine());
                
                sock.close();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}
