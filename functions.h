#pragma once
#include <vector>
using namespace std;
void writeToFile(const string& filename, const string& content);
void writeToFileVec(const string& filename, const vector<int>& text);
string readFromFile(const string& filename);
vector<int> readFromFileVec(const string& filename);
void atbash(const string& password);
void viginer(const string& password);
void rsa(const string& password);
void printMenu();