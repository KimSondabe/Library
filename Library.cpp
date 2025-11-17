#include <iostream>
#include <vector>
using namespace std;

class Library{
	private : 
		int id;
		string title;
		string author;
		int quantity;
		int page;
	public :
		Library(int i, string t, string a, int q, int p){
			id = i;
			title = t;
			author = a;
			quantity = q;
			page = p;
		}
		
};
class Borrowable: public Library{
	private : 
		int start;
		int end;
		string costumer;
	public :
		Borrowable(int i, string t, string a, int q, int p, int s, int e, string c) :Library(i, t, a, q, p){
			start = s;
			end = e;
			costumer = c;
		}
		
};


int main(){

    int status = 1;
    int choice;
    int choice1;
    int choice2;
    int book_id;
    
    
    
    while(status){
        cout << "---------- Library ----------\n";
        cout << "1. Read data from file     \n";
        cout << "2. Write data to file      \n";
        cout << "3. List all book           \n";
        cout << "4. Find book               \n";
        cout << "5. Issue a book            \n"; // Lay x quyen sach
        cout << "6. Return a book           \n"; // Tra sach
        cout << "7. Sorting                 \n";
        cout << "8. Add a new book          \n";
        cout << "9. Exit                    \n";
        cout << "-----------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice){
            case 1:{
                cout << "1\n";
                break;}
            case 2:{
                cout << "2\n";
                break;}
            case 3:{
                cout << "3\n";
                break;}
            case 4:{
            	cout << "--------------------------------------------\n";
                cout << "Do you want to search by id, name or author \n";
                cout << "1. ID \n";
                cout << "2. Name \n";
                cout << "3. Author\n";
                cout << "--------------------------------------------\n";
                cout << "Enter your choice: "; cin >> choice1;
                if(choice1 == 1){
                	cout << "ID \n";
				} else if (choice1 == 2){
					cout << "Name\n";
				} else if (choice1 == 3){
					cout << "Author\n";
				}
                break;}
            case 5:{
                cout << "Which book do you want\n";
                cout << "Enter book's id : "; cin >> book_id;
                cout << book_id << "\n"; //Lay them ngay muon ngay tra
                break;}
            case 6:{
                cout << "6\n";
                break;}
            case 7:{
                cout << "7\n";
                break;}
            case 8:{
                cout << "8\n";
                break;}
            case 9:{
                cout << "Thanks for comming have a good day !\n";
                status = 0;
                break;}
        }
    }
    



    return 0;
}