#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "Bank.h"

using namespace std;

class Graph {
	vector<vector<int>> adj_matrix;
	unordered_map<int, string> customers;

public:
	Graph(int n) {
		adj_matrix = vector<vector<int>>(n, vector<int>(n, 0));
	}

	void add_edge(int u, int v) {
		adj_matrix[u][v] = 1;
		adj_matrix[v][u] = 1;
	}

	void add_customer(int customerId, const string& customerName) {
		customers[customerId] = customerName;
	}

	void show_accounts_related_to_customer(int customerId, Bank& bank) {
		vector<Account<double>*> accounts = bank.getAccountsForCustomer<double>(customerId);

		cout << "Accounts related to customer " << customers[customerId] << ":" << endl;
		for (auto& account : accounts) {
			cout << "Account Number: " << account->getAccountNum() << ", Balance: $" << account->getBalance() << endl;
		}
	}

	void print() {
		cout << "Adjacency Matrix (Customer Relationships):" << endl;
		int n = adj_matrix.size();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << adj_matrix[i][j] << " ";
			}
			cout << endl;
		}
	}
};
