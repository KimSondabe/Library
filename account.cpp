#include "library.h"

bool CheckPass(vector<Account> &Acc, string username, string password){
	for(int i = 0; i < Acc.size(); i++){
		if(username == Acc.at(i).getUser()){
			if(password == Acc.at(i).getPass()){
				return true; //Check acccount when sign in 
			}
			
		}
	}
	return false;
}

string getIndexAcc(vector<Account> &Acc, string &username, string &password){
	for(int i = 0; i < Acc.size(); i++){
		if((username == Acc.at(i).getUser()) && (password == Acc.at(i).getPass())){
			return to_string(i);
		}
	}
	return "";
}

bool isAdmin(vector<Account> &Acc, string index){
	int i = stoi(index);
	if(Acc.at(i).getRole() == "admin"){return true;}
	return false;
}

bool CheckUser(vector<Account> &Acc, string username){
	for(int i = 0; i < Acc.size(); i++){
		if(username == Acc.at(i).getUser()){
			return true;
		}
	}
	return false;
}

void Write(vector<Account> &Acc){
	ofstream output("account.txt");
	
	for(int i = 0; i < (int)Acc.size(); i++){
		output << Acc.at(i).getIndex() << "|" << Acc.at(i).getUser() << "|" << Acc.at(i).getPass() << "|" << Acc.at(i).getRole() << "|\n";
	}
	output.close();
	cout << "===== Wrote to \"account.txt\" =====\n";
}

void CreateAcc(vector<Account> &Acc){
	string username, password, role;
	do{
		cout << "Create account\n";
		cout << "Username: "; cin >> username;
		cout << "Password: "; cin >> password;
		if(CheckUser(Acc, username)){
			cout << "Existed Username\n";
		}else{
			cout << "Account's Role: "; cin >> role;
			Account acc(to_string(1 + Acc.size()),username, password, role);
			Acc.push_back(acc);			
			break;
		}
	}while(true);
	cout << "====Create account successfully ====\n";
}

void DisplayAcc(vector<Account> &Acc){
	for(int i = 0; i < Acc.size(); i++){
		cout << Acc.at(i).getIndex() << "|" << Acc.at(i).getUser() << "|" << Acc.at(i).getPass() <<"|"<< Acc.at(i).getRole() << "|\n";
	}
}