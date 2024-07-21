#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "blockchain/wallet_actions/wallets.h"
#include "blockchain/transactions.h"

using namespace std;

#define RESET       "\033[0m"
#define CYAN        "\033[36m"     
#define RED         "\033[31m" 

string command, password = "yo";
bool root = false;

// WALLET COUNTER TO UNDERSTAND HOW MANY WALLETS ARE CREATED
int wallet_counter;

int main() {
    // CHECK WALLET COUNTER
    string filename = "database/wallet_counter.md";
    ifstream fin(filename);
    if (fin.is_open()) {
        fin >> wallet_counter;
        fin.close();
    } else {
        cerr << RED << "Error: " << CYAN << "Failed to open wallet counter file." << endl;
        return 1;
    }

    // MAIN COMMANDS
    while (true) {
        if (root == true) {
            cout << CYAN << "\n@blockchain" << RESET << " >> ";
        }
        else if (root == false) {
            cout << CYAN << "\n@cmd" << RESET << " >> ";
        }
        string input;
        getline(cin, input);
        cout << RESET;

        istringstream iss(input);
        string main_command, sub_command, option;
        iss >> main_command >> sub_command >> option;

        // ADMIN COMMANDS ONLY YO
        if (root == true) {
            if (main_command == "chain") {
                if (sub_command == "wallet") {
                    if (option == "-n") {
                        new_wallet_func(wallet_counter);
                        wallet_counter++;
                    } 
                    else if (option == "-i") {
                        check_wallet_info_func();
                    } 
                    else {
                        cerr << RED << "Error: " << CYAN << "Invalid wallet option." << endl;
                    }
                } 
                else if (sub_command == "transaction") {
                    if (option == "-s") {
                        send_crypto_func();
                    } else if (option == "-b") {
                        // Handle transaction book command later
                    } else {
                        cerr << RED << "Error: " << CYAN << "Invalid transaction option." << endl;
                    }
                } 
            } 
        }

        // FOR ALL USERS COMMANDS
        if (main_command == "sys") {
            if (sub_command == "out") {
                ofstream outFile(filename);
                if (!outFile) {
                    cerr << RED << "Error: " << CYAN << "Failed to open wallet counter file for writing." << endl;
                    break; 
                }
                outFile << wallet_counter << endl;
                break;
            } 
            else if (sub_command == "help") {
                cout << "All available commands: \n\n" <<
                CYAN << "chain wallet -n " << RESET << "- create new wallet on blockchain.\n" << 
                CYAN << "chain wallet -i " << RESET << "- check wallet info.\n" << 
                CYAN << "chain transaction -s " << RESET << "- transfer crypto to another wallet\n" <<  
                CYAN << "sys root -t" << RESET << " - root rules anable.\n" <<
                CYAN << "sys root -f" << RESET << " - root rules disable.\n" <<
                CYAN << "sys help" << RESET << " - show all available commands.\n" <<
                CYAN << "sys calc" << RESET << " - calculate something.\n" <<
                CYAN << "sys out" << RESET << " - leave the command line.\n";
            }
            else if (sub_command == "calc") {
                string act;
                int fst, snd, result;

                cout << CYAN << "Write a first number: \n >> ";
                cin >> fst;
                cout << CYAN << "Write an action: \n >> ";
                cin >> act;
                cout << CYAN << "Write a second number: \n >> ";
                cin >> snd;

                if (act == "+") {
                    result = fst + snd;
                    cout << RESET << "Result from " CYAN << fst << " " << act << " " << snd << RESET << " is " << CYAN << result << RESET;
                } else if (act == "-") {
                    result = fst - snd;
                    cout << RESET << "Result from " CYAN << fst << " " << act << " " << snd << RESET << " is " << CYAN << result << RESET;
                } else if (act == "*") {
                    result = fst * snd;
                    cout << RESET << "Result from " CYAN << fst << " " << act << " " << snd << RESET << " is " << CYAN << result << RESET;
                } else if (act == "/") {
                    if (snd <= 0) {
                        cout << RED << "Error: " << CYAN << "You can't divide by 0 or less.";
                    } else {
                        result = fst / snd;
                        cout << RESET << "Result from " CYAN << fst << " " << act << " " << snd << RESET << " is " << CYAN << result << RESET;
                    }
                }
            } 
            else if (sub_command == "root") {
                if (option == "-t") {
                    string pswd;
            
                    cout << "\nWrite the password: \n >> ";
                    cin >> pswd;

                    if (pswd == password) {
                        cout << "Root rules activated " << CYAN << "successfully!\n";
                        root = true;
                    }
                } 
                else if (option == "-f") {
                    cout << "\nRoot rules was succesfully put in to" << RED << " false " << RESET << "state.\n";
                    root = false;
                }
            }
            else {
                cerr << RED << "Error: " << RESET << "Invalid command." << endl;
            }
        }
    }
    return 0; 
}
