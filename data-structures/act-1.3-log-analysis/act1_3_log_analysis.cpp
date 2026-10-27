/*
 * TC1031 - Act 1.3
 * Actividad Integral de Conceptos Basicos y Algoritmos Fundamentales
 * Integrantes: Sebastian Noriega Olavarrieta, Sebastian Huerta
 *
 * Lee bitacora.txt, ordena los registros por fecha con Merge Sort,
 * y localiza un rango de fechas usando busqueda binaria + barrido lineal.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// ---------------------------------------------------------------------
// Estructura que representa un registro (una linea) de la bitacora
// ---------------------------------------------------------------------
struct Registro {
    string mes;      // "Jun", "Jul", ... (3 letras, tal como viene en el archivo)
    int dia;          // 1-31
    string hora;      // "hh:mm:ss"
    string ip;         // direccion IP de origen
    int puerto;        // puerto de origen
    string razon;      // motivo de la falla
    int claveFecha;    // clave numerica para ordenar: mes*100 + dia
    int claveHora;      // hora convertida a segundos, para desempatar mismo dia
};

// ---------------------------------------------------------------------
// mesANumero: convierte "Jan".."Dec" a 1..12
// Complejidad: O(1) -- compara contra una lista fija de 12 elementos
// ---------------------------------------------------------------------
int mesANumero(const string& mes) {
    static const string meses[12] = {"Jan","Feb","Mar","Apr","May","Jun",
                                      "Jul","Aug","Sep","Oct","Nov","Dec"};
    for (int i = 0; i < 12; i++) {
        if (meses[i] == mes) return i + 1;
    }
    return -1; // mes invalido
}

// ---------------------------------------------------------------------
// horaASegundos: convierte "hh:mm:ss" a segundos totales del dia
// Complejidad: O(1) -- el string siempre tiene longitud fija (8 chars)
// ---------------------------------------------------------------------
int horaASegundos(const string& hora) {
    int h, m, s;
    sscanf(hora.c_str(), "%d:%d:%d", &h, &m, &s);
    return h * 3600 + m * 60 + s;
}

// ---------------------------------------------------------------------
// leerBitacora: abre el archivo, parsea cada linea y arma el vector
// Formato de cada linea: "Mes Dia hh:mm:ss ip:puerto Razon..."
// Complejidad: O(n) -- se procesa cada una de las n lineas una sola vez,
// y el trabajo por linea (tokenizar, convertir) es O(1)
// ---------------------------------------------------------------------
vector<Registro> leerBitacora(const string& nombreArchivo) {
    vector<Registro> registros;
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir el archivo " << nombreArchivo << endl;
        return registros;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        istringstream iss(linea);
        Registro r;
        string ipPuerto;

        iss >> r.mes >> r.dia >> r.hora >> ipPuerto;
        getline(iss, r.razon);
        // getline deja un espacio inicial (el que separa ipPuerto de la razon)
        if (!r.razon.empty() && r.razon[0] == ' ') {
            r.razon.erase(0, 1);
        }

        // separar ip:puerto en sus dos componentes
        size_t posDosPuntos = ipPuerto.rfind(':');
        if (posDosPuntos != string::npos) {
            r.ip = ipPuerto.substr(0, posDosPuntos);
            r.puerto = stoi(ipPuerto.substr(posDosPuntos + 1));
        } else {
            r.ip = ipPuerto;
            r.puerto = -1;
        }

        int numMes = mesANumero(r.mes);
        r.claveFecha = numMes * 100 + r.dia;   // ej: Jun(6) dia 20 -> 620
        r.claveHora = horaASegundos(r.hora);

        registros.push_back(r);
    }

    archivo.close();
    return registros;
}

// ---------------------------------------------------------------------
// merge: combina dos mitades ya ordenadas [izq..medio] y [medio+1..der]
// Complejidad: O(k) donde k = der - izq + 1 (tamano del segmento combinado)
// ---------------------------------------------------------------------
void merge(vector<Registro>& v, int izq, int medio, int der) {
    vector<Registro> temp;
    temp.reserve(der - izq + 1);

    int i = izq, j = medio + 1;

    while (i <= medio && j <= der) {
        bool tomaIzq;
        if (v[i].claveFecha != v[j].claveFecha)
            tomaIzq = v[i].claveFecha < v[j].claveFecha;
        else
            tomaIzq = v[i].claveHora <= v[j].claveHora; // desempate por hora

        if (tomaIzq) temp.push_back(v[i++]);
        else         temp.push_back(v[j++]);
    }
    while (i <= medio) temp.push_back(v[i++]);
    while (j <= der)   temp.push_back(v[j++]);

    for (int k = 0; k < (int)temp.size(); k++) {
        v[izq + k] = temp[k];
    }
}

// ---------------------------------------------------------------------
// mergeSort: ordena v[izq..der] por fecha (y hora como desempate)
// Complejidad: O(n log n) -- log n niveles de division, O(n) trabajo
// de merge por nivel
// ---------------------------------------------------------------------
void mergeSort(vector<Registro>& v, int izq, int der) {
    if (izq >= der) return;
    int medio = izq + (der - izq) / 2;
    mergeSort(v, izq, medio);
    mergeSort(v, medio + 1, der);
    merge(v, izq, medio, der);
}

// ---------------------------------------------------------------------
// busquedaBinariaInicio: encuentra el indice del PRIMER registro cuya
// claveFecha es >= claveInicio (lower bound). Si no existe ningun
// registro exactamente en esa fecha, regresa la posicion del primer
// registro posterior (que es donde empezaria el rango buscado).
// Precondicion: v esta ordenado por claveFecha.
// Complejidad: O(log n)
// ---------------------------------------------------------------------
int busquedaBinariaInicio(const vector<Registro>& v, int claveInicio) {
    int izq = 0, der = (int)v.size() - 1;
    int resultado = (int)v.size(); // si no se encuentra nada, queda fuera de rango

    while (izq <= der) {
        int medio = izq + (der - izq) / 2;
        if (v[medio].claveFecha >= claveInicio) {
            resultado = medio;
            der = medio - 1; // seguimos buscando hacia la izquierda por el PRIMERO
        } else {
            izq = medio + 1;
        }
    }
    return resultado;
}

// ---------------------------------------------------------------------
// pedirFecha: solicita al usuario mes (3 letras) y dia, valida el mes,
// y regresa la clave de fecha correspondiente (mes*100 + dia)
// Complejidad: O(1) por intento de lectura (mesANumero es O(1))
// ---------------------------------------------------------------------
int pedirFecha(const string& etiqueta) {
    string mes;
    int dia;
    int numMes;

    do {
        cout << "Mes de " << etiqueta << " (3 letras, ej. Jun): ";
        cin >> mes;
        if (!mes.empty()) mes[0] = toupper(mes[0]);
        for (size_t i = 1; i < mes.size(); i++) mes[i] = tolower(mes[i]);
        numMes = mesANumero(mes);
        if (numMes == -1) cout << "Mes invalido, intenta de nuevo.\n";
    } while (numMes == -1);

    cout << "Dia de " << etiqueta << " (1-31): ";
    cin >> dia;

    return numMes * 100 + dia;
}

// ---------------------------------------------------------------------
// main
// Complejidad total del programa: O(n log n), dominada por mergeSort;
// la lectura es O(n), la busqueda binaria O(log n) y el despliegue
// del rango es O(k) con k = numero de registros en el rango.
// ---------------------------------------------------------------------
int main() {
    string nombreArchivo = "bitacora.txt";

    cout << "Leyendo " << nombreArchivo << "...\n";
    vector<Registro> registros = leerBitacora(nombreArchivo);

    if (registros.empty()) {
        cout << "No se encontraron registros. Verifica el archivo.\n";
        return 1;
    }
    cout << registros.size() << " registros leidos.\n\n";

    mergeSort(registros, 0, (int)registros.size() - 1);
    cout << "Registros ordenados por fecha.\n\n";

    int claveInicio = pedirFecha("inicio");
    int claveFin = pedirFecha("termino");

    if (claveInicio > claveFin) {
        cout << "\nLa fecha de inicio es posterior a la de termino. Revisa tu rango.\n";
        return 1;
    }

    int idx = busquedaBinariaInicio(registros, claveInicio);

    cout << "\n--- Registros entre las fechas solicitadas ---\n";
    int encontrados = 0;
    while (idx < (int)registros.size() && registros[idx].claveFecha <= claveFin) {
        const Registro& r = registros[idx];
        cout << r.mes << " " << r.dia << " " << r.hora << "  "
             << r.ip << ":" << r.puerto << "  " << r.razon << "\n";
        idx++;
        encontrados++;
    }

    if (encontrados == 0) {
        cout << "No hay registros en ese rango de fechas.\n";
    } else {
        cout << "\nTotal de registros encontrados: " << encontrados << "\n";
    }

    return 0;
}
