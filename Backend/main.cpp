#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map >
#include "./headers/seller.hpp"
#include "./headers/buyer.hpp"

using namespace std;


// seller typedefs
using seller_class = seller::Seller ;
using seller_addr_class = seller::Address ;
//buyer  typedefs
using buyer_class = buyer::Buyer ;
using buyer_addr_class = buyer::Address;

// all global declaration
unordered_map<string,buyer::Buyer> buyer_map;
unordered_map<string,seller::Seller> seller_map;

void display_favourite_items(){
  
}

int main() {
    char choice;
    char sec_choice;
    while(choice != 'q'){

    // Main Choice
    cout << "-----------------------------" << endl;
    cout << "1 . Buyer " << endl;
    cout << "2 . Seller " << endl;
    cout << "Enter your choice : " << endl;
    cin >> choice;
    if(choice == '1'){
    // If user is Buyer
    cout << "-----------BUYER------------------" << endl;
    cout << "1 . Register" << endl;
    cout << "2 . Delete User " << endl;
    cout << "3 . View Cart " << endl;
    cout << "4 . View Favourites " << endl;
    cout << "5 . View User info " << endl;
    cout << "6 . Add product to cart  " << endl;
    cout << "7 . Add product to favourites" << endl;
    cout << "Enter your choice : " << endl;
    cin >> sec_choice;  

    switch (sec_choice) {

      case '1':
        buyer::register_buyer(buyer_map);

      case '2':
        cout << "Enter your username : ";
        cin >> sec_choice;
        buyer::delete_buyer(buyer_map,username);
        break;

      case '3':
        
        break;

      case '4':

        break;

      case '5':
      
        break;

      default: 
        cout << "Enter valid choice!!!" ;
        break;
    }
    }
    else if(choice == '2'){
    // If user is Seller
    cout << "-----------BUYER------------------" << endl;
    cout << "1 . Register" << endl;
    cout << "2 . Delete User " << endl;
    cout << "3 . View Cart " << endl;
    cout << "4 . View Favourites " << endl;
    cout << "5 . View user info " << endl;
    cout << "6.  Add product " << endl;

    cout << "Enter your choice : " << endl;
    cin >> sec_choice;

    switch (sec_choice) {
      
      case '1':
          seller::register_user(seller_map);

      case '2':
          cout << "Enter your username : ";
          cin >> sec_choice;

      case '3':
          
          break;

      case '4':

          break;

      case '5':

          break;

      case '6':

        break;

      case 'q':
        break;

      default:
          cout << "Enter valid choice!!!" << ednl;
          break;
    }

    }
    else if(choice == 'q'){
    // quit the programme 
    break;
    }
    else{
    // Invalid choice entered
    cout << "Please enter valid choice!!!" << endl;
    }
  }
    

    return 0;
}
