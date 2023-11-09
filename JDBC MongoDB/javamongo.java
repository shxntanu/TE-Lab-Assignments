package mongoJava;

import java.util.*;
import com.mongodb.client.*;
import com.mongodb.MongoClient;
import org.bson.Document;

public class mongo {
    public static void main(String[] args) {
        MongoClient client = new MongoClient("127.0.0.1", 27017);
        System.out.println("Connected to DB");
        MongoDatabase db = client.getDatabase("31380_db");
        MongoCollection<Document> collection = db.getCollection("sampleCollection");

        Scanner sc = new Scanner(System.in);

        while (true) {
            System.out.println("Menu:");
            System.out.println("1. Create");
            System.out.println("2. Read");
            System.out.println("3. Update");
            System.out.println("4. Delete");
            System.out.println("5. Exit");
            System.out.print("Enter your choice: ");
            int choice = sc.nextInt();

            switch (choice) {
                case 1:
                    createDocument(collection, sc);
                    break;

                case 2:
                    readDocuments(collection);
                    break;

                case 3:
                    updateDocument(collection, sc);
                    break;

                case 4:
                    deleteDocument(collection, sc);
                    break;
            }

            System.out.println("Continue? (y/n): ");
            String ans = sc.next();
            if (ans.equals("N") || ans.equals("n"))
                break;
        }
        sc.close();
        client.close();
    }

    public static void createDocument(MongoCollection<Document> collection, Scanner sc) {
        System.out.println("Enter a key: ");
        String key = sc.next();
        System.out.println("Enter its value: ");
        String value = sc.next();
        Document newdoc = new Document(key, value);
        collection.insertOne(newdoc);
        System.out.println("Document inserted successfully");

    }

    public static void readDocuments(MongoCollection<Document> collection) {
        for (Document doc : collection.find()) {
            System.out.println(doc.toJson());
        }
    }

    public static void updateDocument(MongoCollection<Document> collection, Scanner sc) {
        System.out.println("Enter document identifier key: ");
        String key = sc.next();
        System.out.println("Enter corresponding value");
        String value = sc.next();
        Document filter = new Document(key, value);
        System.out.println("Enter new value");
        String uValue = sc.next();
        Document uDoc = new Document(key, uValue);
        collection.updateOne(filter, uDoc);
        System.out.println("Document updated successfully");
    }

    public static void deleteDocument(MongoCollection<Document> collection, Scanner sc) {
        System.out.println("Enter document identifier key: ");
        String key = sc.next();
        System.out.println("Enter corresponding value");
        String value = sc.next();
        Document filter = new Document(key, value);
        collection.deleteOne(filter);
        System.out.println("Document deleted successfully");

    }

}
