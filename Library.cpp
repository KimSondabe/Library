#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

typedef struct {
	string name;
	string customerID;
	string borrowDay;
} customerInfo;

typedef struct {
	string bookID;
	string borrowQuantity;
	customerInfo info;
} BorrowedBookInfo;

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
		vector<customerInfo> customerList;
		
		Books(string id, string title, string author, string quantity, string page, string level, string zone, vector<customerInfo> customerList){
			this->id = id;
			this->title = title;
			this->author = author;
			this->quantity = quantity;
			this->page = page;
			this->level = level;
			this->zone = zone;
			this->customerList = customerList;
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
/* ---- Classes ----*/

/* ---- Functions Declare ----*/
void ReadFile(vector<Books*> &bookHolder, vector<BorrowedBookInfo> &borrowedHolder); // Read data from file
void Write(const string filename, vector<Books*> &bookHolder); // Write data to file
void Write(const string filename, vector<Books*> &bookHolder, vector<BorrowedBookInfo> &borrowedHolder); // Write data to file (overload)
void Find(vector<Books*> &bookHolder, vector<Books*> &foundedBook, const string str, const int choice); // Find book by title/author
void Find(vector<Books*> &bookHolder, vector<Books*> &foundedBook, const string title, const string author); // Find book by title & author
void Add(vector<Books*> &bookHolder, vector<Books*> &foundedBook); // Add book(s)
void Borrow(vector<Books*> &bookHolder, vector<BorrowedBookInfo> &borrowedHolder, const string today, string &inputString); // Borrow book(s)
void Return(vector<Books*> &bookHolder, vector<BorrowedBookInfo> &borrowedHolder, const string today, string &inputString); // Return book(s)

string lowerCase(string str); // Convert string to lower case
bool capitalizeWords(string &s); // Capitalize first letter of each word
string idCounter(string prevID); // Generate next ID
void idInputChecker(vector<Books*> &bookHolder, string &inputString); // Check valid book ID input
bool isLeap(int year); // Check leap year
int daysInMonth(int month, int year); // Check number of days in month
bool dayFormatCheck(string &str); // Check if user has inserted the right dd/mm/yyyy format and normalize
/* ---- Functions Declare ----*/

/* ---- Functions Definition ----*/

void ReadFile(vector<Books*> &bookHolder, vector<BorrowedBookInfo> &borrowedHolder) {
	string buffer, bookInfoList[7], borrowedInfoList[5];
	// book info list: id (0), title(1), author(2), quantity(3), page(4), level(5), zone(6).
	// borrowed info list: bookID(0), name(1), customerID(2), borrowDay(3), borrowQuantity(4).
	vector<customerInfo> customerList;
	bool borrowable = true;
	bookHolder.clear();
	borrowedHolder.clear();

	// Read borrowed books file
	ifstream fileBorrowed("borrowedBooks.txt");
	while(getline(fileBorrowed, buffer)) {
		for (int i = 0; i < 5; i++) {
			getline(fileBorrowed, buffer, '|');
			borrowedInfoList[i] = buffer;
		}
		if (borrowedInfoList[0] != "") {
			BorrowedBookInfo borrowedBook;
			borrowedBook.bookID = borrowedInfoList[0];
			borrowedBook.info.name = borrowedInfoList[1];
			borrowedBook.info.customerID = borrowedInfoList[2];
			borrowedBook.info.borrowDay = borrowedInfoList[3];
			borrowedBook.borrowQuantity = borrowedInfoList[4];
			borrowedHolder.push_back(borrowedBook);
		}
	}
	fileBorrowed.close();

	// Read main book file
	ifstream file("library.txt");
	while(getline(file, buffer)) {
		customerList.clear();
		for (int i = 0; i < 7; i++) {
			getline(file, buffer, '|');
			bookInfoList[i] = buffer;
		}
		if (bookInfoList[0] != "") {
			for (int i = 0; i < (int) borrowedHolder.size(); i++){
				if (borrowedHolder.at(i).bookID == bookInfoList[0]) { 
					// Store customer infomation into a vector
					customerList.push_back(borrowedHolder.at(i).info);
				}
			}
			Books* book = new Books(bookInfoList[0], bookInfoList[1], bookInfoList[2], bookInfoList[3], bookInfoList[4], bookInfoList[5], bookInfoList[6], customerList);
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

void Write(const string filename, vector<Books*> &bookHolder, vector<BorrowedBookInfo> &borrowedHolder) {
	Write(filename, bookHolder);

	// Write borrowed books file
	ofstream output("borrowedBooks.txt");

	output << "*BLANK*\n";
	for (int i = 0; i < (int) borrowedHolder.size(); i++) {
		output << borrowedHolder.at(i).bookID << "|" << borrowedHolder.at(i).info.name << "|" 
		<< borrowedHolder.at(i).info.customerID << "|" << borrowedHolder.at(i).info.borrowDay << "|"
		<< borrowedHolder.at(i).borrowQuantity << "|\n";
	}	

	output.close();
	cout << "Wrote to \"" << filename << "\" and \"borrowedBooks.txt\"\n";
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

void Add(vector<Books*> &bookHolder, vector<Books*> &foundedBook) {
    string id, title, author, zone;
	int quantity, level, page;

	// Checking book's title and author
	
    while(true) {
        cout << "Enter Book's Title: ";
        getline(cin, title);
        if (capitalizeWords(title)) break;
        cout << "Invalid input, please try again!\n";
    }

    while(true) {
        cout << "Enter Book's Author: ";
        getline(cin, author);
        if (capitalizeWords(author)) break;
        cout << "Invalid input, please try again!\n";
    }

	Find(bookHolder, foundedBook, title, author); // Check for same book title & author

	while(true) {
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

	while(true) {
		cout << "Enter Book's Page (0 < page < 9999): ";
		cin >> page;
		cin.ignore();
		if ((page > 0) && (page < 9999)) break;
		cout << "Invalid input, please try again.\n";
	}

	while(true) {
		cout << "Enter Book's Level (1-10): ";
		cin >> level;
		cin.ignore();
		if ((level >= 1) && (level <= 10)) break;
		cout << "Invalid input, please try again\n";
	}

	while(true) {
		cout << "Enter Book's Zone (A-Z): ";
		cin >> zone;
		if ((zone.length() == 1) && (zone[0] >= 'A') && (zone[0] <= 'Z')) break;
		cout << "Invalid input, please try again.\n";
	}

	id = idCounter(bookHolder.back()->getID());
	vector<customerInfo> customerList;
	Books* book = new Books(id, title, author, to_string(quantity), to_string(page), to_string(level), zone, customerList);
	bookHolder.push_back(book);
	cout << "\n--- Added Book successfully ---\n";
}

void Borrow(vector<Books*> &bookHolder, vector<BorrowedBookInfo> &borrowedHolder, const string today, string &inputString) {
	idInputChecker(bookHolder, inputString);
	string buffer;
	// borrowed info list: bookID(0), name(1), customerID(2), borrowDay(3), borrowQuantity(4).
	vector<string> customerIDlist;
    
	// Find the book in bookHolder
	for (int i = 0; i < (int) bookHolder.size(); i++) {
		if (bookHolder.at(i)->getID() == inputString) {
			if (bookHolder.at(i)->getQuantity() == 0) {
				cout << "Sorry, this book is out of stock!\n";
				return;
			}
			customerInfo newCustomer;
			cout << "Enter your name: ";
			cin.ignore();
			getline(cin, buffer);
			newCustomer.name = buffer;
			cout << "Enter your ID: ";
			getline(cin, buffer);
			newCustomer.customerID = buffer;
			newCustomer.borrowDay = today;
			bookHolder.at(i)->customerList.push_back(newCustomer);
			// Ask for quantity to borrow
			do {
				cout << "There are " << bookHolder.at(i)->getQuantity() << " book(s) available.\n";
				cout << "Enter number of book(s) you want to borrow: ";
				cin >> buffer;
				if ((stoi(buffer) > 0) && (stoi(buffer) <= bookHolder.at(i)->getQuantity())) {
					break;
				}
				cout << "Invalid input, please try again.\n";
			} while(true);

			// Add new borrowed book info to vector
			BorrowedBookInfo borrowedBook;
			borrowedBook.bookID = inputString;
			borrowedBook.info = newCustomer;
			borrowedBook.borrowQuantity = buffer;
			borrowedHolder.push_back(borrowedBook);
			bookHolder.at(i)->changeQuantity(-stoi(buffer));
			cout << "Book(s) borrowed successfully!\n";
			return;
		}
	}
}

void Return(vector<Books*> &bookHolder, vector<BorrowedBookInfo> &borrowedHolder, const string today, string &inputString) {
	idInputChecker(bookHolder, inputString);
	string inputName, buffer;
	// borrowed info list: bookID(0), name(1), customerID(2), borrowDay(3), borrowQuantity(4).
	vector<string> customerIDlist;

	// 
}

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
	while(upComingID.length() < 4) {
		upComingID = "0" + upComingID;
	}
    return upComingID;
}

void idInputChecker(vector<Books*> &bookHolder, string &inputString) {
	do {
		cout << "Please enter the book(s) ID you want to find (xxxx): ";
		cin >> inputString;
		for (char i : inputString) {
			if (!isdigit(i)) inputString += "filler";
		}
		if (inputString.length() != 4) {
			cout << "Invalid input, please try again.\n";
			continue;
		}
		bool found = false;
		for (int i = 0; i < (int) bookHolder.size(); i++) {
			if (bookHolder.at(i)->getID() == inputString) {
				found = true;
				break;
			}
		}
		if (found) break;
		cout << "Invalid input, please try again.\n";
	} while(true);
}

bool isLeap(int year) {
	return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

int daysInMonth(int month, int year) {
    switch(month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return isLeap(year) ? 29 : 28;
    }
    return 0;
}

bool dayFormatCheck(string &str) {
    string buffer, tempstr = "";
    if (str.find('/') == string::npos) return false;
    for (char i : str ) {
        if (i != '/') {
            buffer += i;
        }
        else {
            for (char j : buffer) {
                if ((j < '0') || (j > '9')) return false;
            }
            if (buffer.size() == 1) {
                if (buffer == "0") return false;
                else {
                    buffer = "0" + buffer;
                }
            }
            else if (buffer.size() < 1 || buffer.size() > 2) return false;
            tempstr += (buffer + "/");
            buffer = "";
        }
    }
    for (char i : buffer) {
        if ((i < '0') || (i > '9')) return false;
    }
    if (buffer.size() != 4) return false;

    string day, month;
    int count = 0;
    for (char i : tempstr) {
        if (i != '/') {
            if (count <= 1) {
                count++;
                day += i;
            }
            else {
                month += i;
            }
        }
    }
    
    if ((stoi(day) < 1) || (stoi(day) > daysInMonth(stoi(month), stoi(buffer)))) return false;
    str = tempstr + buffer;
    return true;
}
/* ---- Functions Definition ----*/

int main() {
	// Variables Declaration (If need more, declare in specific functions)
	int passcode;
    bool status = true;
	int quantitiesSum = 0;
    int choice;
    int inputNumber;
	string inputString, today;
    vector<Books*> bookHolder;
	vector<Books*> foundedBook;
	vector<BorrowedBookInfo> borrowedHolder;

	// Entrance interface (login, date input, file read)
	cout << "Today is: ";
	do {
		getline(cin, today);
		if (dayFormatCheck(today)) break;
		cout << "Invalid date format, please try again (dd/mm/yyyy): ";
	} while(true);
	cout << "Enter passcode to start the programme: ";
	do {
		cin >> passcode;
		cin.ignore();				
		if (passcode == 123456) {
			ReadFile(bookHolder, borrowedHolder);
			break;
		}
		else {
			cout << "Wrong passcode, please try again.\n";
		}
	} while(true);

	// Main interface
	status = true;
    while(status) {
		cout << "\n";
        cout << "---------- Library ----------\n";
        cout << "|1. Number of books           |\n"; // Done
        cout << "|2. Store into other file     |\n"; // Done
        cout << "|3. View all books            |\n"; // Done
        cout << "|4. Find book                 |\n"; // Done
        cout << "|5. Borrow book (s)           |\n"; // Done
        cout << "|6. Return book (s)           |\n"; // In Progress
		cout << "|7. Book borrowed-customer(s) |\n"; // Done
        cout << "|8. Report book's issue       |\n"; // Done
        cout << "|9. Add book(s)               |\n"; // Done
        cout << "|1o. Exit                     |\n"; // Done
        cout << "-------------------------------\n";
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
				} while((inputNumber != 1) && (inputNumber != 2));
				
				if (inputNumber == 1) {
					while(true) {
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
            
			case 5: {
				Borrow(bookHolder, borrowedHolder, today, inputString);
				break;
			}

            case 6: {
                Return(bookHolder, borrowedHolder, today, inputString);
                break;
			}

			case 7: {
				idInputChecker(bookHolder, inputString);
				for (int i = 0; i < (int) bookHolder.size(); i++) {
					if (bookHolder.at(i)->getID() == inputString) {
						if (bookHolder.at(i)->customerList.empty()) {
							cout << "There are no customer whom borrowed this book!\n";
						}
						else {
							cout << "They are:\n";
							for (int j = 0; j < (int) bookHolder.at(i)->customerList.size(); j++) {
								cout << "- \"" << bookHolder.at(i)->customerList.at(j).name << "\" with ID: \'" 
								<< bookHolder.at(i)->customerList.at(j).customerID 
								<< "\' and borrowed in " << bookHolder.at(i)->customerList.at(j).borrowDay << "\n";
							}
						}
					}
				}
				break;
			}

            case 8: {
                idInputChecker(bookHolder, inputString);				
				for (int i = 0; i < (int) bookHolder.size(); i++) {
					if (bookHolder.at(i)->getID() == inputString) {
						while(true) {
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

            case 9: {
                Add(bookHolder, foundedBook);
                break;
			}

            case 10: {
				Write("library.txt", bookHolder, borrowedHolder);
				for (int i = 0; i < (int) bookHolder.size(); i++)  // Clean up data
					delete bookHolder.at(i);
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

