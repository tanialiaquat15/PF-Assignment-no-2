#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


void registerCustomer(string &name, int &id, int &type);
void displayGroceryList(string items[], double price[], int size);
void addItemsToCart(int qty[], int size);
double calculateGrossBill(int qty[], double price[], int size);
double calculateSalesTax(int qty[], double price[], int size);
double calculateMembershipDiscount(double bill, int type);
double calculateBillDiscount(double bill);
double calculateCardCharges(double bill, int paymentType);
int calculateLoyaltyPoints(double bill);
void redeemLoyaltyPoints(double &bill, int &points);
void displayCustomer(string name, int id, int type);

int main()
{
    const int SIZE = 8;

    string name;
    int id, type, choice, paymentType;

    string items[SIZE] = {
        "Rice 1 KG","Sugar 1 KG","Cooking Oil 1 Litre","Milk Pack",
        "Tea Pack","Flour 5 KG","Eggs Dozen","Detergent"
    };

    double price[SIZE] = {350,180,580,220,450,950,320,600};
    int qty[SIZE] = {0};

    double gross, tax, mDiscount, bDiscount, cardCharge, total;
    int points, oldPoints, newPoints;

    registerCustomer(name, id, type);

    do
    {
        cout << "\n========== GROCERY MART MENU ==========\n";
        cout << "1. View Grocery Items\n";
        cout << "2. Add Items to Cart\n";
        cout << "3. Calculate Bill\n";
        cout << "4. View Customer Details\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1)
        {
            displayGroceryList(items, price, SIZE);
        }
        else if(choice == 2)
        {
            addItemsToCart(qty, SIZE);
        }
        else if(choice == 3)
        {
            gross = calculateGrossBill(qty, price, SIZE);

            tax = calculateSalesTax(qty, price, SIZE);

            mDiscount = calculateMembershipDiscount(gross, type);

            bDiscount = calculateBillDiscount(gross);

            cout << "\nPayment Method (1=Cash, 2=Card): ";
            cin >> paymentType;

            total = gross + tax - mDiscount - bDiscount;

            cardCharge = calculateCardCharges(total, paymentType);

            total += cardCharge;

            points = calculateLoyaltyPoints(total);

            cout << "\nGenerated Loyalty Points: " << points;

            cout << "\nEnter Existing Loyalty Points: ";
            cin >> oldPoints;

            newPoints = oldPoints + points;

            cout << "Total Loyalty Points: " << newPoints;

            redeemLoyaltyPoints(total, newPoints);

            cout << fixed << setprecision(2);
            cout << "\n\n========== FINAL BILL ==========\n";
            cout << "Gross Bill: " << gross << endl;
            cout << "Sales Tax: " << tax << endl;
            cout << "Member Discount: " << mDiscount << endl;
            cout << "Bill Discount: " << bDiscount << endl;
            cout << "Card Charges: " << cardCharge << endl;
            cout << "Total Payable: " << total << endl;
        }
        else if(choice == 4)
        {
            displayCustomer(name, id, type);
        }

    } while(choice != 5);

    cout << "\nThank you for shopping!\n";
    return 0;
}



void registerCustomer(string &name, int &id, int &type)
{
    cout << "Enter Customer Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Customer ID: ";
    cin >> id;

    cout << "1. Regular\n2. Member\nEnter Type: ";
    cin >> type;
}

void displayGroceryList(string items[], double price[], int size)
{
    cout << "\n----- ITEMS -----\n";
    for(int i=0;i<size;i++)
    {
        cout << i+1 << ". " << items[i]
             << " - Rs." << price[i] << endl;
    }
}

void addItemsToCart(int qty[], int size)
{
    int item, q;
    char ch;

    do
    {
        cout << "Enter item number: ";
        cin >> item;

        if(item>=1 && item<=size)
        {
            cout << "Quantity: ";
            cin >> q;
            qty[item-1] += q;
        }

        cout << "Add more? (y/n): ";
        cin >> ch;

    } while(ch=='y' || ch=='Y');
}

double calculateGrossBill(int qty[], double price[], int size)
{
    double sum = 0;
    for(int i=0;i<size;i++)
        sum += qty[i]*price[i];
    return sum;
}

double calculateSalesTax(int qty[], double price[], int size)
{
    double tax = 0;
    for(int i=0;i<size;i++)
    {
        double amt = qty[i]*price[i];

        if(i <= 6)
            tax += amt * 0.05;
        else
            tax += amt * 0.10;
    }
    return tax;
}

double calculateMembershipDiscount(double bill, int type)
{
    if(type == 2)
        return bill * 0.07;
    return 0;
}

double calculateBillDiscount(double bill)
{
    if(bill >= 5000 && bill <= 10000)
        return bill * 0.05;
    else if(bill > 10000)
        return bill * 0.10;
    return 0;
}

double calculateCardCharges(double bill, int paymentType)
{
    if(paymentType == 2)
        return bill * 0.02;
    return 0;
}

int calculateLoyaltyPoints(double bill)
{
    return bill / 100;
}

void redeemLoyaltyPoints(double &bill, int &points)
{
    int ch;
    cout << "\nRedeem Points? (1=Yes, 2=No): ";
    cin >> ch;

    if(ch == 1)
    {
        bill -= points;
        points = 0;
    }
}

void displayCustomer(string name, int id, int type)
{
    cout << "\n===== CUSTOMER DETAILS =====\n";
    cout << "Name: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Type: " << (type==1 ? "Regular" : "Member") << endl;
}


