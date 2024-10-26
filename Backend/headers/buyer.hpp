#ifndef BUYER_H
#define BUYER_H

#include <iostream>
#include <vector>
#include <string>
#include "json.hpp"
#include <fstream>
#include <unordered_map>

using namespace std;
typedef nlohmann::json json;

namespace buyer {

class Address {

private:
    string home_name;
    string street;
    string city;
    string state;
    string zip;

public:
    Address() {}

    Address(string street, string city, string state, string zip) {
        this->street = street;
        this->city = city;
        this->state = state;
        this->zip = zip;
    }

    // setters
    void set_street(string street) { this->street = street; }
    void set_home_name(string home) { this->home_name = home; }
    void set_city(string city) { this->city = city; }
    void set_state(string state) { this->state = state; }
    void set_zip(string zip) { this->zip = zip; }

    // getters
    string get_home_name() const { return home_name; }
    string get_street() const { return street; }
    string get_city() const { return city; }
    string get_state() const { return state; }
    string get_zip() const { return zip; }
    string get_address() const {
        return home_name + ", " + street + ", " + city + ", " + state + ", " + zip + ".";
    }
};

class Buyer {

private:
    string name;
    string email;
    string phone;

public:
    Address address;
    Buyer() {}

    Buyer(string name, string email, string phone, Address addr) {
        this->name = name;
        this->email = email;
        this->phone = phone;
        this->address = addr;
    }

    void print_buyer_info() {
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
        cout << "Address: " << address.get_address() << endl;
    }

    // setters
    void set_name(string name) { this->name = name; }
    void set_email(string email) { this->email = email; }
    void set_phone(string phone) { this->phone = phone; }
    void set_addr(Address addr) { this->address = addr; }

    // getters
    string get_name() const { return name; }
    string get_email() const { return email; }
    string get_phone() const { return phone; }
    Address get_address() const { return address; }
};

inline void register_buyer(unordered_map<string, Buyer> &buyer_map) {
    Address address;
    Buyer buyer;

    string temp;
    string name;
    cout << "Enter your name: ";
    cin >> name;
    buyer.set_name(name);

    cout << "Enter your email: ";
    cin >> temp;
    buyer.set_email(temp);

    cout << "Enter your phone number: ";
    cin >> temp;
    buyer.set_phone(temp);

    cout << "Address: " << endl;
    cout << "Enter home name: ";
    cin >> temp;
    address.set_home_name(temp);

    cout << "Enter street address: ";
    cin >> temp;
    address.set_street(temp);

    cout << "Enter city name: ";
    cin >> temp;
    address.set_city(temp);

    cout << "Enter state name: ";
    cin >> temp;
    address.set_state(temp);

    cout << "Enter zipcode: ";
    cin >> temp;
    address.set_zip(temp);

    // add address object to the buyer class
    buyer.set_addr(address);

    // add object to the map
    buyer_map[name] = buyer;
}

inline void delete_buyer(unordered_map<string, Buyer> &buyer_map, const string &name) {
    buyer_map.erase(name);
}

inline void load_json_data_to_map(unordered_map<string, Buyer> &buyer_map) {
    json j;
    ifstream infile("../JSON/buyer.json");
    if (infile.is_open()) {
        try {
            infile >> j;
        } catch (...) {
            cerr << "Error reading existing JSON data" << endl;
        }
        infile.close();
    } else {
        cerr << "Error opening buyer.json file for loading data to map." << endl;
        return;
    }

    for (auto &[name, buyer_json] : j.items()) {
        try {
            // get address from object
            json addr_json = buyer_json["address"];
            Address address(
                addr_json["street"].get<std::string>(),
                addr_json["city"].get<std::string>(),
                addr_json["state"].get<std::string>(),
                addr_json["zip"].get<std::string>()
            );
            address.set_home_name(addr_json["home_name"].get<std::string>());

            // get all details
            Buyer buyer(
                buyer_json["name"].get<std::string>(),
                buyer_json["email"].get<std::string>(),
                buyer_json["phone"].get<std::string>(),
                address
            );

            // inserting the  buyer into the map using their name as the key
            buyer_map[name] = buyer;
        } catch (...) {
            cerr << "Error parsing buyer data in loading function" << name << endl;
        }
    }
}

inline void save_data(unordered_map<string, Buyer> &buyer_map) {
    json j;

    for (const auto &[name, buyer] : buyer_map) {
        // Create a JSON object for the Address
        json address_json = {
            {"home_name", buyer.address.get_home_name()},
            {"street", buyer.address.get_street()},
            {"city", buyer.address.get_city()},
            {"state", buyer.address.get_state()},
            {"zip", buyer.address.get_zip()}
        };

        // Creating  a JSON object for the Buyer
        json buyer_json = {
            {"name", buyer.get_name()},
            {"email", buyer.get_email()},
            {"phone", buyer.get_phone()},
            {"address", address_json}
        };

        // Adding the  buyer_json to the main JSON object, using name as key
        j[name] = buyer_json;
    }

    // Write JSON to file
    ofstream file("../JSON/buyer.json");
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
    } else {
        cout << "Error saving data in buyer.json file" << endl;
    }
}

}

#endif
