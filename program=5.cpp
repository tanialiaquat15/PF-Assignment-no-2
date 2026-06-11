#include<iostream>
#include<string>
using namespace std;


string clientName, businessName, businessType;
int campaignDays;

string platforms[3] = {"Instagram", "Facebook", "LinkedIn"};
double platformCharges[3] = {15000, 12000, 20000};

int selectedPlatform = 0;

int staticPosts, reelPosts, carouselPosts;

double adBudget;

double postDesignCost = 0;
double handlingFee = 0;
double extraCharges = 0;
double gst = 0;
double discount = 0;
double finalBill = 0;


void registerClient()
{
    cout << "Enter Client Name: ";
    cin.ignore();
    getline(cin, clientName);

    cout << "Enter Business Name: ";
    getline(cin, businessName);

    cout << "Enter Business Type\n";
    cout << "1. Small Business\n";
    cout << "2. Medium Business\n";
    cout << "3. Corporate Business\n";
    cout << "Choice: ";
    
    int choice;
    cin >> choice;

    if(choice == 1)
    {
        businessType = "Small Business";
    }
    else if(choice == 2)
    {
        businessType = "Medium Business";
    }
    else
    {
        businessType = "Corporate Business";
    }

    cout << "Enter Campaign Duration (Days): ";
    cin >> campaignDays;
}

void displayPlatforms()
{
    cout << "\n===== SOCIAL MEDIA PLATFORMS =====\n";

    for(int i = 0; i < 3; i++)
    {
        cout << i + 1 << ". " << platforms[i]
             << " - Rs. " << platformCharges[i] << endl;
    }
}

void selectPlatform()
{
    cout << "\nSelect Platform: ";
    cin >> selectedPlatform;

    selectedPlatform--;

    cout << "Platform Selected Successfully!\n";
}

double calculatePostDesignCost()
{
    cout << "\nEnter Number of Static Posts: ";
    cin >> staticPosts;

    cout << "Enter Number of Reel/Video Posts: ";
    cin >> reelPosts;

    cout << "Enter Number of Carousel Posts: ";
    cin >> carouselPosts;

    postDesignCost =
        (staticPosts * 1000) +
        (reelPosts * 2500) +
        (carouselPosts * 1800);

    return postDesignCost;
}

double calculateHandlingFee()
{
    cout << "Enter Advertisement Budget: ";
    cin >> adBudget;

    if(adBudget < 50000)
    {
        handlingFee = adBudget * 0.05;
    }
    else if(adBudget >= 50000 && adBudget <= 100000)
    {
        handlingFee = adBudget * 0.08;
    }
    else
    {
        handlingFee = adBudget * 0.10;
    }

    return handlingFee;
}

double calculateExtraCharges()
{
    if(campaignDays > 30)
    {
        extraCharges = (campaignDays - 30) * 500;
    }
    else
    {
        extraCharges = 0;
    }

    return extraCharges;
}

double calculateGST(double total)
{
    gst = total * 0.16;
    return gst;
}

double calculateDiscount(double total)
{
    if(businessType == "Small Business")
    {
        discount = total * 0.05;
    }
    else if(businessType == "Medium Business")
    {
        discount = total * 0.08;
    }
    else
    {
        discount = total * 0.10;
    }

    return discount;
}

void displayFinalBill()
{
    double platformCost = platformCharges[selectedPlatform];

    double total =
        platformCost +
        postDesignCost +
        adBudget +
        handlingFee +
        extraCharges;

    gst = calculateGST(total);

    total = total + gst;

    discount = calculateDiscount(total);

    finalBill = total - discount;

    cout << "\n\n========== SOCIAL MEDIA CAMPAIGN BILL ==========\n";

    cout << "Client Name: " << clientName << endl;
    cout << "Business Name: " << businessName << endl;
    cout << "Business Type: " << businessType << endl;
    cout << "Selected Platform: " << platforms[selectedPlatform] << endl;
    cout << "Campaign Duration: " << campaignDays << " Days\n";

    cout << "Platform Management Charges: Rs. "
         << platformCost << endl;

    cout << "Post Design Cost: Rs. "
         << postDesignCost << endl;

    cout << "Ad Budget: Rs. "
         << adBudget << endl;

    cout << "Ad Handling Fee: Rs. "
         << handlingFee << endl;

    cout << "Extra Duration Charges: Rs. "
         << extraCharges << endl;

    cout << "GST: Rs. "
         << gst << endl;

    cout << "Discount: Rs. "
         << discount << endl;

    cout << "----------------------------------------------\n";

    cout << "Final Campaign Cost: Rs. "
         << finalBill << endl;

    cout << "================================================\n";
}

void displayClientDetails()
{
    cout << "\n===== CLIENT DETAILS =====\n";

    cout << "Client Name: " << clientName << endl;
    cout << "Business Name: " << businessName << endl;
    cout << "Business Type: " << businessType << endl;
    cout << "Campaign Duration: " << campaignDays << " Days\n";
}

int main()
{
    registerClient();

    int choice;

    do
    {
        cout << "\n\n===== MAIN MENU =====\n";
        cout << "1. View Platforms\n";
        cout << "2. Select Campaign Platform\n";
        cout << "3. Calculate Campaign Cost\n";
        cout << "4. View Client Details\n";
        cout << "5. Exit\n";

        cout << "Enter Your Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                displayPlatforms();
                break;

            case 2:
                displayPlatforms();
                selectPlatform();
                break;

            case 3:
                calculatePostDesignCost();
                calculateHandlingFee();
                calculateExtraCharges();
                displayFinalBill();
                break;

            case 4:
                displayClientDetails();
                break;

            case 5:
                cout << "\nProgram Closed Successfully!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 5);

    return 0;
}
