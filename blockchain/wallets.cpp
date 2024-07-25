// додаємо всі бібліотеки що нам потрібні
#include "wallets.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

// додаємо код з файлів який нам потрібен
#include "sha256.h"

// кольори для простішого користування консолю
#define RESET       "\033[0m"
#define CYAN        "\033[36m"     
#define RED         "\033[31m" 

// використовуємо namespace std для скорочення коду
using namespace std;

// функція коду SHA-256
string generate_random_string(int length) {
    string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string random_string;
    srand(time(nullptr));

    for (int i = 0; i < length; ++i) {
        random_string += characters[rand() % characters.length()];
    }

    return random_string;
}

// функція створення нового кошелька в блокчейні
void new_wallet_func(int wallet_number) {
    // створення публічного ключа
    string public_key;
    uint8_t hash[SHA256::hash_size];
    public_key = generate_random_string(16);
    SHA256 sha256;
    sha256.update(reinterpret_cast<const uint8_t*>(public_key.c_str()), public_key.size());
    sha256.final(hash);
    public_key = SHA256::toString(hash);

    // створення приватного ключа з публічного ключа
    string private_key = generate_random_string(32);

    // створюєм баланс кошелька
    double balance = 0.0;

    // шлях до папки де буде зберігатися кошельок
    string filename = "database/wallets/wallet_" + to_string(wallet_number) + ".md";

    // відкриваємо файл щоб записати туда інформацію
    ofstream outFile(filename);

    // якщо файл не відкрився
    if (!outFile) {
        cerr << "Cannot open file" << RED << filename << RESET << " for writing." << endl;
        return;
    }

    // записуємо данні в кошельок
    outFile << "# Wallet number: " << to_string(wallet_number) << endl;
    outFile << "# Public key: " << public_key << endl;
    outFile << "# Private key: " << private_key << endl;
    outFile << "# Balance: " << balance << endl;

    // закриваєм файл
    outFile.close();

    // виводимо в консоль записанні данні в файл тільки що створеного кошелька
    cout << CYAN << "New wallet created and data was written successfully.\n\n";
    cout << "# Wallet number: " << to_string(wallet_number) << "\n";
    cout << "# Public key: " << public_key << "\n";
    cout << "# Private key: " << private_key << "\n";
    cout << "# Balance: " << balance << "\n" << RESET;
}

// функція перевірки інформації кошелька
void check_wallet_info_func() {
    string filename;
    int wallet_number;

    // вводимо номер кошелька про який ми хочемо дізнатися 
    // (пізніше замінимо) на адрес кошелька а не на номер
    cout << "\nWrite an wallet number: \n>> ";
    cin >> wallet_number;

    // шлях до кошелька
    filename = "database/wallets/wallet_" + to_string(wallet_number) + ".md";

    // відкриваємо файл
    ifstream fin;
    fin.open(filename);

    // якщо файл не був відкритий
    if (!fin.is_open()) {
        cout << RED << "Error: " << RESET << "file cannot be opened.\n" << RED << 
        "Reason: " << RESET << "no such file exists.\n";
    }
    
    // якщо файл відкрився
    else {
        // читаємо файл та виводимо все в консоль
        char ch;
        cout << endl;
        while (fin.get(ch)) {
            cout << CYAN << ch;
        }
    }

    // закриваємо файл
    fin.close();
}