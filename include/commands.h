// файл для передачі коду в інчий файл
#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

using namespace std;

void handle_root_commands(const string& main_command, const std::string& sub_command, const std::string& option, int& wallet_counter);
void handle_sys_commands(const string& sub_command, const std::string& option, bool& root, const std::string& password, const std::string& filename, int& wallet_counter);

#endif // COMMANDS_H
