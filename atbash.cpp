#include <iostream>
#include <string>
#include <fstream>
#include "functions.h"

using namespace std;

string crypt(string& text) {
    string result;
    for (int i = 0; i < text.size(); i++) {
        unsigned char symb = static_cast<unsigned char>(text[i]);

        if (symb >= 33 && symb <= 64)
            result += static_cast<unsigned char>(64 - symb + 33);
        else if (symb >= 65 && symb <= 90)
            result += static_cast<unsigned char>(90 - symb + 65);
        else if (symb >= 91 && symb <= 96)
            result += static_cast<unsigned char>(96 - symb + 91);
        else if (symb >= 97 && symb <= 122)
            result += static_cast<unsigned char>(122 - symb + 97);
        else if (symb >= 123 && symb <= 126)
            result += static_cast<unsigned char>(126 - symb + 123);
        else if (symb >= 128 && symb <= 175)
            result += static_cast<unsigned char>(175 - symb + 128);
        else if (symb >= 192 && symb <= 223)
            result += static_cast<unsigned char>(223 - symb + 192);
        else if (symb >= 224 && symb <= 255)
            result += static_cast<unsigned char>(255 - symb + 224);
        else
            result += symb;
    }
    return result;
}

void atbash(const string& password) {
    string text, passcode, filename;
    int operation, entry;

    while (true) {
        try {
            printMenu();
            cin >> operation;
            if (cin.peek() != '\n' || cin.fail())
            {
                throw logic_error("Введена строка");
            }
            if (operation == 4)
            {
                system("cls");
                break;
            }
            else if (operation == 3)
            {
                system("cls");
            }
            else if (operation != 1 && operation != 2)
            {
                throw logic_error("Данная операция отсутствует в списке");
            }
            else if (operation == 1) {
                cout << "Введите пароль: ";
                cin >> passcode;
                if (passcode != password) {
                    throw logic_error("Пароль неверный");
                }
                cout << "1 - ввод с консоли, 2 - ввод с файла" << endl;
                cout << "Введите номер нужной операции: ";
                cin >> entry;
                if (cin.peek() != '\n' || cin.fail()) {
                    throw logic_error("Введена строка");
                    cout << "Введите номер нужной операции: ";
                    cin >> entry;
                }
                else if (entry != 1 && entry != 2) {
                    throw logic_error("Данная операция отсутствует в списке");
                }
                cin.ignore(256, '\n');
                if (entry == 1) {
                    cout << "Введите текст: ";
                    getline(cin, text);
                    writeToFile("original_text.txt", text);
                    string encoded = crypt(text);
                    writeToFile("encoded_text.txt", encoded);
                    cout << "Зашифрованный текст записан в файл encoded_text.txt " << endl;
                }
                else if (entry == 2) {
                    cout << "Введите имя файла: ";
                    cin >> filename;
                    cin.ignore(256, '\n');
                    text = readFromFile(filename);
                    string encoded = crypt(text);
                    writeToFile("encoded_text.txt", encoded);

                    cout << "Зашифрованный текст записан в файл encoded_text.txt  "<< endl;
                }
            }
            else if (operation == 2) {
                cin.ignore(256, '\n');
                cout << "Введите пароль: ";
                cin >> passcode;
                if (passcode != password) {
                    throw logic_error("Пароль неверный");
                }
                string encoded = readFromFile("encoded_text.txt");
                string decoded = crypt(encoded);
                writeToFile("decoded_text.txt", decoded);
                cout << "Расшифрованный текст записан в decoded_text.txt" << endl;
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