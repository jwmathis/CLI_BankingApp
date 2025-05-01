#include "Customer.h"
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
Customer::Customer(int id, const string& name, const string& username, const string& pin) 
	: id(id), name(name), username(username), pin(pin) {}

Customer::Customer() : transactionHead(nullptr) {}

Customer::~Customer() {
	Transaction* current = transactionHead;
	while (current) {
		Transaction* toDelete = current;
		current = current->next;
		delete toDelete;
	}
}

int Customer::getId() const {
	return id;
}

const string& Customer::getName() const {
	return name;
}

const string& Customer::getUsername() const {
	return username;
}

bool Customer::verifyPin(const string& inputPin) const {
	return inputPin == pin;
}

string Customer::generateTransactionReceiptFilename() {
	string filename = name + "_transaction_reciept.txt";
	return filename;
}

void Customer::generateTransactionReceipt(const string& transaction) {
	try {
		string filename = generateTransactionReceiptFilename();
		ofstream outputFile(filename, ios::app);
		// Check if file opened successfully
		if (!outputFile.is_open()) {
			throw ios_base::failure("Failed to open file: " + filename);
		}

		// Write to file
		outputFile << "Transaction: " << transaction << "\n";
		outputFile << "------------------------------------------\n";
		cout << "Transaction logged to reciept." << endl;
		outputFile.close();
	}
	catch (const ios_base::failure& e) {
		cerr << "Unexpected error occurred: " << e.what() << endl;
	}
}

void Customer::addTransaction(const string& type, double amount) {

	auto now = chrono::system_clock::now();
	auto in_time_t = chrono::system_clock::to_time_t(now);

	// Convert to a tm structure using localtime_s
	std::tm localTime;
	if (localtime_s(&localTime, &in_time_t) != 0) {
		throw std::runtime_error("Failed to convert time");
	}

	// Format the timestamp as a string (e.g., "YYYY-MM-DD HH:MM:SS")
	std::ostringstream oss;
	oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
	std::string timestamp = oss.str();

	// Create a new transaction and add it to the linked list
	Transaction* newTransaction = new Transaction(type, amount, timestamp);
	newTransaction->next = transactionHead;
	transactionHead = newTransaction;

	undoStack.push(newTransaction);
}

void Customer::undoTransaction() {
	if (undoStack.empty()) {
		cout << "No transactions to undo." << endl;
		return;
	}

	Transaction* lastTransaction = undoStack.top();
	undoStack.pop();

	// Remove the transaction from the linked list
	if (transactionHead == lastTransaction) {
		transactionHead = transactionHead->next;
	}
	else {
		Transaction* current = transactionHead;
		while (current && current->next != lastTransaction) {
			current = current->next;
		}
		if (current) {

			current->next = lastTransaction->next;
		}
	}
	delete lastTransaction;
}

void Customer::addHelpRequest(const string& request) {
	helpRequestQueue.push(request);
}

bool Customer::removeHelpRequest() { 
	if (helpRequestQueue.empty()) {
		return false;
	}
	helpRequestQueue.pop();
	return true;
}
//vector<string>& Customer::getHelpRequests() {
//
//	std::vector<std::string> requests;
//	CustomQueue<std::string> tempQueue = helpRequestQueue; // Assuming helpRequests is a CustomQueue
//	while (!tempQueue.empty()) {
//		requests.push_back(tempQueue.front());
//		tempQueue.pop();
//	}
//	return requests;
//}
CustomQueue<string> Customer::getHelpRequests() {
	return helpRequestQueue;
}
CustomQueue<std::string> Customer::convertVectorToQueue(const std::vector<std::string>& vec) {
	CustomQueue<std::string> queue;
	for (const auto& item : vec) {
		queue.push(item);
	}
	return queue;
}
void Customer::displayTransactionHistory() {

	using namespace ftxui;
	system("cls");
	Elements elements;
	Transaction* current = transactionHead;
	while (current) {
		elements.push_back(text(current->type + ": $" + to_string(current->amount) + " on " + current->timestamp));
		current = current->next;
	}

	// If no transactions, show a placeholder message
	if (elements.empty()) {
		elements.push_back(text("No transactions available.") | dim | center);
	}

	auto transactionList = vbox(move(elements)) | border | vscroll_indicator | frame;
	auto screen = ScreenInteractive::TerminalOutput();
	
	// Back button to cancel the operation.
	auto backButton = Button("Cancel", [] {
		ScreenInteractive::Active()->Exit();
		});

	auto layout = Container::Vertical({
		Renderer([&] { return transactionList; }),
		backButton
		});
	auto component = Renderer(layout, [&] {
		return vbox({
			text("Transaction History") | bold | center,
			separator(),
			transactionList,
			separator(),
			backButton->Render() | hcenter,
		});
	});
	
	screen.Loop(component);
}