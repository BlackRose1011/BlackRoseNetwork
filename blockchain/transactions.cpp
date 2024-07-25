// додаємо всі необхідні бібліотеки для роботи 
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>

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
    if (check == "YES") {
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
    } else if (check == "NO") { // якшо користувач помилився то транзакція відмінається
        cout << RED << "Error: " << RESET << "Operation cancelled." << endl;
    } else { // якщо користувач ввів щось крім YES або NO
        cout << RED << "Error: " << RESET << "Invalid input." << endl;
    }
}