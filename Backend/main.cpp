#include <iostream>
#include <unordered_map>
#include "buyer.hpp"
#include "seller.hpp"

using namespace std;

// Function to display the main menu
void showMenu() {
    cout << "Welcome to the E-commerce Backend!" << endl;
    cout << "1. User Registration" << endl;
    cout << "2. Seller Registration" << endl;
    cout << "3. Show All Products" << endl;
    cout << "4. Add to Favorites" << endl;
    cout << "5. Add to Cart" << endl;
    cout << "6. Show Current Products" << endl;
    cout << "7. Exit" << endl;
}

// Function to add a product to the buyer's cart
void addProductToCart(const string& buyerID, const string& productID, int quantity,
                      unordered_map<string, unordered_map<string, int>>& cart_map,
                      const unordered_map<string, seller::Product>& product_catalog) {
    // Check if the product exists in the seller's product catalog
    if (product_catalog.find(productID) != product_catalog.end()) {
        // Add or update the product quantity in the buyer's cart
        cart_map[buyerID][productID] += quantity; // Increase quantity if already in cart
        cout << "Product added to cart successfully." << endl;
    } else {
        cout << "Product not found in the catalog!" << endl;
    }
}

int main() {
    unordered_map<string, buyer::Buyer> buyer_map; // HashMap for buyers
    unordered_map<string, seller::Seller> seller_map; // HashMap for sellers
    unordered_map<string, unordered_map<string, int>> cart_map; // HashMap for buyer carts
    unordered_map<string, seller::Product> product_catalog; // Catalog of products for quick search

    // Load existing data from JSON files
    buyer::load_json_data_to_map(buyer_map);
    seller::load_json_data_to_map(seller_map);
    seller::load_product_catalog(product_catalog); // Load product catalog for lookup

    int choice;
    do {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: // User Registration
                buyer::user_register(buyer_map);
                buyer::save_data(buyer_map);
                break;
            case 2: // Seller Registration
                seller::register_user(seller_map);
                seller::save_data(seller_map);
                break;
            case 3: // Show All Products
                buyer::show_all_products();
                break;
            case 4: // Add to Favorites
                buyer::add_favourite(buyer_map);
                buyer::save_data(buyer_map);
                break;
            case 5: { // Add to Cart
                string buyerID, productID;
                int quantity;
                cout << "Enter Buyer ID: ";
                cin >> buyerID;
                cout << "Enter Product ID to add to cart: ";
                cin >> productID;
                cout << "Enter quantity: ";
                cin >> quantity;

                addProductToCart(buyerID, productID, quantity, cart_map, product_catalog);
                buyer::save_data(buyer_map); // Save cart updates if needed
                break;
            }
            case 6: // Show Current Products
                seller::show_current_products(seller_map);
                break;
            case 7: // Exit
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 7);

    return 0;
}
