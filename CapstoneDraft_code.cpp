#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

using namespace std;

// Enumeration for club categories
enum ClubCategory{Arts,Technical,Social,General,Sports};

// Structure to represent a member
struct Member{
    string name;
    string student_id;
    vector<string> clubs;
};

// Hash table to store member information
unordered_map<string,Member> member_hash_table;

struct club{
    ClubCategory category;
    vector<string> members;
};

// Hash table to index members by club
unordered_map<string,club> club_hash_table;


// Function to add a new member
void add_member(string& name,string& student_id,vector<string>& clubs){
    Member member;
    member.name=name;
    member.student_id=student_id;
    member.clubs=clubs;
    member_hash_table[name]=member;

    // Update club hashtable
    for(string& club_name : clubs){
       if(club_hash_table.find(club_name)!=club_hash_table.end()){
            club_hash_table[club_name].members.push_back(name);
        }
    }
}

void add_member_in_file(string& name,string& student_id,vector<string>& clubs){
    // Append member to the file
    ofstream memberFile("ClubMembersDetails.csv",ios::app);
    if(!memberFile.is_open()){
         cout<<"_____________________________________"<<endl;
        cout<<"|                                     |"<<endl;
        cout<<"|         Unable to open file         |"<<endl;
        cout<<"|_____________________________________|"<<endl;
        return;
    }
    memberFile<<endl;
    memberFile<<name<<","<<student_id;
    for(string& club : clubs){
        memberFile<<","<<club;
    }
    memberFile.close();
        cout<<" _____________________________________"<<endl;
        cout<<"|                                     |"<<endl;
        cout<<"|    New member added successfully    |"<<endl;
        cout<<"|_____________________________________|"<<endl;
    
}
string str_category(ClubCategory category){
    string category_str;
    switch(category){
        case Arts:
            return "Arts";
        case Technical:
            return "Technical";
        case Social:
            return "Social";
        case General:
            return "General";
        case Sports:
            return "Sports";
        default:
            return "";
    }
}

// Function to add a new club to the map and file
void add_new_club(string& club_name,ClubCategory category){
    // Append club and category to the file
    ofstream categoryFile("ClubCategoriesDetails.csv",ios::app);
    if(!categoryFile.is_open()){
        cout<< "_____________________________________"<<endl;
        cout<<"|                                     |"<<endl;
        cout<<"|         Unable to open file         |"<<endl;
        cout<<"|_____________________________________|"<<endl;
        return;
    }
    categoryFile<<endl;
    categoryFile<<club_name<<",";
    string categoryFilestr=str_category(category);
    if(categoryFilestr==""){
         cout<<"_____________________________________"<<endl;
        cout<<"|                                     |"<<endl;
        cout<<"|         INVALID CLUB CATEGORY       |"<<endl;
        cout<<"|_____________________________________|"<<endl;
        return;
    }
    categoryFile<<categoryFilestr;

    categoryFile.close();
        cout<<" _____________________________________"<<endl;
        cout<<"|                                     |"<<endl;
        cout<<"|     New club added successfully     |"<<endl;
        cout<<"|_____________________________________|"<<endl;
}

// Function to search for members by club name
void search_by_club_name(string club_name) {
    
    if (club_hash_table.find(club_name) == club_hash_table.end()) {
        cout << " _____________________________________" << endl;
        cout << "|                                     |" << endl;
        cout << "|          INVALID CLUB NAME          |" << endl;
        cout << "|_____________________________________|" << endl;
        return;
    }
    bool flag = false;
    vector<string>& members = club_hash_table[club_name].members;
    int maxNameLength = 14; // Maximum length for member name
    int maxIdLength = 14;   // Maximum length for ID
    for (string& member_name : members) {
        maxNameLength = max(maxNameLength, (int)member_name.length());
        maxIdLength = max(maxIdLength, (int)member_hash_table[member_name].student_id.length());
    }
    cout << endl;
    cout << "::::::: Club -> "<<club_name<<" :::::::"<<endl;
    cout << " ________________________________" << endl;
    cout << "| " << setw(maxNameLength) << left << "MEMBERS" << "| " << setw(maxIdLength) << left << "ID" << " |" << endl;
    cout << "|--------------------------------|" << endl;
    for (string& member_name : members) {
        flag = true;
        cout << "| " << setw(maxNameLength) << left << member_name << "| " << setw(maxIdLength) << left << member_hash_table[member_name].student_id << " |" << endl;
    }
    if (!flag) 
    cout << "|     This club has no members   |" << endl;
    cout << "|________________________________|" << endl;
}


// Function to search for members by name
void search_by_member_name() {
    string member_name;
    cout << "        Enter member name:";
    cin >> member_name;
    auto it = member_hash_table.find(member_name);
    if (it != member_hash_table.end()) {
        Member& member = it->second;
        int num_clubs = member.clubs.size();
        int max_length = max((int)member_name.length(), (int)member.student_id.length());
        cout << " _____________________________________" << endl;
        cout << "|                                     |" << endl;
        cout << "|             MEMBER DETAILS          |" << endl;
        cout << "|-------------------------------------|" << endl;
        cout << "|         Name: " << setw(22) << left << member_name << "|" << endl;
        cout << "|         ID:   " << setw(22) << left << member.student_id << "|" << endl;
        cout << "|         Clubs:                      |" << endl;
       
        for (int i = 0; i < num_clubs; ++i) {
        cout << "|           " << setw(26) << left << member.clubs[i] << "|" << endl;
        }
       
        cout << "|_____________________________________|" << endl;
    } else {
        cout << " _____________________________________" << endl;
        cout << "|                                     |" << endl;
        cout << "|         MEMBER NOT FOUND            |" << endl;
        cout << "|_____________________________________|" << endl;
    }
}

// Function to search for members by ID
void search_by_id() {
    string student_id;
    cout << "       Enter member ID: ";
    cin >> student_id;
    bool found = false;
    for (auto& entry : member_hash_table) {
        if (entry.second.student_id == student_id) {
            Member& member = entry.second;
            int num_clubs = member.clubs.size();
            int max_length = max((int)entry.first.length(), (int)student_id.length());
            cout << " _____________________________________" << endl;
            cout << "|                                     |" << endl;
            cout << "|             MEMBER DETAILS          |" << endl;
            cout << "|-------------------------------------|" << endl;
            cout << "|         Name: " << setw(22) << left <<entry.first << "|" << endl;
            cout << "|         ID:   " << setw(22) << left << student_id << "|" << endl;
            cout << "|         Clubs:                      |" << endl;
            for (int i = 0; i < num_clubs; ++i) {
            cout << "|           " << setw(26) << left << member.clubs[i] << "|" << endl;
            }

            cout << "|_____________________________________|" << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << " _____________________________________" << endl;
        cout << "|                                     |" << endl;
        cout << "|    Member of this id is not found   |" << endl;
        cout << "|_____________________________________|" << endl;
    }
}


void print_category(void){
    cout<<" __________________"<<endl;
    cout<<"|                  |"<<endl;
    cout<<"|    1. Arts       |"<<endl;
    cout<<"|    2. Technical  |"<<endl;
    cout<<"|    3. Social     |"<<endl;
    cout<<"|    4. General    |"<<endl;
    cout<<"|    5. Sports     |"<<endl;
    cout<<"|__________________|"<<endl;
}

// Function to search for members by club category
void search_by_club_category(){
    cout<<"         Select club category from below"<<endl;
    print_category();
    cout<<"         Enter category number: ";
    int category_choice;
    cin>>category_choice;
    ClubCategory category=static_cast<ClubCategory>(category_choice - 1);
    string category_str=str_category(category);
    if(category_str==""){
         cout<<"_____________________________________"<<endl;
        cout<<"|                                     |"<<endl;
        cout<<"|        INVALID CLUB CATEGORY        |"<<endl;
        cout<<"|_____________________________________|"<<endl;
        return;
    }

    cout<<"<<===|||| Category => "<<category_str<<" ||||===>>"<<endl;
         bool flage=false;
        //Iterate through each club in the category
        for(auto& club_entry : club_hash_table){
            if(club_entry.second.category==category){
                flage=true;
                string club_name=club_entry.first;
                search_by_club_name(club_name);
            }
        }
   
    if(!flage){
         cout<<"_____________________________________"<<endl;
        cout<<"|                                     |"<<endl;
        cout<<"|        CATEGORY HAS NO MEMBER       |"<<endl;
        cout<<"|_____________________________________|"<<endl;
    }
}

void view_all_members_by_club_and_category() {
    //Iterate through each club category
    for(int i=0;i<5;++i) {
        ClubCategory category=static_cast<ClubCategory>(i);
        string category_str=str_category(category);
        cout<<"<<===|||| Category => "<<category_str<<" ||||===>>"<<endl;

        //Iterate through each club in the category
        for(auto& club_entry : club_hash_table){
            if(club_entry.second.category==category){
                string club_name=club_entry.first;
                search_by_club_name(club_name);
            }
        }
        cout << endl;
    }
}

void remove_member_by_id(string& student_id) {
    ifstream file("ClubMembersDetails.csv");
    if(!file.is_open()){
        cerr<<"      Unable to open file"<<endl;
        return;
    }
    ofstream newFile("new_ClubMembersDetails.csv");
    if(!newFile.is_open()){
        cerr<<"      Unable to create new file"<<endl;
        file.close();
        return;
    }
    string line;
    bool found = false;
    while (getline(file,line)) {
        stringstream ss(line);
        string name,id,club;
        getline(ss,name,',');
        getline(ss,id,',');
        if (id == student_id) {
            found = true;
            continue;
        }
        newFile<<line<<endl;
    }
    file.close();
    newFile.close();
    if(remove("ClubMembersDetails.csv") != 0){
        cerr<<"Error deleting file"<<endl;
        return;
    }
    if(rename("new_ClubMembersDetails.csv","ClubMembersDetails.csv") != 0){
        cerr<<"Error renaming file"<<endl;
        return;
    }
    if (found) {
         cout<<" _____________________________________"<<endl;
        cout<<"|                                     |"<<endl;
        cout<<"|      Member of this id removed      |"<<endl;
        cout<<"|_____________________________________|"<<endl;
        for(auto it = member_hash_table.begin(); it != member_hash_table.end(); ++it){
            if(it->second.student_id==student_id){
                string member_name = it->first;
                for(const string& club : it->second.clubs){
                    if(club_hash_table.find(club)!=club_hash_table.end()){
                        auto& members=club_hash_table[club].members;
                        members.erase(remove(members.begin(),members.end(),member_name),members.end());
                    }
                }
                member_hash_table.erase(member_name);
                return;
            }
        }
    }
        cout<<" _____________________________________"<<endl;
        cout<<"|                                     |"<<endl;
        cout<<"|      Member of this id not found    |"<<endl;
        cout<<"|_____________________________________|"<<endl;
}


int read_ClubMembersDetails(const char* filename){
    ifstream file(filename);
    if(!file.is_open()){
        cerr<<"      Unable to open file"<<endl;
        return 1;
    }

    string line;
    while(getline(file,line)){
        stringstream ss(line);
        string name,student_id,club;
        vector<string> clubs;
        getline(ss,name,',');
        getline(ss,student_id,',');
        while(getline(ss,club,',')){
            if(!club.empty()) clubs.push_back(club);
        }
        add_member(name,student_id,clubs);
    }

    file.close();

    return 0;
}
int read_ClubCategories(const char* filename){
    ifstream categoryFile(filename);
    if(!categoryFile.is_open()){
        cout<<" _____________________________________"<<endl;
        cout<<"|                                     |"<<endl;
        cout<<"|         Unable to open file         |"<<endl;
        cout<<"|_____________________________________|"<<endl;
        return 1;
    }

    // Read club categories from the file and populate club_categories map
    string club, category, line;
    
    while(getline(categoryFile, line)){
        stringstream ss(line);
        getline(ss, club, ',');
        getline(ss, category, ',');
        ClubCategory x;
        if(category=="Arts"){
            x=Arts;
        }
        else if(category=="Technical"){
            x=Technical;
        }
        else if(category=="Social"){
            x=Social;
        }
        else if(category=="General"){
            x=General;
        }
        else if(category=="Sports"){
            x=Sports;
        }
        club_hash_table[club].category=x;
    }
    categoryFile.close();

    
    return 0;
}
void printclubandcategories() {
    // Print categories along with their corresponding clubs
    unordered_set<ClubCategory> printedCategories; // Keep track of printed categories

    cout << " _____________________________________" << endl;
    cout << "|                                     |" << endl;
    cout << "|  Categories and their corresponding |" << endl;
    cout << "|               clubs:                |" << endl;
    cout << "|_____________________________________|" << endl;
    for(auto& categoryEntry : club_hash_table) {
        // Check if category has been printed already
        if(printedCategories.find(categoryEntry.second.category) == printedCategories.end()) {
            cout << "|  Category: " << setw(14) << left << str_category(categoryEntry.second.category) << "           |" << endl;
            cout << "|  Clubs:                             |" << endl;
            for(auto& clubEntry : club_hash_table) {
                if(clubEntry.second.category == categoryEntry.second.category) {
                    cout << "|    - " << setw(30) << left << clubEntry.first << " |" << endl;
                }
            }
            cout << "|_____________________________________|" << endl;
            printedCategories.insert(categoryEntry.second.category);
        }
    }
    
}

int main(){
    
    system("cls");
    cout<<" _____________________________________"<<endl;
    cout<<"|                                     |"<<endl;
    cout<<"|   ENTERING THE CLUB MANAGER MENU    |"<<endl;
    cout<<"|_____________________________________|"<<endl;
    cout<<"                 ";
    for(int i=0;i<5;i++){
    Sleep(500);
    cout<<".";
    }
    system("cls");

    int x=0,y=0;
    y=read_ClubCategories("ClubCategoriesDetails.csv");
    x=read_ClubMembersDetails("ClubMembersDetails.csv"); 
    if(x==1 || y==1){
        return 0;
    }
    
    string pass="Daiict@2023";
    int choice=0;
    while(1){ 
        cout<<"\n\n    CLICK HERE AND PRESS ANY KEY TO GO TO MENU"<<endl;
        if(getch())
        system("cls");   
        
        cout<<" _____________________________________"<<endl;
        cout<<"|                                     |"<<endl;
        cout<<"|     Select any option from below:   |"<<endl;
        cout<<"|     1. Search by club name          |"<<endl;
        cout<<"|     2. Search by member name        |"<<endl;
        cout<<"|     3. Search by member ID          |"<<endl;
        cout<<"|     4. Search by club category      |"<<endl;
        cout<<"|     5. Add new club                 |"<<endl;
        cout<<"|     6. Add new member               |"<<endl;
        cout<<"|     7. Remove member by ID          |"<<endl;
        cout<<"|     8. View Club Category wise      |"<<endl;
        cout<<"|     9. View All members             |"<<endl;
        cout<<"|     10. Exit                        |"<<endl;
        cout<<"|_____________________________________|"<<endl;
        cout<<"      Enter your choice: ";
        cin>>choice;
        system("cls");
        // Perform search based on user choice
        switch(choice){
            case 1:{
                 string club_name;
                 cout << "        Enter club name here:";
                 cin >> club_name;
                search_by_club_name(club_name);
                break;
            }
            case 2:{ 
                search_by_member_name();
                break;
            }
            case 3:{
                search_by_id();
                break;
            }
            case 4:{
               
                search_by_club_category();
                break;
            }
            case 5:{
                cout<<"Enter Password : ";
                string epass;
                cin>>epass;
                if(epass!=pass){
                    cout<<" _____________________________________"<<endl;
                    cout<<"|                                     |"<<endl;
                    cout<<"|           WRONG PASSWORD            |"<<endl;
                    cout<<"|  YOU DON'T HAVE ACCESS TO ADD CLUB  |"<<endl;
                    cout<<"|_____________________________________|"<<endl;
                    break;
                }
                string club_name;
                int category_choice;
                cout<<"Enter the name of the new club: ";
                cin>>club_name;
                cout<<"Select category for the club:"<<endl;
                print_category();
                cout<<"Enter category number: ";
                cin>>category_choice;
                add_new_club(club_name,static_cast<ClubCategory>(category_choice - 1));
                club_hash_table[club_name].category=static_cast<ClubCategory>(category_choice-1);
                break;
            }
            case 6:{
                cout<<"Enter Password : ";
                string epass;
                cin>>epass;
                if(epass!=pass){
                    cout<<" _____________________________________"<<endl;
                    cout<<"|                                     |"<<endl;
                    cout<<"|           WRONG PASSWORD            |"<<endl;
                    cout<<"| YOU DON'T HAVE ACCESS TO ADD MEMBER |"<<endl;
                    cout<<"|_____________________________________|"<<endl;
                    break;
                }
                int num_of_club;
                vector<string> clubs;
                string name,ID;
                cout<<"Enter details of member,\nName: ";
                cin>>name;
                cout<< "ID: ";
                cin>>ID;
                cout<< "Total no of clubs: ";
                cin>>num_of_club;
                clubs.resize(num_of_club);
                cout<<"Enter clubs name(one by one) : "<<endl;
                for(int i=0;i<num_of_club;i++){
                    cin>>clubs[i];
                }
                add_member_in_file(name,ID,clubs);
                add_member(name,ID,clubs);
                break;
            }
            case 7:{ 
                cout<<"Enter Password : ";
                string epass;
                cin>>epass;
                if(epass!=pass){
                    cout<<" _____________________________________"<<endl;
                    cout<<"|                                     |"<<endl;
                    cout<<"|           WRONG PASSWORD            |"<<endl;
                    cout<<"|  YOU DON'T HAVE ACCESS TO REMOVE ID |"<<endl;
                    cout<<"|_____________________________________|"<<endl;
                    break;
                }
                string student_id;
                cout<<"Enter member ID to remove: ";
                cin>>student_id;
                remove_member_by_id(student_id);
                break;
            }
            case 8:{
                    printclubandcategories();
                    break;
            }
            case 9:{
                    view_all_members_by_club_and_category();
                    break;
            }
            case 10:{
                cout<<" _____________________________________"<<endl;
                cout<<"|                                     |"<<endl;
                cout<<"|      EXITING THE CLUB MANAGER       |"<<endl;
                cout<<"|_____________________________________|"<<endl;
                cout<<"                 ";
                for(int i=0;i<5;i++){
                Sleep(500);
                cout<<".";
                }
                system("cls");
                cout<<" _____________________________________"<<endl;
                cout<<"|                                     |"<<endl;
                cout<<"|            THANK YOU :)             |"<<endl;
                cout<<"|_____________________________________|"<<endl;
                return 0;
            }
            default:{
                cout<<" _____________________________________"<<endl;
                cout<<"|                                     |"<<endl;
                cout<<"|            INVALID CHOICE           |"<<endl;
                cout<<"|_____________________________________|"<<endl;
            }
        }
    }
    return 0;
}
