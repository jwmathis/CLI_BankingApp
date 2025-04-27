#pragma once

#include "Bank.h"
#include "Customer.h"
#include "Transfer.h"
#include <string>

using namespace std;

// Color codes for terminal text formatting
#define RESET "\033[0m"      ///< Reset to default terminal text formatting.
#define BOLD "\033[1m"       ///< Apply bold formatting to terminal text.
#define RED "\033[31m"       ///< Set text color to red.
#define GREEN "\033[32m"     ///< Set text color to green.
#define YELLOW "\033[33m"    ///< Set text color to yellow.
#define BLUE "\033[34m"      ///< Set text color to blue.
#define MAGENTA "\033[35m"   ///< Set text color to magenta.
#define CYAN "\033[36m"      ///< Set text color to cyan.
#define ORANGE "\033[38;2;255;165;0m" ///< Set text color to orange using RGB values.

// Enums for menu options
/**
 * @enum MainMenuOption
 * @brief Represents options in the main menu of the banking application.
 */
enum MainMenuOption {
    REGISTER = 1, ///< Register a new customer.
    LOGIN,        ///< Log in as an existing customer.
    EXIT,         ///< Exit the application.
    ADMIN         ///< Access the admin menu.
};

/**
 * @enum CustomerMenuOption
 * @brief Represents options available in the customer's menu.
 */
enum CustomerMenuOption {
    NEW_ACCOUNT = 0,     ///< Create a new account for the customer.
    BALANCE_INQUIRY,     ///< Check the balance of a customer's account.
    DEPOSIT_AMOUNT,      ///< Deposit an amount into a customer's account.
    WITHDRAW_AMOUNT,     ///< Withdraw an amount from a customer's account.
    TRANSFER_AMOUNT,     ///< Transfer an amount between accounts.
    CLOSE_ACCOUNT,       ///< Close a customer's account.
    HISTORY,             ///< View transaction history for a customer's account.
	UNDO,               ///< Undo the last transaction.
	HELP,        ///< Submit a help request for customer support.
    LOGOUT,
    TEST,
};

/**
 * @enum AccountTypeOption
 * @brief Represents account types available for selection.
 */
enum AccountTypeOption {
    CHECKING_ACCOUNT = 1, ///< Checking account type.
    SAVINGS_ACCOUNT       ///< Savings account type.
};

// Constants
/**
 * @brief Welcome message displayed to the user upon starting the application.
 */
const string WELCOME_MESSAGE = "					Welcome to Mercer Money Banking!";

/**
 * @brief Error message displayed when an invalid menu option is selected.
 */
const string INVALID_OPTION = "Invalid option. Please try again.";

// Function declarations

/**
 * @brief Displays the customer accounts menu and handles related operations.
 * @param bank Reference to the Bank object for database operations.
 * @param customer Pointer to the logged-in Customer object.
 */
void displayCustomerAccountsMenu(Bank& bank, Customer* customer);

/**
 * @brief Handles customer registration by collecting user details and adding them to the database.
 * @param bank Reference to the Bank object for database operations.
 */
void registerCustomer(Bank& bank);

/**
 * @brief Handles the login process for customers.
 * @param bank Reference to the Bank object for database operations.
 * @return True if login is successful, false otherwise.
 */
bool loginCustomer(Bank& bank);

/**
 * @brief Displays the customer's main menu and handles operations such as balance inquiries and transactions.
 * @tparam T Type used for account balances and related data.
 * @param customer Pointer to the logged-in Customer object.
 * @param bank Reference to the Bank object for database operations.
 */
template <typename T>
void customerMenu(Customer* customer, Bank& bank);

/**
 * @brief Handles the creation of new customer accounts.
 * @param customer Pointer to the logged-in Customer object.
 * @param bank Reference to the Bank object for database operations.
 */
void newCustomer(Customer* customer, Bank& bank);

/**
 * @brief Displays an animated welcome logo with a dollar sign.
 *
 * This function animates a series of frames to create a dynamic welcome effect
 * using a dollar sign symbol.
 */
void displayWelcomeAnimation(void);

/**
 * @brief Clears the terminal screen.
 *
 * This function sends the appropriate terminal commands to clear the screen,
 * creating a fresh view for the user interface.
 */
void clearScreen(void);

/**
 * @brief Moves the cursor to a specific position in the terminal.
 *
 * @param row The row (line number) to move the cursor to.
 * @param col The column (character position) to move the cursor to.
 */
void moveToPosition(int row, int col);

/**
 * @brief Prints an animated dollar sign at a specified position on the screen.
 *
 * @param frame The current frame of the animation.
 * @param row The row (line number) where the dollar sign should appear.
 * @param col The column (character position) where the dollar sign should appear.
 */
void printAnimatedDollarSign(int frame, int row, int col);

/**
 * @brief Prints a static dollar sign to the terminal.
 *
 * This function is useful for displaying a single, unchanging dollar sign as
 * part of the user interface.
 */
void printDollarSign(void);

/**
 * @brief Prints the "MU" logo to the terminal.
 *
 * This function renders the Mercer University logo using ASCII art or similar
 * visual elements.
 */
void printMU(void);

/**
 * @brief Retrieves a random fruit emoji.
 *
 * This function returns a string containing a randomly selected fruit emoji.
 * Useful for adding playful or decorative elements to the user interface.
 *
 * @return A string containing a random fruit emoji.
 */
string getRandomFruitEmoji(void);