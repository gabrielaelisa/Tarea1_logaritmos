#include <map>
#include <iostream>
#include <string>
#include <list>
#include <fstream>

using namespace std;

ifstream file;

//const ifstream file;

void funcion() {
    string bla;
    for (int i = 0; i < 2; ++i)
        {getline(file, bla);
    cout << bla << endl;
}}

int main() {
    file.open("bla.txt");
    for (int i = 0; i < 5; ++i) {
        funcion();
    }
    file.close();
    return 0;
}
