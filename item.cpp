#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <windows.h>
#include <limits>
#include <chrono>
#include <ctime>
#include <map>

using namespace std;

class Bill {
private:
    string Item;
    int Rate, Quantity;
    string Timestamp;

public:
    Bill() : Item(""), Rate(0), Quantity(0), Timestamp("") {}

    void setItem(string item) { Item = item; }
    void setRate(int rate) { Rate = rate; }
    void setQuant(int quant) { Quantity = quant; }
    void setTimestamp(string timestamp) { Timestamp = timestamp; }

    string getItem() { return Item; }
    int getRate() { return Rate; }
    int getQuant() { return Quantity; }
    string getTimestamp() { return Timestamp; }
};

// Function to get current timestamp in YYYY-MM-DD HH:MM:SS format
string getCurrentTimestamp() {
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    struct tm *time_info = localtime(&now_time);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", time_info);
    return string(buffer);
}

void addItem(Bill& b) {
    system("cls");
    string item;
    int rate, quant;

    cout << "Enter Item Name: ";
    cin.ignore();
    getline(cin, item);  // Accept names with spaces

    cout << "Enter Price for " << item << ": KSh ";
    cin >> rate;

    cout << "Enter Quantity: ";
    cin >> quant;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid quantity. Please enter a number." << endl;
        Sleep(2000);
        return;
    }

    // Set timestamp for the item
    string timestamp = getCurrentTimestamp();
    b.setItem(item);
    b.setRate(rate);
    b.setQuant(quant);
    b.setTimestamp(timestamp);

    // Writing item details to a CSV file
    ofstream out("Bill.csv", ios::app);
    if (!out) {
        cout << "Error: Could not open Bill.csv!" << endl;
        Sleep(2000);
        return;
    }

    // Write item details to CSV file: Item, Rate, Quantity, Timestamp
    out << b.getItem() << "," << b.getRate() << "," << b.getQuant() << "," << b.getTimestamp() << endl;
    out.close();

    cout << "Item successfully written to Bill.csv!" << endl;
    Sleep(2000);
}
void printBill() {
    system("cls");
    ifstream in("Bill.csv");

    if (!in) {
        cout << "No bill found. Please add items first." << endl;
        Sleep(2000);
        return;
    }

    string line;
    double total = 0;

    // Print Header for the bill
    cout << "Supermarket Bill" << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << left << setw(25) << "Item"
         << setw(10) << "Rate"
         << setw(10) << "Qty"
         << setw(15) << "Amount"
         << setw(20) << "Timestamp" << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;

    while (getline(in, line)) {
        stringstream ss(line);
        string name, rateStr, qtyStr, timestamp;

        getline(ss, name, ',');
        getline(ss, rateStr, ',');
        getline(ss, qtyStr, ',');
        getline(ss, timestamp);

        int rate = stoi(rateStr);
        int qty = stoi(qtyStr);
        double amount = rate * qty;  // Calculate amount for each item
        total += amount;

        // Print formatted output with correct spacing
        cout << left << setw(25) << name
     << setw(10) << rate
     << setw(10) << qty
     << setw(15) << "KShs." + to_string(static_cast<int>(amount))  // Concatenates currency with value
     << setw(20) << timestamp << endl;
    }

    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << right << setw(50) << "Total: KSh " << fixed << setprecision(2) << total << endl;

    in.close();
    system("pause");
}

int main() {
    Bill b;
    bool exit = false;

    while (!exit) {
        system("cls");
        int val;

        cout << "Welcome to Supermarket Billing System" << endl;
        cout << "-------------------------------------" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. Print Bill" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter Choice: ";
        cin >> val;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            Sleep(2000);
            continue;
        }

        if (val == 1) {
            addItem(b);
        } else if (val == 2) {
            printBill();
        } else if (val == 3) {
            exit = true;
            cout << "Exiting the system..." << endl;
            Sleep(1500);
        } else {
            cout << "Invalid choice. Please try again." << endl;
            Sleep(2000);
        }
    }

    return 0;
}
