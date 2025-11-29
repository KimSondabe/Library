#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

/* ---- Functions Declare ----*/

string lowerCase(string str);

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
		<< "with" << quantity << "books.\n";
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
		cout << "Please enter ID of book you want to borrow: ";
		cin >> id_buffer;
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
		cout << "Please enter ID of book you want to return: ";
		cin >> id_buffer;
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
        cout << "|5. Issue a book            |\n"; // Lay x quyen sach (Undone)
        cout << "|6. Return a book           |\n"; // Tra sach (Undone)
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
                	cout << "Title you want to search for: ";
					cin.ignore();
					getline(cin, searchString);
					cout << "\n";
					librarian->Find(searchString, searchChoice);
				} 
				else if (searchChoice == 2){
                	cout << "Author you want to search for: ";
					cin.ignore();
					getline(cin, searchString);
					cout << "\n";
					librarian->Find(searchString, searchChoice);
				}
                break;
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
                	cout << "Title you want to search for: ";
					cin.ignore();
					getline(cin, searchString);
					cout << "\n";
					librarian->Find(searchString, searchChoice);
				} 
				else if (searchChoice == 2){
                	cout << "Author you want to search for: ";
					cin.ignore();
					getline(cin, searchString);
					cout << "\n";
					librarian->Find(searchString, searchChoice);
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
                	cout << "Title you want to search for: ";
					cin.ignore();
					getline(cin, searchString);
					cout << "\n";
					librarian->Find(searchString, searchChoice);
				} 
				else if (searchChoice == 2){
                	cout << "Author you want to search for: ";
					cin.ignore();
					getline(cin, searchString);
					cout << "\n";
					librarian->Find(searchString, searchChoice);
				}
				librarian->Return();
				searchChoice = 0;
                break;
			}

            case 7: {
                cout << "7\n";
                break;
			}

            case 8: {
                cout << "8\n";
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
