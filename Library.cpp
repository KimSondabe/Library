#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Library{
	private : 
		int id;
		string title;
		string author;
		int quantity;
		int page;
	public :
		vector<Library> librarian;
		Library(int i, string t, string a, int q, int p){
			id = i;
			title = t;
			author = a;
			quantity = q;
			page = p;
		}
		int getnb(){
			int nb;
			string buffer;
			ifstream f("library.txt");
			getline(f, buffer);
			return nb = stoi(buffer.c_str());
		}
		void Read(){
			int nb = getnb();
			string buffer, t, a;
			int i, q, p;
			librarian.clear();
			
			ifstream f("library.txt");
			getline(f, buffer);
			for(int j = 0; j < nb; j++){
				getline(f, buffer);
				i = stoi(buffer.c_str());
				getline(f, buffer);
				t = buffer;
				getline(f, buffer);
				a = buffer;
				getline(f, buffer);
				q = stoi(buffer.c_str());
				getline(f, buffer);
				p = stoi(buffer.c_str());
				Library lib(i, t, a, q, p);
				librarian.push_back(lib);
			}
			f.close();
		}
		string toString(){
			return to_string(id) + "\n" + title + "\n" + author + "\n" + to_string(quantity) + "\n" + to_string(page) + "\n";
		}
		void List(){
			Read();
			for(int j = 0; j < librarian.size(); j++){
				cout << librarian.at(j).toString();
			}
		
		}
		void Write(){
			ofstream f("output.txt");
			f << getnb() << "\n";
			for(int i = 0; i < getnb(); i++){
				f << librarian[i].toString(); 
			}
			f.close();
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
    int i, q, p;
    string t, a;
    Library* l = new Library(i, t, a, q, p);
    
    
    
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
                l->Read();
                cout << "Data read " << l->getnb() << " books\n"; 
                break;}
            case 2:{
            	l->Write();
                break;}
            case 3:{
                l->List();
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
                cout << "5\n";
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
