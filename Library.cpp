#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

/* ---- Functions Declare ----*/

string lowerCase(string str);
string normalizeZone(string zone);
string capitalizeWords(string s);
string normalizeLevel(string level);
string normalizeID(string id);

bool checkID(const string &id);
bool checkText(const string &s);
bool checkLevel(const string &s);
bool checkZone(const string &s);
bool isNumber(const string &s);
bool checkPage(const string &s);
bool checkQuantity(const string &s);



/* ---- Functions Declare ----*/

/* ---- Classes ----*/

class Library{
	private : 
		string id;
		string title;
		string author;
		string quantity;
		string page;
		string level;
		string zone;
	public :
		vector<Library> bookHolder;
		vector<Library> find;
		vector<int> sort;
		Library(string id, string title, string author, string quantity, string page, string level, string zone){
			this->id = id;
			this->title = title;
			this->author = author;
			this->quantity = quantity;
			this->page = page;
			this->level = level;
			this->zone = zone;
		}

		int getQuantity(){return stoi(quantity);}

		void ReadFile();
		void View();
		void Write();
		void Find(const string str, const int choice);
		void Issue();
		void Return();
		void Add();
		void Sort();
};
class Borrowable: public Library {
	private : 
		string start;
		string end;
		string costumer;
	public :
		Borrowable(string id, string title, string author, string quantity, string level, string zone, string page, string start, string end, string costumer) :Library(id, title, author, quantity, page, level, zone) {
			this->start = start;
			this->end = end;
			this->costumer = costumer;
		}
		
};

/* ---- Classes ----*/

/* ---- Classes' Functions ----*/

void Library::ReadFile() {
	string buffer, id, title, author, quantity, page, level, zone;
	bookHolder.clear();
	
	ifstream file("library.txt");

	while (getline(file, buffer)) {
		getline(file, buffer, '|');
		id = buffer;
		getline(file, buffer, '|');
		title = buffer;
		getline(file, buffer, '|');
		author = buffer;
		getline(file, buffer, '|');
		quantity = buffer;
		getline(file, buffer, '|');
		page = buffer;
		getline(file, buffer, '|');
		level = buffer;
		getline(file, buffer, '|');
		zone = buffer;
		Library lib(id, title, author, quantity, page, level, zone);
		bookHolder.push_back(lib);
	}

	file.close();
}
void Library::View() {
	cout << "Here are the book titles\' list\n";
	cout << "---------------\n";

	for (vector<Library>::size_type i = 0; i < bookHolder.size(); i++) {
		cout << "\"" << bookHolder.at(i).title << "\" by " << bookHolder.at(i).author
		<< " with " << bookHolder.at(i).quantity << " books.\n";
	}

	cout << "---------------\n";
}
void Library::Write() {
	ofstream output("libraryCopy.txt");

	for (vector<Library>::size_type i = 0; i < bookHolder.size(); i++) {
		output << bookHolder.at(i).id << "|" << bookHolder.at(i).title << "|" 
		<< bookHolder.at(i).author << "|" << bookHolder.at(i).quantity << "|"
		<< bookHolder.at(i).page << "|\n";
	}

	output.close();
	cout << "Copied to \"libraryCopy.txt\"\n";
}
void Library::Find(const string str, const int choice) {
	find.clear();
	if (choice == 1) {
		for(vector<Library>::size_type i = 0; i < bookHolder.size(); i++){
			if (lowerCase(bookHolder.at(i).title).find(lowerCase(str)) != string::npos) {
				find.push_back(bookHolder.at(i));
			}
		}
	}
	else if (choice == 2) {
		for(vector<Library>::size_type i = 0; i < bookHolder.size(); i++){
			if(lowerCase(bookHolder.at(i).author).find(lowerCase(str)) != string::npos){
				find.push_back(bookHolder.at(i));
			} 
		}
	}
	int sum = 0;
	for (vector<Library>::size_type i = 0; i < find.size(); i++) {
		sum += stoi(find.at(i).quantity);
	}

	cout << "There are " << sum << " books match with your choice\n";
	if (sum != 0) {
		cout << "They are: \n";
		for (vector<Library>::size_type i = 0; i < find.size(); i++){
			cout << find.at(i).id << "|"<< "\"" << find.at(i).title << "\" by " << find.at(i).author
			<< " with " << find.at(i).quantity << " books in level: "
			<< find.at(i).level << " and zone: " << find.at(i).zone<< "\n";
		}
	}
}
void Library::Issue(){
	int amount;
	int sum = 0;
	string id_buffer;
	for(vector<Library>::size_type i = 0; i < find.size() ;i++){
		sum += stoi(find.at(i).quantity);
	}
	cout << "-------------------------------------------------\n";
	if(sum != 0){
		while(true){
		cout << "Please enter ID of book you want to return: ";
		cin >> id_buffer;
		if(isNumber(id_buffer)) break;
		}
		for(vector<Library>::size_type i = 0; i < bookHolder.size(); i++){
			if(id_buffer == bookHolder.at(i).id){
				cout << "Please enter amounts of book you want to borow ";
				cin >> amount;
				if(amount > stoi(bookHolder.at(i).quantity)|| amount < 0){
					cout << "Valid number\n";
				} else {
					amount = stoi(bookHolder.at(i).quantity) - amount;
					bookHolder.at(i).quantity = to_string(amount);
					
					cout << "----Borrow books successfully!----\n"; 
				}
			}
		}
	}else{
	cout << "Your book didn't exist'\n";
	}
}
void Library::Return(){
	int amount;
	int sum = 0;
	string id_buffer;
	for(vector<Library>::size_type i = 0; i < find.size() ;i++){
		sum += stoi(find.at(i).quantity);
	}
	cout << "-------------------------------------------------\n";
	if(sum != 0){
		while(true){
		cout << "Please enter ID of book you want to return: ";
		cin >> id_buffer;
		if(isNumber(id_buffer)) break;
		}
		for(vector<Library>::size_type i = 0; i < bookHolder.size(); i++){
			if(id_buffer == bookHolder.at(i).id){
				cout << "Please enter amounts of book you want to return ";
				cin >> amount;
				if(amount > stoi(bookHolder.at(i).quantity)|| amount < 0){
					cout << "Valid number\n";
				} else {
					amount = stoi(bookHolder.at(i).quantity) + amount;
					bookHolder.at(i).quantity = to_string(amount);
					
					cout << "----Issue books successfully!----\n"; 
				}
			}
		}
	}else{
	cout << "Your book didn't exist'\n";
	}
}
void Library::Add() {
    string id, title, author, level, zone, quantity, page;
	int check, index;
	int sum = 0;
    while (true) {
        cout << "Enter ID (maximum 4 digits): ";
        cin >> id;
        if (isNumber(id)) {
            while (id.size() < 4) id = "0" + id;
        }
        if (checkID(id)) break;
        cout << "Invalid ID please try again.\n";
    }
    cin.ignore();
    while (true) {
        cout << "Enter Book's Title: ";
        getline(cin, title);
        if (checkText(title)) {
            title = capitalizeWords(title);
            break;
        }
        cout << ".\n";
    }
    while (true) {
        cout << "Enter Book's Author: ";
        getline(cin, author);
        if (checkText(author)) {
            author = capitalizeWords(author);
            break;
        }
        cout << "Unknown Author, please try again.\n";
    }
	for(int i = 0; i < bookHolder.size(); i++){
		if((title == bookHolder.at(i).title) & (author == bookHolder.at(i).author)){
			check = 0;
			index = i;
		}
	}
	if(check == 1){
		while (true) {
			cout << "Enter Book's Level (1-10): ";
			cin >> level;
			if (checkLevel(level)) break;
			cout << "Invalid Level, please try again\n";
		}
		while (true) {
			cout << "Enter Book's Zone (A-Z): ";
			cin >> zone;
			if (checkZone(zone)) {
				zone[0] = toupper(zone[0]);
				break;
			}
			cout << "Invalid book's zone, please try again.\n";
		}
		while (true) {
			cout << "Enter Book's Quantity (<999): ";
			cin >> quantity;
			if (checkQuantity(quantity)) break;
			cout << "Invalid book's quantity, please try again.\n";
		}
		while (true) {
			cout << "Enter Book's Page (9999>x>0): ";
			cin >> page;
			if (checkPage(page)) break;
			cout << "Invalid book's page, please try again.\n";
		}
		cout << "\n--- Adding Book successfully ---\n";
		cout << "ID: " << id << endl;
		cout << "Title: " << title << endl;
		cout << "Author: " << author << endl;
		cout << "Level: " << level << endl;
		cout << "Zone: " << zone << endl;
		cout << "Quantity: " << quantity << endl;
		cout << "Page: " << page << endl;
	}
	if(check == 0){
		while (true) {
			cout << "Add Book's Quantity  (<999): ";
			cin >> quantity;
			if (checkQuantity(quantity)){
				sum = stoi(bookHolder.at(index).quantity) + stoi(quantity);
				bookHolder.at(index).quantity = to_string(sum);
				break;
			}
			cout << "Invalid book's quantity, please try again.\n";
		}
		cout << "Adding book's quantity successfully!\n";
	}
}
void Library::Sort(){
}
/* ---- Classes' Functions ----*/

/* ---- Functions Define ----*/

string lowerCase(string str) {
	string result = "";
	for (char i : str) {
		if ((65 <= (int) i) && ((int) i <= 90)) {
            i += 32;
        }
		result += i;
	}
	return result;
}

/*----Normalize variables-----*/
string normalizeZone(string zone) {
    if (zone.size() != 1) return "unknown";
    if (!isalpha(zone[0])) return "unknown";
    char c = toupper(zone[0]);
    if (c < 'A' || c > 'Z') return "unknown";
    return string(1, c);
}
string normalizeLevel(string level) {
    for (char c : level)
        if (!isdigit(c)) return "unknown";
    int x = stoi(level);
    return (1 <= x && x <= 10) ? level : "unknown";
}
string capitalizeWords(string s) {
    if (s.size() == 0) return "unknown";
    bool newWord = true;
    for (int i = 0; i < (int)s.size(); i++) {
        if (isspace(s[i])) {
            newWord = true;
        } else {
            if (newWord && isalpha(s[i])) {
                s[i] = toupper(s[i]);
                newWord = false;
            } else {
                s[i] = tolower(s[i]);
                newWord = false;
            }
        }
    }
    return s;
}
string normalizeID(string id) {
    for (char c : id) {
        if (!isdigit(c)) return "unknown";
    }
    int num = stoi(id);
    if (num < 0 || num > 9999) return "unknown";
    string res = to_string(num);
    while (res.length() < 4) res = "0" + res;
    return res;
}

/*----Check variables----*/
bool checkID(const string &id) {
    if (id.size() != 4) return false;
    for (char c : id) 
        if (!isdigit(c)) return false;
    return true;
}
bool checkText(const string &s) {
    return !s.empty();
}
bool checkLevel(const string &s) {
    if (s.empty()) return false;
    for (char c : s) if (!isdigit(c)) return false;
    int lv = stoi(s);
    return lv >= 1 && lv <= 10;
}
bool checkZone(const string &s) {
    return (s.size() == 1 && isalpha(s[0]) && toupper(s[0]) >= 'A' && toupper(s[0]) <= 'Z');
}
bool isNumber(const string &s) {
    if (s.empty()) return false;
    for (char c : s) if (!isdigit(c)) return false;
    return true;
}
bool checkPage(const string &s) {
    if (!isNumber(s)) return false;
    int p = stoi(s);
    return p > 0;
}
bool checkQuantity(const string &s) {
    if (!isNumber(s)) return false;
    int q = stoi(s);
    return q > 0 && q < 999;
}




/* ---- Functions Define ----*/
/* ----- Feature ----*/


int main() {

	int passcode;
    bool status = true;
	int quantitiesSum = 0;
    int choice;
    int searchChoice;
	string searchString;
    string id, title, author, quantity, page, level, zone;
    Library* librarian = new Library(id, title, author, quantity, page, level, zone);
    while(status){
		cout << "Enter passcode to start the programme: ";
		cin >> passcode;
		if (passcode == 1) {
			status = false;
			cout << "Welcome to library\n";
			librarian->ReadFile();
		}
		else {
			cout << "Wrong passcode, please try again\n";
		}
	}
	
	status = true;
    while (status) {

		cout << "\n";
        cout << "---------- Library ----------\n";
        cout << "|1. Number of books         |\n"; // Done
        cout << "|2. Store into other file   |\n"; // Done
        cout << "|3. View all books          |\n"; // Done
        cout << "|4. Find book               |\n"; // Done
        cout << "|5. Issue a book            |\n"; // Done
        cout << "|6. Return a book           |\n"; // Done
        cout << "|7. Sorting                 |\n"; // :)?
        cout << "|8. Add a new book          |\n"; // Undone
        cout << "|9. Exit                    |\n"; // Done
        cout << "-----------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
		cout << "\n";

        switch(choice) {
            case 1: {
                librarian->ReadFile();

				for (vector<Library>::size_type i = 0; i < librarian->bookHolder.size(); i++) {
					quantitiesSum += librarian->bookHolder.at(i).getQuantity();
				}

                cout << "There are " << librarian->bookHolder.size() << " book titles & " 
				<< quantitiesSum << " books in total\n"; 
				quantitiesSum = 0;
                break;
			}

            case 2: {
				librarian->Write();
                break;
			}

            case 3: {
                librarian->View();
                break;
			}

            case 4: {
				while(1) {
					cout << "--------------------------------------------\n";
					cout << "|Do you want to search by Title or Author  |\n";
					cout << "|1. Title                                  |\n";
					cout << "|2. Author                                 |\n";
					cout << "--------------------------------------------\n";
					cout << "Enter your choice: "; cin >> searchChoice;
					if (searchChoice == 1 || searchChoice == 2) {
						break;
					}
				}
				if(searchChoice == 1){
					while(true){
                	cout << "Title you want to search for: ";
					cin.ignore();
					getline(cin, searchString);
					if(checkText(searchString)){
						cout << "\n";
						librarian->Find(searchString, searchChoice);
						break;
						}
					else{cout << "Please try again.\n";}
					}
					break;
				} 
				else if (searchChoice == 2){
                	while(true){
                	cout << "Author you want to search for: ";
					cin.ignore();
					getline(cin, searchString);
					if(checkText(searchString)){
						cout << "\n";
						librarian->Find(searchString, searchChoice);
						break;
						}
					else{cout << "Please try again.\n";}
					}
					break;	
				}
			}
            case 5: {
                while(1) {
					cout << "-------------------------------------------------\n";
					cout << "|Do you want to issue a book by Title or Author  |\n";
					cout << "|1. Title                                        |\n";
					cout << "|2. Author                                       |\n";
					cout << "-------------------------------------------------\n";
					cout << "Enter your choice: "; cin >> searchChoice;
					if (searchChoice == 1 || searchChoice == 2) {
						break;
					}
				}
				if(searchChoice == 1){
                	while(true){
                	cout << "Title you want to search for: ";
					cin.ignore();
					getline(cin, searchString);
					if(checkText(searchString)){
						cout << "\n";
						librarian->Find(searchString, searchChoice);
						break;
						}
						cout << "Please try again.\n";
					}
				} 
				else if (searchChoice == 2){
                	while(true){
                	cout << "Author you want to search for: ";
					cin.ignore();
					getline(cin, searchString);
					if(checkText(searchString)){
						cout << "\n";
						librarian->Find(searchString, searchChoice);
						break;
						}
						cout << "Please try again.\n";
					}
				}
				librarian->Issue();
				searchChoice = 0;
                break;
			}

            case 6: {
                while(1) {
					cout << "-------------------------------------------------\n";
					cout << "|Do you want to issue a book by Title or Author  |\n";
					cout << "|1. Title                                        |\n";
					cout << "|2. Author                                       |\n";
					cout << "-------------------------------------------------\n";
					cout << "Enter your choice: "; cin >> searchChoice;
					if (searchChoice == 1 || searchChoice == 2) {
						break;
					}
				}
				if(searchChoice == 1){
                	while(true){
                	cout << "Title you want to search for: ";
					cin.ignore();
					getline(cin, searchString);
					if(checkText(searchString)){
						cout << "\n";
						librarian->Find(searchString, searchChoice);
						break;
						}
						cout << "Please try again.\n";
					}
				} 
				else if (searchChoice == 2){
                	while(true){
                	cout << "Author you want to search for: ";
					cin.ignore();
					getline(cin, searchString);
					if(checkText(searchString)){
						cout << "\n";
						librarian->Find(searchString, searchChoice);
						break;
						}
						cout << "Please try again.\n";
					}
				}
				librarian->Return();
				searchChoice = 0;
                break;
			}

            case 7: {
                while(1) {
					cout << "----------------------------------------------\n";
					cout << "|Do you want to sort by ID orTitle or Author  |\n";
					cout << "|1. ID                                        |\n";
					cout << "|2. Title                                     |\n";
					cout << "|3. Author                                    |\n";
					cout << "--------------------------------------------\n";
					cout << "Enter your choice: "; cin >> searchChoice;
					if (searchChoice == 1 || searchChoice == 2 || searchChoice == 3) {
						break;
					}
				}
				switch(searchChoice){
					case 1:{
						librarian->Sort();
						break;
					}
					case 2:{
						break;
					}
					case 3:{
						break;
					}
				}
				searchChoice = 0;
                break;
			}

            case 8: {
                librarian->Add();
                break;
			}

            case 9: {
                cout << "Thanks for comming have a good day !\n";
                status = false;
                break;
			}

			default: {
				cout << "Invalid syntax, please retry!";
			}
        }
    }
    return 0;
}

