// Додаєм всі необхідні бібліотеки
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// використовуємо namespace std для скорочення коду
using namespace std;

// функція обчислювання + - / *
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

    // Надаєм перевагу множенню та діленню спочатку
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

    // Виконання додавання та віднімання
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
