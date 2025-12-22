#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>

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

        /* ======== Constructor ======== */
		Books(string id, string title, string author, string quantity, string page, string level, string zone, vector<customerInfo> customerList)
        : id(id), title(title), author(author), quantity(quantity), page(page), level(level), zone(zone), customerList(customerList) {}
		/* ======== Constructor ======== */

		/* ======== Getters ========*/
		string getID() {return id;}
		string getTitle() {return title;}
		string getAuthor() {return author;} 
		int getQuantity() {return stoi(quantity);}
		int getPages() {return stoi(page);}
		int getLevel() {return stoi(level);}
		string getZone() {return zone;}
		int getBorrowDate() {return (stoi(page) / 10 < 14) ? 14 : stoi(page) / 10;}
		/* ======== Getters ========*/

		/* ======== Setters ========*/
		void changeQuantity(int quantity) {
			quantity += stoi(this->quantity);
			this->quantity = ((quantity < 0) || (quantity > 999)) ? "0" : to_string(quantity);	
		}
        void setLevel(string level) {
            this->level = level;
        }
        void setZone(string zone) {
            this->zone = zone;
        }
		/* ======== Setters ========*/
};

class Account{
	private:
		string index;
		string username;
		string password;
		string role;
	public:
        /* ======== Constructor ======== */
		Account(string index, string username, string password, string role)
        : index(index), username(username), password(password), role(role) {}
        /* ======== Constructor ======== */

		/* ======== Getters ========*/
		string getUser(){return username;}
		string getPass(){return password;}
		string getRole(){return role;}
		string getIndex(){return index;}
		/* ======== Getters ========*/
		
		/* ======== Setters ========*/
		void setUser(string user){username = user;}
		void setPass(string pass){password = pass;}
		void setAdmin(string r){role = role;}
		void setIndex(int i){index = i;}
		/* ======== Setters ========*/

};

// books.cpp
void ReadFile(vector<Books*> &bookHolder, vector<BorrowedBookInfo> &borrowedHolder, vector<Account> &Acc, unordered_set<string> &setID, unordered_map<string,int> &indexOfBook); // Read data from file
void Write(const string filename, vector<Books*> &bookHolder); // Write data to file
void Write(const string filename, vector<Books*> &bookHolder, vector<BorrowedBookInfo> &borrowedHolder); // Write data to file (overload)
void Find(vector<Books*> &bookHolder, vector<Books*> &foundedBook, const string str, const int choice); // Find book by title/author
void Find(vector<Books*> &bookHolder, vector<Books*> &foundedBook, const string title, const string author); // Find book by title & author
void Add(vector<Books*> &bookHolder, vector<Books*> &foundedBook, unordered_set<string> &setID, unordered_map<string,int> &indexOfBook); // Add book(s)
void Borrow(vector<Books*> &bookHolder, vector<BorrowedBookInfo> &borrowedHolder, const string today, string &inputString); // Borrow book(s)
void Return(vector<Books*> &bookHolder, vector<BorrowedBookInfo> &borrowedHolder, const string today, string &inputString); // Return book(s)
void MoveBooks(vector<Books*> &bookHolder, unordered_set<string> &setID, unordered_map<string,int> &indexOfBook);

// account.cpp
bool CheckPass(vector<Account> &Acc, string username, string password); //Check password
bool CheckUser(vector<Account> &Acc, string username); //Check if username existed
string getIndexAcc(vector<Account> &Acc, string &username, string &password); //Get account index
bool isAdmin(vector<Account> &Acc, string index); //Check if the account is a admin
void Write(vector<Account> &Acc); //Write accounts to file
void CreateAcc(vector<Account> &Acc); // Create Acc
void DisplayAcc(vector<Account> &Acc); //Display Acc

// functions.cpp
string lowerCase(string str); // Convert string to lower case
bool capitalizeWords(string &s); // Capitalize first letter of each word
string idCounter(string prevID); // Generate next ID
void idInputChecker(vector<Books*> &bookHolder, string &inputString); // Check valid book ID input
bool isLeap(int year); // Check leap year
int daysInMonth(int month, int year); // Check number of days in month
bool dayFormatCheck(string &str); // Check if user has inserted the right dd/mm/yyyy format and normalize
int dayCounter(string start, string end); // Count number of days between two dates
string borrowDateCalculate(string start, int borrowDuration); // Calculate return date based on borrow date and duration
bool customerIDchecker(string &customerID); // Check valid customer ID input
void adminMenu();//UI Admin's Menu
void userMenu();//UI User's Menu
int getChoice(int &choice);//get userchoice
void Exit(vector<Books*> &bookHolder, vector<BorrowedBookInfo> &borrowedHolder, vector<Account> &Acc);//Exit

#endif 