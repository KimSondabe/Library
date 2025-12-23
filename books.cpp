#include "library.h"

void ReadFile(vector<Books*> &bookHolder, vector<BorrowedBookInfo> &borrowedHolder, vector<Account> &Acc, unordered_set<string> &setID, unordered_map<string,int> &indexOfBook) {
	string buffer, bookInfoList[7], borrowedInfoList[5], accountList[4];
	// book info list: id (0), title(1), author(2), quantity(3), page(4), level(5), zone(6).
	// borrowed info list: bookID(0), name(1), customerID(2), customerMail(3), borrowDay(4), borrowQuantity(5).
	vector<customerInfo> customerList;
	
    for (Books* b : bookHolder) {
        delete b;
    }
	bookHolder.clear();
	borrowedHolder.clear();
	Acc.clear();

	// Read borrowed books file
	ifstream fileBorrowed("txt/borrowedBooks.txt");
	while(getline(fileBorrowed, buffer)) {
        if(buffer.empty()) {
            continue;
        }
        stringstream ss(buffer);
		for (int i = 0; i < 5; i++) {
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
			borrowedHolder.push_back(borrowedBook);
		}
	}
	fileBorrowed.close();

	//Read account file
	ifstream acc("txt/account.txt");
	while(getline(acc, buffer)){
        if(buffer.empty()) {
            continue;
        }
        stringstream ss(buffer);
		for (int i = 0; i < 4; i++) {
			getline(ss, buffer, '|');
			accountList[i] = buffer;
		}
		if(accountList[0] != ""){
			Account acc(accountList[0], accountList[1], accountList[2], accountList[3]);
			Acc.push_back(acc);
		}
	}
	acc.close();

	// Read main book file
	ifstream file("txt/books.txt");
	while(getline(file, buffer)) {
		customerList.clear();
        if(buffer.empty()) {
            continue;
        }
        stringstream ss(buffer);
		for (int i = 0; i < 7; i++) {
			getline(ss, buffer, '|');
			bookInfoList[i] = buffer;
		}
		if (bookInfoList[0] != "") {
            setID.insert(bookInfoList[0]);
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

void MoveBooks(vector<Books*> &bookHolder, unordered_set<string> &setID, unordered_map<string,int> &indexOfBook) {
    for(auto x : setID) {
        cout<<x<<" ";
    }
	cout << "\n";
    bool validMode = false;
    string mode;
    while(!validMode) {
        cout << "Move books by ID or Name: ";
        getline(cin,mode);
        //cout<<"\n";
        if(mode == "ID" || mode == "Name") {
            validMode = true;
        }else {
            cout << "Invalid mode \n";
        }
    }
    if(mode == "ID") {
        string id;
        bool validID = false;
        while(!validID) {
            cout << "ID: ";
            getline(cin,id);
            if(setID.find(id) != setID.end()) {
                validID = true;
            }else {
                cout<<"Invalid ID\n";
            }
        }
        int indexOfID = stoi(id) - 1;
        string zone;
        cout<<"Zone: ";
        getline(cin, zone);
        //cout<<"\n";
        string level;
        cout<<"Level: ";
        getline(cin, level);
        bookHolder[indexOfID]->setZone(zone);
        bookHolder[indexOfID]->setLevel(level);
    }
}

void Write(const string filename, vector<Books*> &bookHolder) { 
	ofstream output("txt/" + filename);
	for (int i = 0; i < (int) bookHolder.size(); i++) {
		output << bookHolder.at(i)->getID() << "|" << bookHolder.at(i)->getTitle() << "|" 
		<< bookHolder.at(i)->getAuthor() << "|" << bookHolder.at(i)->getQuantity() << "|"
		<< bookHolder.at(i)->getPages() << "|" << bookHolder.at(i)->getLevel() << "|"
		<< bookHolder.at(i)->getZone() << "|\n";
	}	
	output.close();
	cout << "===== Wrote to \"" << filename << "\" =====\n";
}

void Write(const string filename, vector<Books*> &bookHolder, vector<BorrowedBookInfo> &borrowedHolder) {
	Write(filename, bookHolder);
	// Write borrowed books file
	ofstream output("txt/borrowedBooks.txt");
	for (int i = 0; i < (int) borrowedHolder.size(); i++) {
		output << borrowedHolder.at(i).bookID << "|" << borrowedHolder.at(i).info.name << "|" 
		<< borrowedHolder.at(i).info.customerID << "|" << borrowedHolder.at(i).info.customerMail << "|"
		<< borrowedHolder.at(i).info.borrowDay << "|" << borrowedHolder.at(i).borrowQuantity << "|\n";
	}	

	output.close();
	cout << "===== Wrote to \"borrowedBooks.txt\" =====\n";
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

void Add(vector<Books*> &bookHolder, vector<Books*> &foundedBook, unordered_set<string> &setID, unordered_map<string,int> &indexOfBook) {
    string id, title, author, zone;
	int quantity, level, page;
	// Checking book's title and author
	cout << "Enter Book's Title: ";
    do {
		getline(cin, title);
	} while(!capitalizeWords(title));
	cout << "Enter Book's Author: ";
    do {
		getline(cin, author);
	} while(!capitalizeWords(author));
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
		cout << "Enter Book's Page (0 < page < 9999): ";
		cin >> page;
		cin.ignore();
		if ((page > 0) && (page < 9999)) break;
		cout << "Invalid input, please try again.\n";
	}
	while(true) {
		cout << "Enter Book's Level (1-5): ";
		cin >> level;
		cin.ignore();
		if ((level >= 1) && (level <= 5)) break;
		cout << "Invalid input, please try again\n";
	}
	while(true) {
		cout << "Enter Book's Zone (A-E): ";
		cin >> zone;
		if ((zone.length() == 1) && (zone[0] >= 'A') && (zone[0] <= 'E')) break;
		cout << "Invalid input, please try again.\n";
	}
	if (bookHolder.empty()) {
		id = "0001";
	} else {
		id = idCounter(bookHolder.back()->getID());
	}
    setID.insert(id);
	vector<customerInfo> customerList;
	Books* book = new Books(id, title, author, to_string(quantity), to_string(page), to_string(level), zone, customerList);
	bookHolder.push_back(book);
	cout << "\n===== Added Book successfully =====\n";
}

void Borrow(vector<Books*> &bookHolder, vector<BorrowedBookInfo> &borrowedHolder, const string today, string &inputString) {
	idInputChecker(bookHolder, inputString);
	string buffer;
	vector<string> customerIDlist;
    
	// Find the book in bookHolder
	for (int i = 0; i < (int) bookHolder.size(); i++) {
		if (bookHolder.at(i)->getID() == inputString) {
			if (bookHolder.at(i)->getQuantity() == 0) {
				cout << "Sorry, this book is out of stock!\n";
				return;
			}
			// Get customer info
			customerInfo newCustomer;
			cout << "Please provide your information to borrow the book.\n";
			cin.ignore();
			cout << "Enter your name: ";
			do {
				getline(cin, buffer);
			} while(!capitalizeWords(buffer));
			newCustomer.name = buffer;
			cout << "Enter your ID: ";
			do {
				getline(cin, buffer);
			} while (!customerIDchecker(buffer));
			newCustomer.customerID = buffer;
			newCustomer.borrowDay = today;
			// Check if customer has already borrowed this book
			for (int j = 0; j < (int) bookHolder.at(i)->customerList.size(); j++) {
				if (bookHolder.at(i)->customerList.at(j).name == newCustomer.name && bookHolder.at(i)->customerList.at(j).customerID == newCustomer.customerID) {
					cout << "You have already borrowed this book!\n";
					return;
				}
			}
			cout << "Enter your student mail: ";
			do {
				getline(cin, buffer);
				if ((buffer != "") && (buffer.find("@sis.hust.edu.vn") != string::npos)) break;
			} while (true);
			newCustomer.customerMail = buffer;
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

			// Add new borrowed book info to vector "borrowedHolder"
			BorrowedBookInfo borrowedBook;
			borrowedBook.bookID = inputString;
			borrowedBook.info = newCustomer;
			borrowedBook.borrowQuantity = buffer;
			borrowedHolder.push_back(borrowedBook);
			bookHolder.at(i)->changeQuantity(-stoi(buffer));
			cout << "===== Book(s) borrowed successfully! =====\n";
			cout << "You must return on " << borrowDateCalculate(today, bookHolder.at(i)->getBorrowDate()) << "\n";
			return;
		}
	}
}

void Return(vector<Books*> &bookHolder, vector<BorrowedBookInfo> &borrowedHolder, const string today, string &inputString) {
	idInputChecker(bookHolder, inputString);
	string buffer;
	vector<customerInfo> customerlist;

	int originalBorrowedHolderSize = (int) borrowedHolder.size();
	// Find the book in borrowedHolder
	for (int i = 0; i < originalBorrowedHolderSize; i++) {
		if (borrowedHolder.at(i).bookID == inputString) {
			customerInfo returnCustomer;
			cin.ignore();
			cout << "Enter your customer name: ";
			do {
				getline(cin, buffer);
			} while(!capitalizeWords(buffer));
			returnCustomer.name = buffer;
			cout << "Enter your ID: ";
			do {
				getline(cin, buffer);
			} while (!customerIDchecker(buffer));
			returnCustomer.customerID = buffer;
			// Check if customer info matches
			if (borrowedHolder.at(i).info.name != returnCustomer.name || borrowedHolder.at(i).info.customerID != returnCustomer.customerID) {
				cout << returnCustomer.name << " - " << returnCustomer.customerID << "\n";
				cout << "No record found for this customer!\n";
				return;
			}
			// Store borrowed info then remove from borrowedHolder
			BorrowedBookInfo borrowed = borrowedHolder.at(i);
			borrowedHolder.erase(borrowedHolder.begin() + i);
			// Increase book quantity in bookHolder and update customer list
			for (int j = 0; j < (int) bookHolder.size(); j++) {
				if (bookHolder.at(j)->getID() == inputString) {
					// Calculate late days
					int lateDays = 0;
					lateDays = dayCounter(borrowed.info.borrowDay, today) - bookHolder.at(j)->getBorrowDate();
					if (lateDays > 0) {
						cout << "You are late by " << lateDays << " day(s). Please pay fine of " 
						<< lateDays * bookHolder.at(j)->getPages() * stoi(borrowed.borrowQuantity) 
						<< " VND.\n";
						cout << "Press Enter to confirm payment...";
						cin.get();
					}
					else {
						cout << "Thank you for returning on time!\n";
					}
					bookHolder.at(j)->changeQuantity(stoi(borrowed.borrowQuantity));
					int originalCustomerListSize = (int) bookHolder.at(j)->customerList.size();
					for (int k = 0; k < originalCustomerListSize; k++) {
						if (bookHolder.at(j)->customerList.at(k).name == returnCustomer.name && bookHolder.at(j)->customerList.at(k).customerID == returnCustomer.customerID) {
							bookHolder.at(j)->customerList.erase(bookHolder.at(j)->customerList.begin() + k);
							break;
						}
					}
					break;
				}
			}
			cout << "===== Book returned successfully! =====\n";
			return;
		}
	}
}
