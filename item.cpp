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

    string timestamp = getCurrentTimestamp();
    b.setItem(item);
    b.setRate(rate);
    b.setQuant(quant);
    b.setTimestamp(timestamp);

    // **Overwrite Bill.txt to start fresh for new clients**
    ofstream txtOut("Bill.txt", ios::trunc);  // `ios::trunc` clears the file before writing
    if (!txtOut) {
        cout << "Error: Could not open Bill.txt!" << endl;
        Sleep(2000);
        return;
    }

    // Write headers for the new receipt
    txtOut << "Hellen's Supermarket\n";
    txtOut << "--------------------------------------------------------------------------\n";
    txtOut << left << setw(25) << "Item"
           << setw(10) << "Rate"
           << setw(10) << "Qty"
           << setw(15) << "Amount"
           << setw(20) << "Timestamp" << endl;
    txtOut << "--------------------------------------------------------------------------\n";

    // Write the single item details to the receipt
    txtOut << left << setw(25) << b.getItem()
           << setw(10) << b.getRate()
           << setw(10) << b.getQuant()
           << setw(15) << "KShs." + to_string(b.getRate() * b.getQuant())
           << setw(20) << b.getTimestamp() << endl;

    txtOut << "---------------------------------------------------------------------------\n";
    txtOut << "Thank you for shopping with us! Happy Shopping!\n";
    txtOut.close();

    cout << "A fresh receipt has been generated in Bill.txt for the new client!" << endl;
    Sleep(2000);
}
void printBill() {
    system("cls");
    ifstream in("Bill.csv");
    ofstream txtOut("Bill.txt");  // Open Bill.txt to store formatted bill

    if (!in || !txtOut) {
        cout << "Error: Could not open Bill.csv or Bill.txt!" << endl;
        Sleep(2000);
        return;
    }

    string supermarketName = "Hellen's Supermarket ";  // Customize this with your store name!
    string thankYouMessage = "Thank you for shopping with us! Happy Shopping!";  // Footer message

    string line;
    double total = 0;

    // Print and Write Header (Supermarket Name + Table Headers)
    cout << supermarketName << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << left << setw(25) << "Item"
         << setw(10) << "Rate"
         << setw(10) << "Qty"
         << setw(15) << "Amount"
         << setw(20) << "Timestamp" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
    
    txtOut << supermarketName << endl;
    txtOut << "-------------------------------------------------------------------------------------------" << endl;
    txtOut << left << setw(25) << "Item"
           << setw(10) << "Rate"
           << setw(10) << "Qty"
           << setw(15) << "Amount"
           << setw(20) << "Timestamp" << endl;
    txtOut << "---------------------------------------------------------------------------------------------" << endl;

    while (getline(in, line)) {
        stringstream ss(line);
        string name, rateStr, qtyStr, timestamp;

        getline(ss, name, ',');
        getline(ss, rateStr, ',');
        getline(ss, qtyStr, ',');
        getline(ss, timestamp);

        int rate = stoi(rateStr);
        int qty = stoi(qtyStr);
        int amount = rate * qty;
        total += amount;

        // Print and Write each row properly formatted
        cout << left << setw(25) << name
             << setw(10) << rate
             << setw(10) << qty
             << setw(15) << "KShs." + to_string(amount)  
             << setw(20) << timestamp << endl;

        txtOut << left << setw(25) << name
               << setw(10) << rate
               << setw(10) << qty
               << setw(15) << "KShs." + to_string(amount)  
               << setw(20) << timestamp << endl;
    }

    // Print and Write Total
    cout << "----------------------------------------------------------------------------------------------" << endl;
    cout << right << setw(50) << "Total: KShs." << total << endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << thankYouMessage << endl;  // Print the thank you message at the bottom

    txtOut << "---------------------------------------------------------------------------------------------" << endl;
    txtOut << right << setw(50) << "Total: KShs." << total << endl;
    txtOut << "----------------------------------------------------------------------------------------------" << endl;
    txtOut << thankYouMessage << endl;  // Write the thank you message in Bill.txt

    in.close();
    txtOut.close();

    cout << "\nBill successfully saved to `Bill.txt`. You can now print or email it to clients!" << endl;
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
