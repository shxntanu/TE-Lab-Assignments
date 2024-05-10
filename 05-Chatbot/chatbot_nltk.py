"""
This code implements an elementary chatbot for a movie ticket booking application.
"""

from nltk.chat.util import Chat, reflections

# Define some patterns and responses
movies = {
    'Interstellar': ['Morning: 10:00 AM', 'Afternoon: 2:00 PM', 'Evening: 6:00 PM'],
    'The Dark Knight': ['Morning: 11:00 AM', 'Afternoon: 3:00 PM', 'Evening: 7:00 PM'],
    'Dune': ['Morning: 9:30 AM', 'Afternoon: 1:30 PM', 'Evening: 5:30 PM']
}

patterns = [
    (r'hi|hello|hey', 
     ['Hello! How can I assist you today?', 'Hey there! What can I do for you?', 'Hi! Ready to book some movie tickets?']),
    (r'how are you', 
     ['I am just a bot, but I am always ready to help you book tickets!', 'I am doing well, thanks for asking. How can I assist you today?']),
    (r'(.*) movie', 
     ['Here is the list of movies: ' + ', '.join(movies.keys()) + '. Which movie would you like to watch?', 'Sure! Here are the movies currently playing: ' + ', '.join(movies.keys()) + '.']),
    (r'(.*) ticket', 
     ['How many tickets do you need?', 'Sure! How many tickets would you like to book?', 'Got it! How many tickets do you want to book?']),
    (r'(.*) showtime', 
     ['Here are the showtimes for the available movies:' + f"{movie}: {', '.join(timings)}" for movie, timings in movies.items()]),
     (r'(.*) timing', 
     ['Here are the timings for the each movie:' + f"{movie}: {', '.join(timings)}" for movie, timings in movies.items()]),
    (r'(.*) (morning|afternoon|evening|night)', 
     ['We have showtimes available in the morning, afternoon, evening, and night. When would you like to watch?']),
    (r'(.*) book tickets', 
     ['Sure! Let\'s proceed with booking tickets.']),
    (r'(.*) (bye|goodbye)', 
     ['Thank you for visiting ChatBot. Have a great day!', 'Goodbye! Enjoy your movie!', 'Bye! See you soon.']),
]

# create a chatbot
tea_bot = Chat(patterns, reflections)


def book_tickets(movie, tickets, showtime):
    # calculate total bill
    ticket_price = 100  # assuming a fixed price for now
    total_bill = tickets * ticket_price
    return f"Booking confirmed! You have booked {tickets} tickets for {movie} at {showtime}.\nTotal amount: Rs. {total_bill}."


def main():
    print("\nHello! Welcome to ChatBot. How can I assist you today?")
    
    while True:
        user_input = input("You: ")
        response = tea_bot.respond(user_input)
        print("ChatBot:", response)
        
        # extract information for booking tickets
        if "book tickets" in user_input.lower():
            movie = input("Which movie would you like to watch? :")
            tickets = int(input("How many tickets do you need? :"))
            showtime = input("At what time would you like to watch the movie? :")
            booking_response = book_tickets(movie, tickets, showtime)
            print("ChatBot:", booking_response)
        
        # check if the user wants to end the conversation
        if any(word in user_input.lower() for word in ['bye', 'goodbye']):
            break


main()
