/**
 * @file BankTests.cpp
 * @brief Unit tests for the banking system using Google Test framework.
 */


#ifdef RUN_TESTS
#include <gtest/gtest.h>
#include "Bank.h"
#include "Customer.h"
#include "Account.h"
#include "Transfer.h"
#include "Admin.h"
#include "UIUtilities.h"


 /**
  * @struct MockAccount
  * @brief Mock structure for testing account-related functionalities.
  */
// Mock data structure for testing
struct MockAccount : Bank::acc {
	/**
	 * @brief Constructor for MockAccount.
	 * @param id The account ID.
	 * @param userId The user ID associated with the account.
	 * @param accountNumber The account number.
	 * @param balance The initial balance of the account.
	 * @param accountType The type of the account (e.g., Savings, Regular).
	 */
	MockAccount(int id, int userId, std::string accountNumber, double balance, std::string accountType) {
		this->accountId = id;
		this->userId = userId;
		this->accountNumber = accountNumber;
		this->balance = balance;
		this->accountType = accountType;
	}
};

/**
 * @test SystemTest::RegisterCustomer
 * @brief Tests customer registration functionality, including handling duplicate usernames.
 */
// Test Case 1
TEST(SystemTest, RegisterCustomer) {
	Bank testBank("test.db");

	cout << "Step 1: Registering a new customer...\n";
	// Register a new customer
	ASSERT_TRUE(testBank.registerCustomer("John Mathis", "jmathis7", "1113"));

	cout << "Step 2: Attempting to register a duplicate username...\n";
	// Try to register a customer with the same username
	ASSERT_FALSE(testBank.registerCustomer("Juan Mathis", "jmathis7", "1234"));
}

/**
 * @test SystemTest::LoginCustomer
 * @brief Tests customer login functionality, including valid and invalid login attempts.
 */
// Test Case 2
TEST(SystemTest, LoginCustomer) {
	Bank testBank("test.db");

	// Register and log in
	cout << "Step 1: Registering a new user and logging in...\n";
	testBank.registerCustomer("Jane Doe", "janedoe", "5678");
	Customer* customer = testBank.login("janedoe", "5678");

	cout << "Checking if customer was successfully logged in...\n";
	ASSERT_NE(customer, nullptr);
	EXPECT_EQ(customer->getName(), "Jane Doe");

	// Try logging in with incorrect password
	cout << "Attempting to log in with a wrong password...\n";
	Customer* failedCustomerLogin = testBank.login("janedoe", "wrongpassword");
	ASSERT_EQ(failedCustomerLogin, nullptr);
}

/**
 * @test SystemTest::CreateAccount
 * @brief Tests account creation for registered customers and validation of account details.
 */
// Test Case 3
TEST(SystemTest, CreateAccount) {
	// Create a Bank object with the test database
	Bank testBank("test.db");

	// Step 1: Register a new customer
	cout << "Step 1: Register a new customer...\n";
	ASSERT_TRUE(testBank.registerCustomer("Zachary C", "xXxZacAttacxXx", "0707"));
	Customer* customer = testBank.login("xXxZacAttacxXx", "0707");
	ASSERT_NE(customer, nullptr) << "Failed to log in after registration.";

	// Step 2: Create two new accounts
	cout << "Step 2: Create two new accounts...\n";
	int accNum1 = testBank.generateAccountNumber(1);
	ASSERT_TRUE(testBank.addAccountForCustomer(customer->getId(), to_string(accNum1), 1000.00, "Savings"))
		<< "Failed to create a savings account.";

	int accNum2 = testBank.generateAccountNumber(1);
	ASSERT_TRUE(testBank.addAccountForCustomer(customer->getId(), to_string(accNum2), 500.00, "Regular"))
		<< "Failed to create a regular account.";

	// Step 3: Validate the accounts
	cout << "Step 3: Check the two new accounts...\n";
	Account<double>* account1 = testBank.getAccountByNumber<double>(to_string(accNum1));
	Account<double>* account2 = testBank.getAccountByNumber<double>(to_string(accNum2));

	ASSERT_NE(account1, nullptr) << "Savings account not found.";
	ASSERT_NE(account2, nullptr) << "Regular account not found.";
	EXPECT_EQ(account1->getBalance(), 1000) << "Savings account balance mismatch.";
	EXPECT_EQ(account2->getBalance(), 500) << "Regular account balance mismatch.";
}


/**
 * @test SystemTest::DepositFunds
 * @brief Tests deposit functionality for a customer's account.
 */
// Test Case 4
TEST(SystemTest, DepositFunds) {
	Bank testBank("test.db");
	cout << "Step 1: Login...\n";
	Customer* customer = testBank.login("xXxZacAttacxXx", "0707");
	ASSERT_NE(customer, nullptr) << "Failed to log in.";

	// Create new accounts
	cout << "Step 2: Create a new account...\n";
	int accNum = testBank.generateAccountNumber(1);
	ASSERT_TRUE(testBank.addAccountForCustomer(customer->getId(), to_string(accNum), 1000.00, "Savings")) << "Failed to create a savings account.";

	// Fetch the account by number and check the balance
	Account<double>* account = testBank.getAccountByNumber<double>(to_string(accNum));
	ASSERT_NE(account, nullptr) << "Failed to retrieve account";
	EXPECT_EQ(account->getBalance(), 1000.0) << "Account balance mismatch";
}

/**
 * @test SystemTest::WithdrawFunds_SufficientFunds
 * @brief Tests withdrawal functionality when sufficient funds are available.
 */
// Test Case 5
TEST(SystemTest, WithdrawFunds_SufficientFunds) {
	Bank testBank("test.db");
	cout << "Step 1: Login...\n";
	Customer* customer = testBank.login("jmathis7", "1113");

	// Create new accounts
	cout << "Step 2: Create a new account...\n";
	int accNum = testBank.generateAccountNumber(1);
	ASSERT_TRUE(testBank.addAccountForCustomer(customer->getId(), to_string(accNum), 1000.00, "Savings"));

	// Check account creation
	cout << "Step 3: Check account balance...\n";
	Account<double>* account1 = testBank.getAccountByNumber<double>(to_string(accNum));
	account1->withdraw(500.00);
	EXPECT_EQ(account1->getBalance(), 500.00);
}

/**
 * @test SystemTest::WithdrawFunds_InsufficientFunds
 * @brief Tests withdrawal functionality when insufficient funds are available.
 */
// Test Case 6
TEST(SystemTest, WithdrawFunds_InsufficientFunds) {
	Bank testBank("test.db");
	cout << "Step 1: Login...\n";
	Customer* customer = testBank.login("jmathis7", "1113");

	// Create new accounts
	cout << "Step 2: Create a new account...\n";
	int accNum = testBank.generateAccountNumber(1);
	ASSERT_TRUE(testBank.addAccountForCustomer(customer->getId(), to_string(accNum), 1000.00, "Savings"));

	// Check account creation
	cout << "Step 3: Check account balance...\n";
	Account<double>* account1 = testBank.getAccountByNumber<double>(to_string(accNum));
	testing::internal::CaptureStderr();

	account1->withdraw(2000.00);
	string output = testing::internal::GetCapturedStderr();
	EXPECT_EQ(output, "Error: Insufficient funds.\n");
}

/**
 * @test SystemTest::TransferFunds
 * @brief Tests transfer functionality between accounts.
 */
 // Test Case 7
TEST(SystemTest, TransferFunds) {
	Bank testBank("test.db");
	testBank.registerCustomer("Colin", "colingreens", "1111");
	Customer* customer = testBank.login("colingreens", "1111");

	// Create new accounts
	cout << "Step 2: Create two new accounts...\n";
	int accNum = testBank.generateAccountNumber(1);
	testBank.addAccountForCustomer(customer->getId(), to_string(accNum), 1000.00, "Savings");
	int accNum2 = testBank.generateAccountNumber(1);
	testBank.addAccountForCustomer(customer->getId(), to_string(accNum2), 500.00, "Regular");

	Account<double>* senderAccount = testBank.getAccountByNumber<double>(to_string(accNum)); // Fetch the sender account from database
	Account<double>* recieverAccount = testBank.getAccountByNumber<double>(to_string(accNum2)); // Fetch the reciever account from database

	double amount = 300.00;
	Transfer transfer(senderAccount, recieverAccount);
	transfer.setAmount(amount);
	senderAccount->withdraw(amount);
	recieverAccount->deposit(amount);

	testBank.updateAccountBalance(senderAccount->getId(), senderAccount->getBalance());
	testBank.updateAccountBalance(recieverAccount->getId(), recieverAccount->getBalance());

	EXPECT_EQ(senderAccount->getBalance(), 700.00);
	EXPECT_EQ(recieverAccount->getBalance(), 800.00);
}

/**
 * @test SystemTest::BalanceValidation
 * @brief Validates account balance after multiple transactions.
 */
// Test Case 8
TEST(SystemTest, BalanceValidation) {
	Bank testBank("test.db");
	cout << "Step 1: Login...\n";
	Customer* customer = testBank.login("xXxZacAttacxXx", "0707");

	// Create new accounts
	cout << "Step 2: Create a new account...\n";
	int accNum = testBank.generateAccountNumber(1);
	testBank.addAccountForCustomer(customer->getId(), to_string(accNum), 1000.00, "Regular");
	cout << "Step 3: Withdrawal #1...\n";
	Account<double>* account1 = testBank.getAccountByNumber<double>(to_string(accNum));
	account1->withdraw(500.00);
	cout << "Step 4: Deposit #1...\n";
	account1->deposit(12.00);
	cout << "Step 5: Deposit #2...\n";
	account1->deposit(180.00);
	EXPECT_EQ(account1->getBalance(), 692.00);
}

/**
 * @test SystemTest::DatabasePersistance
 * @brief Tests the persistence of customer and account data in the database across system restarts.
 */
// Test Case 9
TEST(SystemTest, DatabasePersistance) {
	Bank testBank("test.db");

	// Register and create accounts
	ASSERT_TRUE(testBank.registerCustomer("Trish N", "trish123", "1234"));
	Customer* customer = testBank.login("trish123", "1234");
	int accNum = testBank.generateAccountNumber(1);
	ASSERT_TRUE(testBank.addAccountForCustomer(customer->getId(), to_string(accNum), 1000.00, "Regular"));

	// Restart the system
	delete customer;
	Bank newTestBank("test.db");

	// Verify data persistance in database
	Customer* reloadedCustomer = newTestBank.login("trish123", "1234");
	ASSERT_NE(reloadedCustomer, nullptr);
	Account<double>* reloadedAccount = newTestBank.getAccountByNumber<double>(to_string(accNum));
	ASSERT_NE(reloadedAccount, nullptr);
	EXPECT_EQ(reloadedAccount->getBalance(), 1000.00);
}

/**
 * @test SystemTest::AccountDeletion
 * @brief Tests account deletion functionality.
 */
// Test Case 10
TEST(SystemTest, AccountDeletion) {
	Bank testBank("test.db");

	cout << "Step 1: Register a new customer...\n";
	testBank.registerCustomer("Corbin Jones", "corb", "5678");
	Customer* customer = testBank.login("corb", "5678");
	cout << "Step 2: Create new account...\n";
	int accNum = testBank.generateAccountNumber(1);
	testBank.addAccountForCustomer(customer->getId(), to_string(accNum), 3000.00, "Regular");
	Account<double>* account = testBank.getAccountByNumber<double>(to_string(accNum));
	cout << "Step 3: Check if account exist...\n";
	EXPECT_EQ(account->getBalance(), 3000.00);

	cout << "Step 4: Delete account...\n";
	testBank.accountRemoveAccount(account->getAccountNum());
	cout << "Step 5: Check if account was deleted...\n";
	ASSERT_EQ(testBank.getAccountByNumber<double>(to_string(accNum)), nullptr);
}

/**
 * @test AdminTests::MergeSort_AccountsSortedByBalance
 * @brief Tests the sorting of accounts by balance using merge sort.
 */
// Test cases for merge sort
TEST(AdminTests, MergeSort_AccountsSortedByBalance) {
	std::vector<Bank::acc> accounts = {
		MockAccount(1, 101, "A123", 1500.0, "Savings"),
		MockAccount(2, 102, "A124", 500.0, "Checking"),
		MockAccount(3, 103, "A125", 2000.0, "Savings")
	};

	mergeSort(accounts, accounts.size());

	EXPECT_EQ(accounts[0].balance, 500.0);
	EXPECT_EQ(accounts[1].balance, 1500.0);
	EXPECT_EQ(accounts[2].balance, 2000.0);
}

/**
 * @test AdminTests::FindLowerBound_ValidIndexFound
 * @brief Tests finding the lower bound for account balances using binary search.
 */
// Test cases for binary search
TEST(AdminTests, FindLowerBound_ValidIndexFound) {
	std::vector<Bank::acc> accounts = {
		MockAccount(1, 101, "A123", 500.0, "Savings"),
		MockAccount(2, 102, "A124", 1500.0, "Checking"),
		MockAccount(3, 103, "A125", 2000.0, "Savings")
	};

	mergeSort(accounts, accounts.size());
	int index = findLowerBound(accounts, 1500.0);

	EXPECT_EQ(index, 1);
}

/**
 * @test AdminTests::FindLowerBound_NoValidIndex
 * @brief Tests binary search when no valid index exists for the given balance.
 */
TEST(AdminTests, FindLowerBound_NoValidIndex) {
	std::vector<Bank::acc> accounts = {
		MockAccount(1, 101, "A123", 500.0, "Savings"),
		MockAccount(2, 102, "A124", 1500.0, "Checking"),
		MockAccount(3, 103, "A125", 2000.0, "Savings")
	};

	mergeSort(accounts, accounts.size());
	int index = findLowerBound(accounts, 3000.0);

	EXPECT_EQ(index, -1);
}

/**
 * @test AdminTests::GetAccountsInBalanceRange_ValidRange
 * @brief Tests retrieval of accounts within a specified balance range.
 */
// Test cases for retrieving accounts in a balance range
TEST(AdminTests, GetAccountsInBalanceRange_ValidRange) {
	std::vector<Bank::acc> accounts = {
		MockAccount(1, 101, "A123", 500.0, "Savings"),
		MockAccount(2, 102, "A124", 1500.0, "Checking"),
		MockAccount(3, 103, "A125", 2000.0, "Savings")
	};

	std::vector<Bank::acc> result = getAccountsInBalanceRange(accounts, 1000.0, 2000.0);

	ASSERT_EQ(result.size(), 2);
	EXPECT_EQ(result[0].balance, 1500.0);
	EXPECT_EQ(result[1].balance, 2000.0);
}

/**
 * @test AdminTests::GetAccountsInBalanceRange_NoAccountsInRange
 * @brief Tests retrieval of accounts when no accounts fall within the specified balance range.
 */
TEST(AdminTests, GetAccountsInBalanceRange_NoAccountsInRange) {
	std::vector<Bank::acc> accounts = {
		MockAccount(1, 101, "A123", 500.0, "Savings"),
		MockAccount(2, 102, "A124", 1500.0, "Checking"),
		MockAccount(3, 103, "A125", 2000.0, "Savings")
	};

	std::vector<Bank::acc> result = getAccountsInBalanceRange(accounts, 3000.0, 4000.0);

	EXPECT_TRUE(result.empty());
}

/**
 * @test AdminTests::AccountBST_InsertAndSearch
 * @brief Tests the insertion and search functionality of the binary search tree for accounts.
 */
// Test cases for binary search tree operations
TEST(AdminTests, AccountBST_InsertAndSearch) {
	AccountBST bst;
	MockAccount acc1(1, 101, "A123", 1500.0, "Savings");
	MockAccount acc2(2, 102, "A124", 500.0, "Checking");
	MockAccount acc3(3, 103, "A125", 2000.0, "Savings");

	bst.insert(acc1);
	bst.insert(acc2);
	bst.insert(acc3);

	auto* foundAccount = bst.searchAccount("A124");
	ASSERT_NE(foundAccount, nullptr);
	EXPECT_EQ(foundAccount->accountNumber, "A124");
	EXPECT_EQ(foundAccount->balance, 500.0);

	auto* notFoundAccount = bst.searchAccount("A999");
	EXPECT_EQ(notFoundAccount, nullptr);
}

#endif