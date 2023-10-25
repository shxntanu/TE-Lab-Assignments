package mongoJava;

import org.bson.Document;

import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.MongoCursor;
import com.mongodb.client.model.Filters;
import com.mongodb.client.model.UpdateOptions;
import com.mongodb.client.result.DeleteResult;
import com.mongodb.client.result.UpdateResult;
import com.mongodb.client.model.Updates;
import java.util.Scanner;

public class javamongo {
    public static void main(String[] args) {
        MongoClient mongoClient = new MongoClient("10.10.14.50", 27017);
        System.out.println("Connected to MongoDB successfully!");

        Scanner scanner = new Scanner(System.in);
        MongoDatabase database = mongoClient.getDatabase("31380_db");
        MongoCollection<Document> collection = database.getCollection("Demo");

        int choice;
        do {
            System.out.println("\nMenu:");
            System.out.println("1. Create Collection");
            System.out.println("2. Add Document");
            System.out.println("3. Delete Document");
            System.out.println("4. Read Documents");
            System.out.println("5. Update Document");
            System.out.println("6. Exit");
            System.out.print("Enter your choice: ");
            choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    createCollection(database, scanner);
                    break;
                case 2:
                    addDocument(collection, scanner);
                    break;
                case 3:
                    deleteDocument(collection, scanner);
                    break;
                case 4:
                    readDocuments(collection);
                    break;
                case 5:
                    updateDocument(collection, scanner);
                    break;
                case 6:
                    System.out.println("Exiting the program.");
                    break;
                default:
                    System.out.println("Invalid choice. Please enter a valid option.");
            }
        } while (choice != 6);

        scanner.close();
        mongoClient.close();
    }

    private static void createCollection(MongoDatabase database, Scanner scanner) {
        System.out.print("Enter the name for the new collection: ");
        String collectionName = scanner.nextLine();
        database.createCollection(collectionName);
        System.out.println("Collection created: " + collectionName);
    }

    private static void addDocument(MongoCollection<Document> collection, Scanner scanner) {
        System.out.print("Enter JSON document to add: ");
        String json = scanner.nextLine();
        Document document = Document.parse(json);
        collection.insertOne(document);
        System.out.println("Document added: " + document.toJson());
    }

    private static void deleteDocument(MongoCollection<Document> collection, Scanner scanner) {
        System.out.print("Enter the document key to delete: ");
        String key = scanner.nextLine();
        DeleteResult result = collection.deleteOne(Filters.eq("your_key_name", key));
        System.out.println("Deleted " + result.getDeletedCount() + " document(s).");
    }

    private static void readDocuments(MongoCollection<Document> collection) {
        MongoCursor<Document> cursor = collection.find().iterator();
        while (cursor.hasNext()) {
            System.out.println(cursor.next().toJson());
        }
        cursor.close();
    }

    private static void updateDocument(MongoCollection<Document> collection, Scanner scanner) {
        System.out.print("Enter the document key to update: ");
        String key = scanner.nextLine();
        System.out.print("Enter JSON document for update: ");
        String json = scanner.nextLine();
        Document updateDoc = Document.parse(json);
        UpdateResult result = collection.updateOne(Filters.eq("your_key_name", key), Updates.set(updateDoc), new UpdateOptions().upsert(true));
        System.out.println("Matched " + result.getMatchedCount() + " document(s) and modified " + result.getModifiedCount() + " document(s).");
    }
}
