#include <iostream>
#include <cstring>
using namespace std;

class SuperMarket
{
private:
    static char AdminUser[20];
    static char AdminPass[20];
    static char CustomerUser[20];
    static char CustomerPass[20];
    char ItemsName[30];
    float ItemPrice;
    static bool isAdminLoggedIn;
    static bool isCustomerLoggedIn;
    static int NumberofItems;
    static char AddItemNametoList[20][20];
    static int AddItemPricetoList[20];
    static int cartitemcount;

public:
    friend void AdminUse(SuperMarket s[], int n);
    friend void CustomerUse(SuperMarket s[], int n);
    friend void AddItems(SuperMarket s[], int n);
    friend void AddToCart(SuperMarket s[], int n);
    friend void ShowItems(SuperMarket s[], int n);
    friend void showCart(SuperMarket s[], int n);
    friend void RemovefromCart(SuperMarket s[], int n);
    friend void bill(SuperMarket s[], int n);
    friend void RemoveItems(SuperMarket s[], int n)
    {
        char removeitemName[30] = "Removed";
        float removeitemPrice = 0;
        char searchItem[30];
        bool isRemoved = false;
        cout << "Enter item name: ";
        cin >> searchItem;
        for (int i = 0; i < n; i++)
        {
            if (strcmp(searchItem, s[i].ItemsName) == 0)
            {
                strcpy(s[i].ItemsName, removeitemName);
                s[i].ItemPrice = removeitemPrice;
                cout << endl;
                cout << "Removed Sucessfully" << endl;
                isRemoved = true;
            }
        }
        if (isRemoved == false)
        {
            cout << "There is no item named " << searchItem << endl;
        }
    }
    void AddtoList(char ItemName[], int ItemPrice)
    {
    }
};

void AddToCart(SuperMarket s[], int n)
{
    bool isFound = false;
    char SearchItem[30];
    cout << endl;
    while (!isFound)
    {
        cout << "Search item: ";
        cin >> SearchItem;
        cout << "Pos.     |"
             << "Item Name     |"
             << "Item Price     " << endl;
        cout << "------------------------------------------------" << endl;
        for (int i = 0; i < SuperMarket::NumberofItems; i++)
        {
            if (strcmp(s[i].ItemsName, SearchItem) == 0)
            {
                cout << i + 1 << "     " << s[i].ItemsName << "     " << s[i].ItemPrice << "     " << endl;
                strcpy(SuperMarket::AddItemNametoList[SuperMarket::cartitemcount], s[i].ItemsName);
                SuperMarket::AddItemPricetoList[SuperMarket::cartitemcount] = s[i].ItemPrice;
                SuperMarket::cartitemcount++;
                isFound = true;
                break;
            }
        }
        if (!isFound)
        {
            cout << "\x1b[31m"
                 << "No item is present"
                 << "\x1b[0m" << endl;
        }
    }
}

void showCart(SuperMarket s[], int n)
{
    cout << "Pos.     |"
         << "Item Name     |"
         << "Item Price   " << endl;
    cout << "------------------------------------------------" << endl;
    int size = sizeof(SuperMarket::AddItemPricetoList) / sizeof(SuperMarket::AddItemPricetoList[0]);
    if (strcmp(SuperMarket::AddItemNametoList[0], "") == 0)
    {
        cout << "Your cart is empty" << endl;
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            if (strcmp(SuperMarket::AddItemNametoList[i], "") == 0)
            {
                break;
            }
            else
            {
                cout << i + 1 << "        " << SuperMarket::AddItemNametoList[i] << "        " << SuperMarket::AddItemPricetoList[i] << endl;
            }
        }
    }
}

void RemovefromCart(SuperMarket s[], int n)
{
    char removeitemName[30] = "Removed";
    int removeitemPrice = 0;
    char searchItem[30];
    bool isRemoved = false;
    cout << "Enter item name: ";
    cin >> searchItem;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(searchItem, SuperMarket::AddItemNametoList[i]) == 0)
        {
            strcpy(SuperMarket::AddItemNametoList[i], removeitemName);
            SuperMarket::AddItemPricetoList[i] = removeitemPrice;
            cout << endl;
            cout << "Removed Sucessfully" << endl;
            isRemoved = true;
        }
    }
    if (isRemoved == false)
    {
        cout << "There is no item named " << searchItem << " in cart" << endl;
    }
}

void bill(SuperMarket s[], int n)
{
    float total = 0.00;
    cout << "******************************BILL******************************" << endl;
    cout << "------------------------ ABC SUPERMARKET--------------------------" << endl;
    cout << "------------------------ Telp:9999999999--------------------------" << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << "Item Name                                               Item Price" << endl;
    cout << "------------------------------------------------------------------" << endl;

    int size = sizeof(SuperMarket::AddItemPricetoList) / sizeof(SuperMarket::AddItemPricetoList[0]);

    if (strcmp(SuperMarket::AddItemNametoList[0], "") == 0)
    {
        cout << "---------------------------- No Items ---------------------------";
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            if (strcmp(SuperMarket::AddItemNametoList[i], "") == 0)
            {
                break;
            }
            else if ((strcmp(SuperMarket::AddItemNametoList[i], "Removed") == 0))
            {
                continue;
            }
            else
            {
                cout << SuperMarket::AddItemNametoList[i] << "                                                  " << SuperMarket::AddItemPricetoList[i] << endl;
                total += SuperMarket::AddItemPricetoList[i];
            }
        }
    }
    cout << "------------------------------------------------------------------" << endl;
    cout << "Total                                                     " << total << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << "------------------------ THANK YOU --------------------------" << endl;

    exit(1);
}

void CustomerUse(SuperMarket s[],  int n)
{
    char Username[30];
    char AdminUsername[30];
    char CheckUsername[20];
    char Password[30];
    char AdminPassword[30];
    char CheckPassword[20];
    cout << "Enter UserName: ";
    cin >> Username;
    strcpy(SuperMarket::CustomerUser, Username);
    cout << "Enter Password: ";
    cin >> Password;
    strcpy(SuperMarket::CustomerPass, Password);
    cout << endl;
    cout << "Confirm User name and Password!";
    cout << endl;
    while (!SuperMarket::isCustomerLoggedIn)
    {
        cout << endl;
        cout << "Enter UserName: ";
        cin >> CheckUsername;
        strcpy(SuperMarket::CustomerUser, Username);
        cout << "Enter Password: ";
        cin >> CheckPassword;
        if (strcmp(Username, CheckUsername) == 0 && strcmp(Password, CheckPassword) == 0)
        {
            cout << endl;
            cout << "\x1b[31m"
                 << "You have logged in as Customer"
                 << "\x1b[0m" << endl;
            SuperMarket::isCustomerLoggedIn = true;
        }
        else
        {
            cout << endl;
            cout << "\x1b[31m"
                 << "Check Username or Password!"
                 << "\x1b[0m" << endl;
        }
    }

    int choice;

    bool isExit = false;
    if (SuperMarket::isCustomerLoggedIn)
    {
        cout << endl;
        cout << "--------------------------------- C U S T O M E R ---------------------------------" << endl;
        cout << endl;
        while (!isExit)
        {
            cout << "Select you option: " << endl;
            cout << "1.Add to Cart" << endl
                 << "2.Show Cart" << endl
                 << "3.Remove from Cart" << endl
                 << "4.Show Products" << endl
                 << "5.Back to Admin Login" << endl
                 << "6.Bill" << endl
                 << "7.exit" << endl;
            cin >> choice;
            if (choice == 1)
            {
                AddToCart(s, n);
            }
            else if (choice == 2)
            {
                showCart(s, n);
            }
            else if (choice == 3)
            {
                RemovefromCart(s, n);
            }
            else if (choice == 4)
            {
                ShowItems(s, n);
            }
            else if (choice == 5)
            {
                AdminUse(s,n);
                break;
            }
            else if (choice == 6)
            {
                bill(s, n);
            }
            else if (choice == 7)
            {
                isExit = true;
            }
            else
            {
                cout << "Enter a valid option! " << endl;
            }
        }
    }
}

void ShowItems(SuperMarket s[], int n)
{
    char removeitemName[30] = "Removed";
    cout << endl;
    cout << "Pos.     |"
         << "Item Name     |"
         << "Item Price     " << endl;
    cout << "------------------------------------------------" << endl;
    for (int i = 0; i < SuperMarket::NumberofItems; i++)
    {
        if (strcmp(s[i].ItemsName, removeitemName) == 0 && s[i].ItemPrice == 0)
        {
            cout << i + 1 << "          "
                 << "\x1b[31m" << s[i].ItemsName << "\x1b[0m" << "               " << s[i].ItemPrice << " Rs            " << endl;
        }
        else
        {
            cout << i + 1 << "          " << s[i].ItemsName << "               " << s[i].ItemPrice << " Rs            " << endl;
        }
    }
    cout << endl;
}

void AdminUse(SuperMarket s[], int n)
{
    char AdminUsername[30];
    char AdminPassword[30];
    cout << "Enter UserName: ";
    cin >> AdminUsername;
    cout << "Enter Password: ";
    cin >> AdminPassword;
    cout << endl;
    if (strcmp(AdminUsername, SuperMarket::AdminUser) == 0 && strcmp(AdminPassword, SuperMarket::AdminPass) == 0)
    {
        cout << "\x1b[31m"
             << "You have logged in as Admin"
             << "\x1b[0m" << endl;
        SuperMarket::isAdminLoggedIn = true;
    }
    else
    {
        cout << "\x1b[31m"
             << "Check Username or Password!"
             << "\x1b[0m" << endl;
    }
    int choice;
    if (SuperMarket::isAdminLoggedIn)
    {
        bool isExit = false;
        cout << endl;
        cout << "--------------------------------- A D M I N ---------------------------------" << endl;
        cout << endl;
        while (!isExit)
        {
            cout << "Select you option: " << endl;
            cout << "1.Add items" << endl
                 << "2.Remove items" << endl
                 << "3.Show items" << endl
                 << "4.Back to Customer Login" << endl
                 << "5.exit" << endl;
            cin >> choice;
            if (choice == 1)
            {
                AddItems(s, n);
            }
            else if (choice == 2)
            {
                RemoveItems(s, n);
            }
            else if (choice == 3)
            {
                ShowItems(s, n);
            }
            else if (choice == 4)
            {
                CustomerUse(s,n);
            }
            else if (choice == 5)
            {
                isExit = true;
            }
            else
            {
                cout << "Enter a valid option! " << endl;
            }
        }
    }
}

void AddItems(SuperMarket s[], int n)
{
    cout << endl;
    cout << "Enter number of items: ";
    cin >> SuperMarket::NumberofItems;
    cout << endl;
    cout << "Item no.     "
         << "Name and Price(Rs)     " << endl;
    cout << "------------------------------" << endl;
    for (int i = 0; i < SuperMarket::NumberofItems; i++)
    {
        cout << i + 1 << ".     ";
        cin >> s[i].ItemsName;
        cout << "       ";
        cin.ignore();
        cout << "Rs ";
        cin >> s[i].ItemPrice;
        cout << "     ";
        cout << "-------------------------" << endl;
    }
}

char SuperMarket::AddItemNametoList[20][20] = {};
int SuperMarket::AddItemPricetoList[20] = {};
int SuperMarket::cartitemcount;
int SuperMarket::NumberofItems;
bool SuperMarket::isAdminLoggedIn = false;
bool SuperMarket::isCustomerLoggedIn = false;
char SuperMarket::CustomerUser[20];
char SuperMarket::CustomerPass[20];
char SuperMarket::AdminPass[20] = "a";
char SuperMarket::AdminUser[20] = "a";

int main(void)
{
    int n = 50;
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << "\x1b[31m"
         << "                               ABC SuperMarket                                       "
         << "\x1b[0m" << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "Welcome to ABC SuperMarket.Where you can buy fresh fruits,Electronic items,Kitchen \nitems,Drinks etc." << endl;
    cout << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;

    // SuperMarket Logincheck;
    SuperMarket Items[n];
    // Logincheck.LoginCheck(Items, Logincheck, n);
    // AdminUse(Items, Logincheck, n);

    int choice;
    cout << "--------------------------------- L O G I N ---------------------------------" << endl;
    cout << endl;
    cout << "Are you" << endl;
    cout << "\x1b[31m" << "1.Customer" << "\x1b[0m" << endl
         << "\x1b[31m" << "2.Admin" << "\x1b[0m" << endl
         << "\x1b[31m" << "3.Exit" << "\x1b[0m" << endl;
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
    {
        CustomerUse(Items, n);
        break;
    }
    case 2:
    {
        AdminUse(Items, n);
        break;
    }
    case 3:
    {
        cout << "Exiting..." << endl;
        exit(1);
    }
    default:
    {
        cout << "\x1b[31m"
             << "Select a valid option!"
             << "\x1b[0m" << endl;
        break;
    }
    }
}
