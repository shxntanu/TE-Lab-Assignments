def ask_question(question: str) -> bool:
    response = input(question + ": ").lower().strip()[0]
    return response == "y"


def diagnose_allergies() -> bool:
    return ask_question("Do you experience any itching or swelling?") or ask_question(
        "Do you have red, watery eyes?"
    )


def diagnose_fever() -> bool:
    return ask_question("Do you have a temperature above 37.5°C?") or ask_question(
        "Do you experience chills?"
    )


def diagnose_cold() -> bool:
    return ask_question("Do you have a runny or stuffy nose?") or ask_question(
        "Are you sneezing frequently?"
    )


def diagnose_flu() -> bool:
    return (
        ask_question("Do you have body aches?")
        and ask_question("Do you feel tired or fatigued?")
        and ask_question("Do you have a temperature above 38°C?")
    )


def diagnose_strep_throat() -> bool:
    return ask_question("Do you have a sore throat?") and ask_question(
        "Are your tonsils swollen?"
    )


def diagnose_food_poisoning() -> bool:
    return (
        ask_question("Do you feel nauseous?")
        and ask_question("Have you been vomiting?")
        and ask_question("Do you have diarrhea?")
    )


def diagnose_appendicitis() -> bool:
    return ask_question("Do you have severe abdominal pain?") and ask_question(
        "Have you lost your appetite?"
    )


print("Expert System for diagnosing ailments")

if diagnose_allergies():
    print("You have allergies")
if diagnose_fever():
    print("You have fever")
if diagnose_cold()():
    print("You have cold")
if diagnose_strep_throat():
    print("You have strep throat")
if diagnose_food_poisoning():
    print("You have food poisoning")
if diagnose_appendicitis():
    print("You have appendicitis")
