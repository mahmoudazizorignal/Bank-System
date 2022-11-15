/*
	FCAI � OOP � 2022 - Assignment 2
	Program Description: Banking System
	Last Modification Date: 12 / 11 / 2022.
	Author1 and ID and Group: Mahmoud Mamdouh Abdelaziz - 20210376 - GROUP B
	Author2 and ID and Group: Aly Khaled Fekry - 20210244 - Group B
	Author3 and ID and Group: Yousuf Mohsen Mohamed - 20210549 - Group B
 */

#include "BankSystem.h"

void BankAccount::setAccountID(string id) {
	AccountID = id;
}
void BankAccount::setClient(Client* c) {
	client = c;
}

SavingBankAccount::SavingBankAccount(double balance, double minimumBalance) {
	if (balance >= minimumBalance) {
		Balance = balance;
		MinimumBalance = minimumBalance;
	}
	else {
		cout << "Your balance should be >= your minimum balance.\n";
		while (balance < minimumBalance) {
			cout << "Try Again!\n";
			cout << "Enter the balance then the minimum balance: ";
			cin >> balance >> minimumBalance;
		}
		Balance = balance;
		MinimumBalance = minimumBalance;
	}
}
bool SavingBankAccount::withdraw(double amount) {
	if (getBalance() - amount < MinimumBalance) {
		return false;
	}
	else {
		Balance -= amount;
		return true;
	}
}
bool SavingBankAccount::deposit(double amount) {
	if (amount < 100) {
		return false;
	}
	else {
		Balance += amount;
		return true;
	}
}
void SavingBankAccount::setBalance(double amount) {
	while (amount < MinimumBalance)
	{
		cout << "Your balance should be >= your minimum balance (";
		cout << MinimumBalance << ").\n";
		cout << "Enter The Balance: ";
		cin >> amount;
	}
	Balance = amount;
}