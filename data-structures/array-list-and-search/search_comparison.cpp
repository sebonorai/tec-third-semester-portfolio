
using namespace std;
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Lista.h"
#include <vector>
#include <algorithm>

int sequentialSearch(const Lista &lista, int target, int &comps) {
    int n = lista.getSize();

    comps = 0;
    int pos = 0;
    while (pos < n) {
        comps++;
        if (target == lista.getData(pos)) {
            return pos;
        }
        pos++;
    }
    return -1;
}

int binarySearch(const vector<int> &vec, int target, int &comps) {
    int n = vec.size();
    int primero = 0;
    int ultimo = n - 1;
    int medio;
    comps = 0;
    while (primero <= ultimo) {
        medio = (primero + ultimo) / 2;
        comps++;
        if (target == vec[medio]) {
            return medio;
        }
        if (target > vec[medio]) {
            primero = medio + 1;
        }
        else {
            ultimo = medio - 1;
        }
    }
    return -1;
}



int main()
{
    int n; // cantidad de valores

    cout << "N? ";
    cin >> n;

    Lista lista;

    srand(time(0));
    for (int i = 0; i < n; i++) {
        lista.insert(rand() % (5 * n));
    }
    cout << "Lista de valores generados aleatoriamente: \n";
    lista.print();

    vector<int> vec;

    for (int i = 0; i < n; i++) {
        vec.push_back(lista.getData(i));
    }
    sort(vec.begin(), vec.end());

    int target, comps, pos;
    do {
        cout << "Valor a buscar? ";
        cin >> target;
        if (target >= 0) {
            pos = sequentialSearch(lista, target, comps);
            if (pos < 0) {
                cout << "Valor" << target << " No encontrado\n";
                cout << "No lo encontro con " << comps << " comparaciones. \n";

            }
            else {
                cout << "Valor" << target << " encontrado en post\n";
                cout << "Lo encontro con " << comps << " comparaciones. \n";
            }
            if (target >= 0) {
                pos = binarySearch(vec, target, comps);
                if (pos < 0) {
                    cout << "Valor" << target << " No encontrado\n";
                    cout << "No lo encontro con" << comps << " comparaciones. \n";

                }
                else {
                    cout << "Valor" << target << " encontrado en post\n";
                    cout << "Lo encontro con" << comps << " comparaciones. \n";
                }
            }
        } 
    } while (target >= 0);
}
