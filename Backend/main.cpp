#include "./headers/json.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Create a JSON object
    nlohmann::json jsonData;

    // Read JSON data from a file
    std::ifstream inputFile("../JSON/seller.json");
    if (!inputFile) {
        std::cerr << "Could not open the file!" << std::endl;
        return 1;
    }

    try {
        // Parse the JSON data from the file
        inputFile >> jsonData;
        inputFile.close();
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "Parse error: " << e.what() << std::endl;
        return 1;
    }

    // Accessing the data
    try {
        std::string userName = "Deep";
        std::string shopName = jsonData["users"][userName]["shop_name"];
        std::string homeProduct = jsonData["users"][userName]["products"]["home"];
        auto techProducts = jsonData["users"][userName]["products"]["tech"];

        // Print the data
        std::cout << "Shop Name: " << shopName << std::endl;
        std::cout << "Home Product: " << homeProduct << std::endl;
        std::cout << "Tech Products: ";
        for (const auto& product : techProducts) {
            std::cout << product << " ";
        }
        std::cout << std::endl;

    } catch (const nlohmann::json::type_error& e) {
        std::cerr << "Type error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}