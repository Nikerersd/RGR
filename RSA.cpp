#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "functions.h"

using namespace std;

bool is_prime(int p) {
    if (p <= 1) return false;
    for (int i = 2; i <= sqrt(p); i++) {
        if (p % i == 0) return false;
    }
    return true;
}

int random(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int eiler(int p) {
    int result = p;
    for (int i = 2; i * i <= p; i++) {
        if (p % i == 0) {
            while (p % i == 0)
                p /= i;
            result -= result / i;
        }
    }
    if (p > 1)
        result -= result / p;
    return result;
}

int NOD (int a, int b) {
    if (b == 0) {
        return a;
    }
    return NOD(b , a % b);
}

int nodsKoef(int c, int m, int& x, int& y) {
    if (m == 0) {
        x = 1;
        y = 0;
        return c;
    }

    int x1, y1;
    int nod = nodsKoef(m, c % m, x1, y1);

    x = y1;
    y = x1 - (c / m) * y1;

    return nod;
}

int obratnCh(int c, int m) {
    int x, y;
    int gcd = nodsKoef(c, m, x, y);
    if (gcd != 1) {
        return -1;
    } 
    else {
        return (x % m + m) % m;
    }
}

long long pow_mod(long long a, long long x, long long p) {
    long long result = 1;
    a = a % p;
    while (x > 0) {
        if (x % 2 == 1) {
            result = (result * a) % p;
        }
        a = (a * a) % p;
        x /= 2;
    }
    return result;
}

int encoding(string message, int N, int OpenKey, vector<int>& encoded) {
    for (char c : message) {
        long long ASC = static_cast<long long>(c);
        if (ASC > N) {
            return -1;
        }
        long long encr = pow_mod(ASC, OpenKey, N);
        encoded.push_back(encr);
    }
    return 0;
}

void decoding(long long encSimv, int N, int ClosedKey, vector<int>& decoded) {
    long long decr = pow_mod(encSimv, ClosedKey, N);
        decoded.push_back(decr);
}

void generationCh(int& p, int& q, int& N, int& openKey, int& closedKey) {
    while (!is_prime(p)) {
        p = random (1000, 7000);
    }
    while (!is_prime(q)) {
        q = random (1000, 7000);
    }
    N = p*q;
    int eilr = eiler(N);
    openKey = random(1000, eilr);
    while (NOD(openKey,eilr) !=1 ) {
        openKey = random(1000, eilr);
    }
    closedKey = obratnCh(openKey, eilr);
}

void rsa(const string& password) {
    srand(time(0));
    int p=10, q=10, N, openKey, closedKey;
    string text, passcode, filename;
    int operation, entry;
    generationCh(p, q, N, openKey, closedKey);
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
                    vector<int> encodeSymb;
                    int encoded = encoding(text, N, openKey, encodeSymb);
                    if (encoded == -1) {
                        throw logic_error("Имеется неизвестный символ для шифрования");
                    }
                    writeToFileVec("encoded_text.txt", encodeSymb);
                    cout << "Зашифрованный текст записан в файл encoded_text.txt" << endl;
                }
                else if (entry == 2) {
                    cout << "Введите имя файла: ";
                    cin >> filename;
                    cin.ignore(256, '\n');
                    text = readFromFile(filename);
                    vector<int> encodeSymb;
                    int encoded = encoding(text, N, openKey, encodeSymb);
                    if (encoded == -1) {
                        throw logic_error("Имеется неизвестный символ для шифрования");
                    }
                    writeToFileVec("encoded_text.txt", encodeSymb);
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
                vector<int> encodeSymb = readFromFileVec("encoded_text.txt");
                vector<int> decodeSymb;
                for (int i : encodeSymb) {
                    decoding(i, N, closedKey, decodeSymb);
                }
                string decoded;
                for (int i : decodeSymb) {
                    char c = static_cast<char>(i);
                    decoded += c;
                }
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