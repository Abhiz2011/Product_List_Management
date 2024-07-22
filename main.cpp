#include <iostream>
#include <string>

using namespace std;

class Product {
public:
    int id;
    string name;
    double price;
    int quantity;

    Product() : id(0), name(""), price(0.0), quantity(0) {}
    Product(int id, string name, double price, int quantity)
        : id(id), name(name), price(price), quantity(quantity) {}
};

class ProductList {
private:
    Product* products;
    int size;
    int capacity;
    int nextId;

    void resize() {
        capacity *= 2;
        Product* newProducts = new Product[capacity];
        for (int i = 0; i < size; ++i) {
            newProducts[i] = products[i];
        }
        delete[] products;
        products = newProducts;
    }

public:
    ProductList(int initialCapacity = 10) : size(0), capacity(initialCapacity), nextId(1) {
        products = new Product[capacity];
    }

    ~ProductList() {
        delete[] products;
    }

    void addProduct(string name, double price, int quantity) {
        if (size == capacity) {
            resize();
        }
        products[size++] = Product(nextId++, name, price, quantity);
        cout << "Product added successfully.\n";
    }

    void displayProducts() {
        if (size == 0) {
            cout << "No products available.\n";
            return;
        }

        for (int i = 0; i < size; ++i) {
            cout << "ID: " << products[i].id
                 << ", Name: " << products[i].name
                 << ", Price: $" << products[i].price
                 << ", Quantity: " << products[i].quantity << "\n";
        }
    }

    void deleteProduct(int id) {
        for (int i = 0; i < size; ++i) {
            if (products[i].id == id) {
                for (int j = i; j < size - 1; ++j) {
                    products[j] = products[j + 1];
                }
                --size;
                cout << "Product deleted successfully.\n";
                return;
            }
        }
        cout << "Product not found.\n";
    }

    Product* findProductById(int id) {
        for (int i = 0; i < size; ++i) {
            if (products[i].id == id) {
                return &products[i];
            }
        }
        return nullptr;
    }
};

class BillingSystem {
private:
    double totalBill;

public:
    BillingSystem() : totalBill(0.0) {}

    void addProductToBill(ProductList& productList, int productId, int quantity) {
        Product* product = productList.findProductById(productId);
        if (product) {
            if (product->quantity >= quantity) {
                totalBill += product->price * quantity;
                product->quantity -= quantity;
                cout << "Product added to bill.\n";
            } else {
                cout << "Insufficient product quantity.\n";
            }
        } else {
            cout << "Product not found.\n";
        }
    }

    void displayBill() {
        cout << "Total Bill: $" << totalBill << "\n";
    }
};

int main() {
    ProductList productList;
    BillingSystem billingSystem;
    int choice;

    while (true) {
        cout << "\nProduct List Management System\n";
        cout << "1. Add New Product\n";
        cout << "2. Display Products\n";
        cout << "3. Delete Product\n";
        cout << "4. Add Product to Bill\n";
        cout << "5. Display Bill\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 6) break;

        int id, quantity;
        string name;
        double price;

        switch (choice) {
            case 1:
                cout << "Enter product name: ";
                cin >> name;
                cout << "Enter product price: ";
                cin >> price;
                cout << "Enter product quantity: ";
                cin >> quantity;
                productList.addProduct(name, price, quantity);
                break;
            case 2:
                productList.displayProducts();
                break;
            case 3:
                cout << "Enter product ID to delete: ";
                cin >> id;
                productList.deleteProduct(id);
                break;
            case 4:
                cout << "Enter product ID to add to bill: ";
                cin >> id;
                cout << "Enter quantity: ";
                cin >> quantity;
                billingSystem.addProductToBill(productList, id, quantity);
                break;
            case 5:
                billingSystem.displayBill();
                break;
            default:
                cout << "Invalid choice.\n";
                break;
        }
    }

    return 0;
}
