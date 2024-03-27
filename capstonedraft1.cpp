#include <bits/stdc++.h>
using namespace std;

// Enumeration for club categories
enum ClubCategory { Arts, Technical, Social, General, Sports };

// Structure to represent a member
struct Member {
    string name;
    string student_id;
    vector<string> clubs;
};

// Hash table to store member information
unordered_map<string, Member> member_hash_table;

// Hash table to index members by club
unordered_map<string, vector<string>> club_index;

// Map to associate each club with its category
unordered_map<string, ClubCategory> club_categories = {
    {"Khoj", Arts}, {"Music_Club", Arts}, {"Dance_Club", Arts}, {"DA-IICT_Theatre", Arts}, {"Khelaiya_Club", Arts}, {"Photography_Club", Arts},
    {"Programming_Club", Technical}, {"GDSC", Technical}, {"IEEE_Student_Branch", Technical}, {"Electronics_Hobby_Club", Technical}, {"MSTC", Technical}, {"Muse_club", Technical}, {"AI_Club", Technical},
    {"Press_Club", Social}, {"Debate_Club", Social}, {"Sambhav", Social}, {"Heritage_Club", Social}, {"Radio_Club", Social},
    {"DCEI", General}, {"Business_Club", General}, {"Headrush", General},
    {"Chess_Club", Sports}, {"Cubing_Club", Sports}
};

// Function to add a new member
void add_member(const string& name, const string& student_id, const vector<string>& clubs) {
    Member member;
    member.name=name;
    member.student_id = student_id;
    member.clubs = clubs;
    member_hash_table[name] = member;

    // Update club index
    for (const string& club : clubs) {
        club_index[club].push_back(name);
    }
}

// Function to search for members by club name
void search_by_club_name(const string& club_name) {
    if (club_index.find(club_name) == club_index.end()) {
        cout << "Club not found" << endl;
        return;
    }

    const vector<string>& members = club_index[club_name];
    for (const string& member_name : members) {
        cout << "Member: " << member_name << ", ID: " << member_hash_table[member_name].student_id << endl;
    }
}

// Function to search for members by name
void search_by_member_name(const string& member_name) {
    auto it = member_hash_table.find(member_name);
    if (it != member_hash_table.end()) {
        Member& member = it->second;
        cout << "Member: " << member_name << ", ID: " << member.student_id << "\n";
        cout << "Clubs: ";
        for (int i = 0; i < member.clubs.size(); ++i) {
            cout << member.clubs[i];
            if (i != member.clubs.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    } else {
        cout << "Member not found" << endl;
    }
}

// Function to search for members by ID
void search_by_id(const string& student_id) {
    for (const auto& entry : member_hash_table) {
        if (entry.second.student_id == student_id) {
            cout << "Member: " << entry.first << ", ID: " << student_id << "\n";
            cout << "Clubs: ";
            const Member& member = entry.second;
            for (int i = 0; i < member.clubs.size(); ++i) {
                cout << member.clubs[i];
                if (i != member.clubs.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
            return;
        }
    }
    cout << "Member with ID " << student_id << " not found" << endl;
}

// Function to search for members by club category
void search_by_club_category(ClubCategory category) {
    string category_str;
    switch (category) {
        case Arts:
            category_str = "Arts";
            break;
        case Technical:
            category_str = "Technical";
            break;
        case Social:
            category_str = "Social";
            break;
        case General:
            category_str = "General";
            break;
        case Sports:
            category_str = "Sports";
            break;
        default:
            cout << "Invalid club category" << endl;
            return;
    }
    
    bool flage=false;
    for (const auto& entry : member_hash_table) {
        const Member& member = entry.second;
        for (const string& club : member.clubs) {
            if (club_categories[club] == category) {
                cout << "Member: " << member.name << ", ID: " << member.student_id << endl;
                flage=true;
            }
        }
    }
    if(!flage){
        cout << "No members found in the " << category_str << " category" << endl;
    }
}


int main() {
    ifstream inputFile("club_members.txt");
    if (!inputFile.is_open()) {
        cout << "Unable to open file" << endl;
        return 1;
    }

    // Read data from the file and populate member_hash_table and club_index
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string name, student_id, club;
        vector<string> clubs;
        ss >> name >> student_id;
        while (ss >> club) {
            clubs.push_back(club);
        }
        add_member(name, student_id, clubs);
    }
    inputFile.close();

     int choice=0;
    while(choice<5){    
        cout << "Select search type:" << endl;
        cout << "1. Search by club name" << endl;
        cout << "2. Search by member name" << endl;
        cout << "3. Search by member ID" << endl;
        cout << "4. Search by club category" << endl;
        cout << "5. Exit" << endl; // Added option to exit the program
        cout << "Enter your choice: ";
        cin >> choice;
        cout<<endl;
        // Perform search based on user choice
        switch (choice) {
            case 1: {
                string club_name;
                cout << "Enter club name: ";
                cin >> club_name;
                search_by_club_name(club_name);
                break;
            }
            case 2: {
                string member_name;
                cout << "Enter member name: ";
                cin >> member_name;
                search_by_member_name(member_name);
                break;
            }
            case 3: {
                string student_id;
                cout << "Enter member ID: ";
                cin >> student_id;
                search_by_id(student_id);
                break;
            }
            case 4: {
                cout << "Select club category:" << endl;
                cout << "1. Arts" << endl;
                cout << "2. Technical" << endl;
                cout << "3. Social" << endl;
                cout << "4. General" << endl;
                cout << "5. Sports" << endl;
                cout << "Enter category number: ";
                int category_choice;
                cin >> category_choice;
                search_by_club_category(static_cast<ClubCategory>(category_choice - 1));
                break;
            }
            case 5: // Exit the program
                cout << "Exiting the program..." << endl;
                return 0;
            default:
                cout << "Invalid choice" << endl;
                break;
        }
        cout<<endl;
    }
    return 0;
}
