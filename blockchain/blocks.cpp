#include <iostream>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// кольори для простішого користування консолю
#define RESET       "\033[0m"
#define CYAN        "\033[36m"     
#define RED         "\033[31m" 

void new_block(int& block_number) {
    string block_structure;
    block_structure = "BLOCK HEADER: "
    "previous block hash: "
    "block hash: "
    "timestamp: "
    "nonce: "
    "merkle root: "
    "block version: "
    "block size: "
    "mining difficulty: "
    "block reward: "
    "transactions: "
    "commision per transaction: ";

    string filename = "database/blocks/block_1" + to_string(block_number) + "/block_1" + to_string(block_number) + ".md";

    // відкриваємо файл щоб записати туда інформацію
    ofstream outFile(filename);

    // якщо файл не відкрився
    if (!outFile) {
        cerr << "Cannot open file" << RED << filename << RESET << " for writing." << endl;
        return;
    } 

    outFile << block_structure;
}
