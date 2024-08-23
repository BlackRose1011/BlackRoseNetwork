// файл для передачі коду в інчий файл
#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

using namespace std;

void handle_root_commands(const string& main_command, const string& sub_command, const string& option, int& wallet_counter);
void handle_sys_commands(const string& sub_command, const string& option, bool& root, const string& password, const string& filename, int& wallet_counter, bool& status);

#endif // COMMANDS_H
