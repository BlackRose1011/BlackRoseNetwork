// додаємо необхідні бібліотеки для роботи
#include <iostream>
#include <string>
#include <fstream>
#include <thread>

// додаємо необхідний код з файлів
#include "wallets.h"
#include "transactions.h"
#include "calculator.h"
#include "file.h"
#include "commands.h"

// використовуємо namespace std для скорочення коду
using namespace std;

// додаємо кольори для того щоб легче було користуватись консолю
#define RESET       "\033[0m"
#define CYAN        "\033[36m"     
#define RED         "\033[31m" 

/* створення перемінних command - туди куди ми вводимо команди 
password - пароль для щоб получити root-права
input - для створення логіки першої другої команди та опції 
root = false, це ми обізначаємо що спочатку у користувача немає root-прав
wallet_counter - ініціалізуєм перемінну номера кошелька щоб потім получити значення з файлу wallet_counter.md */
string command, password = "yo", input;
bool root = false;
int wallet_counter;

int main() {
    // вказуємо шлях до файлу де лежить значення скільки кошельків уже створенно
    string filename = "database/wallet_counter.md";

    // відкриваєм файл та считуємо значення і передаємо його змінній wallet_counter
    ifstream fin(filename);
    if (fin.is_open()) {
        fin >> wallet_counter;
        fin.close();
    } 
    else { // якщо файлу wallet_counter.md немає
        cerr << RED << "Error: " << CYAN << "Failed to open wallet counter file." << endl;
        return 1;
    }

    while (true) { // зациклення консолі щоб можно було вводити безкінечну кількість команд
        if (root) { // якщо у тебе є root-права
            cout << CYAN << "\n@blockchain" << RESET << " >> ";
        } 
        else { // якщо root-прав немає
            cout << CYAN << "\n@cmd" << RESET << " >> ";
        }
        getline(cin, input); // отримуємо цілий рядок написанно користувачем 

        // ініціалізуєм логіку першої другою команд та опції
        istringstream iss(input);
        string main_command, sub_command, option;
        iss >> main_command >> sub_command >> option;

        // ROOT-COMMANDS
        if (root) { // функція root-команд
            handle_root_commands(main_command, sub_command, option, wallet_counter);
        }

        // COMMON-COMMANDS
        if (main_command == "sys") { // функція команд простого користувача
            handle_sys_commands(sub_command, option, root, password, filename, wallet_counter);
        } 
        else if (main_command == "file") { // функція роботи з файлами
            files_actions(input);
        }
    }
    return 0; 
}
