#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Bank.h"
#include "Transfer.h"
#include "Account.h"
#include "Customer.h"
#include "SQLiteFunctions.h"

using namespace std;

/**
 * @brief Merges two halves of a vector of accounts, sorted by balance.
 *
 * @param accounts The vector of accounts.
 * @param low The starting index of the first half.
 * @param mid The ending index of the first half.
 * @param high The ending index of the second half.
 */
void merge(vector<Bank::acc>& accounts, int low, int mid, int high);

/**
 * @brief Recursively performs merge sort on a vector of accounts.
 *
 * @param accounts The vector of accounts.
 * @param low The starting index.
 * @param high The ending index.
 */
void merge_recurse(vector<Bank::acc>& accounts, int low, int high);

/**
 * @brief Sorts a vector of accounts using merge sort.
 *
 * @param accounts The vector of accounts to sort.
 * @param length The number of accounts in the vector.
 */
void mergeSort(vector<Bank::acc>& accounts, int length);

/**
 * @brief Finds the lower bound of an account balance in a sorted vector using binary search.
 *
 * @param accounts The sorted vector of accounts.
 * @param minBalance The minimum balance to search for.
 * @return The index of the first account with a balance >= minBalance, or -1 if not found.
 */
int findLowerBound(const vector<Bank::acc>& accounts, double minBalance);

/**
 * @brief Retrieves accounts within a specified balance range.
 *
 * @param accounts The vector of accounts to filter.
 * @param minBalance The minimum balance of the range.
 * @param maxBalance The maximum balance of the range.
 * @return A vector of accounts within the specified balance range.
 */
vector<Bank::acc> getAccountsInBalanceRange(vector<Bank::acc>& accounts, double minBalance, double maxBalance);

/**
 * @brief Represents a node in the binary search tree for storing accounts.
 */
// Binary Search Tree for storing accounts
struct TreeNode {
    Bank::acc account; ///< The account stored in this node.
    TreeNode* left; ///< Pointer to the left child node.
    TreeNode* right; ///< Pointer to the right child node.

    /**
     * @brief Constructs a TreeNode with the given account.
     *
     * @param acc The account to store in the node.
     */
    TreeNode(Bank::acc acc) : account(acc), left(nullptr), right(nullptr) {}
};


class AccountBST {
private:
    TreeNode* root; ///< The root node of the BST.

    /**
     * @brief Inserts an account into the BST recursively.
     *
     * @param node The current node.
     * @param account The account to insert.
     * @return The updated node.
     */
    TreeNode* insert(TreeNode* node, Bank::acc account) {
        if (!node) return new TreeNode(account); // Create a new node if none exists
        if (account.accountNumber < node->account.accountNumber) {
            node->left = insert(node->left, account); // Recursively insert into left subtree
        } else {
            node->right = insert(node->right, account); // Recursively insert into right subtree
        }
        return node;
    }

    /**
     * @brief Performs an in-order traversal of the BST.
     *
     * @param node The current node.
     */
    void inorder(TreeNode* node) {
        if (!node) return; // Base case: empty tree
        inorder(node->left); // Recursively traverse left subtree
        printAccount(node->account); // Print the current node's account
        inorder(node->right); // Recursively traverse right subtree
    }

    /**
     * @brief Searches for an account in the BST by account number.
     *
     * @param node The current node.
     * @param accNumber The account number to search for.
     * @return A pointer to the account if found, or nullptr otherwise.
     */
    Bank::acc* search(TreeNode* node, const string& accNumber) {
        if (!node) return nullptr; // Account not found
        if (node->account.accountNumber == accNumber) return &node->account; // Account found, return it
        if (accNumber < node->account.accountNumber) {
            return search(node->left, accNumber); // Recursively search left subtree
        } else {
            return search(node->right, accNumber); // Recursively search right subtree
        }
    }

public:
    /**
     * @brief Constructs an empty AccountBST.
     */
    AccountBST() : root(nullptr) {}

    /**
     * @brief Prints the details of an account.
     *
     * @param acc The account to print.
     */
    void printAccount(const Bank::acc& acc) {
        cout << "Account ID: " << acc.accountId << "\n";
        cout << "User ID: " << acc.userId << "\n";
        cout << "Account Number: " << acc.accountNumber << "\n";
        cout << "Balance: " << acc.balance << "\n";
        cout << "Account Type: " << acc.accountType << "\n";
    }

    /**
     * @brief Inserts an account into the BST.
     *
     * @param account The account to insert.
     */
    void insert(Bank::acc account) {
        root = insert(root, account); // Insert a new account into the tree
    }

    /**
     * @brief Builds the BST from a vector of accounts.
     *
     * @param accounts The vector of accounts.
     */
    void buildTree(const vector<Bank::acc>& accounts) {
        for (const auto& account : accounts) {
            insert(account); // Insert each account into the tree
        }
    }

    /**
     * @brief Displays all accounts in the BST.
     */
    void displayAllAccounts() {
        inorder(root); // Print all accounts in the tree
    }

    /**
     * @brief Searches for an account by account number.
     *
     * @param accNumber The account number to search for.
     * @return A pointer to the account if found, or nullptr otherwise.
     */
    Bank::acc* searchAccount(const string& accNumber) {
        return search(root, accNumber);
    }

};

// Merge Sort Functions

/**
 * @brief Merges two halves of a vector of accounts during sorting.
 *
 * @param accounts The vector of accounts to merge.
 * @param low The starting index of the first half.
 * @param mid The ending index of the first half.
 * @param high The ending index of the second half.
 */
inline void merge(vector<Bank::acc>& accounts, int low, int mid, int high) {
    vector<Bank::acc> temp(high - low + 1);

    int i = low, j = mid + 1, k = 0;

    while (i <= mid && j <= high) {
        if (accounts[i].balance < accounts[j].balance) {
            temp[k++] = accounts[i++];
        }
        else {
            temp[k++] = accounts[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = accounts[i++];
    }

    while (j <= high) {
        temp[k++] = accounts[j++];
    }

    for (int i = low; i <= temp.size(); i++) {
        accounts[low + i] = temp[i];
    }
}


/**
 * @brief Recursively splits and merges a vector of accounts for merge sort.
 *
 * @param accounts The vector of accounts.
 * @param low The starting index.
 * @param high The ending index.
 */
inline void merge_recurse(vector<Bank::acc>& accounts, int low, int high) {
    if (low >= high) {
        return;
    }

    int mid = (low + high) / 2;
    merge_recurse(accounts, low, mid);
    merge_recurse(accounts, mid + 1, high);
    merge(accounts, low, mid, high);

}

/**
 * @brief Performs merge sort on a vector of accounts.
 *
 * @param accounts The vector of accounts to sort.
 * @param length The number of elements in the vector.
 */
inline void mergeSort(vector<Bank::acc>& accounts, int length) {
    merge_recurse(accounts, 0, length - 1);
}

/**
 * @brief Finds the index of the first account with a balance >= minBalance.
 *
 * @param accounts The sorted vector of accounts.
 * @param minBalance The minimum balance to search for.
 * @return The index of the account or -1 if not found.
 */
inline int findLowerBound(const vector<Bank::acc>& accounts, double minBalance) { // Binary Search: Returns the index of the first account with a balance greater than or equal to minBalance
    int low = 0, high = accounts.size() - 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (accounts[mid].balance < minBalance) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }

    return (accounts[low].balance >= minBalance) ? low : -1;
}

/**
 * @brief Retrieves accounts within a specified balance range.
 *
 * @param accounts The vector of accounts.
 * @param minBalance The minimum balance of the range.
 * @param maxBalance The maximum balance of the range.
 * @return A vector of accounts within the specified range.
 */
inline vector<Bank::acc> getAccountsInBalanceRange(vector<Bank::acc>& accounts, double minBalance, double maxBalance) {
    sort(accounts.begin(), accounts.end(), [](const Bank::acc& a, const Bank::acc& b) {
        return a.balance < b.balance; // Compare based on balance
        });
    //mergeSort(accounts, accounts.size());

    int startIdx = findLowerBound(accounts, minBalance);
    if (startIdx == -1) return {};

    vector<Bank::acc> filteredAccounts;
    for (int i = startIdx; i < accounts.size() && accounts[i].balance <= maxBalance; i++) {
        filteredAccounts.push_back(accounts[i]);
    }

    return filteredAccounts;
}