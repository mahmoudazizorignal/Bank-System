/*
	FCAI – OOP – 2022 - Assignment 2
	Program Description: Banking System
	Last Modification Date: 12 / 11 / 2022.
	Author1 and ID and Group: Mahmoud Mamdouh Abdelaziz - 20210376 - GROUP B
	Author2 and ID and Group: Aly Khaled Fekry - 20210244 - Group B
	Author3 and ID and Group: Yousuf Mohsen Mohamed - 20210549 - Group B
 */

#include "BankSystem.h"

Client::Client(string n, string a, string p, BankAccount* B) {
	Name = n;
	Address = a;
	Phone = p;
	Bank = B;
}
void Client::setName(string n) {
	Name = n;
}
void Client::setAddress(string a) {
	Address = a;
}
void Client::setPhone(string p) {
	Phone = p;
}
void Client::showBankInfo() {
	cout << "Account ID: " << Bank->getAccountID() << " (" << Bank->BankType() << ")\n";
	cout << "Balance: " << Bank->getBalance() << endl;
}
void Client::showAllInfo() {
	cout << "Name: " << Name << endl;
	cout << "Address: " << Address << endl;
	cout << "Phone: " << Phone << endl;
	showBankInfo();
}