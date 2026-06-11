#include <iostream>
#include <string>
using namespace std;


void displayMenu(string items[], int prices[], int size);
int placeOrder(string items[], int prices[], int size);
float calculateServiceCharges(float bill, string orderType);
float calculateGST(float bill);
float calculateDiscount(float bill);
void displayCustomerDetails(string name, string contact, string orderType, int persons);
void displayFinalBill(string name, string orderType, int persons,
                      float foodBill, float serviceCharges,
                      float gst, float discount, float total);

int main()
{
    
    string customerName, contactNumber, orderType;
    int persons;

    
    string foodItems[8] = {
        "Chicken Burger",
        "Zinger Burger",
        "Pizza Small",
        "Pizza Large",
        "Chicken Biryani",
        "BBQ Platter",
        "Fries",
        "Cold Drink"
    };

    int prices[8] = {450, 550, 900, 1800, 350, 1200, 250, 120};

    cout << "========== RESTAURANT BILLING SYSTEM ==========\n\n";

    
    cout << "Enter Customer Name: ";
    getline(cin, customerName);

    cout << "Enter Contact Number: ";
    getline(cin, contactNumber);

    cout << "Enter Order Type (Dine-in / Takeaway): ";
    getline(cin, orderType);

    cout << "Enter Number of Persons: ";
    cin >> persons;

    int choice;

    do
    {
        cout << "\n========== MAIN MENU ==========\n";
        cout << "1. View Food Menu\n";
        cout << "2. Place Order\n";
        cout << "3. Calculate Bill\n";
        cout << "4. View Customer Details\n";
        cout << "5. Exit\n";

        cout << "Enter Your Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                displayMenu(foodItems, prices, 8);
                break;

            case 2:
            {
                float foodBill = placeOrder(foodItems, prices, 8);

                float serviceCharges = calculateServiceCharges(foodBill, orderType);
                float gst = calculateGST(foodBill);
                float discount = calculateDiscount(foodBill);

                float total = foodBill + serviceCharges + gst - discount;

                cout << "\nFree Delivery Applied!\n";
                if(foodBill <= 5000)
                {
                    cout << "No Free Delivery.\n";
                }

                displayFinalBill(customerName, orderType, persons,
                                 foodBill, serviceCharges,
                                 gst, discount, total);
                break;
            }

            case 3:
                cout << "\nPlease Place Order First.\n";
                break;

            case 4:
                displayCustomerDetails(customerName, contactNumber,
                                       orderType, persons);
                break;

            case 5:
                cout << "\nThank You for Using System!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 5);

    return 0;
}


void displayMenu(string items[], int prices[], int size)
{
    cout << "\n========== FOOD MENU ==========\n";

    for(int i = 0; i < size; i++)
    {
        cout << i + 1 << ". "
             << items[i]
             << " - Rs. " << prices[i] << endl;
    }
}


int placeOrder(string items[], int prices[], int size)
{
    int itemNo, quantity;
    char more;

    int totalBill = 0;

    do
    {
        displayMenu(items, prices, size);

        cout << "\nEnter Item Number: ";
        cin >> itemNo;

        cout << "Enter Quantity: ";
        cin >> quantity;

        if(itemNo >= 1 && itemNo <= size)
        {
            int itemBill = prices[itemNo - 1] * quantity;
            totalBill += itemBill;

            cout << items[itemNo - 1]
                 << " Added Successfully!\n";

            cout << "Current Bill: Rs. "
                 << totalBill << endl;
        }
        else
        {
            cout << "Invalid Item Number!\n";
        }

        cout << "Do You Want to Order More? (y/n): ";
        cin >> more;

    } while(more == 'y' || more == 'Y');

    return totalBill;
}


float calculateServiceCharges(float bill, string orderType)
{
    if(orderType == "Dine-in" || orderType == "dine-in")
    {
        return bill * 0.10;
    }
    else
    {
        return bill * 0.05;
    }
}


float calculateGST(float bill)
{
    return bill * 0.16;
}


float calculateDiscount(float bill)
{
    if(bill >= 3000 && bill <= 5000)
    {
        return bill * 0.05;
    }
    else if(bill >= 5001 && bill <= 10000)
    {
        return bill * 0.10;
    }
    else if(bill > 10000)
    {
        return bill * 0.15;
    }
    else
    {
        return 0;
    }
}


void displayCustomerDetails(string name, string contact,
                            string orderType, int persons)
{
    cout << "\n========== CUSTOMER DETAILS ==========\n";

    cout << "Customer Name: " << name << endl;
    cout << "Contact Number: " << contact << endl;
    cout << "Order Type: " << orderType << endl;
    cout << "Number of Persons: " << persons << endl;
}


void displayFinalBill(string name, string orderType, int persons,
                      float foodBill, float serviceCharges,
                      float gst, float discount, float total)
{
    cout << "\n\n========== RESTAURANT BILL ==========\n";

    cout << "\nCustomer Name: " << name << endl;
    cout << "Order Type: " << orderType << endl;
    cout << "Number of Persons: " << persons << endl;

    cout << "\nFood Bill: Rs. " << foodBill << endl;
    cout << "Service Charges: Rs. " << serviceCharges << endl;
    cout << "GST: Rs. " << gst << endl;
    cout << "Discount: Rs. " << discount << endl;

    cout << "\n-----------------------------------\n";

    cout << "Total Payable Amount: Rs. "
         << total << endl;

    cout << "Enjoy Your Meal :)\n";

    cout << "=====================================\n";
}
