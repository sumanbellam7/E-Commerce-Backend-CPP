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

int main() {

    unordered_map <string,seller_class> seller_map;

    seller::register_user(seller_map);
    seller::save_data(seller_map);

    return 0;
}
