/*
	FCAI – OOP – 2022 - Assignment 2
	Program Description: Banking System
	Last Modification Date: 12 / 11 / 2022.
	Author1 and ID and Group: Mahmoud Mamdouh Abdelaziz - 20210376 - GROUP B
	Author2 and ID and Group: Aly Khaled Fekry - 20210244 - Group B
	Author3 and ID and Group: Yousuf Mohsen Mohamed - 20210549 - Group B
 */

#include "BankSystem.h"

void BankingApplication::APP() {
	while (true) {
		int choice;
		cout << "Welcome to FCAI Banking Application\n";
		cout << "1. Create a New Account\n2. List Clients and Accounts\n";
		cout << "3. Withdraw Money\n4. Deposit Money\n5. Exit The System\n";
		cout << "Please Enter Choice =========> ";
		cin >> choice;
		cin.ignore();
		if (choice == 1) addClients();
		else if (choice == 2) DisplayClients();
		else if (choice == 3) Withdraw();
		else if (choice == 4) Disposit();
		else {
			cout << "Exiting The System....\n";
			Sleep(5000);
			return;
		}
		Sleep(5000);
		system("cls");
	}
}
void BankingApplication::addClients() {
	load();
	string n, a, p;
	double b, mb;
	int t;

	cout << "Please Enter Client Triple Name(i.e. Aly Amr Aly) =========> ";
	getline(cin, n);

	cout << "Please Enter Client Address(i.e. 24st Talaat Harb, Giza) =======> ";
	getline(cin, a);

	cout << "Please Enter Client Phone =======> ";
	getline(cin, p);
	cout << "What Type of Account Do You Like? (1) Basic (2) Saving - Type 1 or 2 =========> ";
	cin >> t;
	cin.ignore();
	cout << "Please Enter the Starting Balance =========> ";
	cin >> b;
	cin.ignore();

	BankAccount* account;
	Client* user;
	if (t == 2)
	{
		cout << "Please Enter the Minimum Balance =========> ";
		cin >> mb;
		cin.ignore();
		account = new SavingBankAccount(b, mb);
	}
	else
	{
		account = new BankAccount(b);
	}
	string id = to_string(CntIDs());
	while (id.size() < 3) id.insert(0, 1, '0');
	account->setAccountID("FCAI-" + id);
	user = new Client(n, a, p, account);
	account->setClient(user);
	users.push_back(user);
	cout << "An account was created with ID " << account->getAccountID();
	cout << " and Starting Balance " << account->getBalance() << " L.E.\n";
	cout << "-----------------------------------------------------------------------\n";
	save();
}
int BankingApplication::CntIDs() {
	int cnt = 0;
	ifstream input;
	input.open("Client - Bank Account.txt", ios::in);
	for (int i : {0, 1}) {
		string temp;
		getline(input, temp);
	}
	while (!input.eof() && !input.fail()) {
		string tmp;
		getline(input, tmp);
		cnt++;
	}
	input.close();
	return cnt;
}
void BankingApplication::load() {
	users.clear();
	fstream read;
	read.open("Client - Bank Account.txt", ios::in);
	for (int i : {0, 1}) {
		string temp;
		getline(read, temp);
	}

	while (!read.eof() && !read.fail()) {
		string line;
		getline(read, line);
		istringstream ss(line);
		string n, a, p, id, t, mb;
		double b;
		for (int i : {0, 1, 2}) {
			string temp;
			ss >> temp;
			n += temp += " ";
		}
		for (; ;) {
			string temp;
			ss >> temp;
			if (temp.size() > 2 && isdigit(temp[2])) {
				p = temp;
				break;
			}
			a += temp += " ";
		}
		//ss >> p;
		ss >> id;
		ss >> b;
		ss >> t;
		ss >> mb;
		BankAccount* account;
		Client* user;
		if (t == "Saving")
		{
			account = new SavingBankAccount(b, stod(mb));
		}
		else
		{
			account = new BankAccount(b);
		}
		account->setAccountID(id);
		user = new Client(n, a, p, account);
		account->setClient(user);
		users.push_back(user);
	}
	read.close();
}
void BankingApplication::save() {
	fstream write;
	write.open("Client - Bank Account.txt", ios::out);
	write << setw(30) << left << "|Name" << "";
	write << setw(30) << left << "|Address" << "";
	write << setw(15) << left << "|Phone" << "";
	write << setw(10) << left << "|ID" << "";
	write << setw(17) << left << "|Balance" << "";
	write << setw(13) << left << "|BankType" << "";
	write << "|Minimum Balance|" << endl;
	write << "===================================================";
	write << "===========================================";
	write << "======================================";
	if (users.size() > 0) write << endl;
	for (size_t i = 0; i < users.size(); i++)
	{
		write << " " << setw(29) << left << users[i]->getName() << "";
		write << " " << setw(29) << left << users[i]->getAddress() << "";
		write << " " << setw(14) << left << users[i]->getPhone() << "";
		write << " " << setw(9) << left << users[i]->getBank()->getAccountID() << "";
		write << " " << setw(16) << left << users[i]->getBank()->getBalance() << "";
		write << " " << setw(12) << left << users[i]->getBank()->BankType() << "";
		write << " " << users[i]->getBank()->getMinimumBalance();
		if (i < users.size() - 1) {
			write << endl;
		}
	}
	write.close();
}
void BankingApplication::DisplayClients() {
	load();
	for (size_t i = 0; i < users.size(); i++)
	{
		cout << "--------------------------";
		cout << users[i]->getName() << "--------------------------\n";
		cout << "Address: " << users[i]->getAddress() << endl;
		cout << "Phone: " << users[i]->getPhone() << endl;
		cout << "Account ID: " << users[i]->getBank()->getAccountID();
		cout << " (" << users[i]->ClientBankType() << ")\n";
		cout << "Balance: " << users[i]->getBank()->getBalance() << endl;
		cout << "Min. Balance: " << users[i]->getBank()->getMinimumBalance() << endl;
	}
}
void BankingApplication::Disposit() {
	load();
	string id;
	double amount;
	cout << "Please Enter Account ID (e.g., FCAI-015) =========> ";
	cin >> id;
	cin.ignore();

	size_t i = 0;
	for (; i < users.size(); i++)
	{
		if (users[i]->getBank()->getAccountID() == id) break;
	}
	cout << "Account ID: " << users[i]->getBank()->getAccountID() << endl;
	cout << "Acocunt Type: " << users[i]->ClientBankType() << endl;
	cout << "Balance: " << users[i]->getBank()->getBalance() << endl;

	cout << "Please Enter The Amount to deposit =========> ";
	cin >> amount;
	cin.ignore();
	while (!users[i]->getBank()->deposit(amount)) {
		cout << "Sorry. This is less than what you can deposit.\n";
		cout << "Please Enter The Amount to deposit =========> ";
		cin >> amount;
		cin.ignore();
	}
	cout << "Thank You.\n";
	cout << "Account ID: " << users[i]->getBank()->getAccountID() << endl;
	cout << "New Balance: " << users[i]->getBank()->getBalance() << endl;
	save();
}
void BankingApplication::Withdraw() {
	load();
	string id;
	double amount;
	cout << "Please Enter Account ID (e.g., FCAI-015) =========> ";
	cin >> id;
	cin.ignore();

	size_t i = 0;
	for (; i < users.size(); i++)
	{
		if (users[i]->getBank()->getAccountID() == id) break;
	}
	if (i < users.size() && users[i]->getBank()->getAccountID() == id) {
		cout << "Account ID: " << users[i]->getBank()->getAccountID() << endl;
		cout << "Acocunt Type: " << users[i]->ClientBankType() << endl;
		cout << "Balance: " << users[i]->getBank()->getBalance() << endl;

		cout << "Please Enter The Amount to withdraw =========> ";
		cin >> amount;
		cin.ignore();
		while (!users[i]->getBank()->withdraw(amount)) {
			cout << "Sorry. This is more than what you can withdraw.\n";
			cout << "Please Enter The Amount to withdraw =========> ";
			cin >> amount;
			cin.ignore();
		}
		cout << "Thank You.\n";
		cout << "Account ID: " << users[i]->getBank()->getAccountID() << endl;
		cout << "New Balance: " << users[i]->getBank()->getBalance() << endl;
	}
	else {
		cout << "Sorry. ID is not found in the bank system\n";
		return Withdraw();
	}
	save();
}
BankingApplication::BankingApplication() {
	APP();
}