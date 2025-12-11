#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
/* ---- Classes ----*/
class Books{
	private : 
		string id;
		string title;
		string author;
		string quantity;
		string page;
		string level;
		string zone;
	public :
		Books(string id, string title, string author, string quantity, string page, string level, string zone){
			this->id = id;
			this->title = title;
			this->author = author;
			this->quantity = quantity;
			this->page = page;
			this->level = level;
			this->zone = zone;
		}

		/* ---- Getters ----*/
		string getID() {
			return id;
		}
		string getTitle() {
			return title;
		}
		string getAuthor() {
			return author;
		}
		int getQuantity() { 
			return stoi(quantity);
		}
		int getPages() {
			return stoi(page);
		}
		int getLevel() {
			return stoi(level);
		}
		string getZone() {
			return zone;
		}	
		/* ---- Getters ----*/

		/* ---- Setters ----*/
		void changeQuantity(int quantity) {
			quantity += stoi(this->quantity);
			this->quantity = ((quantity < 0) || (quantity > 999)) ? "0" : to_string(quantity);	
		}
		/* ---- Setters ----*/
};
// class BorrowableBook: public Books {
// 	private: 
// 		string borrowDate;
// 	public:
// 		BorrowableBook(string id, string title, string author, string quantity, string page, string level, string zone) :Books(id, title, author, quantity, page, level, zone) {
// 			-+7
// 		}
// };
/* ---- Classes ----*/
/* ---- Functions Declare ----*/
void ReadFile(vector<Books*> &bookHolder);
void Write(const string filename, vector<Books*> &bookHolder);
void Find(vector<Books*> &bookHolder, vector<Books*> &foundedBook, const string str, const int choice);
void Find(vector<Books*> &bookHolder, vector<Books*> &foundedBook, const string title, const string author);
void Add(vector<Books*> &bookHolder, vector<Books*> &foundedBook);

string lowerCase(string str);
bool capitalizeWords(string &s);
string idCounter(string prevID);
/* ---- Functions Declare ----*/
/* ---- Classes' Functions ----*/

void ReadFile(vector<Books*> &bookHolder) {
	string buffer;
	string bookInfo[7];
	bookHolder.clear();

	// Read main book file
	ifstream file("library.txt");
	while (getline(file, buffer)) {
		for (int i = 0; i < 7; i++) {
			getline(file, buffer, '|');
			bookInfo[i] = buffer;
		}
		if (bookInfo[0] != "") {
			Books* book = new Books(bookInfo[0], bookInfo[1], bookInfo[2], bookInfo[3], bookInfo[4], bookInfo[5], bookInfo[6]);
			bookHolder.push_back(book);
		}
	}
	file.close();

}

void Write(const string filename, vector<Books*> &bookHolder) {
	ofstream output(filename);

	output << "*BLANK*\n";
	for (int i = 0; i < (int) bookHolder.size(); i++) {
		output << bookHolder.at(i)->getID() << "|" << bookHolder.at(i)->getTitle() << "|" 
		<< bookHolder.at(i)->getAuthor() << "|" << bookHolder.at(i)->getQuantity() << "|"
		<< bookHolder.at(i)->getPages() << "|" << bookHolder.at(i)->getLevel() << "|"
		<< bookHolder.at(i)->getZone() << "|\n";
	}	

	output.close();
	cout << "Wrote to \"" << filename << "\"\n";
}

void Find(vector<Books*> &bookHolder, vector<Books*> &foundedBook, const string str, const int choice) {
	
	// Check for same title/author in original vector -> push to vector "foundedBook"
	foundedBook.clear();
	if (choice == 1) {
		for (int i = 0; i < (int) bookHolder.size(); i++) {
			if (lowerCase(bookHolder.at(i)->getTitle()).find(lowerCase(str)) != string::npos) {
				foundedBook.push_back(bookHolder.at(i));
			}
		}
	}
	else if (choice == 2) {
		for (int i = 0; i < (int) bookHolder.size(); i++) {
			if(lowerCase(bookHolder.at(i)->getAuthor()).find(lowerCase(str)) != string::npos){
				foundedBook.push_back(bookHolder.at(i));
			} 
		}
	}

}

void Find(vector<Books*> &bookHolder, vector<Books*> &foundedBook, const string title, const string author) {
	foundedBook.clear();
	for (int i = 0; i < (int) bookHolder.size(); i++){
			if((lowerCase(bookHolder.at(i)->getAuthor()).find(lowerCase(author)) != string::npos)
			&& (lowerCase(bookHolder.at(i)->getTitle()).find(lowerCase(title)) != string::npos)){
				foundedBook.push_back(bookHolder.at(i));
		} 
	}
}

// void Borrow(vector<Books*> &bookHolder, vector<Books*> &foundedBook){ // In progress
// 	// Missing customer, date, merging info with bookHolder
// 	int amount;
// 	int sum = 0;
// 	string id_buffer;

// 	for (int i = 0; i < (int) foundedBook.size(); i++) {
// 		sum += foundedBook.at(i)->getQuantity();
// 	}
// 	cout << "-------------------------------------------------\n";

// 	if (sum != 0) {
// 		while (true) {
// 			cout << "Please enter ID of book you want to borrow: ";
// 			cin >> id_buffer;
// 			if(isNumber(id_buffer)) break; // ?????
// 		}

// 		for (int i = 0; i < (int) bookHolder.size(); i++){
// 			if(id_buffer == bookHolder.at(i)->getID()){
// 				cout << "Please enter amounts of book you want to borow ";
// 				cin >> amount;
// 				if (amount > bookHolder.at(i)->getQuantity() || amount < 0) { 
// 					cout << "Invalid number\n";
// 				} 
// 				else {
// 					bookHolder.at(i)->setQuantity(bookHolder.at(i)->getQuantity() - amount);				
// 					cout << "----Borrow books successfully!----\n"; 
// 				}
// 			}
// 		}
// 	}

// 	else {
// 		cout << "Your book didn't exist'\n";
// 	}
// }

// void Return(vector<Books*> &bookHolder, vector<Books*> &foundedBook){ // In progress
// 	int amount;
// 	int sum = 0;
// 	string id_buffer;

// 	for (int i = 0; i < (int) foundedBook.size() ;i++){
// 		sum += foundedBook.at(i)->getQuantity();
// 	}

// 	cout << "-------------------------------------------------\n";
// 	if (sum != 0) {
// 		while (true) {
// 			cout << "Please enter ID of book you want to return: ";
// 			cin >> id_buffer;
// 			if (isNumber(id_buffer)) break; // ????
// 		}
// 		for(int i = 0; i < (int) bookHolder.size(); i++){
// 			if(id_buffer == bookHolder.at(i)->getID()){
// 				cout << "Please enter amounts of book you want to return ";
// 				cin >> amount;
// 				if(amount > bookHolder.at(i)->getQuantity()|| amount < 0){
// 					cout << "Invalid number\n";
// 				} else {
// 					bookHolder.at(i)->setQuantity(bookHolder.at(i)->getQuantity() - amount);				
// 					cout << "----Borrow books successfully!----\n"; 
// 				}
// 			}
// 		}
// 	}
// 	else {
// 		cout << "Your book didn't exist'\n";
// 	}
// }

void Add(vector<Books*> &bookHolder, vector<Books*> &foundedBook) {
    string id, title, author, zone;
	int quantity, level, page;

	// Checking book's title and author
    while (true) {
        cout << "Enter Book's Title: ";
        getline(cin, title);
        if (capitalizeWords(title)) break;
        cout << "Invalid input, please try again!\n";
    }

    while (true) {
        cout << "Enter Book's Author: ";
        getline(cin, author);
        if (capitalizeWords(author)) break;
        cout << "Invalid input, please try again!\n";
    }

	Find(bookHolder, foundedBook, title, author); // foundedBook book with the same title & author

	while (true) {
		cout << "Enter Book's Quantity (<= 999): ";
		cin >> quantity;
		cin.ignore();
		if ((quantity > 0) && (quantity < 999)) {
			if (!foundedBook.empty()) { // If there is a book in vector "foundedBook"
				for (int i = 0; i < (int) bookHolder.size(); i++){
					if ((bookHolder.at(i)->getID() == foundedBook.front()->getID())) {
						bookHolder.at(i)->changeQuantity(quantity);
						cout << "Added " << quantity << " book(s) successfully!\n";
						break;
					}
				}
				return;
			}
			break;
		}
		cout << "Invalid input, please try again.\n";
	}

	while (true) {
		cout << "Enter Book's Page (0 < page < 9999): ";
		cin >> page;
		cin.ignore();
		if ((page > 0) && (page < 9999)) break;
		cout << "Invalid input, please try again.\n";
	}

	while (true) {
		cout << "Enter Book's Level (1-10): ";
		cin >> level;
		cin.ignore();
		if ((level >= 1) && (level <= 10)) break;
		cout << "Invalid input, please try again\n";
	}

	while (true) {
		cout << "Enter Book's Zone (A-Z): ";
		cin >> zone;
		if ((zone.length() == 1) && (zone[0] >= 'A') && (zone[0] <= 'Z')) break;
		cout << "Invalid input, please try again.\n";
	}

	id = idCounter(bookHolder.back()->getID());
	Books* book = new Books(id, title, author, to_string(quantity), to_string(page), to_string(level), zone);
	bookHolder.push_back(book);
	cout << "\n--- Added Book successfully ---\n";
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

bool capitalizeWords(string &str) {
    if (str.size() == 0) return false;
    bool newWord = true;
    for (int i = 0; i < (int) str.size(); i++) {
        if (isspace(str[i])) {
            newWord = true;
        } 
		else {
            if (newWord && isalpha(str[i])) {
                str[i] = toupper(str[i]);
                newWord = false;
            } 
			else {
                str[i] = tolower(str[i]);
                newWord = false;
            }
        }
    }
    return true;
}

string idCounter(string prevID) {
    if (prevID.size() != 4) return "";
    for (char c : prevID) { 
        if (!isdigit(c)) return "";
	}
	string upComingID = to_string((stoi(prevID) + 1));
	if (upComingID.length() > 4) {
		cout << "Out of storage!\n";
		return "";
	}
	while (upComingID.length() < 4) {
		upComingID = "0" + upComingID;
	}
    return upComingID;
}
/* ---- Functions Define ----*/

int main() {

	int passcode;
    bool status = true;
	int quantitiesSum = 0;
    int choice;
    int inputNumber;
	string inputString;
    vector<Books*> bookHolder;
	vector<Books*> foundedBook;

	// Enter passcode + read file to fill bookHolder
    while(status){
		cout << "Enter passcode to start the programme: ";
		cin >> passcode;
		cin.ignore();
		if (passcode == 1) {
			status = false;
			cout << "\nWelcome to library\n";
			ReadFile(bookHolder);
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
        cout << "|5. Borrow a book           |\n"; // In Progress
        cout << "|6. Return a book           |\n"; // In Progress
        cout << "|7. Report book's issue     |\n"; // Undone
        cout << "|8. Add book(s)             |\n"; // Done
        cout << "|9. Exit                    |\n"; // Done
        cout << "-----------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
		cin.ignore();
		cout << "\n";

        switch(choice) {
            case 1: { 
				for (int i = 0; i < (int) bookHolder.size(); i++) {
					quantitiesSum += bookHolder.at(i)->getQuantity();
				}
                cout << "There are " << bookHolder.size() << " book titles & " 
				<< quantitiesSum << " books in total\n"; 
				quantitiesSum = 0;
                break;
			}

            case 2: {
				Write("libraryCopy.txt", bookHolder);
                break;
			}

            case 3: {
                cout << "Here are the book titles\' list\n";
				cout << "---------------\n";
				for (int i = 0; i < (int) bookHolder.size(); i++) {
					cout << "\"" << bookHolder.at(i)->getTitle() << "\" by " << bookHolder.at(i)->getAuthor()
					<< " with " << bookHolder.at(i)->getQuantity() << " books.\n";
				}
				cout << "---------------\n";
                break;
			}

            case 4: {
				do {
					cout << "--------------------------------------------\n";
					cout << "|Do you want to search by Title or Author  |\n";
					cout << "|1. Title                                  |\n";
					cout << "|2. Author                                 |\n";
					cout << "--------------------------------------------\n";
					cout << "Enter your choice: "; 
					cin >> inputNumber;
					cin.ignore();
				} while ((inputNumber != 1) && (inputNumber != 2));
				
				if (inputNumber == 1) {
					while (true) {
                		cout << "Title you want to search for: ";
						getline(cin, inputString);
						if (inputString != "") {
							cout << "\n";
							Find(bookHolder, foundedBook, inputString, inputNumber);
							break;
						}
						else {
							cout << "Please try again.\n";
						}
					}
				} 
				else if (inputNumber == 2) {
                	while(true){
                		cout << "Author you want to search for: ";
						getline(cin, inputString);
						if (inputString != "") {
							cout << "\n";
							Find(bookHolder, foundedBook, inputString, inputNumber);
							break;
						}
						else {
							cout << "Please try again.\n";
						}
					}	
				}

				if (foundedBook.empty()) {
					cout << "There are no book match with your search!\n";
					break;
				}

				cout << "The book(s) you want to search for are:\n";
				for (int i = 0; i < (int) foundedBook.size(); i++) {
					cout << "\"" << foundedBook.at(i)->getTitle() << "\" by " << foundedBook.at(i)->getAuthor() << " with " << foundedBook.at(i)->getQuantity()
					<< " books in level \'" << foundedBook.at(i)->getLevel() << "\' and zone \'" << foundedBook.at(i)->getZone() << "\'!\n"; 
				}
				break;
			}
            
			// case 5: {
		
            //     while(1) {
			// 		cout << "-------------------------------------------------\n";
			// 		cout << "|Do you want to borrow a book by Title or Author  |\n";
			// 		cout << "|1. Title                                        |\n";
			// 		cout << "|2. Author                                       |\n";
			// 		cout << "-------------------------------------------------\n";
			// 		cout << "Enter your choice: "; 
			// 		cin >> inputNumber;
			// 		if (inputNumber == 1 || inputNumber == 2) {
			// 			break;
			// 		}
			// 	}
			// 	if(inputNumber == 1){
            //     	while (true) {
			// 			cout << "Title you want to search for: ";
			// 			cin.ignore();
			// 			getline(cin, inputString);
			// 			if (inputString == "") {
			// 				cout << "\n";
			// 				Find(bookHolder, foundedBook, inputString, inputNumber);
			// 				break;
			// 			}
			// 			cout << "Please try again.\n";
			// 		}
			// 	} 
			// 	else if (inputNumber == 2){
            //     	while(true){
			// 			cout << "Author you want to search for: ";
			// 			cin.ignore();
			// 			getline(cin, inputString);
			// 			if (inputString == "") {
			// 				cout << "\n";
			// 				Find(bookHolder, foundedBook, inputString, inputNumber);
			// 				break;
			// 			}
			// 				cout << "Please try again.\n";
			// 		}
			// 	}
			// 	Borrow(bookHolder, foundedBook);
            //     break;
			// }

            // case 6: {
		
            //     while(1) {
			// 		cout << "-------------------------------------------------\n";
			// 		cout << "|Do you want to return a book by Title or Author |\n";
			// 		cout << "|1. Title                                        |\n";
			// 		cout << "|2. Author                                       |\n";
			// 		cout << "-------------------------------------------------\n";
			// 		cout << "Enter your choice: "; 
			// 		cin >> inputNumber;
			// 		if (inputNumber == 1 || inputNumber == 2) {
			// 			break;
			// 		}
			// 	}
			// 	if(inputNumber == 1){
            //     	while(true){
			// 			cout << "Title you want to search for: ";
			// 			cin.ignore();
			// 			getline(cin, inputString);
			// 			if (inputString == "") {
			// 				cout << "\n";
			// 				Find(bookHolder, foundedBook, inputString, inputNumber);
			// 				break;
			// 			}
			// 			cout << "Please try again.\n";
			// 		}
			// 	} 
			// 	else if (inputNumber == 2){
            //     	while(true){
			// 			cout << "Author you want to search for: ";
			// 			cin.ignore();
			// 			getline(cin, inputString);
			// 			if(inputString == ""){
			// 				cout << "\n";
			// 				Find(bookHolder, foundedBook, inputString, inputNumber);
			// 				break;
			// 			}
			// 			cout << "Please try again.\n";
			// 		}
			// 	}
			// 	Return(bookHolder, foundedBook);
            //     break;
			// }

            case 7: {
                while (true) {
					cout << "Please enter the book(s) ID you want to report (xxxx): ";
					cin >> inputString;
					for (char i : inputString) {
						if (!isdigit(i)) inputString += "filler";
					}
					if (inputString.length() != 4) continue;
					if (stoi(bookHolder.back()->getID()) >= stoi(inputString)) break;
					cout << "Invalid input, please try again.\n";
				}
				
				for (int i = 0; i < (int) bookHolder.size(); i++) {
					if (bookHolder.at(i)->getID() == inputString) {
						while (true) {
							cout << "Please enter number of book you want to report: ";
							cin >> inputNumber;
							cin.ignore();
							if (bookHolder.at(i)->getQuantity() >= inputNumber) {
								bookHolder.at(i)->changeQuantity(-inputNumber);
								cout << "Reported successfully " << inputNumber << " book(s)";
								break;
							}
							cout << "Invalid input, please try again.\n";
						}
						break;
					}
				}
                break;
			}

            case 8: {
                Add(bookHolder, foundedBook);
                break;
			}

            case 9: {
				Write("library.txt", bookHolder);
				for (int i = 0; i < (int) bookHolder.size(); i++) { // Clean up data
					delete bookHolder.at(i);
				}
				cout << "\nThanks for comming have a good day !\n";
                status = false;
                break;
			}

			default: {
				cout << "Invalid syntax, please retry!\n";
			}
        }
    }
    return 0;
}

