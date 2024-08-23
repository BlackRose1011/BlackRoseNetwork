// додаємо всі необхідні бібліотеки для роботи 
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h> 

#include "sha256.h"
#include "utils.h"

// використуваємо namespace std для скорочення коду
using namespace std;

/* Створення перемінних 
from - від якого користувача буде надсилатися криптовалюта
to - до якого користувача буде надсилатися криптовалюта 
check - перевірка чи не помилився користувач данними при вводі
sum - сумма яку користувач хоче надіслати інчому користувачу */
int from, to;
double sum;
string check;

// додаєм кольори для легчого користуванню консолю
#define RESET       "\033[0m"
#define CYAN        "\033[36m"     
#define RED         "\033[31m" 

// функція для перепису лінії в файлі, у нашому випадку балансу користувача
void rewrite_line(const string& filename, int target_line, const string& new_content) {
    ifstream fin(filename); // відкриваємо файл для читання
    if (!fin.is_open()) {
        cerr << "Unable to open file!" << endl;
        return;
    }

    vector<string> lines;
    string line;
    int current_line = 1;

    // зчитування вмісту файлу в пам'ять
    while (getline(fin, line)) {
        if (current_line == target_line) {
            lines.push_back(new_content); // замінюємо потрібну строчку
        } else {
            lines.push_back(line); // зберігаємо інші строчки без змін
        }
        current_line++;
    }

    fin.close(); // закриваємо файл після читання

    ofstream fout(filename); // відкриття файлу для запису
    if (!fout.is_open()) {
        cerr << "Unable to open file for writing!" << endl;
        return;
    }

    // записуємо модифікований вміст назад у файл
    for (const string& l : lines) {
        fout << l << endl;
    }

    fout.close(); // закриваємо файл після запису
}

// функція надсилання криптовалюти 
void send_crypto_func() {
    // вкажіть кошельок з якого ви хочете надіслати криптовалюту
    cout << "\nWrite wallet number from what you want to send:\n>> ";
    cin >> from; 

    // вкажіть кошельок який отримає криптовалюту
    cout << "Write what wallet will recieve:\n>> ";
    cin >> to;

    // скільки ви хочете надіслати?
    cout << "How much you would like to send?\n>> ";
    cin >> sum;

    // перевірка введених данних
    cout << "\n\nAre you sure that all the entered information is correct? (YES / NO)\n"
    << CYAN << "\nFrom: " << RESET << from << CYAN << "\nTo: " << RESET 
    << to << CYAN << "\nSum: " << RESET << sum << "\n\n>> ";
    cin >> check;
    cout << "\n";

    // перевірка чи дійсно користувач ввід потрібні данні
    if (check == "YES") 
    {
        // шлях до файлу з відки забереться криптовалюта
        string filename_from = "database/wallets/wallet_" + to_string(from) + ".md";
        ifstream fin_from(filename_from); // відкриття файлу

        // шлях куди надішлеться криптовалюта
        string filename_to = "database/wallets/wallet_" + to_string(to) + ".md";
        ifstream fin_to(filename_to); // відкриття файлу

        double digits_1 = 0; 
        double digits_2 = 0;

        if (fin_from.is_open()) { // відкриваємо файл з відки ми надсилаємо криптовалюту
            string line;
            int lineNumber = 1; // лінія з якої ми починаємо считувати файл
            
            while (getline(fin_from, line)) {
                if (lineNumber == 4) { // считуємо четверту строчку у файлі (звичайно можна її змінити за необхідності)
                    
                    // читаємо всю строчку, символ за символом
                    string digits_str; 
                    for (char c : line) {
                        if (isdigit(c) || c == '.') {
                            digits_str += c;
                        }
                    }
                    try {
                        digits_1 = stod(digits_str);
                    } catch (const std::invalid_argument& e) { // якщо формат балансу в файлі неправельний
                        cerr << "Invalid balance format in file: " << filename_from << endl;
                        return;
                    } catch (const std::out_of_range& e) { // якщо баланса у користувача немає
                        cerr << "Balance value out of range in file: " << filename_from << endl;
                        return;
                    }
                    break; // виходимо з циклу 
                }
                lineNumber++;
            }

            fin_from.close(); // закриваємо файл після його считування
        } 
        else { // якщо неможемо відкрити файл
            cout << RED << "Error " << RESET << ": Unable to open file!" << endl;
        }

        if (fin_to.is_open()) { // відкриваємо файл куди ми надсилаємо криптовалюту
            string line;
            int lineNumber = 1; // лінія з якої ми починаємо считувати файл
            
            while (getline(fin_to, line)) { 
                if (lineNumber == 4) { // считуємо четверту строчку у файлі (звичайно можна її змінити за необхідності)
                    
                    // читаємо всю строчку, символ за символом
                    string digits_str;
                    for (char c : line) {
                        if (isdigit(c) || c == '.') {
                            digits_str += c;
                        }
                    }
                    try {
                        digits_2 = stod(digits_str);
                    } catch (const std::invalid_argument& e) { // якщо формат балансу в файлі неправельний
                        cerr << "Invalid balance format in file: " << filename_to << endl;
                        return;
                    } catch (const std::out_of_range& e) { // якщо баланса у користувача немає
                        cerr << "Balance value out of range in file: " << filename_to << endl;
                        return;
                    }
                    break; // виходимо з циклу
                }
                lineNumber++;
            }

            fin_to.close();
        } 
        else { // якщо неможемо відкрити файл виводимо помилку
            cout << RED << "Error " << RESET << ": Unable to open file!" << endl;
        }
        
        if (digits_1 >= sum) {
            // тут ми рахуємо який баланс буде у відправника та одержувача після операції тобто - та +
            double balance_1 = digits_1 - sum;
            double balance_2 = digits_2 + sum;

            // створення перемінних де буде нова строчка балансу у файлах
            string new_content_from = "# Balance: " + to_string(balance_1);
            string new_content_to = "# Balance: " + to_string(balance_2);

            rewrite_line(filename_from, 4, new_content_from); // обновляємо баланс відправника
            rewrite_line(filename_to, 4, new_content_to); // обновляємо баланс отримувача
            cout << "Transaction completed " << CYAN << "successfully" << ".\n";
        }
        else { // помилка якшо відправник немає на балансі достатньо криптовалюти
            cout << RED << "Error " << RESET << ": Not enough balance to make the transaction." << endl;
        }
    } else if (check == "NO") 
    { // якшо користувач помилився то транзакція відмінається
        cout << RED << "Error: " << RESET << "Operation cancelled." << endl;
    } else 
    { // якщо користувач ввів щось крім YES або NO
        cout << RED << "Error: " << RESET << "Invalid input." << endl;
    }
}

// функція запису тразакції у файл
void write_transaction_info(int transaction_number = 0, int block_number = 0) {
    
    string file = "database/block_counter.md";
    string file2 = "database/transaction_counter.md";

    //  шлях до файлу де буде записана тразакція
    string directory = "database/transaction/block_" + to_string(block_number);
    string filename = directory + "/transaction_" + to_string(transaction_number) + ".md";

    // Створюємо директорію, якщо її не існує
    struct stat info;

    if (stat(directory.c_str(), &info) != 0) {
        // Директорія не існує, створюємо її
        if (mkdir(directory.c_str(), 0777) != 0) {
            cerr << "Cannot create directory " << directory << endl;
            return;
        }
    } else if (!(info.st_mode & S_IFDIR)) {
        cerr << directory << " is not a directory!" << endl;
        return;
    }

    ofstream outFile(filename);

    // якщо файл не відкрився
    if (!outFile) {
        cerr << "Cannot open file " << RED << filename << RESET << " for writing." << endl;
        return;
    }


    ifstream fin;
    fin.open(file2);
    
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
            transaction_number = ch;
        }
    }
    
    // відкриваємо файл
    fin.open(file);
    
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
            block_number = ch;
        }
    }

    fin.close();

    //  шлях до файлу де буде записана тразакція
    string filename = "database/transaction/block_" + to_string(block_number) + "/transaction_" + to_string(transaction_number) + ".md";

    ofstream outFile(filename);

    // якщо файл не відкрився
    if (!outFile) {
        cerr << "Cannot open file" << RED << filename << RESET << " for writing." << endl;
        return;
    }

    // створення хешу транзакції
    string transaction_hash;
    uint8_t hash[SHA256::hash_size];
    transaction_hash = generate_random_string(64);
    SHA256 sha256;
    sha256.update(reinterpret_cast<const uint8_t*>(transaction_hash.c_str()), transaction_hash.size());
    sha256.final(hash);
    transaction_hash = SHA256::toString(hash);

    // записуємо данні в кошельок
    outFile << "# From: " << to_string(from) << endl;
    outFile << "# To: " << to << endl;
    outFile << "# Sum: " << sum << endl;
    outFile << "# Time: " << time << endl;
    outFile << "# Hash: " << transaction_hash << endl;
    outFile << "# Transaction number: " << transaction_number << endl;

    outFile.close();
}