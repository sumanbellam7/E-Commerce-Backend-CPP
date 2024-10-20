#ifndef SELLER_H
#define SELLER_H

#include <iostream>
#include <vector>
#include <string>
#include "json.hpp"
#include <fstream>
#include <unordered_map>

using namespace std;

namespace seller {
//can delete this later 
//there is address included in the seller info so i added it
struct Address {
        string street;
        string city;
        string state;
        string zip;
    };
//for the seller info
struct SellerInfo {
         string seller_id;
        string name;
        string email;
        string phone;
        Address address;
    };
//maping to store sellers info 
 unordered_map<string, SellerInfo> seller_map;\

    inline void register_user(const string& name,const string& shopname){
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to open file: " << filename << endl;
            return;
    }

json sellers_json;
        file >> sellers_json;
        file.close();

for (const auto& seller : sellers_json["sellers"]) {
            SellerInfo info;
            info.seller_id = seller["seller_id"].get<string>();
            info.name = seller["name"].get<string>();
            info.email = seller["email"].get<string>();
            info.phone = seller["phone"].get<string>();


            info.address.street = seller["address"]["street"].get<string>();
            info.address.city = seller["address"]["city"].get<string>();
            info.address.state = seller["address"]["state"].get<string>();
            info.address.zip = seller["address"]["zip"].get<string>();
seller_map[info.seller_id] = info;
}

        cout << "Loaded " << seller_map.size() << " sellers from " << filename << endl;
    }
 inline void register_user(const string& seller_id, const string& name, const string& email, const string& phone, const Address& address) {
        if (seller_map.find(seller_id) != seller_map.end()) {
            cout << "Seller with ID " << seller_id << " is already registered." << endl;
            return;
        }

        SellerInfo info = {seller_id, name, email, phone, address};
        seller_map[seller_id] = info;
        cout << "Registered seller: " << name << endl;
    }
inline void display_sellers() {
        for (const auto& pair : seller_map) {
            const SellerInfo& info = pair.second;
            cout << "Seller ID: " << info.seller_id << ", Name: " << info.name
                 << ", Email: " << info.email << ", Phone: " << info.phone
                 << ", Address: " << info.address.street << ", " << info.address.city
                 << ", " << info.address.state << ", " << info.address.zip << endl;
        }
    }
}


#endif 
