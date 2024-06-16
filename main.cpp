#include <iostream>
#include <string>

using namespace std;

string command;

int main() {
    while (true) {
        cin >> command;
        
        if (command == "wallet -n") {
            // NEW WALLET FUNC
        }
        else if (command == "wallet -d") {
            // DELETE WALLET FUNC
        }
        else if (command == "wallet -i") {
            // WALLET INFO FUNCS
        }
        else if (command == "wallet -s") {
            // SEND COINS FUNC
        }
        else if (command == "wallet -a") {
            // SHOW USER ADRESS
        }
        else if (command == "wallet -o") {
            // ALL USER WALLETS
        }

        

        else if (command == "out") {
            break;
        }
    }

    return 0; 
}