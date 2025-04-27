#pragma once

#include <string>
#include <vector>
#include "Account.h"
#include "sqlite3.h"
#include "StructuresAndAlgorithms.h"
using namespace std;

/**
 * @file Customer.h
 * @brief Defines the Customer class for managing customer information, transactions, and help requests.
 */

 /**
  * @class Customer
  * @brief Represents a bank customer, including their accounts, transaction history, and support requests.
  */
class Customer {
private:
    int id; ///< Unique ID of the customer in the database.
    string name; ///< Full name of the customer.
    string username; ///< Unique username for customer login.
    string pin; ///< Personal Identification Number (PIN) for authentication.

    /**
     * @struct Transaction
     * @brief Represents a single transaction in the customer's history.
     */
    struct Transaction {
        string type; ///< Type of transaction (e.g., "Deposit", "Withdrawal").
        double amount; ///< Amount involved in the transaction.
        string timestamp; ///< Timestamp of the transaction.
        Transaction* next; ///< Pointer to the next transaction in the linked list.

        /**
         * @brief Constructs a Transaction object.
         * @param type Type of transaction.
         * @param amount Amount involved in the transaction.
         * @param timestamp Timestamp of the transaction.
         */
        Transaction(const string& type, double amount, const string& timestamp)
            : type(type), amount(amount), timestamp(timestamp), next(nullptr) {
        }
    };

    Transaction* transactionHead; ///< Head pointer for the transaction history linked list.
    CustomStack<Transaction*> undoStack; ///< Stack to store transactions for undo functionality.
    CustomQueue<string> helpRequestQueue; ///< Queue to manage customer help requests.

public:
    /**
     * @brief Default constructor for the Customer class.
     */
    Customer();

    /**
     * @brief Constructs a Customer object with specified details.
     * @param id Unique ID of the customer.
     * @param name Full name of the customer.
     * @param username Username for the customer.
     * @param pin PIN for the customer's account.
     */
    Customer(int id, const string& name, const string& username, const string& pin);

    /**
     * @brief Destructor for the Customer class.
     */
    ~Customer();

    // Getters

    /**
     * @brief Retrieves the ID of the customer.
     * @return The customer's unique ID.
     */
    int getId() const;

    /**
     * @brief Retrieves the name of the customer.
     * @return The customer's full name.
     */
    const string& getName() const;

    /**
     * @brief Retrieves the username of the customer.
     * @return The customer's username.
     */
    const string& getUsername() const;

    // Behavior methods

    /**
     * @brief Verifies the customer's PIN.
     * @param inputPin The PIN input by the user.
     * @return True if the PIN matches, false otherwise.
     */
    bool verifyPin(const string& inputPin) const;

    /**
     * @brief Generates a filename for a transaction receipt.
     * @return A string containing the generated filename.
     */
    string generateTransactionReceiptFilename();

    /**
     * @brief Generates a transaction receipt.
     * @param transaction A description of the transaction.
     */
    void generateTransactionReceipt(const string& transaction);

    // Transaction methods

    /**
     * @brief Adds a new transaction to the customer's history.
     * @param type The type of transaction (e.g., "Deposit").
     * @param amount The amount involved in the transaction.
     * @param timestamp The timestamp of the transaction.
     */
    void addTransaction(const string& type, double amount, const string& timestamp);

    /**
     * @brief Undoes the last transaction in the customer's history.
     */
    void undoTransaction();

    /**
     * @brief Adds a help request to the customer's queue.
     * @param request The help request string.
     */
    void addHelpRequest(const string& request);

    /**
     * @brief Removes the next help request from the customer's queue.
     * @return True if a help request was removed, false otherwise.
     */
    bool removeHelpRequest();

    /**
     * @brief Retrieves all help requests from the customer's queue.
     * @return A queue containing all help requests.
     */
    CustomQueue<string>& getHelpRequests();

    /**
     * @brief Displays the customer's transaction history.
     */
    void displayTransactionHistory(); // To integrate with FTXUI
};