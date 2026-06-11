#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

string userName;
string userEmail;
string userCity;
int    customerType;   


const int TOTAL_PRODUCTS = 8;

string productNames[TOTAL_PRODUCTS] = {
    "T-Shirt", "Jeans", "Shoes", "Watch",
    "Handbag", "Headphones", "Mobile Cover", "Perfume"
};

double productPrices[TOTAL_PRODUCTS] = {
    1200, 3500, 5000, 2500,
    4200, 3000, 700,  2800
};


const int MAX_CART = 20;
int    cartProductIndex[MAX_CART];   
int    cartQuantity[MAX_CART];       
int    cartSize = 0;                 


void registerUser()
{
    cout << "\n========== USER REGISTRATION ==========\n";

    cout << "Enter Your Name   : ";
    cin.ignore();
    getline(cin, userName);

    cout << "Enter Your Email  : ";
    getline(cin, userEmail);

    cout << "Enter Your City   : ";
    getline(cin, userCity);

    cout << "Customer Type\n";
    cout << "  1. New Customer\n";
    cout << "  2. Returning Customer\n";
    cout << "Enter choice (1/2): ";
    cin >> customerType;

    while (customerType != 1 && customerType != 2)
    {
        cout << "Invalid! Enter 1 or 2: ";
        cin >> customerType;
    }

    cout << "========================================\n";
    cout << "  Registration Successful! Welcome, " << userName << "!\n";
    cout << "========================================\n";
}



void displayProducts()
{
    cout << fixed << setprecision(2);
    cout << "\n========== AVAILABLE PRODUCTS ==========\n";
    cout << left << setw(5)  << "No."
         << setw(20) << "Product"
         << "Price\n";
    cout << "-----------------------------------------\n";

    for (int i = 0; i < TOTAL_PRODUCTS; i++)
    {
        cout << left << setw(5)  << (i + 1)
             << setw(20) << productNames[i]
             << "Rs. " << productPrices[i] << "\n";
    }

    cout << "=========================================\n";
}


void addToCart()
{
    if (cartSize >= MAX_CART)
    {
        cout << "\nCart is full! Cannot add more items.\n";
        return;
    }

    displayProducts();

    int productNo, qty;

    cout << "\nEnter Product Number to add (1-" << TOTAL_PRODUCTS << "): ";
    cin >> productNo;

    while (productNo < 1 || productNo > TOTAL_PRODUCTS)
    {
        cout << "Invalid! Enter between 1 and " << TOTAL_PRODUCTS << ": ";
        cin >> productNo;
    }

    cout << "Enter Quantity: ";
    cin >> qty;

    while (qty < 1)
    {
        cout << "Quantity must be at least 1: ";
        cin >> qty;
    }


    bool found = false;
    for (int i = 0; i < cartSize; i++)
    {
        if (cartProductIndex[i] == productNo - 1)
        {
            cartQuantity[i] += qty;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cartProductIndex[cartSize] = productNo - 1;
        cartQuantity[cartSize]     = qty;
        cartSize++;
    }

    cout << "\n  '" << productNames[productNo - 1]
         << "' (x" << qty << ") added to cart!\n";
}


double calculateProductTotal()
{
    double total = 0;
    for (int i = 0; i < cartSize; i++)
    {
        total += productPrices[cartProductIndex[i]] * cartQuantity[i];
    }
    return total;
}


double calculateGST(double productTotal)
{
    return productTotal * 0.17;
}



double calculateDeliveryCharges()
{
    string city = userCity;
    for (int i = 0; i < (int)city.size(); i++)
    {
        if (city[i] >= 'A' && city[i] <= 'Z')
            city[i] = city[i] + 32;
    }

    if (city == "lahore" || city == "karachi" || city == "islamabad")
        return 250;
    else
        return 500;
}


double calculateCustomerDiscount(double productTotal)
{
    if (customerType == 1)        
        return productTotal * 0.05;
    else                          
        return productTotal * 0.10;
}


double calculateOrderValueDiscount(double productTotal)
{
    if (productTotal > 10000)
        return productTotal * 0.12;
    else if (productTotal >= 5000)
        return productTotal * 0.05;
    else
        return 0;
}



double calculatePaymentCharges(double amount, int paymentMethod)
{
    if (paymentMethod == 2)   
        return amount * 0.025;
    return 0;
}



void displayCheckoutBill()
{
    if (cartSize == 0)
    {
        cout << "\nYour cart is empty! Add products first.\n";
        return;
    }

    
    cout << fixed << setprecision(2);
    cout << "\n------------- YOUR CART ----------------\n";
    cout << left << setw(20) << "Product"
         << setw(8)  << "Qty"
         << "Subtotal\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < cartSize; i++)
    {
        int    idx      = cartProductIndex[i];
        int    qty      = cartQuantity[i];
        double subtotal = productPrices[idx] * qty;

        cout << left << setw(20) << productNames[idx]
             << setw(8)  << qty
             << "Rs. " << subtotal << "\n";
    }
    cout << "----------------------------------------\n";

  
    int paymentMethod;
    cout << "\nSelect Payment Method:\n";
    cout << "  1. Cash on Delivery\n";
    cout << "  2. Debit/Credit Card\n";
    cout << "Enter choice (1/2): ";
    cin >> paymentMethod;

    while (paymentMethod != 1 && paymentMethod != 2)
    {
        cout << "Invalid! Enter 1 or 2: ";
        cin >> paymentMethod;
    }

    
    double productTotal    = calculateProductTotal();
    double gst             = calculateGST(productTotal);
    double delivery        = calculateDeliveryCharges();
    double customerDisc    = calculateCustomerDiscount(productTotal);
    double orderDisc       = calculateOrderValueDiscount(productTotal);

    
    double amountBeforePayment = productTotal + gst + delivery
                               - customerDisc - orderDisc;

    double paymentCharges  = calculatePaymentCharges(amountBeforePayment, paymentMethod);

    double finalAmount     = amountBeforePayment + paymentCharges;

    string typeStr         = (customerType == 1) ? "New Customer" : "Returning Customer";
    string payStr          = (paymentMethod == 1) ? "Cash on Delivery" : "Debit/Credit Card";

    
    cout << "\n========== ONLINE SHOPPING BILL ==========\n";
    cout << "User Name         : " << userName     << "\n";
    cout << "Email             : " << userEmail    << "\n";
    cout << "City              : " << userCity     << "\n";
    cout << "Customer Type     : " << typeStr      << "\n";
    cout << "Payment Method    : " << payStr       << "\n";
    cout << "------------------------------------------\n";
    cout << "Product Total     : Rs. " << productTotal   << "\n";
    cout << "GST (17%)         : Rs. " << gst            << "\n";
    cout << "Delivery Charges  : Rs. " << delivery       << "\n";
    cout << "Customer Discount : Rs. " << customerDisc   << "\n";
    cout << "Order Discount    : Rs. " << orderDisc      << "\n";
    cout << "Payment Charges   : Rs. " << paymentCharges << "\n";
    cout << "------------------------------------------\n";
    cout << "Final Payable Amt : Rs. " << finalAmount    << "\n";
    cout << "\n    Thank You for Shopping :)\n";
    cout << "==========================================\n";
}

int displayMenu()
{
    int choice;
    cout << "\n========== MAIN MENU ====================\n";
    cout << "  1. View Products\n";
    cout << "  2. Add Product to Cart\n";
    cout << "  3. Calculate Checkout Bill\n";
    cout << "  4. View User Details\n";
    cout << "  5. Exit\n";
    cout << "==========================================\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}



void viewUserDetails()
{
    string typeStr = (customerType == 1) ? "New Customer" : "Returning Customer";
    cout << "\n========== USER DETAILS =================\n";
    cout << "Name          : " << userName     << "\n";
    cout << "Email         : " << userEmail    << "\n";
    cout << "City          : " << userCity     << "\n";
    cout << "Customer Type : " << typeStr      << "\n";
    cout << "Cart Items    : " << cartSize     << "\n";
    cout << "==========================================\n";
}

int main()
{
    cout << fixed << setprecision(2);
    cout << "==========================================\n";
    cout << "   Welcome to Online Shopping System     \n";
    cout << "==========================================\n";

    registerUser();

    int choice = 0;

    while (choice != 5)
    {
        choice = displayMenu();

        if (choice == 1)
        {
            displayProducts();
        }
        else if (choice == 2)
        {
            addToCart();
        }
        else if (choice == 3)
        {
            displayCheckoutBill();
        }
        else if (choice == 4)
        {
            viewUserDetails();
        }
        else if (choice == 5)
        {
            cout << "\nThank you for visiting. Goodbye!\n";
        }
        else
        {
            cout << "\nInvalid choice! Please enter 1-5.\n";
        }
    }

    return 0;
}
