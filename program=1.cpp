#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
void registerCustomer(string &name, string &id, int &type, int &meters);
void displayMenu();
double calculateConsumption(int units);
double calculateGST(double total);
double calculateIncomeTax(double total, int type);
double calculateDuty(double consumption);
double calculateFixedCharges(int units);
void displayBill(string name, string id, int type, int units, double consumption, double duty, double fixed, double gst, double tax);

int main() {
    string custName, custID;
    int custType, meters, choice, units = 0;
double consumption = 0;

    registerCustomer(custName, custID, custType, meters);

    do {
        displayMenu();
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter units consumed: ";
                cin >> units;
consumption = calculateConsumption(units);
                cout << "Bill Calculated Successfully!\n";
                break;
            case 2:
                cout << "New Connection Applied. Additional charges will be added to record.\n";
                break;
            case 3:
                displayBill(custName, custID, custType, units, consumption, 
                            calculateDuty(consumption), calculateFixedCharges(units), 
                            calculateGST(consumption), calculateIncomeTax(consumption, custType));
                break;
        }
    } while (choice != 4);

    return 0;
}

void registerCustomer(string &name, string &id, int &type, int &meters) {
    cout << "Enter Name: "; cin >> name;
    cout << "Enter ID: "; cin >> id;
    cout << "Type (1. Household, 2. Commercial): "; 
cin >> type;
cout << "Meters installed: "; 
cin >> meters;
}

void displayMenu() {
    cout << "\n1. Calculate Bill\n2. Apply New Connection\n3. View Details\n4. Exit\nChoice: ";
}

double calculateConsumption(int units) {
    double rates[] = {12.21, 14.53, 31.51, 38.41, 41.62, 43.04, 44.18, 49.10};
    if (units <= 100) return units * rates[0];
else if (units <= 200) return (100 * rates[0]) + (units - 100) * rates[1];
    else return units * rates[7];
}

double calculateGST(double total) { return total * 0.18; }
double calculateIncomeTax(double total, int type) { return (type == 1) ? total * 0.10 : total * 0.15; }
double calculateDuty(double cons) { return cons * 0.015; }
double calculateFixedCharges(int units) {
    if (units <= 300) return 0;
    if (units <= 400) return 200;
    if (units <= 500) return 400;
return 1000;
}

void displayBill(string name, string id, int type, int units, double consumption, double duty, double fixed, double gst, double tax) {
    cout << "\n========== LESCO ELECTRICITY BILL ==========" << endl;
    cout << "Customer Name: " << name << "\nCustomer ID: " << id << endl;
    cout << "Units Consumed: " << units << "\nConsumption Charges: Rs. " << consumption << endl;
    cout << "Fixed Charges: Rs. " << fixed << "\nGST: Rs. " << gst << endl;
    cout << "Total Payable: Rs. " << (consumption + duty + fixed + gst + tax + 250 + 35) << endl;
cout << "============================================" << endl;
}

