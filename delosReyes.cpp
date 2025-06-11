#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

// Product structure to store details and history
struct Product {
    string id, name;
    double price;
    int stock;
    vector<string> history; // To track product history
};

vector<Product> products; // List of products
int nextId = 1; // Counter for product IDs starting from 001

// Generate product ID like 001, 002, etc.
string generateId() {
    ostringstream ss;
    ss << setw(3) << setfill('0') << nextId++;
    return ss.str();
}

// Add a new product
void addProduct() {
    Product p;
    p.id = generateId();
    cout << "Product ID: " << p.id << endl;
    cin.ignore();
    cout << "Product Name: ";
    getline(cin, p.name);
    cout << "Selling Price: ₱";
    cin >> p.price;

    do {
        cout << "Stock Quantity: ";
        cin >> p.stock;
        if (p.stock < 0)
            cout << "Invalid. Stock can't be negative. Try again.\n";
    } while (p.stock < 0);

    ostringstream hs;
    hs << "Added - Name: " << p.name << ", Price: ₱" << p.price << ", Stock: " << p.stock;
    p.history.push_back(hs.str());

    products.push_back(p);
    cout << "Product added!\n";
}

// Update product details
void updateProduct() {
    string id;
    cout << "Enter Product ID: ";
    cin >> id;

    for (auto& p : products) {
        if (p.id == id) {
            int opt;
            cout << "1. Update Price\n2. Stock In\n3. Stock Out\nChoice: ";
            cin >> opt;

            if (opt == 1) {
                double oldPrice = p.price;
                cout << "New Price: ₱";
                cin >> p.price;
                ostringstream hs;
                hs << "Price updated from ₱" << oldPrice << " to ₱" << p.price;
                p.history.push_back(hs.str());
            } else if (opt == 2) {
                int in;
                cout << "Stock In: ";
                cin >> in;
                p.stock += in;
                ostringstream hs;
                hs << "Stock increased by " << in << ", Total stock: " << p.stock;
                p.history.push_back(hs.str());
            } else if (opt == 3) {
                if (p.stock == 0) {
                    cout << "No stock available to deduct.\n";
                    return;
                }
                int out;
                cout << "Stock Out: ";
                cin >> out;
                if (out <= p.stock) {
                    p.stock -= out;
                    ostringstream hs;
                    hs << "Stock reduced by " << out << ", Remaining stock: " << p.stock;
                    p.history.push_back(hs.str());
                    cout << "Stock updated.\n";
                } else {
                    cout << "Not enough stock.\n";
                }
            }
            return;
        }
    }
    cout << "Product not found.\n";
}

// Display all product details
void displayProducts() {
    cout << fixed << setprecision(2);
    for (auto& p : products) {
        cout << "\nID: " << p.id << ", Name: " << p.name << ", Price: ₱" << p.price << ", Stock: " << p.stock << endl;
        cout << "History:" << endl;
        for (const auto& h : p.history) {
            cout << "  - " << h << endl;
        }
    }
    cout << "\n";
}

// Main menu loop
int main() {
    int ch;
    do {
        cout << "-----[Inventory]-----";
        cout << "\n1. Add Product\n2. Update Product\n3. Display Products\n4. Exit\nChoice: ";
        cin >> ch;
        if (ch == 1) addProduct();
        else if (ch == 2) updateProduct();
        else if (ch == 3) displayProducts();
    } while (ch != 4);
    return 0;
}