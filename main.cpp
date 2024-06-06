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
    cout << "������� ������ ��� ������ ������: ";
    getline(cin, enteredPass);
    while (enteredPass != password) {
        cout << "������ ��������" << endl;
        cout << "������� ������ ��� ������ ������: ";
        getline(cin, enteredPass);
    }
    system("cls");
    while (true) {
        try {
            cout << "=====================================" << endl;
            cout << "|               ����                |" << endl;
            cout << "=====================================" << endl;
            cout << "| 1. ����� ����� RSA                |" << endl;
            cout << "| 2. ����� ����� ��������           |" << endl;
            cout << "| 3. ����� ����� �����              |" << endl;
            cout << "| 4. ���������� ������ ���������    |" << endl;
            cout << "=====================================" << endl;
            cout << "������� ����� ��������� ��������: ";
            cin >> action;
            if (cin.peek() != '\n' || cin.fail())
            {
                throw logic_error("������� ������");
            }
            else if (action != 1 && action != 2 && action != 3 && action != 4) {
                throw logic_error("������ �������� ����������� � ������");
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
            cerr << "������: " << e.what() << endl;
            cin.clear();
            cin.ignore(256, '\n');
        }
    }
}