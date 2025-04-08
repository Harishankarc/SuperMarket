#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Console colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

class Item {
public:
    string name;
    int price;
    int quantity;

    Item(string n, int p, int q) : name(n), price(p), quantity(q) {}
};

vector<Item> storeItems;
vector<Item> cartItems;
string adminUsername = "admin";
string adminPassword = "admin123";

void printBanner(const string& title) {
    cout << BOLD << CYAN << "\n=========== " << title << " ===========\n" << RESET;
}

bool adminLogin() {
    string username, password;
    printBanner("Admin Login");
    cout << "Enter Admin Username: ";
    cin >> username;
    cout << "Enter Admin Password: ";
    cin >> password;
    return username == adminUsername && password == adminPassword;
}

void addItem() {
    string name;
    int price, quantity;
    printBanner("Add Item");
    cout << "Enter item name: ";
    cin >> name;
    cout << "Enter price: ";
    cin >> price;
    cout << "Enter quantity: ";
    cin >> quantity;

    for (auto &item : storeItems) {
        if (item.name == name) {
            item.quantity += quantity;
            cout << GREEN << "Item quantity updated successfully!\n" << RESET;
            return;
        }
    }

    storeItems.push_back(Item(name, price, quantity));
    cout << GREEN << "Item added successfully!\n" << RESET;
}

void removeItem() {
    string name;
    printBanner("Remove Item");
    cout << "Enter item name to remove: ";
    cin >> name;

    for (auto it = storeItems.begin(); it != storeItems.end(); ++it) {
        if (it->name == name) {
            storeItems.erase(it);
            cout << GREEN << "Item removed successfully!\n" << RESET;
            return;
        }
    }
    cout << RED << "Item not found!\n" << RESET;
}

void viewItems() {
    printBanner("Available Items");
    if (storeItems.empty()) {
        cout << YELLOW << "No items in the store.\n" << RESET;
        return;
    }
    for (auto &item : storeItems) {
        cout << "Name: " << item.name << ", Price: Rs." << item.price << ", Quantity: " << item.quantity << endl;
    }
}

void addToCart() {
    string name;
    int quantity;
    printBanner("Add to Cart");
    cout << "Enter item name to add to cart: ";
    cin >> name;
    cout << "Enter quantity: ";
    cin >> quantity;

    for (auto &item : storeItems) {
        if (item.name == name) {
            if (item.quantity >= quantity) {
                cartItems.push_back(Item(name, item.price, quantity));
                item.quantity -= quantity;
                cout << GREEN << "Item added to cart!\n" << RESET;
                return;
            } else {
                cout << RED << "Not enough stock available!\n" << RESET;
                return;
            }
        }
    }
    cout << RED << "Item not found!\n" << RESET;
}

void viewCart() {
    printBanner("Cart Items");
    if (cartItems.empty()) {
        cout << YELLOW << "Cart is empty.\n" << RESET;
        return;
    }
    for (auto &item : cartItems) {
        cout << "Name: " << item.name << ", Price: Rs." << item.price << ", Quantity: " << item.quantity << endl;
    }
}

void generateBill() {
    printBanner("Bill Details");
    int total = 0;
    for (auto &item : cartItems) {
        int cost = item.price * item.quantity;
        cout << item.name << " x " << item.quantity << " = Rs." << cost << endl;
        total += cost;
    }
    cout << BOLD << BLUE << "Total Amount: Rs." << total << "\n" << RESET;
    cartItems.clear();
}

int main() {
    int choice;
    string userType;

    while (true) {
        printBanner("Supermarket System");
        cout << "Choose user type (admin/customer/exit): ";
        cin >> userType;

        if (userType == "exit") {
            cout << GREEN << "Exiting...\n" << RESET;
            break;
        }

        if (userType == "admin") {
            if (!adminLogin()) {
                cout << RED << "Invalid login credentials!\n" << RESET;
                continue;
            }
            while (true) {
                printBanner("Admin Panel");
                cout << "1. Add Item\n2. Remove Item\n3. View Items\n4. Logout\nEnter choice: ";
                cin >> choice;
                if (choice == 1) addItem();
                else if (choice == 2) removeItem();
                else if (choice == 3) viewItems();
                else if (choice == 4) break;
                else cout << RED << "Invalid choice!\n" << RESET;
            }
        } else if (userType == "customer") {
            while (true) {
                printBanner("Customer Panel");
                cout << "1. View Items\n2. Add to Cart\n3. View Cart\n4. Generate Bill\n5. Logout\nEnter choice: ";
                cin >> choice;
                if (choice == 1) viewItems();
                else if (choice == 2) addToCart();
                else if (choice == 3) viewCart();
                else if (choice == 4) generateBill();
                else if (choice == 5) break;
                else cout << RED << "Invalid choice!\n" << RESET;
            }
        } else {
            cout << RED << "Invalid user type!\n" << RESET;
        }
    }

    return 0;
}
