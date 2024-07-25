// додаєм необхідні бібліотеки для роботи
#include <iostream>
#include <thread>
#include <chrono>

// використовуємо namespace std для скорочення коду
using namespace std;

// функція загрузки
void showprogress(int duration) {
    // скільки всього кроків для виконання тобто %
    const int totalSteps = 100;

    // довжину в часі ділимо на * 1000 тобто 5 * 1000 / 100 наприклад
    const int interval = duration * 1000 / totalSteps;

    // математика фу
    for (int i = 1; i <= totalSteps; ++i) {
        string progressBar = string(i / 2, '#') + string(50 - i / 2, ' ');
        cout << "\r" << progressBar << " " << i << "%" << flush;
        this_thread::sleep_for(chrono::milliseconds(interval));
    }

    // виводимо нашу загрузку
    cout << "\r" << string(50, '#') << " 100%" << endl;
}
