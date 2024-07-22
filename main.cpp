#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <thread>
#include "blockchain/wallet_actions/wallets.h"
#include "blockchain/transactions.h"

using namespace std;

#define RESET       "\033[0m"
#define CYAN        "\033[36m"     
#define RED         "\033[31m" 

string command, password = "yo", input;
bool root = false;
bool tru = tru;

// WALLET COUNTER TO UNDERSTAND HOW MANY WALLETS ARE CREATED
int wallet_counter;

int calculate(const string &expression) {
    vector<int> numbers;
    vector<char> operations;

    stringstream ss(expression);
    int num;
    char op;

    while (ss >> num) {
        numbers.push_back(num);
        if (ss >> op) {
            operations.push_back(op);
        }
    }

    // PERFORM TO MULTIPLICATION AND DIVISION FIRST
    for (size_t i = 0; i < operations.size(); ++i) {
        if (operations[i] == '*' || operations[i] == '/') {
            int left = numbers[i];
            int right = numbers[i + 1];
            int result = 0;
            if (operations[i] == '*') {
                result = left * right;
            } else {
                if (right == 0) {
                    cout << "Error: You can't divide by 0." << endl;
                    return 0;
                }
                result = left / right;
            }
            numbers[i] = result;
            numbers.erase(numbers.begin() + i + 1);
            operations.erase(operations.begin() + i);
            --i;
        }
    }

    // PERFORD ADDITION AND SUBTRACTION
    int result = numbers[0];
    for (size_t i = 0; i < operations.size(); ++i) {
        if (operations[i] == '+') {
            result += numbers[i + 1];
        } else if (operations[i] == '-') {
            result -= numbers[i + 1];
        }
    }

    return result;
}

void showprogress(int duration) {
    const int totalSteps = 100;
    const int interval = duration * 1000 / totalSteps;

    for (int i = 1; i <= totalSteps; ++i) {
        string progressBar = string(i / 2, '#') + string(50 - i / 2, ' ');
        cout << "\r" << progressBar << " " << i << "%" << flush;
        this_thread::sleep_for(chrono::milliseconds(interval));
    }

    cout << "\r" << string(50, '#') << " 100%" << endl;
}

int main() {
    // JUST TO MINIMIZE SPACE FOR CODERS
    string filename = "database/wallet_counter.md";
    // CHECK WALLET COUNTER
    ifstream fin(filename);
    if (fin.is_open()) {
        fin >> wallet_counter;
        fin.close();
    } 
    else {
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
                        int duration = 5;
                        showprogress(duration);

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
                CYAN << "sys root -t" << RESET << " - root rules anable.\n" <<
                CYAN << "sys root -f" << RESET << " - root rules disable.\n" <<
                CYAN << "sys timer" << RESET << " - set up the timer;\n" <<
                CYAN << "sys clear" << RESET << " - clear the screen.\n" <<
                CYAN << "sys help" << RESET << " - show all available commands.\n" <<
                CYAN << "sys calc" << RESET << " - calculate something.\n" <<
                CYAN << "sys out" << RESET << " - leave the command line.\n";

                if (root == true) {
                    cout << "\nAll avaluible root commands: \n\n"
                    CYAN << "chain wallet -n " << RESET << "- create new wallet on blockchain.\n" << 
                    CYAN << "chain wallet -i " << RESET << "- check wallet info.\n" << 
                    CYAN << "chain transaction -s " << RESET << "- transfer crypto to another wallet\n";
                }
            }
            else if (sub_command == "calc") {
                string expression;
                cout << "Enter an expression: \n >> ";
                cin >> expression;

                int result = calculate(expression);
                cout << "Result: " << CYAN << result << RESET << endl;
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
            else if (sub_command == "clear") {
                cout << "\033[2J\033[1;1H";
            }
            else if (sub_command == "timer") {
                int seconds;
                cout << "Write the time what you want to set up the timer: \n >> ";
                cin >> seconds;
                cout << "Timer set for " << seconds << CYAN << " seconds" << RESET << ".\n";
                this_thread::sleep_for(chrono::seconds(seconds));
                cout << CYAN << "Time's up!\n" << RESET;
            }
            else {
                cerr << RED << "Error: " << RESET << "Invalid command." << endl;
            }
        }

        // FILE AND FOLDERS MANAGMENT FUNCTIONS
        if (main_command == "file") {
            if (sub_command == "create") {

            }
            else if (sub_command == "open") {

            }
            else if (sub_command == "delete") {

            }
            else if (sub_command == "write") {

            }
            else if (sub_command == "rewrite") {

            }
            else if (sub_command == "open") {

            }
            else if (sub_command == "close") {

            }
            else if (sub_command == "copy") {

            }
            else if (sub_command == "replace") {

            }
            else if (sub_command == "archive") {

            }
            else if (sub_command == "unpack") {

            }
            
            // REPOSITORY MANAGMENT FUNCTIONS
            else if (sub_command == "folder") {
                if (option == "-c") { // create

                }
                else if (option == "-d") { // delete

                }
                else if (option == "-r") { // rename

                }
                else if (option == "-p") { // change place

                }
            }
        }
    }
    return 0; 
}
