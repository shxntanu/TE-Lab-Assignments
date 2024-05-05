class Role:
    def __init__(self, name):
        self.name = name
        self.responses = {}  # Dictionary to map keywords to responses

    # Add a response to the role
    def add_response(self, keyword, response):
        self.responses[keyword] = response


# Function to simulate user interaction and handle role-based responses
def interact(roles):
    # Simulate user input
    input_text = input("Enter your message: ")

    # Find the best matching role based on keywords in the input
    best_match_score = 0
    best_match_role = None
    for role in roles:
        score = 0
        for keyword in role.responses:
            if keyword in input_text:
                score += 1
        if score > best_match_score:
            best_match_score = score
            best_match_role = role

    # Handle no matching role or keyword
    if best_match_role is None:
        return "I don't understand. Could you rephrase?"

    # Search for a keyword match within the best matching role
    for keyword, response in best_match_role.responses.items():
        if keyword in input_text:
            return response

    # If no keyword match is found within the best matching role, provide a generic response
    return "I'm still learning. How can I help you?"


if __name__ == "__main__":
    # Create roles and add responses
    roles = []

    customer_service = Role("Customer Service")
    customer_service.add_response("order", "I can help you with your order. What is your order number?")
    customer_service.add_response("payment", "I can answer questions about payment options.")
    customer_service.add_response("return", "We offer a hassle-free return policy. Please tell me more about the item you want to return.")
    roles.append(customer_service)

    technical_support = Role("Technical Support")
    technical_support.add_response("bug", "I'm here to help you with technical issues. Can you describe the bug you're experiencing?")
    technical_support.add_response("feature", "We're constantly working on new features. What feature would you like to see?")
    technical_support.add_response("compatibility", "I can help you with compatibility issues. What device or system are you using?")
    roles.append(technical_support)

    # Simulate user interaction
    while True:
        response = interact(roles)
        print(response)
        if response == "exit":
            break
