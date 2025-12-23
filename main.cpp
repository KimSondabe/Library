#include "library.h"

int main() {
    // Variables Declaration (If need more, declare in specific functions)
    bool status = true;
	int quantitiesSum = 0;
    int choice;
    int inputNumber;
	string inputString, today;
	string username, password;
    vector<Books*> bookHolder;
	vector<Books*> foundedBook;
	vector<BorrowedBookInfo> borrowedHolder;
	vector<Account> Acc;
    unordered_set<string> setID;
    unordered_map<string,int> indexOfBook;
    
	// Entrance interface (login, date input, file read)
	cout << "Today is: ";
	do {
		getline(cin, today);
		if (dayFormatCheck(today)) break;
		cout << "Invalid date format, please try again (dd/mm/yyyy): ";
	} while(true);
	ReadFile(bookHolder, borrowedHolder, Acc, setID, indexOfBook);
	do {
		cout << "Username: "; cin >> username;
		cout << "Password: "; cin >> password;
		if(CheckPass(Acc, username, password)){
			cout << "Successfully!\n";
			break;
		}else{
			cout << "Wrong username or password, please try again\n";
			}
	} while(true);

	// Main interface
	status = true;
    while(status) {
		if(isAdmin(Acc, getIndexAcc(Acc, username, password))){
			adminMenu();
			getChoice(choice);

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
					Write("booksCopy.txt", bookHolder);
					break;
				}

				case 3: {
					cout << "Here are the book titles\' list\n";
					cout << "===================\n";
					for (int i = 0; i < (int) bookHolder.size(); i++) {
						cout << "\"" << bookHolder.at(i)->getTitle() << "\" by " << bookHolder.at(i)->getAuthor()
						<< " with " << bookHolder.at(i)->getQuantity() << " books.\n";
					}
					cout << "==================\n";
					break;
				}

				case 4: {
					DisplayAcc(Acc);
					break;
				}

				case 5: {
					do {
						cout << "=============================================\n";
						cout << "|Do you want to search by Title or Author  |\n";
						cout << "|1. Title                                  |\n";
						cout << "|2. Author                                 |\n";
						cout << "=============================================\n";
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
				
				case 6: {
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
									<< "\' and borrowed in " << bookHolder.at(i)->customerList.at(j).borrowDay;
									if ((dayCounter(bookHolder.at(i)->customerList.at(j).borrowDay, today) - bookHolder.at(i)->getBorrowDate()) > 0) {
										cout << " (late for " << (dayCounter(bookHolder.at(i)->customerList.at(j).borrowDay, today) - bookHolder.at(i)->getBorrowDate())
										<< " day(s))\n";
										cout << "Sent email to " << bookHolder.at(i)->customerList.at(j).customerMail << "\n";
									}
									else cout << "\n";
								}
							}
						}
					}
					break;
				}
				case 7: {
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

				case 8: {
					Add(bookHolder, foundedBook, setID, indexOfBook);
					break;
				}

				case 9: {
					MoveBooks(bookHolder, setID, indexOfBook);
					break;
				}

				case 10:{
					CreateAcc(Acc);
					break;
				}

				case 11: {
					Exit(bookHolder,borrowedHolder,Acc);
					status = false;
					break;
				}

				default: {
					cout << "Invalid syntax, please retry!\n";
				}
        	}
		}
		else{
			userMenu();
			getChoice(choice);
			switch(choice){
				case 1:{
					cout << "Here are the book titles\' list\n";
					cout << "===================\n";
					for (int i = 0; i < (int) bookHolder.size(); i++) {
						cout << "\"" << bookHolder.at(i)->getTitle() << "\" by " << bookHolder.at(i)->getAuthor()
						<< " with " << bookHolder.at(i)->getQuantity() << " books.\n";
					}
					cout << "==================\n";
					break;
				}
				case 2:{
					do {
						cout << "=============================================\n";
						cout << "|Do you want to search by Title or Author  |\n";
						cout << "|1. Title                                  |\n";
						cout << "|2. Author                                 |\n";
						cout << "=============================================\n";
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
				case 3:{
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
				case 4:{
					Borrow(bookHolder, borrowedHolder, today, inputString);
					break;
				}
				case 5:{
					Return(bookHolder, borrowedHolder, today, inputString);
					break;
				}
				case 6:{

					break;
				}
				case 7:{
					Exit(bookHolder,borrowedHolder,Acc);
					status = false;
					break;
				}
				default: {
					cout << "Invalid syntax, please retry!\n";
				}
			}
		}
    }
    return 0;
}