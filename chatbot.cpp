#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Structure to represent a role in the chatbot
struct Role {
    string name;
    unordered_map<string, string> responses; // Map keywords to responses

    // Constructor
    Role(const string& name) : name(name) {}

    // Add a response to the role
    void add_response(const string& keyword, const string& response) {
        responses[keyword] = response;
    }
};

// Function to simulate user interaction and handle role-based responses
string interact(vector<Role>& roles) {
    string input;
    cout << "Enter your message: ";
    getline(cin, input);

    // Find the best matching role based on keywords in the input
    int best_match_score = 0;
    Role* best_match_role = nullptr;
    for (Role& role : roles) {
        int score = 0;
        for (const auto& [keyword, _] : role.responses) {
            if (input.find(keyword) != string::npos) {
                score++;
            }
        }
        if (score > best_match_score) {
            best_match_score = score;
            best_match_role = &role;
        }
    }

    // Handle no matching role or keyword
    if (!best_match_role) {
        return "I don't understand. Could you rephrase?";
    }

    // Search for a keyword match within the best matching role
    for (const auto& [keyword, response] : best_match_role->responses) {
        if (input.find(keyword) != string::npos) {
            return response;
        }
    }

    // If no keyword match is found within the best matching role, provide a generic response
    return "I'm still learning. How can I help you?";
}

int main() {
    // Create roles and add responses
    vector<Role> roles;
    Role customer_service("Customer Service");
    customer_service.add_response("order", "I can help you with your order. What is your order number?");
    customer_service.add_response("payment", "I can answer questions about payment options.");
    customer_service.add_response("return", "We offer a hassle-free return policy. Please tell me more about the item you want to return.");
    roles.push_back(customer_service);

    Role technical_support("Technical Support");
    technical_support.add_response("bug", "I'm here to help you with technical issues. Can you describe the bug you're experiencing?");
    technical_support.add_response("feature", "We're constantly working on new features. What feature would you like to see?");
    technical_support.add_response("compatibility", "I can help you with compatibility issues. What device or system are you using?");
    roles.push_back(technical_support);

    // Simulate user interaction
    string response;
    do {
        response = interact(roles);
        cout << response << endl;
    } while (response != "exit"); // Allow user to exit the interaction

    return 0;
}
