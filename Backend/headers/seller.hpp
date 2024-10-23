#ifndef SELLER_H
#define SELLER_H

#include <iostream>
#include <vector>
#include <string>
#include "json.hpp"
#include <fstream>
#include <unordered_map>

using namespace std;

//can delete this later
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

    void set_street(string street){
        this->street = street;
    }

    void set_shop_name(string shop){
        this->shop_name = shop;
    }

    void set_city(string city){
        this->city = city;
    }

    void set_state(string state){
        this->state = state;
    }

    void set_zip(string zip){
        this->zip = zip;
    }

    string get_address(){
        string addr = street + ", " + city + ", " + state + ", " + zip + ".";
        return addr; 
    }

};

//for the seller info
class Seller {

private:

    string name;
    string email;
    string phone;
    Address address;

public:

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

    void set_name(string name){
        this->name = name;
    }

    void set_email(string email){
        this->email = email;
    }

    void set_phone(string phone){
        this->phone = phone;
    }

    void set_addr(Address addr){
        this->address = addr;
    }
};

namespace seller {

//maping to store sellers info 
unordered_map<string, Seller> seller_map;
// name -> Seller object 

inline void register_user(){

    Address address;
    Seller seller;

    string temp;
    cout << "Enter your name : " ;
    cin >> temp;
    seller.set_name(temp);

    cout << "Enter your email : ";
    cin >> temp;
    seller.set_email(temp);

    cout << "Enter your phone number : ";
    cin >> temp;
    seller.set_phone(temp);

    cout << "Address : " << endl;
    cout << "Enter shop name : ";
    cin >> temp;
    address.set_shop_name()


}

}

#endif 
