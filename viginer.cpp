#include <iostream>
#include <string>
#include <fstream>
#include "functions.h"

using namespace std;

void printMenu() {
    cout << "=====================================" << endl;
    cout << "|               ����                |" << endl;
    cout << "=====================================" << endl;
    cout << "| 1. ����������                     |" << endl;
    cout << "| 2. �������������                  |" << endl;
    cout << "| 3. ������� �������                |" << endl;
    cout << "| 4. �����                          |" << endl;
    cout << "=====================================" << endl;
    cout << "������� ����� ������ ��������: ";
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
                throw logic_error("������� ������");
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
                throw logic_error("������ �������� ����������� � ������");
            }
            else if (operation == 1) {
                cout << "������� ������: ";
                cin >> passcode;
                if (passcode != password) {
                    throw logic_error("������ ��������");
                }
                cout << "1 - ���� � �������, 2 - ���� � �����" << endl;
                cout << "������� ����� ������ ��������: ";
                cin >> entry;
                if (cin.peek() != '\n' || cin.fail()) {
                    throw logic_error("������� ������");
                    cout << "������� ����� ������ ��������: ";
                    cin >> entry;
                }
                else if (entry != 1 && entry != 2) {
                    throw logic_error("������ �������� ����������� � ������");
                }
                cin.ignore(256, '\n');
                if (entry == 1) {
                    cout << "������� �����: ";
                    getline(cin, text);
                    writeToFile("original_text.txt", text);
                    cout << "������� ��������� ����: ";
                    getline(cin, key);

                    string encoded = encrypt(text, key);
                    writeToFile("encoded_text.txt", encoded);
                    cout << "������������� ����� ������� � ���� encoded_text.txt" << endl;
                }
                else if (entry == 2) {
                    cout << "������� ��� �����: ";
                    cin >> filename;
                    cin.ignore(256, '\n');
                    text = readFromFile(filename);
                    cout << "������� ��������� ����: ";
                    getline(cin, key);

                    string encoded = encrypt(text, key);
                    writeToFile("encoded_text.txt", encoded);

                    cout << "������������� ����� ������� � ���� encoded_text.txt  "<< endl;
                }
            }
            else if (operation == 2) {
                cin.ignore(256, '\n');
                cout << "������� ������: ";
                cin >> passcode;
                if (passcode != password) {
                    throw logic_error("������ ��������");
                }
                cout << "������� ��������� ��� �������� ����: ";
                cin.ignore(256, '\n');
                getline(cin, key);
                string encoded = readFromFile("encoded_text.txt");
                string decoded = decrypt(encoded, key);
                writeToFile("decoded_text.txt", decoded);
                cout << "�������������� ����� ������� � decoded_text.txt" << endl;
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