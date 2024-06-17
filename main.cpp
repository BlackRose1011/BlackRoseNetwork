#include <iostream>
#include <string>
#include "blockchain/wallet_actions/wallets.h"

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"   
#define GREEN   "\033[32m"     
#define YELLOW  "\033[33m"  
#define BLUE    "\033[34m"     
#define MAGENTA "\033[35m"

string command;

int wallet_counter = 1;

int main() {
    while (true) {
        cout << RED << "\n@chain" << RESET << " >> " << YELLOW;
        cin >> command;
        cout << RESET ;
        
        if (command == "--wallet_new") {
            new_wallet_func(wallet_counter);
            wallet_counter++;
        }

        else if (command == "--out") {
            break;
        }
        
        else if (command == "--help") {
            cout << "All avaluible commands: \n\n" <<
            YELLOW << "--wallet_new " << RESET << "- create new wallet on blockchain.\n" << 
            YELLOW << "--help" << RESET << " - show all avaluible commands.\n"
            YELLOW << "--out" << RESET" - leave the blockchain.\n";
        }
    }
    return 0; 
}