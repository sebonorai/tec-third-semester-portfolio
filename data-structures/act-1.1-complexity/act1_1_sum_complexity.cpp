#include <iostream>
using namespace std;

/*
    Calcula la sumatoria de 1 hasta n usando un ciclo.
    Complejidad temporal: O(n)
*/
long long sumaIterativa(int n) {
    long long suma = 0;

    for (int i = 1; i <= n; i++) {
        suma += i;
    }

    return suma;
}

/*
    Calcula la sumatoria de 1 hasta n usando recursividad.
    Complejidad temporal: O(n)
*/
long long sumaRecursiva(int n) {
    if (n == 1) {
        return 1;
    }

    return n + sumaRecursiva(n - 1);
}

/*
    Calcula la sumatoria de 1 hasta n mediante
    la fórmula matemática n(n + 1) / 2.
    Complejidad temporal: O(1)
*/
long long sumaDirecta(int n) {
    return (long long)n * (n + 1) / 2;
}

int main() {
    int s;
    cin >> s;

    for (int i = 0; i < s; i++) {
        int n;
        cin >> n;

        cout << sumaIterativa(n) << " "
            << sumaRecursiva(n) << " "
            << sumaDirecta(n) << endl;
    }

    return 0;
}