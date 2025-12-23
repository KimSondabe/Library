#include "library.h"

/*------ General Function ------*/
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

/*------ Books Function ------*/
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

bool customerIDchecker(string &customerID) {
	if (customerID.length() != 12) {
		cout << "Invalid input, please try again.\n";
		return false;
	}
	for (char c : customerID) {
		if (!isdigit((unsigned char)c)) {
			cout << "Invalid input, please try again.\n";
			return false;
		}
	}
	return true;
}

/*-------- Date Function --------*/
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

/*-------- UI Function --------*/

void adminMenu(){
    cout << "\n";
	cout << "============== Library ==============\n";
	cout << "|1. Number of books                 |\n"; // Done
	cout << "|2. Store data into other file      |\n"; // Done
    cout << "|3. View all books                  |\n"; // Done
	cout << "|4. View all accounts               |\n"; //Done
	cout << "|5. Find book                       |\n"; // Done
    cout << "|6. View book borrower(s)           |\n"; // Done
	cout << "|7. Report book's issue             |\n"; // Done
	cout << "|8. Add book(s)                     |\n"; // Done
	cout << "|9. Move book(s) to another place   |\n"; // To be done
	cout << "|10. Create an account              |\n"; //Undone
	cout << "|11. Exit                           |\n"; // Done
	cout << "=====================================\n";
}

void userMenu(){
    cout << "\n";
	cout << "============== Library ==============\n";
	cout << "|1. View all books                  |\n"; // Done
	cout << "|2. Find book                       |\n"; // Done
    cout << "|3. Report book's issue             |\n"; // Done
	cout << "|4. Borrow book (s)                 |\n"; // Done
	cout << "|5. Return book (s)                 |\n"; // Done
    cout << "|6. Profile                         |\n"; // Done
	cout << "|7. Exit                            |\n"; // Done
	cout << "=====================================\n";
}

int getChoice(int &choice){
    cout << "Enter your choice: ";
    cin >> choice;
	cin.ignore();
	cout << "\n";
    return choice;
}

void Exit(vector<Books*> &bookHolder, vector<BorrowedBookInfo> &borrowedHolder, vector<Account> &Acc){
    Write("books.txt", bookHolder, borrowedHolder);
    Write(Acc);
	for (int i = 0; i < (int) bookHolder.size(); i++)  // Clean up data
	delete bookHolder.at(i);
	cout << "\nThanks for comming have a good day !\n";
}