// додавання необхіних бібліотек
#include <iostream>
#include <sstream>
#include <string>

// додавання необхідного коду з файлів
#include "file.h"

// використання namespace std для скорочення коду
using namespace std;

// функція роботи з файлами та директоріями
void files_actions(const string& input) {
    
    // створення логіки першої другої команд та опції для них
    istringstream iss(input);
    string main_command, sub_command, option;
    iss >> main_command >> sub_command >> option;

    if (main_command == "file") { // ось основна команда яка відповідає за роботу з файлами
        // додаткові команди нижче
        if (sub_command == "create") { // create = створити, тобто тут ми створюєм файл
            // потім
        }
        else if (sub_command == "open") { // open = відкрити, тут ми відкриваємо файлі
            // потім
        }
        else if (sub_command == "delete") { // delete = видалити, тут ми видаляємо файл
            // потім
        }
        else if (sub_command == "write") { // write = записати, тут ми записуємо у файл данні
            // потім
        }
        else if (sub_command == "rewrite") { // rewrite = переписати, тут ми перезаписуємо вже існуючі данні
            // потім
        }
        else if (sub_command == "close") { // close = закрити, закриваємо роботу файла
            // потім
        }
        else if (sub_command == "copy") { // copy = копіювати, копіюємо файл або вміст файла
            // потім
        }
        else if (sub_command == "replace") { // replace = перемістити, переміщаємо файл в інше місце
            // потім
        }
        else if (sub_command == "archive") { // archive = архівувати, архівуємо файл, або групу файлів
            // потім
        }
        else if (sub_command == "unpack") { // unpack = розпакувати, розпаковуємо архів
            // потім
        }

        else if (sub_command == "folder") { // основна команда яка відповідає за роботу з директоріями (папками)
            if (option == "-c") { // c = create = створити, створюємо директорію
                // потім
            }
            else if (option == "-d") { // d = delete = видалити, видаляємо директорію
                // потім
            }
            else if (option == "-r") { // r = rename = переіменувати, переіменовуєм директорію
                // потім
            }
            else if (option == "-rp") { // rp = replace = перемістити, переміщуємо директорію з одного місця і інче
                // потім
            }
        }
    }
}
