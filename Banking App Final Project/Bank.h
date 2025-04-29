#pragma once
#include <string>
#include <iostream>
#include "sqlite3.h"
#include "Customer.h"
#include "SavingsAccount.h"
using namespace std;


/**
 * @file Bank.h
 * @brief Defines the Bank class for managing banking operations and accounts.
 */

 /**
  * @class Bank
  * @brief Represents a banking system that manages customers, accounts, and database operations.
  */
class Bank
{
private:
	sqlite3* db; ///< Pointer to the SQLite database connection.

	/**
	 * @brief Creates the necessary tables in the database.
	 * @return True if tables were created successfully, false otherwise.
	 */
	bool createTables();

	/**
	 * @brief Executes a SQL query on the database.
	 * @param query The SQL query string to execute.
	 * @param stmt Pointer to an SQLite statement object (optional).
	 * @return True if the query executed successfully, false otherwise.
	 */
	bool executeSQL(const string& query, sqlite3_stmt** stmt = nullptr);

	/**
	 * @brief Retrieves the user ID based on the username.
	 * @param username The username of the customer.
	 * @return The user ID if the username exists, -1 otherwise.
	 */
	int getUserId(const string& username);

	int accountNumberCounter = 100000; ///< Counter for generating unique account numbers.
public:

	/**
	 * @struct acc
	 * @brief Represents an account record in the bank.
	 */
	struct acc {
        string accountHolder;
		int accountId; ///< The unique ID of the account.
		int userId; ///< The ID of the user owning the account.
		string accountNumber; ///< The unique account number.
		double balance; ///< The current balance of the account.
		string accountType; ///< The type of the account (e.g., Savings, Checking).
	};

	/**
	 * @brief Constructs a Bank object and opens the database connection.
	 * @param dbName The name of the SQLite database file.
	 */
	Bank(const string& dbName); // Constructor to open database

	/**
	 * @brief Destructs the Bank object and closes the database connection.
	 */
	~Bank(); 

    /**
     * @brief Registers a new customer in the bank.
     * @param name The full name of the customer.
     * @param username The username of the customer.
     * @param pin The PIN for the customer's account.
     * @return True if registration was successful, false otherwise.
     */
    bool registerCustomer(const string& name, const string& username, const string& pin);

    /**
     * @brief Logs in a customer to the bank system.
     * @param username The username of the customer.
     * @param pin The PIN for the customer's account.
     * @return A pointer to the Customer object if login is successful, nullptr otherwise.
     */
    Customer* login(const string& username, const string& pin);

    /**
     * @brief Adds a new account for a customer.
     * @param userId The ID of the user owning the account.
     * @param accountNumber The unique account number.
     * @param initialBalance The initial balance of the account.
     * @param accountType The type of the account (e.g., Savings, Checking).
     * @return True if the account was added successfully, false otherwise.
     */
    bool addAccountForCustomer(int userId, const string& accountNumber, double initialBalance, const string& accountType);

    /**
     * @brief Retrieves all accounts associated with a customer.
     * @tparam T The account type (e.g., SavingsAccount).
     * @param userId The ID of the customer.
     * @return A vector of pointers to Account objects.
     */
    template <typename T>
    vector<Account<T>*> getAccountsForCustomer(int userId);

    /**
     * @brief Retrieves an account by its account number.
     * @tparam T The account type (e.g., SavingsAccount).
     * @param accountNumber The account number to search for.
     * @return A pointer to the Account object if found, nullptr otherwise.
     */
    template <typename T>
    Account<T>* getAccountByNumber(const string& accountNumber);

    /**
     * @brief Updates the balance of an account.
     * @param accountId The ID of the account to update.
     * @param newBalance The new balance to set.
     * @return True if the balance was updated successfully, false otherwise.
     */
    bool updateAccountBalance(int accountId, double newBalance);

    /**
     * @brief Removes an account from the bank.
     * @param accountNumber The account number of the account to remove.
     * @return True if the account was removed successfully, false otherwise.
     */
    bool accountRemoveAccount(const string& accountNumber);

    /**
     * @brief Generates a unique account number.
     * @param accountType The type of account for which the number is generated.
     * @return The generated account number.
     */
    int generateAccountNumber(const int accountType);

    /**
     * @brief Checks if an account number already exists in the bank.
     * @param accountNumber The account number to check.
     * @return True if the account number exists, false otherwise.
     */
    bool accountNumberExists(const string& accountNumber);

    /**
     * @brief Fetches all accounts from the database.
     * @return A vector of acc structs representing the accounts.
     */
    vector<acc> fetchAccountsFromDatabase();
};

