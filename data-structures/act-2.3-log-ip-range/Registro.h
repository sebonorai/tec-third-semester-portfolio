/*
 * Registro.h
 * Act 2.3 - TC1031 Programación de estructuras de datos y algoritmos fundamentales
 *
 * Representa una línea de la bitácora con el formato:
 *   Mes Día HH:MM:SS IP:Puerto Razón de la falla
 * Ejemplo:
 *   Oct 9 10:32:24 423.2.230.77:6166 Failed password for illegal user guest
 *
 * La IP se convierte a un número (claveIP) para compararla numéricamente
 * octeto por octeto y no como texto ("9.x" debe ir antes que "10.x").
 * Se usa base 1000 por octeto porque la bitácora puede traer octetos > 255.
 */
#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include <sstream>

class Registro {
public:
    std::string mes;     // Mes abreviado (Jun, Jul, ...)
    int dia;             // Día del mes
    std::string hora;    // Hora en formato HH:MM:SS
    std::string ip;      // IP sin puerto
    int puerto;          // Puerto
    std::string razon;   // Razón de la falla
    long long claveIP;   // IP convertida a número para comparar

    /*
     * Constructor por defecto: registro vacío.
     * Complejidad: O(1)
     */
    Registro() : dia(0), puerto(0), claveIP(0) {}

    /*
     * Constructor para búsquedas: registro que solo tiene IP y puerto.
     * Parámetros: ip - IP sin puerto; puerto - puerto a usar como límite.
     * Complejidad: O(1) (la IP tiene longitud acotada)
     */
    Registro(const std::string& ip, int puerto)
        : dia(0), ip(ip), puerto(puerto), claveIP(ipANumero(ip)) {}

    /*
     * Constructor a partir de una línea de la bitácora.
     * Separa mes, día, hora, IP:puerto y razón.
     * Parámetros: linea - texto de una línea del archivo.
     * Complejidad: O(L), con L la longitud de la línea.
     */
    explicit Registro(const std::string& linea) : dia(0), puerto(0), claveIP(0) {
        std::stringstream ss(linea);
        std::string ipPuerto;
        ss >> mes >> dia >> hora >> ipPuerto;
        std::getline(ss, razon);
        if (!razon.empty() && razon[0] == ' ') {
            razon.erase(0, 1);   // Quita el espacio que separa la razón
        }
        size_t pos = ipPuerto.find(':');
        if (pos != std::string::npos) {
            ip = ipPuerto.substr(0, pos);
            puerto = std::stoi(ipPuerto.substr(pos + 1));
        } else {
            ip = ipPuerto;
        }
        claveIP = ipANumero(ip);
    }

    /*
     * ipANumero: convierte una IP "a.b.c.d" a un número a*10^9 + b*10^6 + c*10^3 + d,
     * lo que preserva el orden numérico octeto por octeto.
     * Si la cadena trae ":puerto" lo ignora.
     * Parámetros: texto - IP en texto.
     * Regresa: la clave numérica, o -1 si el formato es inválido.
     * Complejidad: O(1) (la IP tiene longitud acotada)
     */
    static long long ipANumero(const std::string& texto) {
        std::string s = texto.substr(0, texto.find(':'));
        long long clave = 0;
        int octetos = 0;
        std::stringstream ss(s);
        std::string parte;
        while (std::getline(ss, parte, '.')) {
            if (parte.empty() || parte.size() > 3) return -1;
            for (char c : parte) {
                if (c < '0' || c > '9') return -1;
            }
            clave = clave * 1000 + std::stoi(parte);
            octetos++;
        }
        return (octetos == 4) ? clave : -1;
    }

    /*
     * operator<: compara primero por IP y, en empate, por puerto.
     * Complejidad: O(1)
     */
    bool operator<(const Registro& otro) const {
        if (claveIP != otro.claveIP) return claveIP < otro.claveIP;
        return puerto < otro.puerto;
    }

    /*
     * operator<=: menor o igual, usando operator<.
     * Complejidad: O(1)
     */
    bool operator<=(const Registro& otro) const {
        return !(otro < *this);
    }

    /*
     * toString: reconstruye la línea con el mismo formato de la bitácora.
     * Complejidad: O(L), con L la longitud de la línea.
     */
    std::string toString() const {
        return mes + " " + std::to_string(dia) + " " + hora + " " +
               ip + ":" + std::to_string(puerto) + " " + razon;
    }
};

#endif // REGISTRO_H
