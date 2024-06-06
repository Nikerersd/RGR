#include <iostream>
#include <string>
#include <fstream>
#include "functions.h"

using namespace std;

void printMenu() {
    cout << "=====================================" << endl;
    cout << "|               МЕНЮ                |" << endl;
    cout << "=====================================" << endl;
    cout << "| 1. шифрование                     |" << endl;
    cout << "| 2. расшифрование                  |" << endl;
    cout << "| 3. очистка консоли                |" << endl;
    cout << "| 4. выход                          |" << endl;
    cout << "=====================================" << endl;
    cout << "Введите номер нужной операции: ";
}

string encrypt(const string& text, const string& key) {
    string cipherText;
    for (size_t i = 0; i < text.length(); i++) {
        if (text[i] == '\n' || text[i] == 32)
            cipherText.push_back(text[i]);
        else {
            unsigned char x = (static_cast<unsigned char>(text[i]) + static_cast<unsigned char>(key[i%key.length()])) % 256;
            cipherText.push_back(x);
        }
    }
    return cipherText;
}

string decrypt(const string& cipherText, const string& key) {
    string origText;
    for (size_t i = 0; i < cipherText.length(); i++) {
        if (cipherText[i] == '\n' || cipherText[i] == 32)
            origText.push_back(cipherText[i]);
        else {
            unsigned char x = (static_cast<unsigned char>(cipherText[i]) - static_cast<unsigned char>(key[i%key.length()]) + 256) % 256;
            origText.push_back(x);
        }
    }
    origText.pop_back();
    return origText;
}

void viginer(const string& password) {
    string text, passcode, filename, key;
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
                    cout << "Введите требуемый ключ: ";
                    getline(cin, key);

                    string encoded = encrypt(text, key);
                    writeToFile("encoded_text.txt", encoded);
                    cout << "Зашифрованный текст записан в файл encoded_text.txt" << endl;
                }
                else if (entry == 2) {
                    cout << "Введите имя файла: ";
                    cin >> filename;
                    cin.ignore(256, '\n');
                    text = readFromFile(filename);
                    cout << "Введите требуемый ключ: ";
                    getline(cin, key);

                    string encoded = encrypt(text, key);
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
                cout << "Введите указанный при шифровке ключ: ";
                cin.ignore(256, '\n');
                getline(cin, key);
                string encoded = readFromFile("encoded_text.txt");
                string decoded = decrypt(encoded, key);
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