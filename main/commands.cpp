// Додаємо всі необхідні бібліотеки
#include <iostream>
#include <string>
#include <fstream>
#include <thread>

// Додаємо всі необхідні функції з інчих файлів
#include "commands.h"
#include "wallets.h"
#include "transactions.h"
#include "calculator.h"
#include "load_bar.h"

// Додаємо кольори для простішого використання консолі
#define RESET       "\033[0m"
#define CYAN        "\033[36m"     
#define RED         "\033[31m" 

// Використовуємо namespace std для скорочення коду
using namespace std;

// функція root-команд тобто тих команд які можуть виконувати тільки root-користувачі
void handle_root_commands(const string& main_command, const string& sub_command, const string& option, int& wallet_counter) {
    // тут ми використувуєм рівневу систему коду тобто команда виглядає так chain wallet -n
    if (main_command == "chain") {
        if (sub_command == "wallet") { // керування кошельками (створення, інформація, видалення і тд.)
            if (option == "-n") { // створення нового кошелька тобто -n = new = новий
                int duration = 2.5;
                showprogress(duration);
                new_wallet_func(wallet_counter);
                wallet_counter++;
            } 
            else if (option == "-i") { // виведення інформацію про кошельок -i = info = інформація
                check_wallet_info_func();
            } 
            else { // помилка якщо було введена невірна опція
                cerr << RED << "Error: " << CYAN << "Invalid wallet option." << endl;
            }
        } 
        else if (sub_command == "transaction") { // виконання транзакцій
            if (option == "-s") { // надсилання криптовалюти тобто -s = send = надіслати
                send_crypto_func();
            } 
            else if (option == "-l") { // виведення списку транзакцій у останньому блоку -l = list = список
                // Допрацюємо пізніше
            } 
            else { // помилка якщо введена неправельна опція
                cerr << RED << "Error: " << CYAN << "Invalid transaction option." << endl;
            }
        } 
        else { // помилка якщо додаткова команда вказана невірно
            cerr << RED << "Error: " << CYAN << "Invalid command." << endl;
        }
    }
}

// функція основного списку команд тобто sys доступно всім користувачам
void handle_sys_commands(const string& sub_command, const string& option, bool& root, const string& password, const string& filename, int& wallet_counter) {
    if (sub_command == "out") { // вихід з консолі
        ofstream outFile(filename); // відкриття файлу щоб обновити рахунок створених кошельків
        if (!outFile) { // помилка якщо файлу, де зберігається число створенних кошельків, немає
            cerr << RED << "Error: " << CYAN << "Failed to open wallet counter file for writing." << endl;
            return; 
        }
        outFile << wallet_counter << endl; // запис у файл
        outFile.close(); // закриття файлу

        exit(0); // вихід з програми
    } 
    else if (sub_command == "help") { // вивід усіх доступних команд
        cout << "All available commands: \n\n" << 
        CYAN << "sys root -t" << RESET << " - root rules enable.\n" <<
        CYAN << "sys root -f" << RESET << " - root rules disable.\n" <<
        CYAN << "sys timer" << RESET << " - set up the timer;\n" <<
        CYAN << "sys clear" << RESET << " - clear the screen.\n" <<
        CYAN << "sys help" << RESET << " - show all available commands.\n" <<
        CYAN << "sys calc" << RESET << " - calculate something.\n" <<
        CYAN << "sys out" << RESET << " - leave the command line.\n";

        if (root) { // команди для root-користувачі будуть виводитись тільки для root-користувачів
            cout << "\nAll available root commands: \n\n"
            CYAN << "chain wallet -n " << RESET << "- create new wallet on blockchain.\n" << 
            CYAN << "chain wallet -i " << RESET << "- check wallet info.\n" << 
            CYAN << "chain transaction -s " << RESET << "- transfer crypto to another wallet\n";
        }
    }
    else if (sub_command == "calc") { // функція калькулятора, відтворенна у файлі calculator.cpp
        string expression; // expression = вираз, наприклад: 2+2-5*18/3
        cout << "Enter an expression: \n >> ";
        cin >> expression;

        int result = calculate(expression);
        cout << "Result: " << CYAN << result << RESET << endl; // виведення результату
    } 
    else if (sub_command == "root") { // активація або деактивація root-прав
        if (option == "-t") { // активація root-прав -t = true = правда
            string pswd;

            cout << "\nWrite the password: \n >> ";
            cin >> pswd;

            if (pswd == password) {
                cout << "Root rules activated " << CYAN << "successfully!\n";
                root = true;
            }
        } 
        else if (option == "-f") { // деактивація root-прав -f = false = брехня
            cout << "\nRoot rules were successfully set to " << RED << "false" << RESET << " state.\n";
            root = false;
        }
    }
    else if (sub_command == "clear") { // очистка консолі
        cout << "\033[2J\033[1;1H";
    }
    else if (sub_command == "timer") { // таймер консолі
        // консоль засне та не буде працювати стільки часу, скільки ви написали
        int seconds;
        cout << "Write the time you want to set for the timer: \n >> ";
        cin >> seconds;
        cout << "Timer set for " << seconds << CYAN << " seconds" << RESET << ".\n";
        this_thread::sleep_for(chrono::seconds(seconds));
        cout << CYAN << "Time's up!\n" << RESET;
    }
    else { // якщо такої команди не існує
        cerr << RED << "Error: " << RESET << "Invalid command." << endl;
    }
}
