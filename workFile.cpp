#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "functions.h"
using namespace std;
void writeToFile(const string& filename, const string& text) {
    ofstream file(filename);
    if (file.is_open()) {
        file << text;
        file.close();
    }
    else {
        throw runtime_error("Невозможно произвезти запись в файл: " + filename);
    }
}

void writeToFileVec(const string& filename, const vector<int>& text) {
    ofstream file(filename);
    if (file.is_open()) {
        for (auto i : text) {
            file << i << " ";
        }
        file.close();
    }
    else {
        throw runtime_error("Невозможно произвезти запись в файл: " + filename);
    }
}

string readFromFile(const string& filename) {
    ifstream file(filename);
    string result;
    if (file.is_open()) {
        string line;
        while (getline(file, line))
        {
            result += line + "\n";
        }
        file.close();
        return result;
    }
    else {
        throw runtime_error("Невозможно прочесть файл: " + filename);
    }
}

vector<int> readFromFileVec(const string& filename) {
    ifstream file(filename);
    vector<int> result;
    if (file.is_open()) {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            int number;
            while (ss >> number) {
                result.push_back(number);
            }
        }
        file.close();
        return result;
    }
    else {
        throw runtime_error("Невозможно прочесть файл: " + filename);
    }
}