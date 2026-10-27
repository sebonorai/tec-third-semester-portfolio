/*
 * main.cpp
 * Act 2.3 - Actividad Integral estructura de datos lineales
 * TC1031 Programación de estructuras de datos y algoritmos fundamentales
 *
 * Integrantes: Sebastián Noriega Olavarrieta, Sebastián Huerta
 *
 * Descripción:
 *   1. Lee bitacora.txt y guarda cada registro en una lista simplemente encadenada.
 *   2. Ordena la lista por IP (y puerto) con Merge Sort directamente sobre los nodos.
 *   3. Solicita al usuario la IP de inicio y la IP de fin.
 *   4. Despliega los registros de la IP de inicio y de la IP de fin.
 *   5. Despliega todos los registros dentro del rango de IPs.
 *
 * Compilación: g++ -std=c++17 -o act23 main.cpp
 */
#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"
#include "Registro.h"

using namespace std;

const int PUERTO_MIN = 0;        // Puerto menor posible (límite inferior de búsqueda)
const int PUERTO_MAX = 99999;    // Puerto mayor que cualquiera de la bitácora

/*
 * leerBitacora: abre el archivo y agrega cada línea no vacía como un Registro
 * al final de la lista.
 * Si no encuentra el archivo en la carpeta de ejecución, lo busca en la carpeta
 * padre (útil en CLion, que ejecuta desde cmake-build-debug).
 * Parámetros: nombre - nombre del archivo; lista - lista donde se guardan los datos.
 * Regresa: true si se pudo abrir el archivo, false en otro caso.
 * Complejidad: O(n), con n el número de líneas (addLast es O(1)).
 */
bool leerBitacora(const string& nombre, LinkedList<Registro>& lista) {
    ifstream archivo(nombre);
    if (!archivo.is_open()) {
        archivo.open("../" + nombre);
        if (!archivo.is_open()) {
            return false;
        }
    }
    string linea;
    while (getline(archivo, linea)) {
        if (!linea.empty() && linea.back() == '\r') {
            linea.pop_back();   // Por si el archivo tiene fin de línea de Windows
        }
        if (!linea.empty()) {
            lista.addLast(Registro(linea));
        }
    }
    archivo.close();
    return true;
}

/*
 * pedirIP: solicita una IP al usuario hasta que tenga un formato válido.
 * Acepta "a.b.c.d" o "a.b.c.d:puerto" (el puerto se ignora).
 * Parámetros: mensaje - texto a mostrar al usuario.
 * Regresa: la IP capturada sin puerto.
 * Complejidad: O(1) por intento (la IP tiene longitud acotada).
 */
string pedirIP(const string& mensaje) {
    string ip;
    while (true) {
        cout << mensaje;
        cin >> ip;
        ip = ip.substr(0, ip.find(':'));
        if (Registro::ipANumero(ip) >= 0) {
            return ip;
        }
        cout << "  IP invalida. Usa el formato a.b.c.d (por ejemplo 10.15.176.241)\n";
    }
}

/*
 * desplegarIP: despliega todos los registros de una IP específica (cualquier puerto).
 * Parámetros: lista - lista ordenada; ip - IP a buscar; etiqueta - título a mostrar.
 * Complejidad: O(n) en el peor caso (ver LinkedList::printRange).
 */
void desplegarIP(const LinkedList<Registro>& lista, const string& ip, const string& etiqueta) {
    cout << "\n--- Registros de la IP de " << etiqueta << " (" << ip << ") ---\n";
    int n = lista.printRange(Registro(ip, PUERTO_MIN), Registro(ip, PUERTO_MAX));
    if (n == 0) {
        cout << "No hay registros con esa IP.\n";
    } else {
        cout << "Total: " << n << " registro(s)\n";
    }
}

/*
 * desplegarRango: despliega todos los registros con IP entre ipInicio e ipFin (inclusivo).
 * Parámetros: lista - lista ordenada; ipInicio, ipFin - límites del rango.
 * Complejidad: O(n) en el peor caso (ver LinkedList::printRange).
 */
void desplegarRango(const LinkedList<Registro>& lista, const string& ipInicio, const string& ipFin) {
    cout << "\n--- Registros en el rango " << ipInicio << " a " << ipFin << " ---\n";
    int n = lista.printRange(Registro(ipInicio, PUERTO_MIN), Registro(ipFin, PUERTO_MAX));
    if (n == 0) {
        cout << "No hay registros en ese rango.\n";
    } else {
        cout << "Total: " << n << " registro(s)\n";
    }
}

/*
 * main: coordina la lectura, el ordenamiento y las búsquedas.
 * Permite hacer varias búsquedas hasta que el usuario decida salir.
 * Complejidad: O(n log n) por el ordenamiento, más O(n) por cada búsqueda.
 */
int main() {
    LinkedList<Registro> bitacora;

    // 1. Lectura de datos - O(n)
    if (!leerBitacora("bitacora.txt", bitacora)) {
        cout << "No se pudo abrir bitacora.txt\n";
        return 1;
    }
    cout << "Registros leidos: " << bitacora.getSize() << "\n";

    // 2. Ordenamiento por IP con Merge Sort sobre la lista - O(n log n)
    bitacora.sort();
    cout << "Bitacora ordenada por IP.\n";

    // 3 a 5. Búsquedas - O(n) cada una
    string opcion = "s";
    while (opcion == "s" || opcion == "S") {
        string ipInicio = pedirIP("\nIP de inicio: ");
        string ipFin = pedirIP("IP de fin: ");

        // Si el usuario las da al revés, se intercambian
        if (Registro::ipANumero(ipFin) < Registro::ipANumero(ipInicio)) {
            swap(ipInicio, ipFin);
            cout << "(La IP de inicio era mayor que la de fin; se intercambiaron.)\n";
        }

        desplegarIP(bitacora, ipInicio, "inicio");
        desplegarIP(bitacora, ipFin, "fin");
        desplegarRango(bitacora, ipInicio, ipFin);

        cout << "\nOtra busqueda? (s/n): ";
        cin >> opcion;
    }

    return 0;
}
