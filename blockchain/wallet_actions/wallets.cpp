#include "wallets.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "SHA256/sha256.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"   
#define GREEN   "\033[32m"     
#define YELLOW  "\033[33m"  
#define BLUE    "\033[34m"     
#define MAGENTA "\033[35m"

using namespace std;

string generate_random_string(int length) {
    string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string random_string;
    srand(time(nullptr));

    for (int i = 0; i < length; ++i) {
        random_string += characters[rand() % characters.length()];
    }

    return random_string;
}

void new_wallet_func(int wallet_number) {
    string public_key;
    uint8_t hash[SHA256::hash_size];

    public_key = generate_random_string(16);
    SHA256 sha256;
    sha256.update(reinterpret_cast<const uint8_t*>(public_key.c_str()), public_key.size());
    sha256.final(hash);
    public_key = SHA256::toString(hash);

    string private_key = generate_random_string(32);
    double balance = 0.0;

    string filename = "database/wallets/wallet_" + to_string(wallet_number) + ".md";

    ofstream outFile(filename);

    if (!outFile) {
        cerr << "Cannot open file" << RED << filename << RESET << " for writing." << endl;
        return;
    }

    outFile << "# Wallet number: " << to_string(wallet_number) << endl;
    outFile << "# Public key: " << public_key << endl;
    outFile << "# Private key: " << private_key << endl;
    outFile << "# Balance: " << balance << endl;

    outFile.close();

    cout << "New wallet created and data was written " << GREEN << "successfully.\n" << RESET << endl;
    cout << "# Wallet number: " << MAGENTA << to_string(wallet_number) << RESET << endl;
    cout << "# Public key: " << MAGENTA << public_key << RESET << endl;
    cout << "# Private key: " << MAGENTA << private_key << RESET << endl;
    cout << "# Balance: " << MAGENTA << balance << RESET << endl;
}
