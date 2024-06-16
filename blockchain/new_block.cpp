#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

string block_version = "1.02";

string merkleroot, timestamp, difficulty, nonce, transactions, transaction_limit,
previous_hash, block_header, block_hash;

int block_number;

int main() {

    if (block_number == 0) {
        
        block_header = "Block Header:\n"
                " Version: " + block_version +
                " Previous hash: N/A"
                " Merkle Root: " + merkleroot +
                " Timestamp: " + timestamp +
                " Difficulty: " + difficulty +
                " Nonce: " + nonce;

        block_number++;
    } 
    else {
        
        block_header = "Block Header:\n"
                " Version: " + block_version +
                " Previous hash: " + previous_hash +
                " Merkle Root: " + merkleroot +
                " Timestamp: " + timestamp +
                " Difficulty: " + difficulty +
                " Nonce: " + nonce;
    }
}