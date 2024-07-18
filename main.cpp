// ADD ALL THINGS WE NEED
#include <iostream>
#include <string>
#include "blockchain/wallet_actions/wallets.h"
#include <fstream>
#include "blockchain/transactions.h"

// USING NAMESPACE STD TO SAFE PLACE AND GET CODE CLEARLY
using namespace std;

// ADD COLORS FOR MORE ATTRACTIVENESS
#define RESET   "\033[0m"
#define RED     "\033[31m"   
#define GREEN   "\033[32m"     
#define YELLOW  "\033[33m"  
#define BLUE    "\033[34m"     
#define MAGENTA "\033[35m"

string command;

// WALLET COUNTER TO UNDERSTANT HOW MANY WALLETS IS CREATED
int wallet_counter;

int main() {
    // CHECK WALLET COUNTER
    string filename = "database/wallet_counter.md";
    ifstream fin(filename);
    if (fin.is_open()) {
        fin >> wallet_counter;
        fin.close();
    } else {
        cerr << RED << "Error: " << RESET << "Failed to open wallet counter file." << endl;
        return 1;
    }

    // MAIN COMMANDS
    while (true) {
        cout << RED << "\n@chain" << RESET << " >> " << YELLOW;
        cin >> command;
        cout << RESET;
        
        // WALLET MANAGMENT
        if (command == "--wallet_new") {
            new_wallet_func(wallet_counter);
            wallet_counter++;
        }        
        else if (command == "--wallet_info") {
            check_wallet_info_func();
        }
        
        // TRANSACTIONS MANAGMENT
        else if (command == "--transaction") {
            send_crypto_func();
        }
        else if (command == "--transaction_book") {
            // LATER
        }

        // OTHER
        else if (command == "--out") {
            ofstream outFile(filename);
            if (!outFile) {
                cerr << RED << "Error: " << RESET << "Failed to open wallet counter file for writing." << endl;
                break; // или return 1; в зависимости от вашей логики обработки ошибок
            }
            outFile << wallet_counter << endl;
            break;
        }     
        else if (command == "--help") {
            cout << "All available commands: \n\n" <<
            YELLOW << "--wallet_new " << RESET << "- create new wallet on blockchain.\n" << 
            YELLOW << "--wallet_info " << RESET << "- check wallet info.\n" << 
            YELLOW << "--transaction " << RESET << "-transfer crypto to another wallet\n" <<  
            YELLOW << "--help" << RESET << " - show all available commands.\n" <<
            YELLOW << "--out" << RESET << " - leave the blockchain.\n" <<
            YELLOW << "--calc" << RESET << " - calculate something.\n";
        }
        else if (command == "--calc") {
            string act;
            int fst, snd, result;

            cout << BLUE << "Write an first number: \n" << YELLOW;
            cin >> fst;

            cout << BLUE << "Write an action: \n" << YELLOW;
            cin >> act;

            cout << BLUE << "Write an second number: \n" << YELLOW;
            cin >> snd;

            if (act == "+") {
                result = fst + snd;
                cout << RESET << "Result from " YELLOW << fst << " " << act << " " << snd << RESET << " is " << BLUE << result << RESET;
            }
            else if (act == "-") {
                result = fst - snd;
                cout << RESET << "Result from " YELLOW << fst << " " << act << " " << snd << RESET << " is " << BLUE << result << RESET;
            }
            else if (act == "*") {
                result = fst * snd;
                cout << RESET << "Result from " YELLOW << fst << " " << act << " " << snd << RESET << " is " << BLUE << result << RESET;
            }
            else if (act == "/") {
                if (snd <= 0) {
                    cout << RED << "You can't divide by 0 or less.";
                }
                else {
                    result = fst / snd;
                    cout << RESET << "Result from " YELLOW << fst << " " << act << " " << snd << RESET << " is " << BLUE << result << RESET;
                }
            }
        }
    }
    return 0; 
}