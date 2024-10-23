#ifndef SELLER_H
#define SELLER_H

#include <iostream>
#include <vector>
#include <string>
#include "json.hpp"
#include <fstream>
#include <unordered_map>

using namespace std;
typedef nlohmann::json json;

namespace seller {

class Address {

private:

    string shop_name;
    string street;
    string city;
    string state;
    string zip;

public:

    Address(){}

    Address(string street,string city,string state,string zip){
        this->street = street;
        this->city = city;
        this->state = state;
        this->zip = zip;
    }

    // setters
    void set_street(string street){ this->street = street; }
    void set_shop_name(string shop){ this->shop_name = shop; }
    void set_city(string city){ this->city = city; }
    void set_state(string state){ this->state = state; }
    void set_zip(string zip){ this->zip = zip; }

    // getters
    string get_shop_name() const { return shop_name; }
    string get_street() const { return street; }
    string get_city() const { return city; }
    string get_state() const { return state; }
    string get_zip() const { return zip; }
    string get_address() const {
        string addr =shop_name + ", " + street + ", " + city + ", " + state + ", " + zip + ".";
        return addr; 
    }

};

//for the seller info
class Seller {

private:

    string name;
    string email;
    string phone;

public:

    Address address;
    Seller(){}

    Seller(string name,string email,string phone,Address addr){
        this->name = name;
        this->email = email;
        this->phone = phone;
        this->address = addr;
    }

    void print_seller_info(){
        cout << "name : " << name << endl;
        cout << "email : " << email << endl;
        cout << "phone : " << phone << endl;
        cout << "address : " << address.get_address() << endl;

    }

    // setters
    void set_name(string name) { this->name = name; }
    void set_email(string email){ this->email = email; }
    void set_phone(string phone){ this->phone = phone; }
    void set_addr(Address addr){ this->address = addr; }

    //getters
    string get_name() const { return name; }
    string get_email() const { return email; }
    string get_phone() const { return phone; }
    Address get_address() const { return address; }

};


inline void register_user(unordered_map<string,Seller> &seller_map){

    Address address;
    Seller seller;

    string temp;
    string name;
    cout << "Enter your name : " ;
    cin >> name;
    seller.set_name(name);

    cout << "Enter your email : ";
    cin >> temp;
    seller.set_email(temp);

    cout << "Enter your phone number : ";
    cin >> temp;
    seller.set_phone(temp);

    cout << "Address : " << endl;
    cout << "Enter shop name : ";
    cin >> temp;
    address.set_shop_name(temp);

    cout << "Enter street address : ";
    cin >> temp;
    address.set_street(temp);

    cout << "Enter city name : ";
    cin >> temp;
    address.set_city(temp);

    cout << "Enter state name : ";
    cin >> temp;
    address.set_state(temp);

    cout << "Enter zipcode : ";
    cin >> temp;
    address.set_zip(temp);

    // add address object to the seller class
    seller.set_addr(address);

    // add object to the map
    seller_map[name] = seller;

}

inline void delete_user(unordered_map<string,Seller> &seller_map,const string &name){
    seller_map.erase(name);
}

inline void load_json_data_to_map(unordered_map<string,Seller> &seller_map){
    json j;
    ifstream infile("../JSON/seller.json");
    if(infile.is_open()){
        try{
            infile >> j;
        }
        catch(...){
            cerr << "Error reading existing JSON data" << endl;
        }
        infile.close();
    }
    else{
        cerr << "Error opening seller.json file for loading data to map.";
        return;
    }

     for (auto& [name, seller_json] : j.items()) {
        try {
            // get address from object
            json addr_json = seller_json["address"];
            Address address(
                addr_json["street"].get<std::string>(),
                addr_json["city"].get<std::string>(),
                addr_json["state"].get<std::string>(),
                addr_json["zip"].get<std::string>()
            );
            address.set_shop_name(addr_json["shop_name"].get<std::string>());

            // get all details
            Seller seller(
                seller_json["name"].get<std::string>(),
                seller_json["email"].get<std::string>(),
                seller_json["phone"].get<std::string>(),
                address
            );

            // insert seller into the map using their name as the key
            seller_map[name] = seller;
        } catch (...) {
            std::cerr << "Error parsing seller data in loading function" << name << std::endl;
        }
    }
}

inline void save_data(unordered_map<string, Seller> &seller_map) {
    
    json j;

    for (const auto& [name, seller] : seller_map) {

        // Create a JSON object for the Address
       json address_json = {
            {"shop_name", seller.address.get_shop_name()},
            {"street", seller.address.get_street()},
            {"city", seller.address.get_city()},
            {"state", seller.address.get_state()},
            {"zip", seller.address.get_zip()}
        };

        // Create a JSON object for the Seller
        json seller_json = {
            {"name", seller.get_name()},
            {"email", seller.get_email()},
            {"phone", seller.get_phone()},
            {"address", address_json}
        };

        // Add seller_json to the main JSON object, using name as key
        j[name] = seller_json;
    }

    // Write JSON to file
    std::ofstream file("../JSON/seller.json");
    if (file.is_open()) {
        file << j.dump(4);  
        file.close();
    } else {
        cout << "Error saving data in seller.json file" << endl;
    }
}

}

#endif 
