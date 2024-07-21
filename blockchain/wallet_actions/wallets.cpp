// INCLUDE ALL THING WHAT WE NEED
#include "wallets.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "SHA256/sha256.h"

// COLORS
#define RESET       "\033[0m"
#define CYAN        "\033[36m"     
#define RED         "\033[31m" 

// USING NAMESPACE STD TO SAFE PLACE AND GET CODE CLEARLY
using namespace std;

// LIKE SHA 256 RANDOM STRING GENERATION
string generate_random_string(int length) {
    string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string random_string;
    srand(time(nullptr));

    for (int i = 0; i < length; ++i) {
        random_string += characters[rand() % characters.length()];
    }

    return random_string;
}

// NEW WALLET CREATION FUNC
void new_wallet_func(int wallet_number) {
    // ALL SHA256 MECHANISM
    string public_key;
    uint8_t hash[SHA256::hash_size];
    public_key = generate_random_string(16);
    SHA256 sha256;
    sha256.update(reinterpret_cast<const uint8_t*>(public_key.c_str()), public_key.size());
    sha256.final(hash);
    public_key = SHA256::toString(hash);
    string private_key = generate_random_string(32);

    // CREATE WALLET BALANCE
    double balance = 0.0;

    // PATH WHERE WALLET INFO WILL SAVED
    string filename = "database/wallets/wallet_" + to_string(wallet_number) + ".md";

    // OPEN FILE TO WRITE INFO THERE
    ofstream outFile(filename);

    // IF FILE WASN'T OPEN
    if (!outFile) {
        cerr << "Cannot open file" << RED << filename << RESET << " for writing." << endl;
        return;
    }

    // WRITE WALLET INFO TO FILE
    outFile << "# Wallet number: " << to_string(wallet_number) << endl;
    outFile << "# Public key: " << public_key << endl;
    outFile << "# Private key: " << private_key << endl;
    outFile << "# Balance: " << balance << endl;

    // CLOSE FILE
    outFile.close();

    // CMD OUTPUT
    cout << CYAN << "New wallet created and data was written successfully.\n\n";
    cout << "# Wallet number: " << to_string(wallet_number) << "\n";
    cout << "# Public key: " << public_key << "\n";
    cout << "# Private key: " << private_key << "\n";
    cout << "# Balance: " << balance << "\n" << RESET;
}

// WALLET CHECK INFO FUNCTION
void check_wallet_info_func() {
    string filename;
    int wallet_number;

    // GET THE WALLET NUMBER TO UNDERSTAND WHAT FILE WEE NEED TO OPEN
    cout << "\nWrite an wallet number: \n>> ";
    cin >> wallet_number;

    // PATH TO WALLET
    filename = "database/wallets/wallet_" + to_string(wallet_number) + ".md";

    // OPEN THE FILE
    ifstream fin;
    fin.open(filename);

    // IF FILE ISN'T OPEN
    if (!fin.is_open()) {
        cout << RED << "Error: " << RESET << "file cannot be opened.\n" << RED << 
        "Reason: " << RESET << "no such file exists.\n";
    }
    // IF FILE OPEN AND ALL IS GOOD
    else {
        // READ FUNCTION AND OUTPUT TO CMD
        char ch;
        cout << endl;
        while (fin.get(ch)) {
            cout << CYAN << ch;
        }
    }

    // CLOSE FILE
    fin.close();
}