#include <iostream>
#include <vector>
using namespace std;

// ---------------------------------------------------------------------
// Contadores globales de comparaciones.
// Se usan variables globales porque las firmas de las funciones de
// ordenamiento solo reciben el vector (Salida: Nada), tal como lo pide
// el enunciado; para poder reportar el numero de comparaciones en el
// main sin cambiar esas firmas, se acumulan aqui.
// ---------------------------------------------------------------------
long long compIntercambio = 0;
long long compBurbuja = 0;
long long compMerge = 0;
long long compSecuencial = 0;
long long compBinaria = 0;

/**
 * ordenaIntercambio
 * Descripcion : Ordena en forma ascendente el vector usando el metodo de Intercambio
 *               (compara cada elemento contra todos los que le siguen e intercambia
 *               si estan en el orden incorrecto).
 * Entrada     : v - vector<int> con los n numeros
 * Salida      : Nada (el vector se modifica en el propio parametro, por referencia)
 * Precondicion: v debe contener los n numeros
 * Postcondicion: v contendra los datos ya ordenados ascendentemente
 * Complejidad : O(n^2) en mejor, promedio y peor caso, ya que siempre recorre
 *               todos los pares (i, j) con i < j sin condicion de salida anticipada.
 */
void ordenaIntercambio(vector<int>& v) {
    int n = (int)v.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            compIntercambio++;
            if (v[i] > v[j]) {
                swap(v[i], v[j]);
            }
        }
    }
}

/**
 * ordenaBurbuja
 * Descripcion : Ordena en forma ascendente el vector usando el metodo de Burbuja
 *               (compara elementos adyacentes e intercambia si estan desordenados,
 *               "burbujeando" el mayor hacia el final en cada pasada).
 * Entrada     : v - vector<int> con los n numeros
 * Salida      : Nada
 * Precondicion: v debe contener los n numeros
 * Postcondicion: v contendra los datos ya ordenados ascendentemente
 * Complejidad : O(n^2) en mejor, promedio y peor caso. (No se agrego bandera de
 *               corte anticipado para que el conteo de comparaciones sea
 *               consistente y comparable contra ordenaIntercambio).
 */
void ordenaBurbuja(vector<int>& v) {
    int n = (int)v.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            compBurbuja++;
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

/**
 * merge (funcion auxiliar privada de ordenaMerge)
 * Combina dos sub-vectores ya ordenados v[inicio..medio] y v[medio+1..fin]
 * en un solo segmento ordenado dentro de v.
 */
void merge(vector<int>& v, int inicio, int medio, int fin) {
    vector<int> izquierda(v.begin() + inicio, v.begin() + medio + 1);
    vector<int> derecha(v.begin() + medio + 1, v.begin() + fin + 1);

    size_t i = 0, j = 0;
    int k = inicio;

    while (i < izquierda.size() && j < derecha.size()) {
        compMerge++;
        if (izquierda[i] <= derecha[j]) {
            v[k] = izquierda[i];
            i++;
        } else {
            v[k] = derecha[j];
            j++;
        }
        k++;
    }
    while (i < izquierda.size()) { v[k] = izquierda[i]; i++; k++; }
    while (j < derecha.size())   { v[k] = derecha[j];   j++; k++; }
}

/**
 * mergeSort (funcion auxiliar privada, recursiva, de ordenaMerge)
 * Divide el rango [inicio, fin] a la mitad recursivamente y llama a merge()
 * para combinar los resultados.
 */
void mergeSort(vector<int>& v, int inicio, int fin) {
    if (inicio < fin) {
        int medio = inicio + (fin - inicio) / 2;
        mergeSort(v, inicio, medio);
        mergeSort(v, medio + 1, fin);
        merge(v, inicio, medio, fin);
    }
}

/**
 * ordenaMerge
 * Descripcion : Ordena en forma ascendente el vector usando el metodo de Merge (Mezcla).
 * Entrada     : v - vector<int> con los n numeros
 * Salida      : Nada
 * Precondicion: v debe contener los n numeros
 * Postcondicion: v contendra los datos ya ordenados ascendentemente
 * Complejidad : O(n log n) en mejor, promedio y peor caso.
 */
void ordenaMerge(vector<int>& v) {
    if (!v.empty()) {
        mergeSort(v, 0, (int)v.size() - 1);
    }
}

/**
 * busqSecuencial
 * Descripcion : Busca un dato entero dentro del vector recorriendolo elemento
 *               por elemento desde el inicio.
 * Entrada     : v - vector<int> del espacio de busqueda (puede estar desordenado)
 *               dato - entero que se desea buscar
 * Salida      : el indice donde se encuentra el dato, o -1 si no se localiza
 * Precondicion: v debe contener los n numeros
 * Postcondicion: Ninguna
 * Complejidad : Mejor caso O(1) (dato en la primera posicion);
 *               peor caso y caso promedio O(n).
 */
int busqSecuencial(const vector<int>& v, int dato) {
    for (size_t i = 0; i < v.size(); i++) {
        compSecuencial++;
        if (v[i] == dato) {
            return (int)i;
        }
    }
    return -1;
}

/**
 * busqBinaria
 * Descripcion : Busca un dato entero dentro de un vector ordenado ascendentemente
 *               usando busqueda binaria.
 * Entrada     : v - vector<int> ordenado ascendentemente (espacio de busqueda)
 *               dato - entero que se desea buscar
 * Salida      : el indice donde se encuentra el dato, o -1 si no se localiza
 * Precondicion: v debe contener los n numeros ordenados en forma ascendente
 * Postcondicion: Ninguna
 * Complejidad : Mejor caso O(1) (dato en la posicion media inicial);
 *               peor caso y caso promedio O(log n).
 */
int busqBinaria(const vector<int>& v, int dato) {
    int izq = 0, der = (int)v.size() - 1;
    while (izq <= der) {
        int medio = izq + (der - izq) / 2;
        compBinaria++;
        if (v[medio] == dato) {
            return medio;
        } else if (v[medio] < dato) {
            izq = medio + 1;
        } else {
            der = medio - 1;
        }
    }
    return -1;
}

int main() {
    int n;
    cout << "Ingrese la cantidad de numeros (n): ";
    cin >> n;

    vector<int> original(n);
    cout << "Ingrese los " << n << " numeros:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> original[i];
    }

    // Se usan 3 copias independientes del arreglo original, porque cada
    // metodo de ordenamiento debe ordenar el MISMO arreglo original por
    // separado y contar sus propias comparaciones; si se reutilizara un
    // solo vector ya ordenado, los conteos de los siguientes metodos
    // quedarian artificialmente bajos.
    vector<int> vIntercambio = original;
    vector<int> vBurbuja     = original;
    vector<int> vMerge       = original;

    ordenaIntercambio(vIntercambio);
    ordenaBurbuja(vBurbuja);
    ordenaMerge(vMerge);

    // Linea 1: comparaciones de ordenaIntercambio, ordenaBurbuja y mergeSort
    cout << compIntercambio << " " << compBurbuja << " " << compMerge << endl;

    int b;
    cout << "Ingrese la cantidad de busquedas a realizar (b): ";
    cin >> b;

    vector<int> valoresBuscar(b);
    cout << "Ingrese los " << b << " valores a buscar:" << endl;
    for (int i = 0; i < b; i++) {
        cin >> valoresBuscar[i];
    }

    for (int i = 0; i < b; i++) {
        // Se reinician los contadores de busqueda en cada valor, porque
        // el reporte de comparaciones es por cada valor buscado.
        compSecuencial = 0;
        compBinaria = 0;

        int posSec = busqSecuencial(original, valoresBuscar[i]); // sobre el arreglo original (desordenado)
        int posBin = busqBinaria(vMerge, valoresBuscar[i]);      // sobre el arreglo ya ordenado

        cout << posSec << " " << compSecuencial << " "
             << posBin << " " << compBinaria << endl;
    }

    return 0;
}
