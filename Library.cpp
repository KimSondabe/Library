#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Library{
	private : 
		string id;
		string title;
		string author;
		string quantity;
		string page;
	public :
		vector<Library> librarian;
		Library(string id, string title, string author, string quantity, string page){
			this->id = id;
			this->title = title;
			this->author = author;
			this->quantity = quantity;
			this->page = page;
		}

		int getQuantity() {return stoi(quantity);}
		
		void Read();
		void View();
		void Write();
		void Find(const string str, const int choice);
};
class Borrowable: public Library{
	private : 
		string start;
		string end;
		string costumer;
	public :
		Borrowable(string id, string title, string author, string quantity, string page, string start, string end, string costumer) :Library(id, title, author, quantity, page){
			this->start = start;
			this->end = end;
			this->costumer = costumer;
		}
		
};

void Library::Read(){
	string buffer, title, author, id, quantity, page;
	librarian.clear();
	
	ifstream file("library.txt");

	while (getline(file, buffer)){
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
		Library lib(id, title, author, quantity, page);
		librarian.push_back(lib);
	}

	file.close();
}

void Library::View(){
	Read();
	cout << "Here are the book titles\' list\n";
	cout << "---------------\n";

	for (vector<Library>::size_type i = 0; i < librarian.size(); i++){
		cout << "\"" << librarian.at(i).title << "\" by " << librarian.at(i).author
		<< "with" << quantity << "books.\n";
	}

	cout << "---------------\n";
}

void Library::Write(){
	Read();
	ofstream output("libraryCopy.txt");

	for (vector<Library>::size_type i = 0; i < librarian.size(); i++) {
		output << librarian.at(i).id << "|" << librarian.at(i).title << "|" 
		<< librarian.at(i).author << "|" << librarian.at(i).quantity << "|"
		<< librarian.at(i).page << "|\n";
	}

	output.close();
	cout << "Copied to \"libraryCopy.txt\"\n";
}

void Library::Find(const string str, const int choice) {
	string buffer, id, title, author, quantity, page;
	librarian.clear();

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
		Library lib(id, title, author, quantity, page);

		if (choice == 1) {
			if (lib.title == str) {
				librarian.push_back(lib);
			}
		}
		else if (choice == 2) {
			if (lib.author == str) {
				librarian.push_back(lib);
			}
		}
	}

	file.close();

	int sum = 0;
	for (vector<Library>::size_type i = 0; i < librarian.size(); i++) {
		sum += stoi(librarian.at(i).quantity);
	}

	cout << "There are " << sum << " books match with your choice\n";
	if (sum != 0) {
		cout << "They are: \n";
		for (vector<Library>::size_type i = 0; i < librarian.size(); i++){
			cout << "\"" << librarian.at(i).title << "\" by " << librarian.at(i).author
			<< " with " << quantity << " books.\n";
		}
	}

	
}
int main(){

    int status = 1;
	int quantitiesSum = 0;
    int choice;
    int searchChoice;
	string searchString;
    string title, author, id, quantity, page;
    Library* lib = new Library(id, title, author, quantity, page);
    
    
    
    while (status){

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

        switch(choice){
            case 1:{
                lib->Read();

				for (vector<Library>::size_type i = 0; i < lib->librarian.size(); i++) {
					quantitiesSum += lib->librarian.at(i).getQuantity();
				}

                cout << "There are " << lib->librarian.size() << " book titles & " 
				<< quantitiesSum << " books in total\n"; 
				quantitiesSum = 0;
                break;
			}

            case 2:{
				lib->Write();
                break;
			}

            case 3:{
                lib->View();
                break;
			}

            case 4:{
            	cout << "--------------------------------------------\n";
                cout << "|Do you want to search by Title or Author  |\n";
                cout << "|1. Title                                  |\n";
                cout << "|2. Author                                 |\n";
                cout << "--------------------------------------------\n";
                cout << "Enter your choice: "; cin >> searchChoice;

				if(searchChoice == 1){
                	cout << "Title you want to search for: ";
					cin.ignore();
					getline(cin, searchString);
					cout << "\n";
					lib->Find(searchString, searchChoice);
				} 
				else if (searchChoice == 2){
                	cout << "Author you want to search for: ";
					cin.ignore();
					getline(cin, searchString);
					cout << "\n";
					lib->Find(searchString, searchChoice);
				}
                break;
			}

            case 5:{
                cout << "5\n";
                break;
			}

            case 6:{
                cout << "6\n";
                break;
			}

            case 7:{
                cout << "7\n";
                break;
			}

            case 8:{
                cout << "8\n";
                break;
			}

            case 9:{
                cout << "Thanks for comming have a good day !\n";
                status = 0;
                break;
			}

			default: {
				cout << "Invalid syntax, please retry!";
			}
        }
    }
    



    return 0;
}
