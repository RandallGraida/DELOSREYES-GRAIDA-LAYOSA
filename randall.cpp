#include <iostream>
#include <string>
#include <vector>
#include <limits>   

// Holds the product's ID, name, current price, current stock, and full history of the stock price
struct Product {
    std::string id;                   
    std::string name;                  
    double currentPrice = 0.0;         
    int currentStock = 0;           

    // History logs of the stocks
    std::vector<double> priceHistory;  
    std::vector<int> stockHistory;  
};

// Encapsulates the product catalog and all operations on it 
// I used class to avoid namin conflicts rather than use global variables
class StockMarket {
public:
    // User input
    void run() {
        bool keepRunning = true;
        while (keepRunning) {
            showMainMenu();
            int choice = getMenuChoice();
            switch (choice) {
                case 1: addNewProduct();break;
                case 2: updateProductPrice();break;
                case 3: updateProductStockIn();break;
                case 4: updateProductStockOut();break;
                case 5: displaySingleProduct();break;
                case 6: displayAllProducts();break;
                case 7: keepRunning = false;break;
                default:
                    std::cout << "Invalid selection. Please try again.\n\n";
            }
        }
        std::cout << "Exiting program. Goodbye!\n";
    }

private:
    std::vector<Product> catalog_;

    // Display the main menu
    void showMainMenu() const {
        std::cout << "Group 24 Management System\n"
                  << "1. Add New Product\n"
                  << "2. Update Product Price\n"
                  << "3. Update Product Stock (Stock In)\n"
                  << "4. Update Product Stock (Stock Out)\n"
                  << "5. Display Product Details\n"
                  << "6. Display All Products & Histories\n"
                  << "7. Exit\n"
                  << "Select an option (1-7): ";
    }

    // Error handler
    int getMenuChoice() const {
        int choice;
        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid number: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return choice;
    }

    // Nonempty string
    std::string promptForString(const std::string &prompt) const {
        std::string input;
        do {
            std::cout << prompt;
            std::getline(std::cin, input);
        } while (input.empty());
        return input;
    }

    // Positive double
    double promptForDouble(const std::string &prompt) const {
        double value;
        std::cout << prompt;
        while (!(std::cin >> value) || value < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a non-negative number: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }

    // Non-negative integer
    int promptForInt(const std::string &prompt) const {
        int value;
        std::cout << prompt;
        while (!(std::cin >> value) || value < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a non-negative integer: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }

    // Find a product by ID 
    Product* findProductById(const std::string &id) {
        for (auto &prod : catalog_) {
            if (prod.id == id) {
                return &prod;
            }
        }
        return nullptr;
    }

    // Add new product
    void addNewProduct() {
        std::cout << "\n-- Add New Product --\n";
        std::string id = promptForString("Enter Product ID (e.g. 001): ");
        // Check uniqueness
        if (findProductById(id) != nullptr) {
            std::cout << "Error: Product ID already exists.\n\n";
            return;
        }
        Product newProd;
        newProd.id = id;
        newProd.name = promptForString("Enter Product Name: ");
        newProd.currentPrice = promptForDouble("Enter Selling Price: ");
        newProd.currentStock = promptForInt("Enter Initial Stock Quantity: ");

        // Record initial history
        newProd.priceHistory.push_back(newProd.currentPrice);
        newProd.stockHistory.push_back(newProd.currentStock);

        catalog_.push_back(newProd);
        std::cout << "Product added successfully.\n\n";
    }

    // Update product price
    void updateProductPrice() {
        std::cout << "\n-- Update Product Price --\n";
        std::string id = promptForString("Enter Product ID: ");
        Product* prod = findProductById(id);
        if (!prod) {
            std::cout << "Error: No product with that ID.\n\n";
            return;
        }
        double newPrice = promptForDouble("Enter New Price: ");
        prod->currentPrice = newPrice;
        prod->priceHistory.push_back(newPrice);
        std::cout << "Price updated.\n\n";
    }

    // Update stock in
    void updateProductStockIn() {
        std::cout << "\n-- Stock In (Add Quantity) --\n";
        std::string id = promptForString("Enter Product ID: ");
        Product* prod = findProductById(id);
        if (!prod) {
            std::cout << "Error: No product with that ID.\n\n";
            return;
        }
        int qtyIn = promptForInt("Enter Quantity to Add: ");
        prod->currentStock += qtyIn;
        prod->stockHistory.push_back(prod->currentStock);
        std::cout << "Stock increased.\n\n";
    }

    // Update stock out
    void updateProductStockOut() {
        std::cout << "\n-- Stock Out (Remove Quantity) --\n";
        std::string id = promptForString("Enter Product ID: ");
        Product* prod = findProductById(id);
        if (!prod) {
            std::cout << "Error: No product with that ID.\n\n";
            return;
        }
        int qtyOut = promptForInt("Enter Quantity to Remove: ");
        if (qtyOut > prod->currentStock) {
            std::cout << "Error: Not enough stock to remove.\n\n";
            return;
        }
        prod->currentStock -= qtyOut;
        prod->stockHistory.push_back(prod->currentStock);
        std::cout << "Stock decreased.\n\n";
    }

    // Display one product’s details + history
    void displaySingleProduct() const {
        std::cout << "\n-- Display Product Details --\n";
        std::string id = promptForString("Enter Product ID: ");
        const Product* prod = nullptr;
        for (const auto &p : catalog_) {
            if (p.id == id) {
                prod = &p;
                break;
            }
        }
        if (!prod) {
            std::cout << "Error: No product with that ID.\n\n";
            return;
        }
        printProductDetails(*prod);
    }

    // Display all products + histories
    void displayAllProducts() const {
        std::cout << "\n-- All Products & Histories --\n";
        if (catalog_.empty()) {
            std::cout << "No products in catalog.\n\n";
            return;
        }
        for (const auto &prod : catalog_) {
            printProductDetails(prod);
            std::cout << "\n";
        }
    }

    // Print a product’s data and history
    void printProductDetails(const Product &prod) const {
        std::cout << "Product ID   : " << prod.id << "\n"
                  << "Name         : " << prod.name << "\n"
                  << "Current Price: $" << prod.currentPrice << "\n"
                  << "Current Stock: "   << prod.currentStock << "\n";

        std::cout << "Price History: ";
        for (double p : prod.priceHistory) {
            std::cout << p << " ";
        }
        std::cout << "\nStock History: ";
        for (int s : prod.stockHistory) {
            std::cout << s << " ";
        }
        std::cout << "\n\n";
    }
};

// int main to run the class
int main() {
    std::cout << "Welcome to the Inventory Management System\n\n";
    StockMarket app;
    app.run();
    return 0;
}