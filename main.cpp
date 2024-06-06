#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "functions.h"

using namespace std;

int main() {
    system("chcp 1251 > nul");
    string enteredPass;
    string password = "522005";
    int action;
    cout << "Введите пароль для начала работы: ";
    getline(cin, enteredPass);
    while (enteredPass != password) {
        cout << "Пароль неверный" << endl;
        cout << "Введите пароль для начала работы: ";
        getline(cin, enteredPass);
    }
    system("cls");
    while (true) {
        try {
            cout << "=====================================" << endl;
            cout << "|               МЕНЮ                |" << endl;
            cout << "=====================================" << endl;
            cout << "| 1. Выбор шифра RSA                |" << endl;
            cout << "| 2. Выбор шифра Вижинера           |" << endl;
            cout << "| 3. Выбор шифра Атбаш              |" << endl;
            cout << "| 4. Завершение работы программы    |" << endl;
            cout << "=====================================" << endl;
            cout << "Введите номер требуемой операции: ";
            cin >> action;
            if (cin.peek() != '\n' || cin.fail())
            {
                throw logic_error("Введена строка");
            }
            else if (action != 1 && action != 2 && action != 3 && action != 4) {
                throw logic_error("Данная операция отсутствует в списке");
            }
            else if (action == 4) {
                break;
            }
            else if (action == 1) {
                system("cls");
                rsa(password);
            }
            else if (action == 2) {
                system("cls");
                viginer(password);
            }
            else if (action == 3) {
                system("cls");
                atbash(password);
            }

        }
        catch (const exception& e) {
            system("cls");
            cerr << "Ошибка: " << e.what() << endl;
            cin.clear();
            cin.ignore(256, '\n');
        }
    }
}