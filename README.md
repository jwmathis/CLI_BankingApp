# Banking CLI Application

A comprehensive command-line banking application built in C++, designed to provide users with basic banking functionalities. It builds on top of a previous banking CLI application offering improvements to the original functionality. It supports customer and administrative interactions, account management, and transaction processing. This application uses data structures like linked lists and binary search trees to ensure efficient operations and introduces a user-friendly interface enhanced by the FTXUI library for dynamic and visually appealing outputs.

---

## Features


### Customer Features:
- **Account Management**: Open, close, and manage bank accounts.
- **Transactions**: Deposit, Withdraw, and transfer funds between accounts.
- **Help Requests**: Submit, view, and delete help requests.


### Adminstrative Features:
- View, search, and manage all accounts using a binary search tree.
- Sort accounts by balance using Merge sort.
- Filter accounts within a specified balance range using binary search.
- Manage help request queue for customer support.

---

## Technical Highlights

- **Data Structures**:
    - **Linked List**: For managing customer transaction history.
    - **Stack**: To implement undo functionality for transactions.
    - **Queue**: To manage help requests in a FIFO order.
    - **Binary Search Tree**: For efficient searching and sorting of accounts in the admin interface.

- **Algorithms**:
    - **Merge Sort**: To sort accounts based on balances.
    - **Binary Search**: For quickly locating accounts within a specific balance range.

- **FTXUI Integration**: Modern and user-friendly terminal interface with support for input fields, buttons, and menus.

- **Unicode Support**: Displays emojis and other symbols to enhance user experience.

---
## Downloading the App
1. Navigate to the Releases section of this repository.
2. Find the latest release and click on it.
3. Download the .exe file (for Windows only).
4. Run the application.
   
## Setup and Installation
To build the application from the source code:

1. Clone the repository:
```
git clone https://github.com/jwmathis/CLI_BankingApp.git
cd CLI_BankingApp
```

2. Install dependencies:
    - Install FTXUI uisng vcpkg:
    ```
    ./vcpkg install ftxui
    ```
    - Follow the instructions to set up VCPKG [here](https://vcpkg.io/en/).
    - Follow the instructions to set up FTXUI [here](https://github.com/ArthurSonzogni/FTXUI).
    - Ensure [SQLite3](https://www.sqlite.org/) is installed and properly linked. 

3. Open the project in Visual Studio:
    ```
    code .
    ```

4. Configure the project with vcpkg:
    ```
    ./vcpkg integrate install
    ```
    - This will set up Visual Studio to use the libraries installed by vcpkg.

5. Build the project:
    - In Visual Studio, build the project by selecting Build > Build Solution or pressing Ctrl+Shift+B

6. Run the application

## Unit Tests
To run the unit tests for this project, follow these steps:
1. Open the project in Visual Studio
2. Switch to the "Test" Congfiguration
    * In the top toolbar, locate the Solution Configurations dropdown menu (usually near the "Start" button).
    * Select Test from the dropdown options.
3. Build the project
4. View the the test results
    * Once the tests have run, the results (pass/fail) will apppear in a terminal window.
      
Note: Ensure [Gtest](https://github.com/google/googletest) is installed and properly linked.

---

## Usage
- **Customer Mode**:
    - Log in or register a new account.
    - Follow on-screen prompts to perform transactions, view balance, and manage requests.

- **Admin Mode**:
    - Log in as an admin to access the management panel.
    - View all accounts, search by account number, and filter by balance range.

---

## File Structure
Link to doxygen documentation: [https://jwmathis.github.io/CLI_BankingApp/]
- **main.cpp**: Entry point for the application
- **Customer.h/Customer.cpp**: Manages customer-related operations.
- **Admin.h**: Contains admin functionalities.
- **uihelpers.h/uihelpers.cpp**: Utility functions for UI and animations.
- **Bank.h**: Core banking functionality.
- **SQLiteFunctions.h**: Database operations using SQLite.

---

## Future Improvements
- Enhance security for user authentication.
- Add support for external configuration files.
- Extend sorting/filtering capabilities with additional criteria.
- Implement more robust error handling.
- Modularize menu functions with FTXUI implementation.

---

## Acknowledgements
- FTXUI
- SQLite
