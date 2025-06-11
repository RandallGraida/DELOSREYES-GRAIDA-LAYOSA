#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

struct Product {
    string id;
    string name;
    double price;
    int quantity;
    vector<string> history;
};

// Utility to safely get numeric input
template <typename T>
void getInput(T& var, const string& prompt) {
    while (true) {
        cout << prompt;
        cin >> var;
        if (!cin.fail()) break;
        cout << "Invalid input. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Check if ID is unique
bool isUniqueID(const vector<Product>& products, const string& id) {
    for (const auto& p : products)
        if (p.id == id) return false;
    return true;
}

// Add new product
void addProduct(vector<Product>& products) {
    Product p;
    cout << "\n--- Add Product ---\n";
    cout << "Enter Product ID (start with 001): ";
    cin >> p.id;
    if (!isUniqueID(products, p.id)) {
        cout << "Error: Product ID already exists.\n";
        return;
    }
    cin.ignore();
    cout << "Enter Product Name: ";
    getline(cin, p.name);
    getInput(p.price, "Enter Product Selling Price: ");
    getInput(p.quantity, "Enter Product Stock Quantity: ");

    p.history.emplace_back("Product added with quantity: " + to_string(p.quantity));
    products.push_back(p);
    cout << "Product added successfully.\n";
}

// Find product by ID
Product* findProduct(vector<Product>& products, const string& id) {
    for (auto& p : products)
        if (p.id == id) return &p;
    return nullptr;
}

// Update existing product
void updateProduct(vector<Product>& products) {
    cout << "\n--- Update Product ---\n";
    cout << "Enter Product ID: ";
    string id;
    cin >> id;

    Product* p = findProduct(products, id);
    if (!p) {
        cout << "Product not found.\n";
        return;
    }

    int choice;
    cout << "\n1. Update Price\n2. Stock In\n3. Stock Out\nChoose option: ";
    getInput(choice, "");

    switch (choice) {
        case 1: {
            getInput(p->price, "Enter new price: ");
            p->history.emplace_back("Price updated to: " + to_string(p->price));
            cout << "Price updated.\n";
            break;
        }
        case 2: {
            int stockIn;
            getInput(stockIn, "Enter stock to add: ");
            p->quantity += stockIn;
            p->history.emplace_back("Stock in: +" + to_string(stockIn));
            cout << "Stock added.\n";
            break;
        }
        case 3: {
            int stockOut;
            getInput(stockOut, "Enter stock to remove: ");
            if (stockOut > p->quantity) {
                cout << "Insufficient stock.\n";
            } else {
                p->quantity -= stockOut;
                p->history.emplace_back("Stock out: -" + to_string(stockOut));
                cout << "Stock removed.\n";
            }
            break;
        }
        default:
            cout << "Invalid option.\n";
    }
}

// Display all product details
void displayProducts(const vector<Product>& products) {
    if (products.empty()) {
        cout << "No products to display.\n";
        return;
    }

    cout << "\n--- Product List ---\n";
    for (const auto& p : products) {
        cout << "\nID       : " << p.id
             << "\nName     : " << p.name
             << "\nPrice    : " << fixed << setprecision(2) << p.price
             << "\nQuantity : " << p.quantity
             << "\nHistory  :\n";
        for (const auto& h : p.history)
            cout << "  - " << h << "\n";
        cout << "-------------------------\n";
    }
}

// Main menu
void menu() {
    vector<Product> products;
    int option;

    do {
        cout << "\n=== PRODUCT MENU ===\n"
             << "1. Add Product\n"
             << "2. Update Product\n"
             << "3. Display Products\n"
             << "4. Exit\n";
        getInput(option, "Select an option: ");

        switch (option) {
            case 1: addProduct(products); break;
            case 2: updateProduct(products); break;
            case 3: displayProducts(products); break;
            case 4: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (option != 4);
}

int main() {
    menu();
    return 0;
}