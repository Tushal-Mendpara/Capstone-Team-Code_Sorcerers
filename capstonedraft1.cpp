#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Structure to represent a member
struct Member {
    string student_id;
    vector<string> clubs;
};

// Hash table to store member information
unordered_map<string, Member> member_hash_table;

// Hash table to index members by club
unordered_map<string, vector<string>> club_index;

// Function to add a new member
void add_member(string name, string student_id, const vector<string>& clubs) {
    Member member;
    member.student_id = student_id;
    member.clubs = clubs;
    member_hash_table[name] = member;
    
    // Update club index
    for (const string& club : clubs) {
        club_index[club].push_back(name);
    }
}

// Function to search for members by club name
void search_by_club_name(string club_name) {
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
void search_by_member_name(string member_name) {
    if (member_hash_table.find(member_name) == member_hash_table.end()) {
        cout << "Member not found" << endl;
        return;
    }
    
    Member& member = member_hash_table[member_name];
    cout << "Member: " << member_name << ", ID: " << member.student_id << endl;
    for (const string& club : member.clubs) {
        cout << "Club: " << club << endl;
    }
}

// Function to search for members by ID
void search_by_id(string student_id) {
    for (const auto& entry : member_hash_table) {
        if (entry.second.student_id == student_id) {
            cout << "Member: " << entry.first << ", ID: " << student_id << endl;
            for (const string& club : entry.second.clubs) {
                cout << "Club: " << club << endl;
            }
            return;
        }
    }
    cout << "Member with ID " << student_id << " not found" << endl;
}

int main() {
    // Example usage
    add_member("John Doe", "123456", {"Science Club", "Chess Club"});
    add_member("Alice Smith", "789012", {"Arts Club", "Music Club"});
    add_member("Bob Johnson", "345678", {"Sports Club"});
    add_member("manav", "202358", {"Science Club"});
    // Searching by club name
    cout << "Searching by club name (Science Club):" << endl;
    search_by_club_name("Science Club");
    
    // Searching by member name
    cout << "\nSearching by member name (Alice Smith):" << endl;
    search_by_member_name("Alice Smith");

    // Searching by member ID
    cout << "\nSearching by ID (789012):" << endl;
    search_by_id("789012");
    
    return 0;
}
