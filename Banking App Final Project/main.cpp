/**
* @file main.cpp
* @brief Main entry point for the Mercer Bank application with FTXUI integration.
* 
* This file contains the implementation of the CLI-based banking application
* featuring FTXUI for the user interface. It includes the main menu, user registration,
* login, and admin functions. The application interacts with SQLite for database management.
*/


#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include "SQLiteFunctions.h"
#include "UIUtilities.h"
#include "Bank.h"
#include "Admin.h"
#include "graph.h"
// Include files for FTXUI
#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
//#include <memory>

#ifdef RUN_TESTS
#include <gtest/gtest.h>
#endif

using namespace std;
using namespace ftxui;

// Global variables
/**
* @brief User option input buffer
*/
char option[1];

/**
* @brief Flag to track user input.
*/
bool userInput;
/**
* @brief User's menu choice.
*/
int choice;
/**
* @brief Path to the SQLite database file.
*/
const char* databaseDir = "MercerBank.db";

/**
*@brief Creates a styled window with a title and a component.
*
* @param title The title of the window.
* @param component The FTXUI component to be displayed inside the window.
* @return An FTXUI component representing the styled window.
*/
Component Window(string title, Component component) {
	return Renderer(component, [component, title] {
		return window(text(title), component->Render()) | flex;
	});
}

/**
 * @brief Entry point for the Mercer Bank application.
 *
 * This function initializes the banking system, sets up the main menu, and
 * handles user interactions for both customer and admin functionalities.
 *
 * @return int Returns 0 on successful execution.
 */
int main(int argc, char* argv[]) {

#ifdef RUN_TESTS // If running tests
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
#else // If not running tests
	Bank MercerBank(databaseDir); //initialize bank and database
	bool exitFlag = false;

	//cout << "Press enter to continue...\n";
	//displayWelcomeAnimation();
	clearScreen(); // Clear the terminal screen
	printDollarSign(); // Print the static dollar sign
	cout << "\n" << WELCOME_MESSAGE << "\n" << endl; // Display welcome message
	printMU(); // Print the MU logo
	system("pause");
	
	auto screen = ScreenInteractive::TerminalOutput(); // FTXUI: Initialize the screen
	vector<string> MainMenuEntries = { // Main menu entries
		"1. Register",
		"2. Login",
		"3. Exit",
		"4. Admin"
	};

	int selectedMenuEntry = 0; // FTXUI: Selected menu entry variable
	auto menuOption = MenuOption(); // FTXUI: Menu options	
	menuOption.on_enter = screen.ExitLoopClosure(); // FTXUI: Exit loop on enter
	auto menu = Menu(&MainMenuEntries, &selectedMenuEntry, menuOption); // FTXUI: Main Menu	component

	clearScreen(); // Clear the terminal screen
	printDollarSign(); // Print the static dollar sign
	cout << "\n" << WELCOME_MESSAGE << "\n" << endl; // Display welcome message
	printMU(); // Print the MU logo

	// Display Main menu options
	while (true) {
		system("cls");
		selectedMenuEntry = 0; // FTXUI: Reset the selected menu entry
		screen.Loop(Window("Mercer Bank", menu)); // FTXUI: Display the menu

		selectedMenuEntry += 1; // FTXUI: Increment the selected menu entry for switch case selection

		switch (selectedMenuEntry) {
		case REGISTER:
			clearScreen();
			registerCustomer(MercerBank);
			break;

		case LOGIN: {
			clearScreen();
			if (!loginCustomer(MercerBank)) {
				auto screen = ScreenInteractive::TerminalOutput(); // FTXUI: Initialize the screen
				string userChoice; // FTXUI: User choice variable
				bool proceedToRegister = false; // FTXUI: Proceed to register variable

				auto messageText = text("\xE2\x9D\x8C Login failed. Would you like to register (Y/N)?") | bold | center; // FTXUI: Message text

				auto yesButton = Button("Yes", [&] { // FTXUI: Yes button action
					proceedToRegister = true;
					screen.Exit();
					});

				auto noButton = Button("No", [&] { // FTXUI: No button action
					proceedToRegister = false;
					screen.Exit();
					});

				auto layout = Container::Vertical({ // FTXUI: Layout of the message and buttons
					Container::Horizontal({
					yesButton,
					noButton,
					}),
					});

				auto renderer = Renderer(layout, [&] { // FTXUI: Renderer to display the message and buttons
					return vbox({ // FTXUI: Vertical box layout of message and buttons
							messageText,
							hbox({
								yesButton->Render() | center, // FTXUI: Render yes button
								noButton->Render() | center, // FTXUI: Render no button
							}),
						}) | border;
					});

				screen.Loop(renderer); // FTXUI: Loop to display the screen until the user clicks yes or no

				// After user clicks yes or no, proceed to register or exit
				if (proceedToRegister) {
					registerCustomer(MercerBank);
				}
			}
			break;
		}


		case EXIT: {
			cout << "Thanks for banking with us!" << endl;
			return 0;
		}

		// Admin Login
		case ADMIN: {
			system("cls");
			auto screen = ScreenInteractive::TerminalOutput(); // FTXUI: Initialize the screen

			string username, password; // FTXUI: Username and password variables
			bool loginStatus = false; // FTXUI: Login status variable
			string error_message = ""; // FTXUI: Error message variable
			string loginMessage = "Please enter your admin credentials:"; // FTXUI: Login message variable

			auto usernameInput = Input(&username, "Username (admin): "); // FTXUI: Username input box
			auto passwordInput = Input(&password, "Password (admin): "); // FTXUI: Password input box


			auto submitButton = Button("Login", [&] { // FTXUI: Submit button action
				if (username.empty() || password.empty()) { // FTXUI: Check if username or password is empty
					error_message = "\xE2\x9D\x8C Error: Please enter both username and password.";
					return;
				}
				else if (username == "admin" && password == "admin") { // FTXUI: Check if username and password are correct
					loginStatus = true;
					screen.Exit();
				}
				else { // FTXUI: Invalid username or password
					error_message = "\xE2\x9D\x8C Login failed. Invalid username or password.";
					loginStatus = false;
					return;
				}
				}); // FTXUI: Submit button action

			// Cancel button to exit without logging in
			auto backButton = Button("Back to Main Menu", [&] { loginStatus = false; screen.Exit(); });

			// Layout of inputs and buttons
			auto layout = Container::Vertical({
				usernameInput | flex,
				passwordInput | flex,
				Container::Horizontal({
					submitButton | flex,
					backButton | flex
				}) | flex
				});

			// Renderer to display layout and inputs
			auto renderer = Renderer(layout, [&] {
				return vbox({
					text(loginMessage) | bold | center,
					usernameInput->Render() | center,
					passwordInput->Render() | center,
					hbox({
						submitButton->Render() | center,
						backButton->Render() | center,
					}),
					}) | border;
				});

			screen.Loop(renderer); // FTXUI: Loop to display the screen until the user clicks submit or cancel

			if (loginStatus) { // FTXUI: If login is successful
				string adminMenuChoice; // FTXUI: Admin menu choice variable

				auto adminMenuEntries = vector<string>{ // FTXUI: Admin menu entries
					"1. View All Accounts",
					"2. Search for Accounts By Balance Range",
					"3. Search for Accounts By Name",
					"4. Dummy Account",
					"5. Exit",
					"6. Implementing Graphs Testing"
				};

				int selectedAdminMenuEntry = 0; // FTXUI: Selected admin menu entry variable
				auto adminMenuOption = MenuOption(); // FTXUI: Admin menu options
				adminMenuOption.on_enter = screen.ExitLoopClosure(); // FTXUI: Exit loop on enter

				auto adminMenu = Menu(&adminMenuEntries, &selectedAdminMenuEntry, adminMenuOption); // FTXUI: Admin menu component
				bool flag = true; // FTXUI: Flag to control the loop
			while (flag) {
				selectedAdminMenuEntry = 0; // FTXUI: Reset the selected admin menu entry
				screen.Loop(Window("Admin Menu", adminMenu)); // FTXUI: Display the admin menu
				selectedAdminMenuEntry += 1; // FTXUI: Increment the selected admin menu entry for switch case selection
				switch (selectedAdminMenuEntry) { // FTXUI: Switch case for admin menu options
				case 1: { //FTXUI: View all accounts
					system("cls");
					showAllTables(databaseDir);
					system("pause");
					clearScreen();
					break;
				}
				case 2: { // FTXUI: Search for accounts by balance range
					system("cls");

					// Prepare the screen and inputs
					auto screen = ScreenInteractive::TerminalOutput(); // FTXUI: Initialize the screen
					string minBalanceString, maxBalanceString; // FTXUI: String variables for balance range
					double minBalance = 0.0, maxBalance = 0.0; // FTXUI: Double variables for balance range
					string error_message = ""; // FTXUI: Error message variable

					// Inputs for balance range
					auto minBalanceInput = Input(&minBalanceString, "Enter minimum balance: "); // FTXUI: Minimum balance input box
					auto maxBalanceInput = Input(&maxBalanceString, "Enter maximum balance: "); // FTXUI: Maximum balance input box

					bool submitClicked = false; // FTXUI: Flag to check if submit button is clicked

					// Submit button to confirm the balance range
					auto submitButton = Button("Submit", [&] { // FTXUI: Submit button action
						try {
							// Try to convert strings to double
							minBalance = stod(minBalanceString);
							maxBalance = stod(maxBalanceString);

							// Validate the balance range
							if (minBalance > maxBalance) {
								error_message = "\xE2\x9D\x8C Minimum balance cannot be greater than maximum balance!";
								return;
							}

							submitClicked = true; // Proceed to filter accounts after submitting
							screen.Exit();
						}
						catch (const std::invalid_argument&) { // FTXUI: Handle invalid input
							error_message = "\xE2\x9D\x8C Invalid input. Please enter valid numbers for balance.";
						}
						catch (const std::out_of_range&) { // FTXUI: Handle out of range error
							error_message = "\xE2\x9D\x8C Balance values are too large!";
						}
						});

					// Cancel button to exit without filtering
					auto cancelButton = Button("Cancel", [&] { screen.Exit(); });

					// Layout of inputs and buttons
					auto layout = Container::Vertical({
						minBalanceInput,
						maxBalanceInput,
						Container::Horizontal({
							submitButton,
							cancelButton
						})
						});

					// Renderer to display layout and inputs
					auto renderer = Renderer(layout, [&] {
						return vbox({
							text("Enter balance range to filter accounts:") | bold | center,
							separator(),
							minBalanceInput->Render(),
							maxBalanceInput->Render(),
							hbox({
								submitButton->Render() | center,
								cancelButton->Render() | center,
							}),
							error_message.empty() ? text("") : text(error_message) | color(Color::Red),
							}) | border;
						});

					// Loop to display the screen until the user clicks submit or cancel
					screen.Loop(renderer);

					// After submit, filter and display the accounts
					if (submitClicked) {
						// Fetch accounts from database
						vector<Bank::acc> accounts = MercerBank.fetchAccountsFromDatabase();

						// Filter the accounts based on the given balance range
						vector<Bank::acc> filteredAccounts = getAccountsInBalanceRange(accounts, minBalance, maxBalance);

						// Display the filtered accounts
						if (filteredAccounts.empty()) { // FTXUI: No accounts found in the specified balance range
							error_message = "\xE2\x9D\x8C No accounts found in the specified balance range."; // \xE2\x9D\x8C Unicode for red cross symbol
							screen.Loop(renderer);
						}
						else {
							// Display accounts
							for (const auto& acc : filteredAccounts) {
								cout << "Account Holder Name: " << acc.accountHolder << endl;
								cout << "Account ID: " << acc.accountId << endl;
								cout << "User ID: " << acc.userId << endl;
								cout << "Account Number: " << acc.accountNumber << endl;
								cout << "Balance: $" << acc.balance << endl;
								cout << "Account Type: " << acc.accountType << endl;
								cout << endl;
							}
							system("pause");
							system("cls");
						}
					}

					break;
				}
				case 3: { // FTXUI: Search for accounts by name
					system("cls");
					vector<Bank::acc> accounts = MercerBank.fetchAccountsFromDatabase(); // Fetch accounts from database
					AccountBST bst; // Create a binary search tree
					bst.buildTree(accounts); // Build the tree with the fetched accounts

					// Display all
					//bst.displayAllAccounts();

					string inputAccNumber; // FTXUI: Input variable for account number
					cout << "Enter the account number to find: "; // FTXUI: Prompt for account number
					cin >> inputAccNumber; // FTXUI: Read account number from user input
					Bank::acc* result = bst.searchAccount(inputAccNumber); // FTXUI: Search for the account in the tree
					if (result) { // FTXUI: If account is found
						cout << "Account found:\n";
						bst.printAccount(*result);
					}
					else { // FTXUI: If account is not found
						cout << "\xE2\x9D\x8C Account not found.\n";
					}
					system("pause");
					system("cls");
					break;
				}

				case 4: { // FTXUI: Dummy account creation

					string name = "dummy_account";
					string username = "username";
					string pin = "1234";
					MercerBank.registerCustomer(name, username, pin);
					Customer* customer = MercerBank.login(username, pin);
					customerMenu<double>(customer, MercerBank);
					break;
				}

				case 5: { // FTXUI: Exit admin menu
					flag = false;// FTXUI: Set flag to false to exit the loop
					break;
				}

				case 6: {
					cout << "This section is for demonstration purposes only." << endl;
					Bank bank("Mercer Bank");
					bank.registerCustomer("John Doe", "john123", "1234");
					Customer* customer = bank.login("john123", "1234");

					if (customer) {
						// Create graph for customer relationships
						Graph graph(10);  // Assume 10 customers for simplicity
						graph.add_customer(customer->getId(), customer->getName());

						// Add a few accounts for the customer
						bank.addAccountForCustomer(customer->getId(), "123456789", 1000.0, "Savings");
						bank.addAccountForCustomer(customer->getId(), "987654321", 2000.0, "Checking");

						// Show accounts related to the customer
						graph.show_accounts_related_to_customer(customer->getId(), bank);

						// Optionally, you can now print the graph of customer relationships
						graph.print();
					}
					else {
						cout << "Login failed!" << endl;
					}
					system("pause");
					system("cls");
				}
				default:
					break;
				}
			}
				break;
			}
			break;
		}

		default:
			cout << "Thanks for banking with us!" << endl;
			return 0;

		return 0;
		}
	}
#endif
}