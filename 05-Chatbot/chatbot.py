search_tree = {
    "Admission": {
        "Cutoff": "The cutoff is > 99 percentile for MHTCET. For more info, refer https://pict.edu/cutoff-FE/",
        "Fee": "The fees is 93K for open-category candidates. For more info, refer https://pict.edu/fee-structure/",
        "Branch": "Branches are COMP, IT, EnTC, ECE, AIDS",
    },

    "Hostel": "The campus has a girls and boys hostel in-premises. For more info, refer https://pict.edu/hostel/",
    "Placement": {
        "Statistic": "For this year, 706 students are placed. For detailed statistics, refer https://pict.edu/placement/index.php#statistics",
        "Training": "https://pict.edu/placement/index.php#trainingactivities",
    },

    "Library": "PICT central library being information hub provides access to full text, digital and printed resources to support the scholarly and informational needs of the students, faculty, researchers, and other users.",
    "Timetable": "https://pict.edu/time_table_syllabus/",
    "Syllabus": "https://pict.edu/time_table_syllabus/",
}

def search(query, subtree):
    query = query.lower()  # Convert query to lowercase
    if type(subtree) == str:
        print(f"Reply: {subtree}")
        print("-------------")
        return
    
    found = False
    for child in subtree:
        if child.lower() in query:
            search(query, subtree[child])
            found = True
            break
    
    if not found:
        print("Could not understand context.")
        if isinstance(subtree, dict):
            print(f"For this category, the options are: {', '.join(subtree.keys())}")

while True:
    question = input("Enter your query: ")
    search(question, search_tree)
