#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

class Bill{
    private:
     string Item;
     int Rate, Quantity;
    public:
     Bill():Item(""), Rate(0), Quantity(0) { }

     void setItem(string item){
        Item = item;
     }
     void setRate(int rate){
        Rate = rate;
     }
    void setQuant(int quant){
        Quantity = quant;
     }
string getItem(){
    return Item;
}
string getRate(){
    return Rate;
}
string getQuant(){
    return Quantity;
}
};

addItem(Bill b){
    bool close = false;
    while(!close){
        int choice;
    cout << "Add." << endl;
    cout < "close." << endl;
    cout << "Enter Choice: ";
    cin >> choice;

if (choice ==1){
    string Item;
    int rate,quant;

}
}
}
int main() {
    Bill b;
    bool exit = false;
    while(!exit){
        system("cls");
        int val;


cout << "Welcome to Supermarket Billing System" << endl;
cout << "-------------------------------------" << endl;
cout << "Add Item." << endl;
cout << "Print Bill." << endl;
cout << "Exit" << endl;
cout << "Enter Choice:";
cin>>val;
if(val==1){

}
    }
}