package mongoJava;

import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import org.bson.Document;
import java.util.Scanner;
import com.mongodb.MongoCredential;


public class javamongo {
	public static void main(String[] args) {
        MongoClient mongoClient = new MongoClient("10.10.11.238", 27017);
        MongoCredential credential; 
        credential = MongoCredential.createCredential("te31375", "31375_db", "te31375".toCharArray()); 
        System.out.println("Connected to the database successfully");// Connect to MongoDB
        MongoDatabase database = mongoClient.getDatabase("31375_db"); // Replace with your database name
        MongoCollection<Document> collection = database.getCollection("sampleCollection"); // Replace with your collection name
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("Menu:");
            System.out.println("1. Create");
            System.out.println("2. Read");
            System.out.println("3. Update");
            System.out.println("4. Delete");
            System.out.println("5. Exit");
            System.out.print("Enter your choice: ");
            int choice = scanner.nextInt();

            switch (choice) {
                case 1:
                    // Create operation
                    createDocument(collection, scanner);
                    break;
                case 2:
                    // Read operation
                    readDocuments(collection);
                    break;
                case 3:
                    // Update operation
                    updateDocument(collection, scanner);
                    break;
                case 4:
                    // Delete operation
                    deleteDocument(collection, scanner);
                    break;
                case 5:
                    System.out.println("Exiting the program.");
                    mongoClient.close(); // Close the MongoDB connection
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid choice. Please select a valid option.");
                    break;
            }
        }
	}
private static void createDocument(MongoCollection<Document> collection, Scanner scanner) {
    System.out.print("Enter a key: ");
    String key = scanner.next();
    System.out.print("Enter a value: ");
    String value = scanner.next();
    Document document = new Document(key, value);
    collection.insertOne(document);
    System.out.println("Document added successfully.");
}

private static void readDocuments(MongoCollection<Document> collection) {
    for (Document doc : collection.find()) {
        System.out.println(doc.toJson());
    }
}

private static void updateDocument(MongoCollection<Document> collection, Scanner scanner) {
    System.out.print("Enter the key of the document to update: ");
    String key = scanner.next();
    System.out.print("Enter the new value: ");
    String value = scanner.next();
    Document filter = new Document(key, value);
    Document update = new Document("$set", new Document(key, value));
    collection.updateOne(filter, update);
    System.out.println("Document updated successfully.");
}

private static void deleteDocument(MongoCollection<Document> collection, Scanner scanner) {
    System.out.print("Enter the key of the document to delete: ");
    String key = scanner.next();
    System.out.print("Enter the value of the document to delete: ");
    String value = scanner.next();
    Document filter = new Document(key, value);
    collection.deleteOne(filter);
    System.out.println("Document deleted successfully.");
}
}
