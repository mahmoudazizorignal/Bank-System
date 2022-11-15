/*
	FCAI – OOP – 2022 - Assignment 2
	Program Description: Banking System
	Last Modification Date: 12 / 11 / 2022.
	Author1 and ID and Group: Mahmoud Mamdouh Abdelaziz - 20210376 - GROUP B
	Author2 and ID and Group: Aly Khaled Fekry - 20210244 - Group B
	Author3 and ID and Group: Yousuf Mohsen Mohamed - 20210549 - Group B
 */

#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H



#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

class Client;
class BankAccount
{
	protected:
		string AccountID;
		double Balance;
		Client* client;
	public:
		BankAccount() : Balance(0) {}
		BankAccount(double balance) : Balance(balance) {}
		virtual bool withdraw(double amount) {
			if (amount > Balance) {
				return false;
			}
			else {
				Balance -= amount;
				return true;
			}
		}
		virtual bool deposit(double amount) {
			Balance += amount;
			return true;
		}
		virtual void setBalance(double balance) {
			Balance = balance;
		}
		void setAccountID(string id);
		void setClient(Client* c);
		string getAccountID() { return AccountID; }
		double getBalance() { return Balance; }
		virtual double getMinimumBalance() { return 0; }
		virtual string BankType() { return "Basic"; }
};
class SavingBankAccount : public BankAccount
{
	private:
		double MinimumBalance;
	public:
		SavingBankAccount(double balance = 0, double minimumBalance = 0);
		bool withdraw(double amount);
		bool deposit(double amount);
		void setBalance(double amount);
		double getMinimumBalance() { return MinimumBalance; }
		string BankType() { return "Saving"; }
};
class Client {
	private:
		string Name;
		string Address;
		string Phone;
		BankAccount* Bank;
	public:
		Client(string n, string a, string p, BankAccount* B);
		void setName(string n);
		void setAddress(string a);
		void setPhone(string p);
		string getName() { return Name; }
		string getAddress() { return Address; }
		string getPhone() { return Phone; }
		string ClientBankType() { return Bank->BankType(); }
		BankAccount* getBank() { return Bank; }
		void showBankInfo();
		void showAllInfo();
};
class BankingApplication
{
	private:
		vector<Client*> users;
		void APP();
		void addClients();
		int CntIDs();
		void load();
		void save();
		void DisplayClients();
		void Disposit();
		void Withdraw();
	public:
		BankingApplication();
};



#endif