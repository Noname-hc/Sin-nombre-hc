#include <iostream>
#include <string>
#include <variant>

#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Mensaje.h"

Mensaje::Mensaje(std::string Nombre, int codigo, std::vector<datos> V_dato){
    this->codigo = codigo;
    this->V_dato = V_dato;
}
Mensaje::Mensaje(std::string Nombre, int codigo){
    this->codigo = codigo;
}

void Mensaje::SetName(std::string Nombre){
    this->Nombre = Nombre;
}
//====================================================================================================================
std::vector<datos> Mensaje::GetMensaje(){
    return V_dato;
}
//------------------------------------------------------------------------------------------------------------------------------------------------
void Mensaje::SetMensaje(std::vector<datos> V_dato){
    this->V_dato = V_dato;
}
//------------------------------------------------------------------------------------------------------------------------------------------------
void Mensaje::EscribirLinea(int linea, datos cadena){
    if (linea < 0) return;
    if (linea < V_dato.size()) {
        V_dato[linea] = cadena;
        return;
    }
    if (linea == V_dato.size()) {
        V_dato.push_back(cadena);
        return;
    }
    // linea > size: rellenamos con ints 0 hasta llegar a la posición (decisión simple)
    int current = V_dato.size();
    while (current < linea) {
        V_dato.push_back(0); // default: int 0
        ++current;
    }
    V_dato.push_back(cadena);
}
//------------------------------------------------------------------------------------------------------------------------------------------------
void Mensaje::BorrarLinea(int linea){
    if (linea < 0 || linea >= V_dato.size()) return;
    V_dato.erase(V_dato.begin() + linea );
}


//==================================  Manejo de archivos   ====================================

void Mensaje::EscribirArchivo(int linea, std::string frase) {
    std::fstream fs("./" + Nombre, std::ios::ate | std::ios::out | std::ios::in); 
    // Usamos ate para que el puntero por defecto quede al final al escribir pero se pueda mover  

    if (!fs) throw std::runtime_error("No se puede abrir archivo para escritura: " + Nombre);

    int linea_actual = 0;
    std::string str_aux;
    std::streampos pos_cursor;
    
    bool escribir = false;
    // Este while busca el puntero a la linea que se quiere escribir y en su defecto linea_actual queda
    // en la ultima posicion donde hay algo escrito
    fs.seekg(0);// Posicionamos el puntero de lectura al inicio del archivo

    while(std::getline(fs, str_aux)){ //Si ya no hay nada que leer se sale del while
        linea_actual++;// La ultima linea hasta el momento con algo escrito

        if(linea == linea_actual){
            pos_cursor = fs.tellg(); // Posicion actual del puntero de lectura modificado por getline
            escribir = true;
        }
    }
    pos_cursor = fs.tellg();
    fs.seekp(pos_cursor);

    if(!escribir){ // SI el while anterior no llego a la linea objetivo agregamos saltos de linea hasta llegar
        int sumador = 0;
        for(int i = linea_actual; i < linea-1;i++){
            fs << "\n";
            //std::getline(fs, str_aux); // Lo usamos para mover el puntero a la posicion del cursor de escritura
        }

        escribir = false;
        fs << frase << std::endl;
    }

    if (escribir){
        fs.seekp(pos_cursor); // mueve el cursor de escritura
        fs << frase << std::endl;
        escribir = false;
    }
    fs.close();
}

void Mensaje::EscribirArchivo(std::string frase){
    std::fstream fs("./" + Nombre, std::ios::app | std::ios::out | std::ios::in);
    fs << frase << std::endl;
    fs.close();
}
//------------------------------------------------------------------------------------------------------------------------------------------------
void Mensaje::LoadFromFile() {
    std::fstream fs("./" + Nombre, std::ios::ate | std::ios::out | std::ios::in);
    if (!fs) throw std::runtime_error("No se puede abrir archivo para lectura: " + Nombre);

    std::string line;
    while (std::getline(fs, line)) {
        if (line.empty()) continue;
        // separar por el primer ':'
        size_t pos = line.find(':');
        if (pos == std::string::npos) continue; // línea malformada -> ignoramos

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        if (key == "codigo") {
            try {
                codigo = std::stoi(value);
            } catch (...) {
                // si no se puede convertir, dejamos el codigo sin cambiar
            }
        } 
    }
    fs.close();
}
//------------------------------------------------------------------------------------------------------------------------------------------------
// Imprime el contenido
void Mensaje::PrintFile() {
    LoadFromFile();
    std::cout << "Codigo: " << codigo << "\n";

    std::string str_aux;
    size_t pos;
    std::fstream fs("./" + Nombre, std::ios::app | std::ios::in);

    while(getline(fs, str_aux)) {
        std::cout << str_aux << std::endl;
    }
}
