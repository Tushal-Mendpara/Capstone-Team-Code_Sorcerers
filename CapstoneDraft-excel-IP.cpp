#include <bits/stdc++.h>
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
        cout<<"Unable to open club members file"<<endl;
        return;
    }
    memberFile<<endl;
    memberFile<<name<<","<<student_id;
    for(string& club : clubs){
        memberFile<<","<<club;
    }
    memberFile.close();
    cout<<"New member "<<name<<" added successfully"<<endl;
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
        cout<<"Unable to open club category file"<<endl;
        return;
    }
    categoryFile<<endl;
    categoryFile<<club_name<<",";
    string categoryFilestr=str_category(category);
    if(categoryFilestr==""){
        cout<<"Invalid club category"<<endl;
        return;
    }
    categoryFile<<categoryFilestr;
    categoryFile.close();
}

// Function to search for members by club name
void search_by_club_name(string& club_name){
    if(club_hash_table.find(club_name)==club_hash_table.end()){
        cout<<"Club not found"<<endl;
        return;
    }
    bool flage=false;
     vector<string>& members=club_hash_table[club_name].members;
    for(string& member_name : members){
        flage=true;
        cout<<"Member: "<<member_name<<",ID: "<<member_hash_table[member_name].student_id<<endl;
    }
    if(!flage) cout<<"This club has no members."<<endl;
}

// Function to search for members by name
void search_by_member_name(string& member_name){
    cout<<endl;
    auto it=member_hash_table.find(member_name);
    if(it!=member_hash_table.end()){
        Member& member=it->second;
        cout<<"Member: "<<member_name<<",ID: "<<member.student_id<<"\n";
        cout<<"Clubs: ";
        for(int i=0; i < member.clubs.size(); ++i){
            cout<<member.clubs[i];
            if(i!=member.clubs.size() - 1){
                cout<<",";
            }
        }
        cout<<endl;
    }
    else{
        cout<<"Member not found"<<endl;
    }
}

// Function to search for members by ID
void search_by_id(string& student_id){
    cout<<endl;
    for(auto& entry : member_hash_table){
        if(entry.second.student_id==student_id){
            cout<<"Member: "<<entry.first<<",ID: "<<student_id<<"\n";
            cout<<"Clubs: ";
             Member& member=entry.second;
            for(int i=0; i < member.clubs.size(); ++i){
                cout<<member.clubs[i];
                if(i!=member.clubs.size() - 1){
                    cout<<",";
                }
            }
            cout<<endl;
            return;
        }
    }
    cout<<"Member with ID "<<student_id<<" not found"<<endl;
}


// Function to search for members by club category
void search_by_club_category(ClubCategory category){
    cout<<endl;
    string category_str=str_category(category);
    if(category_str==""){
        cout<<"Invalid club category"<<endl;
        return;
    }
    bool flag=false;
    // Iterate through club hash table
    for(auto& entry : club_hash_table){
        club& current_club=entry.second;

        // Check if club belongs to the given category
        if(current_club.category==category){
            flag=true;
            cout<<"Club: "<<entry.first<<endl;
            string x=entry.first;
            search_by_club_name(x);
            cout<<endl;
        }
    }
    // If no clubs found in the given category
    if(!flag){
        cout << "No clubs found in the " << category_str << " category with members" << endl;
    }
}


void remove_member_by_id(string& student_id) {
    ifstream file("ClubMembersDetails.csv");
    if(!file.is_open()){
        cerr<<"Unable to open file"<<endl;
        return;
    }
    ofstream newFile("new_ClubMembersDetails.csv");
    if(!newFile.is_open()){
        cerr<<"Unable to create new file"<<endl;
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
        cout<<"Member with ID "<<student_id<<" has been successfully removed."<<endl;
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
    cout<<"Member with ID "<<student_id<<" not found."<<endl;
}

void print_category(void){
    cout<<"1. Arts"<<endl;
    cout<<"2. Technical"<<endl;
    cout<<"3. Social"<<endl;
    cout<<"4. General"<<endl;
    cout<<"5. Sports"<<endl;
}
int read_ClubMembersDetails(const char* filename){
    ifstream file(filename);
    if(!file.is_open()){
        cerr<<"Unable to open file"<<endl;
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
            clubs.push_back(club);
        }
        add_member(name,student_id,clubs);
    }

    file.close();

    return 0;
}
int read_ClubCategories(const char* filename){
    ifstream categoryFile(filename);
    if(!categoryFile.is_open()){
        cout<<"Unable to open club category file"<<endl;
        return 1;
    }

    // Read club categories from the file and populate club_categories map
    string club, category, line;
    unordered_set<ClubCategory> printedCategories; // Keep track of printed categories
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

    // Print categories along with their corresponding clubs
    cout<<"Categories and their corresponding clubs:"<<endl;
    for(auto& entry : club_hash_table) {
        // Check if category has been printed already
        if(printedCategories.find(entry.second.category)==printedCategories.end()) {
            cout<<"Category: "<<str_category(entry.second.category)<<endl;
            cout<<"Clubs: ";
            for(auto& clubEntry : club_hash_table) {
                if(clubEntry.second.category==entry.second.category) {
                    cout<<clubEntry.first<<", ";
                }
            }
            cout<<endl<<endl;
            printedCategories.insert(entry.second.category);
        }
    }
  
    return 0;
}

int main(){
    int x=0,y=0;
    y=read_ClubCategories("ClubCategoriesDetails.csv");
    x=read_ClubMembersDetails("ClubMembersDetails.csv"); 
    if(x==1 || y==1){
        return 0;
    }
    string pass="Daiict@2023";
    int choice=0;
    while(choice<8){    
        cout<<"Select Option from below:"<<endl;
        cout<<"1. Search by club name"<<endl;
        cout<<"2. Search by member name"<<endl;
        cout<<"3. Search by member ID"<<endl;
        cout<<"4. Search by club category"<<endl;
        cout<<"5. Add new club" <<endl;
        cout<<"6. Add new member" <<endl;
        cout<<"7. Remove member by ID"<<endl;
        cout<<"8. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        cout<<endl;
        // Perform search based on user choice
        switch(choice){
            case 1:{
                string club_name;
                cout<<"Enter club name: ";
                cin>>club_name;
                search_by_club_name(club_name);
                break;
            }
            case 2:{
                string member_name;
                cout<<"Enter member name: ";
                cin>>member_name;
                search_by_member_name(member_name);
                break;
            }
            case 3:{
                string student_id;
                cout<<"Enter member ID: ";
                cin>>student_id;
                search_by_id(student_id);
                break;
            }
            case 4:{
                cout<<"Select club category:"<<endl;
                print_category();
                cout<<"Enter category number: ";
                int category_choice;
                cin>>category_choice;
                search_by_club_category(static_cast<ClubCategory>(category_choice - 1));
                break;
            }
            case 5:{
                cout<<"Enter Password : ";
                string epass;
                cin>>epass;
                if(epass!=pass){
                    cout<<"Wrong Password"<<endl;
                    cout<<"You don't have access to add club"<<endl;
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
                    cout<<"Wrong Password"<<endl;
                    cout<<"You don't have access to add member"<<endl;
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
                    cout<<"Wrong Password"<<endl;
                    cout<<"You don't have access to add member"<<endl;
                    break;
                }
                string student_id;
                cout<<"Enter member ID to remove: ";
                cin>>student_id;
                remove_member_by_id(student_id);
                break;
            }
            case 8:
                cout<<"Exiting the program..."<<endl;
                return 0;
            default:
                cout<<"Invalid choice"<<endl;
                break;
        }
        cout<<endl;
    }
    return 0;
}
