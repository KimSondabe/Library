#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <limits>

using namespace std;

typedef struct {
	string name;
	string customerID;
	string customerMail;
	string borrowDay;
} customerInfo;

typedef struct {
	string bookID;
	string borrowQuantity;
	customerInfo info;
} BorrowedBookInfo;

class LibraryItems {
	private:
		string level;
		string zone;
	public:
		/* ======== Default Constructor ======== */
		LibraryItems() : level("0"), zone("A") {}
		/* ======== Default Constructor ======== */

		/* ======== Constructor ======== */
		LibraryItems(string level, string zone)
		: level(level), zone(zone) {}
		/* ======== Constructor ======== */

		/* ======== Getters ========*/
		int getLevel() {return stoi(level);}
		string getZone() {return zone;}
		/* ======== Getters ========*/

		/* ======== Setters ========*/
		void Move(string level, string zone) {
			this->zone = zone;
			this->level = level;
			cout << "Moved successfully!\n";
		}
		/* ======== Setters ========*/
};

class Books : public LibraryItems {
	private : 
		string title;
		string author;
		string quantity;
		string page;
	public :
		vector<customerInfo> customerList;

		/* ======== Default Constructor ======== */
		Books()
		: LibraryItems(), title(""), author(""), quantity("0"), page("0"), customerList({}) {}
		/* ======== Default Constructor ======== */

        /* ======== Constructor ======== */
		Books(string title, string author, string quantity, string page, string level, string zone, vector<customerInfo> customerList)
        : LibraryItems(level, zone), title(title), author(author), quantity(quantity), page(page), customerList(customerList) {}
		/* ======== Constructor ======== */

		/* ======== Getters ========*/
		string getTitle() {return title;}
		string getAuthor() {return author;} 
		int getQuantity() {return stoi(quantity);}
		int getPages() {return stoi(page);}
		int getBorrowDate() {return (stoi(page) / 10 < 14) ? 14 : stoi(page) / 10;}
		/* ======== Getters ========*/

		/* ======== Setters ========*/
		void changeQuantity(int quantity) {
			quantity += stoi(this->quantity);
			this->quantity = ((quantity < 0) || (quantity > 999)) ? "0" : to_string(quantity);	
		}
		/* ======== Setters ========*/
};

class Computers : public LibraryItems {
	private:
		string specs;
		bool available;
	public:
		/* ======== Default Constructor ======== */
		Computers() : LibraryItems(), specs(""), available(true) {}
		/* ======== Default Constructor ======== */

		/* ======== Constructor ======== */
		Computers(string specs, string level, string zone)
		: LibraryItems(level, zone), specs(specs), available(true) {}
		/* ======== Constructor ======== */

		/* ======== Getters ========*/
		int rentMoney(int hours) {
			return (specs == "HIGH") ? 12000 * hours : (specs == "MID") ? 10000 * hours : 7000 * hours;
		}
		string getSpecs() {return specs;}
		bool isAvailable() {return available;}
		/* ======== Getters ========*/

		/* ======== Setters ========*/
		void setSpecs(string specs) {this->specs = specs;}
		void rentComputer(string hours) {
			if (available){
				available = false;
				cout << "Total rent cost: " << rentMoney(stoi(hours)) << " VND\n";
				cout << "Enter to confirm payment...";
				cin.get();
				return;
			}
			cout << "This computer is currently unavailable!\n";
		}
		/* ======== Setters ========*/
};

class Account{
	private:
		string index;
		string mail;
		string password;
		string studentID;
		string username;
		string role;
	public:
        /* ======== Constructor ======== */
		Account(string index, string mail, string password, string studentID, string username, string role)
        : index(index), mail(mail), password(password), studentID(studentID), username(username), role(role) {}
        /* ======== Constructor ======== */

		/* ======== Getters ========*/
		string getMail() {return mail;}
		string getUser() {return username;}
		string getPass() {return password;}
		string getRole() {return role;}
		string getIndex() {return index;}
		string getStudentID() {return studentID;}
		/* ======== Getters ========*/
		
		/* ======== Setters ========*/
		void setUser(string user) {username = user;}
		void setPass(string pass) {password = pass;}
		void setAdmin(string r) {role = r;}
		void setIndex(int i) {index = i;}
		void setMail(string m) {mail = m;}
		void setStudentID(string id) {studentID = id;}
		/* ======== Setters ========*/

};
typedef struct {
	map<string, Books> bookHolder;
	map<string, Books> foundedBook;
	vector<BorrowedBookInfo> borrowedHolder;
	map<string, Computers> computerHolder;
	vector<Account> Acc;
	string today;
	int currentAcc;
} Library;

/*======= Declare Function =======*/

// File working functions
void ReadFile(Library &lib); // Read data from file
void Write(Library &lib,bool writeToBooks, bool writeToCopy, bool writeToBorrowed, bool writeToAccounts, bool writeToComputers); // Write data to file
void View(Library &lib, const string choice); // View book(s)

// Book Features Functions
void Find(Library &lib, const string title, const string author, const string choice); // Find book by title/author
void CountBooks(Library &lib); // Count total books
void Add(Library &lib); // Add book(s)
void Borrow(Library &lib); // Borrow book(s)
void Return(Library &lib); // Return book(s)
void MoveItem(Library &lib); // Move item(s)
void FindBooks(Library &lib); // Find Feature
void ReportBooks(Library &lib); //Report books' issues
void viewBorrowedUsers(Library &lib); // View users who borrowed a specific book

// Computer Features Functions
void rentComputer(Library &lib); // Rent computer(s)

// Account Main Function
bool CheckPass(vector<Account> &Acc, string mail, string password); //Check password
bool CheckUser(vector<Account> &Acc, string mail); //Check if mail existed
int getIndexAcc(vector<Account> &Acc, string &mail, string &password); //Get account index
bool isAdmin(vector<Account> &Acc, int index); //Check if the account is a admin
void CreateAcc(vector<Account> &Acc); // Create Acc
void DisplayAcc(vector<Account> &Acc); //Display Acc

//General Function
string lowerCase(string str); // Convert string to lower case
bool capitalizeWords(string &s); // Capitalize first letter of each word

//Date Function 
bool isLeap(int year); // Check leap year
int daysInMonth(int month, int year); // Check number of days in month
int dayCounter(string start, string end); // Count number of days between two dates
string borrowDateCalculate(string start, int borrowDuration); // Calculate return date based on borrow date and duration

//Book Function
string idCounter(string prevID); // Generate next ID
void idInputChecker(map<string, Books> &bookHolder, string &inputString); // Check valid book ID input
void idInputChecker(map<string, Computers> &computerHolder, string &inputString); // Check valid computer ID input

//UI Function
void adminMenu();//UI Admin's Menu
void userMenu();//UI User's Menu
string getIntInput(string str); //Get user input
void Profile(Library &lib); //Display profile information

/*========MAIN PROGRAM=======*/
int main() {
    // Variables Declaration (If need more, declare in specific functions)
    bool status = true;
	bool open = true;
	string mail, password;
	Library lib;
    
	// Today's date
	cout << "Today is: ";
	time_t now = time(0);
	ctime(&now);
	tm *ltm = localtime(&now);
	lib.today = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
	cout << lib.today << "\n";

	// Read data from file
	ReadFile(lib);

	// Login interface
	cout << "===== Welcome to Ta Quang Buu Library =====\n";
	while(open){
		do {
			cout << "Mail: "; 
			getline(cin, mail);
			cout << "Password: "; 
			getline(cin, password);
			if(CheckPass(lib.Acc, mail, password)) {
				cout << "Successfully!\n";
				break;
			}
			else{
				cout << "Wrong mail or password, please try again\n";
			}
		} while(true);

		lib.currentAcc = getIndexAcc(lib.Acc, mail, password);

		// Main interface
		status = true;
		while(status) {
			if(isAdmin(lib.Acc, lib.currentAcc)) {
				adminMenu();
				switch(stoi(getIntInput("Enter your choice: "))) {
					case 1: { 
						CountBooks(lib);
						break;
					}

					case 2: {
						Write(lib, false, true, false, false, false);
						break;
					}

					case 3: {
						View(lib, "books");
						break;
					}
					case 4: {
						View(lib, "computers");
						break;
					}
					case 5: {
						DisplayAcc(lib.Acc);
						break;
					}

					case 6: {
						FindBooks(lib);
						if (lib.foundedBook.empty()) {
							cout << "There are no book match with your search!\n";
							break;
						}
						cout << "The book(s) you want to search for are:\n";
						for (auto i : lib.foundedBook) {
							cout << "\"" << i.second.getTitle() << "\" by " << i.second.getAuthor() << " with " << i.second.getQuantity()
							<< " books in level \'" << i.second.getLevel() << "\' and zone \'" << i.second.getZone() << "\'!\n"; 
						}
						break;
					}
					
					case 7: {
						viewBorrowedUsers(lib);
						break;
					}
					case 8: {
						ReportBooks(lib);
						break;
					}

					case 9: {
						Add(lib);
						break;
					}

					case 10: {
						MoveItem(lib);
						break;
					}

					case 11:{
						CreateAcc(lib.Acc);
						break;
					}

					case 12:{
						Write(lib, true, false, true, true, true);
						cout << "===== Welcome to Ta Quang Buu Library =====\n";
						status = false;
						break;
					}

					case 13: {
						Write(lib, true, false, true, true, true);
						cout << "Exiting program...\n";
						status = false;
						open = false;
						break;
					}

					default: {
						cout << "Invalid syntax, please retry!\n";
					}
				}
			}

			else {
				userMenu();
				switch(stoi(getIntInput("Enter your choice: "))) {
					case 1:{
						View(lib, "books");
						break;
					}
					case 2:{
						View(lib, "computers");
						break;
					}
					case 3:{
						FindBooks(lib);
						if (lib.foundedBook.empty()) {
							cout << "There are no book match with your search!\n";
							break;
						}

						cout << "The book(s) you want to search for are:\n";
						for (auto i : lib.foundedBook) {
							cout << "\"" << i.second.getTitle() << "\" by " << i.second.getAuthor() << " with " << i.second.getQuantity()
							<< " books in level \'" << i.second.getLevel() << "\' and zone \'" << i.second.getZone() << "\'!\n"; 
						}
						break;	
					}
					case 4:{
						ReportBooks(lib);
						break;
					}
					case 5:{
						Borrow(lib);
						break;
					}
					case 6:{
						Return(lib);
						break;
					}
					case 7:{
						rentComputer(lib);
						break;
					}
					case 8:{
						Profile(lib);
						break;
					}
					case 9:{
						Write(lib, true, false, true, true, true);
						cout << "===== Welcome to Ta Quang Buu Library =====\n";
						status = false;
						break;
					}
					case 10:{
						Write(lib, true, false, true, true, true);
						cout << "Thanks for coming to our library! Have a nice day!\n";
						status = false;
						open = false;
						break;
					}
					default: {
						cout << "Invalid syntax, please retry!\n";
					}
				}
			}
		}
	}
    return 0;
}

/*=======FUNCTION=======*/

//Book Main Function
void ReadFile(Library &lib) {
	const int borrowedBooksCount = 6;
	const int accountCount = 6;
	const int bookInfoCount = 7;
	const int computerInfoCount = 4;
	string buffer, bookInfoList[bookInfoCount], borrowedInfoList[borrowedBooksCount], accountList[accountCount], computerInfoList[computerInfoCount];
	// book info list: id (0), title(1), author(2), quantity(3), page(4), level(5), zone(6).
	// borrowed info list: bookID(0), name(1), customerID(2), customerMail(3), borrowDay(4), borrowQuantity(5).
	// account list: index(0), mail(1), password(2),studentID(4), username(5), role(6).
	// computer info list: id(0), spec(1), level(2), zone(3).
	vector<customerInfo> customerList;
	lib.bookHolder.clear();
	lib.borrowedHolder.clear();
	lib.Acc.clear();

	// Read borrowed books file
	ifstream fileBorrowed("txt/borrowedBooks.txt");
	while(getline(fileBorrowed, buffer)) {
        if(buffer.empty()) {
            continue;
        }
        stringstream ss(buffer);
		for (int i = 0; i < borrowedBooksCount; i++) {
			getline(ss, buffer, '|');
			borrowedInfoList[i] = buffer;
		}
		if (borrowedInfoList[0] != "") {
			BorrowedBookInfo borrowedBook;
			borrowedBook.bookID = borrowedInfoList[0];
			borrowedBook.info.name = borrowedInfoList[1];
			borrowedBook.info.customerID = borrowedInfoList[2];
			borrowedBook.info.customerMail = borrowedInfoList[3];
			borrowedBook.info.borrowDay = borrowedInfoList[4];
			borrowedBook.borrowQuantity = borrowedInfoList[5];
			lib.borrowedHolder.push_back(borrowedBook);
		}
	}
	fileBorrowed.close();

	//Read account file
	ifstream accFile("txt/account.txt");
	while(getline(accFile, buffer)) {
        if(buffer.empty()) {
            continue;
        }
        stringstream ss(buffer);
		for (int i = 0; i < accountCount; i++) {
			getline(ss, buffer, '|');
			accountList[i] = buffer;
		}
		if(accountList[0] != "") {
			Account acc(accountList[0], accountList[1], accountList[2], accountList[3], accountList[4], accountList[5]);
			lib.Acc.push_back(acc);
		}
	}
	accFile.close();

	// Read main book file
	ifstream file("txt/books.txt");
	while(getline(file, buffer)) {
		customerList.clear();
        if(buffer.empty()) {
            continue;
        }
        stringstream ss(buffer);
		for (int i = 0; i < bookInfoCount; i++) {
			getline(ss, buffer, '|');
			bookInfoList[i] = buffer;
		}
		if (bookInfoList[0] != "") {
			// Store customer infomation into a vector
			for (int i = 0; i < (int) lib.borrowedHolder.size(); i++) {
				if (lib.borrowedHolder[i].bookID == bookInfoList[0]) {
					customerList.push_back(lib.borrowedHolder[i].info);
				}
			}
			Books book(bookInfoList[1], bookInfoList[2], bookInfoList[3], bookInfoList[4], bookInfoList[5], bookInfoList[6], customerList);
			lib.bookHolder[bookInfoList[0]] = book;      
		}
	}
	file.close();

	// Read computers file
	ifstream computerFile("txt/computers.txt");
	while (getline(computerFile, buffer)) {
		if(buffer.empty()) {
			continue;
		}
		stringstream ss(buffer);
		for (int i = 0; i < computerInfoCount; i++) {
			getline(ss, buffer, '|');
			computerInfoList[i] = buffer;
		}
		if (computerInfoList[0] != "") {
			Computers computer(computerInfoList[1], computerInfoList[2], computerInfoList[3]);
			lib.computerHolder[computerInfoList[0]] = computer;      
		}
	}
	computerFile.close();
}

void MoveItem(Library &lib) {
	string itemType;
	cout << "Which item do you want to move?\n";
	cout << "1. Book\n";
	cout << "2. Computer\n";
	do {
		itemType = getIntInput("Enter your choice (1-2): ");
		if ((itemType == "1") || (itemType == "2")) break;
		cout << "Invalid input, please try again.\n";
	} while(true);
	if (itemType == "1") {	
		string bookID, level, zone;
		idInputChecker(lib.bookHolder, bookID);
		cout << "Current location - Level: " << lib.bookHolder[bookID].getLevel()
		<< ", Zone: " << lib.bookHolder[bookID].getZone() << "\n";
		while(true) {
			level = getIntInput("Enter Level (1-5): ");
			if ((stoi(level) >= 1) && (stoi(level) <= 5)) break;
			cout << "Invalid input, please try again\n";
		}

		while(true) {
			cout << "Enter Zone (A-E): ";
			getline(cin, zone);
			if ((zone.length() == 1) && (zone[0] >= 'A') && (zone[0] <= 'E')) break;
			cout << "Invalid input, please try again.\n";
		}
		lib.bookHolder[bookID].Move(level, zone);
	}

	else if (itemType == "2") {
		string computerID, level, zone;
		idInputChecker(lib.computerHolder, computerID);
		cout << "Current location - Level: " << lib.computerHolder[computerID].getLevel()
		<< ", Zone: " << lib.computerHolder[computerID].getZone() << "\n";
		while(true) {
			level = getIntInput("Enter Level (5-7): ");
			if ((stoi(level) >= 5) && (stoi(level) <= 7)) break;
			cout << "Invalid input, please try again\n";
		}

		while(true) {
			cout << "Enter Zone (A-E): ";
			getline(cin, zone);
			if ((zone.length() == 1) && (zone[0] >= 'A') && (zone[0] <= 'E')) break;
			cout << "Invalid input, please try again.\n";
		}
		lib.computerHolder[computerID].Move(level, zone);
	}
}

void Write(Library &lib, bool writeToBooks, bool writeToCopy, bool writeToBorrowed, bool writeToAccounts, bool writeToComputers) {
	cout << "===== Wrote to ";

	if(writeToBooks) {
		ofstream bookFile("txt/books.txt");
		for (auto i : lib.bookHolder) {
			bookFile << i.first << "|" << i.second.getTitle() << "|" 
			<< i.second.getAuthor() << "|" << i.second.getQuantity() << "|"
			<< i.second.getPages() << "|" << i.second.getLevel() << "|"
			<< i.second.getZone() << "|\n";
		}	
		bookFile.close();
		cout << "\"books.txt\"";
	}

	if(writeToCopy) {
		ofstream bookCopyFile("txt/booksCopy.txt");
		for (auto i : lib.bookHolder) {
			bookCopyFile << i.first << "|" << i.second.getTitle() << "|" 
			<< i.second.getAuthor() << "|" << i.second.getQuantity() << "|"
			<< i.second.getPages() << "|" << i.second.getLevel() << "|"
			<< i.second.getZone() << "|\n";
		}	
		bookCopyFile.close();
		cout << " & \"booksCopy.txt\"";
	}

	if(writeToBorrowed) {
		ofstream borrowedFile("txt/borrowedBooks.txt");
		for (int i = 0; i < (int) lib.borrowedHolder.size(); i++) {
			borrowedFile << lib.borrowedHolder[i].bookID << "|" << lib.borrowedHolder[i].info.name << "|" 
			<< lib.borrowedHolder[i].info.customerID << "|" << lib.borrowedHolder[i].info.customerMail << "|"
			<< lib.borrowedHolder[i].info.borrowDay << "|" << lib.borrowedHolder[i].borrowQuantity << "|\n";
		}    

		borrowedFile.close();
		cout << " & \"borrowedBooks.txt\"";
	}
	
	if(writeToAccounts) {
		ofstream accFile("txt/account.txt");
		
		for(auto i : lib.Acc) {
			accFile << i.getIndex() << "|" << i.getMail() << "|" << i.getPass() << "|" << i.getStudentID() << "|" << i.getUser() << "|" << i.getRole() << "|\n";
		}
		accFile.close();
		cout << " \"account.txt\"";
	}

	if (writeToComputers) {
		// Write computers file
		ofstream computerFile("txt/computers.txt");
		for (auto i : lib.computerHolder) {
			computerFile << i.first << "|" << i.second.getSpecs() << "|" 
			<< i.second.getLevel() << "|" << i.second.getZone() << "|\n";
		}
		computerFile.close();
		cout << " & \"computers.txt\"";
	}
	cout << " successfully! =====\n";
}

void CountBooks(Library &lib) {	
	int quantitiesSum = 0;

	for (auto i : lib.bookHolder) {
		quantitiesSum += i.second.getQuantity();
	}
	cout << "There are " << lib.bookHolder.size() << " book titles & " 
	<< quantitiesSum << " books in total\n"; 
	quantitiesSum = 0;
}

void View(Library &lib, const string choice) {
	if (choice == "books") {	
		cout << "Here are the book titles\' list\n";
		cout << "===================\n";
		for (auto i : lib.bookHolder) {
			cout << "\"" << i.second.getTitle() << "\" by " << i.second.getAuthor()
			<< " with " << i.second.getQuantity() << " books.\n";
		}
		cout << "==================\n";
	}
	else if (choice == "computers") {
		cout << "Here are the computer(s) available in the library:\n";
		cout << "===================\n";
		for (auto i : lib.computerHolder) {
			if (i.second.isAvailable()) {
				cout << "Computer ID: " << i.first << "\n - Specs: " << i.second.getSpecs()
				<< "\n - Location: Level " << i.second.getLevel() << ", Zone " << i.second.getZone() << "\n";
			}
		}
		cout << "==================\n";
	}
}

void Find(Library &lib, const string title, const string author, const string choice) {
	
	// Check for same title/author in original vector -> push to vector "foundedBook"
	lib.foundedBook.clear();
	if (choice == "Title") {
		for (auto i : lib.bookHolder) {
			if (lowerCase(i.second.getTitle()).find(lowerCase(title)) != string::npos) {
				lib.foundedBook[i.first] = i.second;
			}
		}
	}
	else if (choice == "Author") {
		for (auto i : lib.bookHolder) {
			if(lowerCase(i.second.getAuthor()).find(lowerCase(author)) != string::npos) {
				lib.foundedBook[i.first] = i.second;
			} 
		}
	}

	else if (choice == "Both") {
		for (auto i : lib.bookHolder) {
			if ((lowerCase(i.second.getTitle()).find(lowerCase(title)) != string::npos) &&
			(lowerCase(i.second.getAuthor()).find(lowerCase(author)) != string::npos)) {
				lib.foundedBook[i.first] = i.second;
			}
		}
	}

	else {
		cout << "Invalid choice!\n";
	}

}

void Add(Library &lib) {
	cout << "Which item do you want to add?\n";
	cout << "1. Book\n";
	cout << "2. Computer\n";
	string itemType;
	do {
		itemType = getIntInput("Enter your choice (1-2): ");
		if ((itemType == "1") || (itemType == "2")) break;
		cout << "Invalid input, please try again.\n";
	} while(true);
	if (itemType == "1") {
		string id, title, author, zone, quantity, page, level;
		// Checking book's title and author
		cout << "Enter Book's Title: ";
		do {
			getline(cin, title);
		} while(!capitalizeWords(title));
		cout << "Enter Book's Author: ";
		do {
			getline(cin, author);
		} while(!capitalizeWords(author));

		Find(lib, title, author, "Both"); // Check for same book title & author

		while(true) {
			quantity = getIntInput("Enter Book's Quantity (0 < quantity < 999): ");
			if ((stoi(quantity) > 0) && (stoi(quantity) < 999)) {
				if (!lib.foundedBook.empty()) { // If there is a book in vector "foundedBook"
					for (auto i : lib.bookHolder) {
						if (i.first == lib.foundedBook.begin()->first) {
							i.second.changeQuantity(stoi(quantity));
							cout << "===== Added " << quantity << " book(s) successfully! =====\n";
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
			page = getIntInput("Enter Book's Page (0 < page < 9999): ");
			if ((stoi(page) > 0) && (stoi(page) < 9999)) break;
			cout << "Invalid input, please try again.\n";
		}

		while(true) {
			level = getIntInput("Enter Book's Level (1-5): ");
			if ((stoi(level) >= 1) && (stoi(level) <= 5)) break;
			cout << "Invalid input, please try again\n";
		}

		while(true) {
			cout << "Enter Book's Zone (A-E): ";
			getline(cin, zone);
			if ((zone.length() == 1) && (zone[0] >= 'A') && (zone[0] <= 'E')) break;
			cout << "Invalid input, please try again.\n";
		}

		if (lib.bookHolder.empty()) {
			id = "0001";
		} 
		else {
			id = idCounter(lib.bookHolder.rbegin()->first);
		}

		vector<customerInfo> customerList;
		Books book(title, author, quantity, page, level, zone, customerList);
		lib.bookHolder[id] = book;

		cout << "\n===== Added Book successfully =====\n";
	}
	else if (itemType == "2") {
		string id, specs, zone, level;
		// Checking computer's specs
		cout << "Enter Computer's Specs (HIGH/MID/LOW): ";
		do {
			getline(cin, specs);
			if ((specs == "HIGH") || (specs == "MID") || (specs == "LOW")) break;
			cout << "Invalid input, please try again.\n";
		} while(true);

		while(true) {
			level = getIntInput("Enter Computer's Level (5-7): ");
			if ((stoi(level) >= 5) && (stoi(level) <= 7)) break;
			cout << "Invalid input, please try again\n";
		}

		while(true) {
			cout << "Enter Computer's Zone (A-E): ";
			getline(cin, zone);
			if ((zone.length() == 1) && (zone[0] >= 'A') && (zone[0] <= 'E')) break;
			cout << "Invalid input, please try again.\n";
		}

		if (lib.computerHolder.empty()) {
			id = "0001";
		} 
		else {
			id = idCounter(lib.computerHolder.rbegin()->first);
		}

		Computers computer(specs, level, zone);
		lib.computerHolder[id] = computer;

		cout << "\n===== Added Computer successfully =====\n";
	}
}

void viewBorrowedUsers(Library &lib) {
	string bookID;
	idInputChecker(lib.bookHolder, bookID);
	if (lib.bookHolder[bookID].customerList.empty()) {
		cout << "There are no customer whom borrowed this book!\n";
	}
	else {
		cout << "They are:\n";
		for (int i = 0; i < (int) lib.bookHolder[bookID].customerList.size(); i++) {
			cout << "- Name: \"" << lib.bookHolder[bookID].customerList[i].name 
			<< "\"\n - ID: \'" << lib.bookHolder[bookID].customerList[i].customerID 
			<< "\'\n - Borrowed on: " << lib.bookHolder[bookID].customerList[i].borrowDay;
			if ((dayCounter(lib.bookHolder[bookID].customerList[i].borrowDay, lib.today) - lib.bookHolder[bookID].getBorrowDate()) > 0) {
				cout << " (late for " << (dayCounter(lib.bookHolder[bookID].customerList[i].borrowDay, lib.today) - lib.bookHolder[bookID].getBorrowDate())
				<< " day(s))\n" << "Sent email to " << lib.bookHolder[bookID].customerList[i].customerMail << "\n";
			}
			else cout << "\n";
		}
	}
}

void Borrow(Library &lib) {
	string bookID, buffer;
	idInputChecker(lib.bookHolder, bookID);
	vector<string> customerIDlist;
	// Find the book in bookHolder
	if (lib.bookHolder[bookID].getQuantity() == 0) {
		cout << "Sorry, this book is out of stock!\n";
		return;
	}
	// Get customer info
	customerInfo newCustomer;
	newCustomer.name = lib.Acc.at(lib.currentAcc).getUser();
	newCustomer.customerID = lib.Acc.at(lib.currentAcc).getStudentID();
	newCustomer.borrowDay = lib.today;
	// Check if customer has already borrowed this book
	for (int i = 0; i < (int) lib.bookHolder[bookID].customerList.size(); i++) {
		if (lib.bookHolder[bookID].customerList[i].name == newCustomer.name && lib.bookHolder[bookID].customerList[i].customerID == newCustomer.customerID) {
			cout << "You have already borrowed this book!\n";
			return;
		}
	}
	newCustomer.customerMail = lib.Acc.at(lib.currentAcc).getMail();

	lib.bookHolder[bookID].customerList.push_back(newCustomer);
	// Ask for quantity to borrow
	do {
		cout << "There are " << lib.bookHolder[bookID].getQuantity() << " book(s) available.\n";
		buffer = getIntInput("Enter number of book(s) you want to borrow: ");
		if ((stoi(buffer) > 0) && (stoi(buffer) <= lib.bookHolder[bookID].getQuantity())) {
			break;
		}
		cout << "Invalid input, please try again.\n";
	} while(true);

	// Add new borrowed book info to vector "borrowedHolder"
	BorrowedBookInfo borrowedBook;
	borrowedBook.bookID = bookID;
	borrowedBook.info = newCustomer;
	borrowedBook.borrowQuantity = buffer;
	lib.borrowedHolder.push_back(borrowedBook);
	lib.bookHolder[bookID].changeQuantity(-stoi(buffer));
	cout << "===== Book(s) borrowed successfully! =====\n";
	cout << "You must return on " << borrowDateCalculate(lib.today, lib.bookHolder[bookID].getBorrowDate()) << "\n";
	return;
}

void Return(Library &lib) {
	string bookID, buffer;
	idInputChecker(lib.bookHolder, bookID);
	vector<customerInfo> customerlist;
	int originalBorrowedHolderSize = (int) lib.borrowedHolder.size();

	// Find the book in borrowedHolder
	for (int i = 0; i < originalBorrowedHolderSize; i++) {
		if (lib.borrowedHolder[i].bookID == bookID) {
			customerInfo returnCustomer;
			returnCustomer.name = lib.Acc.at(lib.currentAcc).getUser();
			returnCustomer.customerID = lib.Acc.at(lib.currentAcc).getStudentID();

			// Check if customer info matches
			if (lib.borrowedHolder[i].info.name != returnCustomer.name || lib.borrowedHolder[i].info.customerID != returnCustomer.customerID) {
				cout << returnCustomer.name << " - " << returnCustomer.customerID << "\n";
				cout << "No record found for this customer!\n";
				return;
			}
			// Store borrowed info then remove from borrowedHolder
			BorrowedBookInfo borrowed = lib.borrowedHolder[i];
			lib.borrowedHolder.erase(lib.borrowedHolder.begin() + i);
			// Increase book quantity in bookHolder and update customer list
			// Calculate late days
			int lateDays = 0;
			lateDays = dayCounter(borrowed.info.borrowDay, lib.today) - lib.bookHolder[bookID].getBorrowDate();
			if (lateDays > 0) {
				cout << "You are late by " << lateDays << " day(s). Please pay fine of " 
				<< lateDays * lib.bookHolder[bookID].getPages() * stoi(borrowed.borrowQuantity) 
				<< " VND.\n";
				cout << "Press Enter to confirm payment...";
				cin.get();
			}
			else {
				cout << "Thank you for returning on time!\n";
			}
				lib.bookHolder[bookID].changeQuantity(stoi(borrowed.borrowQuantity));
				int originalCustomerListSize = (int) lib.bookHolder[bookID].customerList.size();
				for (int k = 0; k < originalCustomerListSize; k++) {
					if (lib.bookHolder[bookID].customerList[k].name == returnCustomer.name && lib.bookHolder[bookID].customerList[k].customerID == returnCustomer.customerID) {
						lib.bookHolder[bookID].customerList.erase(lib.bookHolder[bookID].customerList.begin() + k);
						break;
					}
				}
				cout << "===== Book returned successfully! =====\n";
				return;
		}
	}
}

void FindBooks(Library &lib) {
	string choice, inputString;
		do {
			cout << "=============================================\n";
			cout << "|FIND BOOK MENU                            |\n";
			cout << "|1. Search book(s) by title                |\n";
			cout << "|2. Search book(s) by author               |\n";
			cout << "=============================================\n";
			choice = getIntInput("Enter your choice (1-2): ");
		} while((choice != "1") && (choice != "2"));

		if (choice == "1") {
			while(true) {
                cout << "Title you want to search for: ";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, inputString);
                if (!inputString.empty()) {
                    cout << "\n--- SEARCH RESULTS ---\n";
                    Find(lib, inputString, "", "Title");
                    cout << "\nPress Enter to continue...";
                    cin.ignore(); 
                    break;
                } else {
                    cout << "Please try again.\n";
                }
            }
		}

		else if (choice == "2") {
			while(true) {
                cout << "Author you want to search for: ";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, inputString);
                if (!inputString.empty()) {
                    cout << "\n--- SEARCH RESULTS ---\n";
                    Find(lib, "", inputString, "Author");
                    cout << "\nPress Enter to continue...";
                    cin.ignore(); 
                    break;
                } else {
                    cout << "Please try again.\n";
                }
            }
		}
	}

void ReportBooks(Library &lib) {
	string bookID, quantity;

	idInputChecker(lib.bookHolder, bookID);				

	while(true) {
		quantity = getIntInput("Please enter number of book you want to report: ");

		if (lib.bookHolder[bookID].getQuantity() >= stoi(quantity)) {
			lib.bookHolder[bookID].changeQuantity(-stoi(quantity));
			cout << "Reported successfully " << quantity << " book(s)";
			break;
		}
		cout << "Invalid input, please try again.\n";
	}
}

void rentComputer(Library &lib) {
	string comID, choice;
	do {
		idInputChecker(lib.computerHolder, comID);
		cout << "You have chosen computer " << comID << " with specs: " << lib.computerHolder[comID].getSpecs() << "\n";
		cout << "Are you sure you want to rent this computer? (Press Y to confirm): ";
		getline(cin, choice);
	} while (lowerCase(choice) != "y");
	if (!lib.computerHolder[comID].isAvailable()) {
		cout << "Sorry, this computer is currently rented out!\n";
		return;
	}
	lib.computerHolder[comID].rentComputer(getIntInput("How many hours do you want to rent the computer for?"));
	cout << "You have successfully rented computer " << comID << "!\n";
	cout << "Location: Level " << lib.computerHolder[comID].getLevel() << ", Zone " << lib.computerHolder[comID].getZone() << "\n";

}
string idCounter(string prevID) {
	int idBooklength = 4;
    if (prevID.size() != idBooklength) return "";
    for (char c : prevID) { 
        if (!isdigit(c)) return "";
	}
	string upComingID = to_string((stoi(prevID) + 1));
	if (upComingID.length() > idBooklength) {
		cout << "Out of storage!\n";
		return "";
	}
	while(upComingID.length() < idBooklength) {
		upComingID = "0" + upComingID;
	}
    return upComingID;
}

void idInputChecker(map<string, Books> &bookHolder, string &bookID) {
	int idBooklength = 4;
	do {
		cout << "Please enter the book(s) ID you want to choose (xxxx): ";
		getline(cin, bookID);
		for (char i : bookID) {
			if (!isdigit(i)) bookID += "filler";
		}
		if (bookID.length() != idBooklength) {
			cout << "Invalid input, please try again.\n";
			continue;
		}
		bool found = false;
		for (auto i : bookHolder) {
			if (i.first == bookID) {
				found = true;
				break;
			}
		}
		if (found) break;
		cout << "Invalid input, please try again.\n";
	} while(true);
}
void idInputChecker(map<string, Computers> &computerHolder, string &computerID) {
	int idComputerlength = 4;
	do {
		cout << "Please enter the computer(s) ID you want to choose (xxxx): ";
		getline(cin, computerID);
		for (char i : computerID) {
			if (!isdigit(i)) computerID += "filler";
		}
		if (computerID.length() != idComputerlength) {
			cout << "Invalid input, please try again.\n";
			continue;
		}
		bool found = false;
		for (auto i : computerHolder) {
			if (i.first == computerID) {
				found = true;
				break;
			}
		}
		if (found) break;
		cout << "Invalid input, please try again.\n";
	} while(true);
}

//Account Function 

bool CheckPass(vector<Account> &Acc, string mail, string password) {
	for(int i = 0; i < (int) Acc.size(); i++) {
		if(mail == Acc[i].getMail()) {
			if(password == Acc[i].getPass()) {
				return true; //Check acccount when sign in 
			}
			
		}
	}
	return false;
}

int getIndexAcc(vector<Account> &Acc, string &mail, string &password) {
	for(int i = 0; i < (int) Acc.size(); i++) {
		if((mail == Acc[i].getMail()) && (password == Acc[i].getPass())) {
			return i;
		}
	}
	return 0;
}

bool isAdmin(vector<Account> &Acc, int index) {
	if(Acc[index].getRole() == "admin") {return true;}
	return false;
}

bool CheckUser(vector<Account> &Acc, string mail) {
	for(int i = 0; i < (int) Acc.size(); i++) {
		if(mail == Acc[i].getMail()) {
			return true;
		}
	}
	return false;
}

void CreateAcc(vector<Account> &Acc) {
	string username, password, role, mail, studentID;
	string buffer;
	do{
		cout << "=======Create account======\n";
		cout << "Email (must be @sis.hust.edu.vn): ";
		do {
		getline(cin, mail);
		if ((mail != "") && (mail.find("@sis.hust.edu.vn") != string::npos)) break;
		} while (true);
		cout << "Password: "; 
		do{
			getline(cin, password);
			if (password != "") break;
		}while(true);
		cout << "Username: "; 
		do{
			getline(cin, username);
			if(capitalizeWords(username)) break;
		}while(true);
		do{
			studentID = getIntInput("Student ID must be 8 digits (20200000 - 20309999): ");
			if((stoi(studentID) > 20200000) && (stoi(studentID) < 20309999)) break;
		}while(true);
		if(CheckUser(Acc, mail)) {
			cout << "Existed Mail\n";
		}
		else{
			cout << "Account's Role: "; 
			getline(cin, role);
			Account acc(to_string(1 + Acc.size()), mail, password, studentID, username, role);
			Acc.push_back(acc);			
			break;
		}
	}while(true);
	cout << "====Create account successfully ====\n";
}

void DisplayAcc(vector<Account> &Acc) {
	for(int i = 0; i < (int) Acc.size(); i++) {
		cout << Acc[i].getIndex() << "|" << Acc[i].getMail() << "|" << Acc[i].getPass() <<"|"<< Acc[i].getStudentID() << "|" << Acc[i].getUser() << "|" << Acc[i].getRole() << "|\n";
	}
}

//General Function 
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
    if (str.size() == 0) {
		cout << "Invalid input, please try again: \n";
		return false;
    }
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

//Date function 
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

string borrowDateCalculate(string start, int borrowDuration) {
    string buffer, day, month, year;
    int d, m, y;
    for (char i : start) {
        if (i != '/') {
            buffer += i;
        }
        else {
            if (day == "") {
                day = buffer;
                buffer = "";
            }
            else if (month == "") {
                month = buffer;
                buffer = "";
            }
        }
    }
    year = buffer;

    d = stoi(day);
    m = stoi(month);
    y = stoi(year);

    d += borrowDuration;
    while (d > daysInMonth(m, y)) {
        d -= daysInMonth(m, y);
        m++;
        if (m > 12) {
            m = 1;
            y++;
        }
    }

    string result = "";
    if (d < 10) result += "0";
    result += to_string(d) + "/";
    if (m < 10) result += "0";
    result += to_string(m) + "/" + to_string(y);
    return result;
}

int dayCounter(string start, string end) {
    string buffer, day, month;
    int startDay, endDay = 0;
    for (char i : start) {
        if (i != '/') {
            buffer += i;
        }
        else {
            if (day != "") {
                if (month == "") {
                    month = buffer;
                    buffer = "";
                }
            }
            else {
                day = buffer;
                buffer = "";
            }
        }
    }

    startDay = stoi(day);
    for (int i = 1; i < stoi(month); i++) {
        startDay += daysInMonth(i, stoi(buffer));
    }
    for (int i = 1; i < stoi(buffer); i++) {
        startDay += isLeap(i) ? 366 : 365;
    }

    buffer = day = month = "";

    for (char i : end) {
        if (i != '/') {
            buffer += i;
        }
        else {
            if (day != "") {
                if (month == "") {
                    month = buffer;
                    buffer = "";
                }
            }
            else {
                day = buffer;
                buffer = "";
            }
        }
    }

    endDay += stoi(day);
    for (int i = 1; i < stoi(month); i++) {
        endDay += daysInMonth(i, stoi(buffer));
    }
    for (int i = 1; i < stoi(buffer); i++) {
        endDay += isLeap(i) ? 366 : 365;
    }

    if (endDay < startDay) return 0;
    return (endDay - startDay);
}

//UI Function 
void adminMenu() {
    cout << "\n";
	cout << "============== Library ==============\n";
	cout << "|1. Number of books                 |\n"; // Done
	cout << "|2. Store data into other file      |\n"; // Done
    cout << "|3. View all books                  |\n"; // Done
	cout << "|4. View all available computers    |\n"; // Done
	cout << "|5. View all accounts               |\n"; // Done
	cout << "|6. Find book                       |\n"; // Done
    cout << "|7. View book borrower(s)           |\n"; // Done
	cout << "|8. Report item's issue             |\n"; // Done
	cout << "|9. Add item(s)                     |\n"; // Done
	cout << "|10. Move item to another place     |\n"; // Done
	cout << "|11. Create an account              |\n"; // Done
	cout << "|12. Return to sign in page         |\n"; // Done
	cout << "|13. Exit                           |\n"; // Done
	cout << "=====================================\n";
}

void userMenu() {
    cout << "\n";
	cout << "============== Library ==============\n";
	cout << "|1. View all books                  |\n"; // Done
	cout << "|2. View all available computers    |\n"; // Done
	cout << "|3. Find book                       |\n"; // Done
    cout << "|4. Report book's issue             |\n"; // Done
	cout << "|5. Borrow book (s)                 |\n"; // Done
	cout << "|6. Return book (s)                 |\n"; // Done
	cout << "|7. Rent computer                   |\n"; // Done
    cout << "|8. Profile                         |\n"; // Undone
	cout << "|9. Return to sign in page          |\n"; // Done
	cout << "|10. Exit                           |\n"; // Done
	cout << "=====================================\n";
}

string getIntInput(string str) {
	string input;
	bool isNumber = false;
	do {
		cout << str;
		getline(cin, input);
		for (char c : input) {
			if (!isdigit(c)) {
				isNumber = false;
				break;
			}
			else isNumber = true;
		}
		if (!isNumber) {
			cout << "Invalid input, please try again.\n";
		}
	} while (!isNumber);
    return input;
}

void Profile(Library &lib) {
	cout << "\n======== Your Profile ========\n";
	cout << "|Username: " << lib.Acc.at(lib.currentAcc).getUser() << "\n";
	cout << "|Email: " << lib.Acc.at(lib.currentAcc).getMail() << "\n";
	cout << "|Student ID: " << lib.Acc.at(lib.currentAcc).getStudentID() << "\n";
	cout << "|Role: " << lib.Acc.at(lib.currentAcc).getRole() << "\n";
	cout << "========================\n";
}