#include <iostream>
#include <fstream>
#include <unordered_map>
#include "./headers/json.hpp"
#include "./headers/seller.hpp"
#include "./headers/buyer.hpp"

using namespace std;

// seller typedefs
using seller_class = seller::Seller ;
using seller_addr_class = seller::Address ;
//buyer  typedefs
using buyer_class = buyer::Seller ;
using buyer_addr_class = buyer::Address 

int main() {

    unordered_map <string,seller_class> seller_map;

    seller::register_user(seller_map);
    seller::save_data(seller_map);

   //for the registration of the buyer
    buyer::register_user(buyer_map);
    buyer::save_data(buyer_map);

    return 0;
}
