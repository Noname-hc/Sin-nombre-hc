#include <iostream>
#include <string>
#include <variant>
#include <array>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <cmath>

#include "Mensaje.h"

Mensaje::Mensaje(std::string Nombre, int codigo, std::vector<datos> V_dato){
    this->codigo = codigo;
    this->V_dato = V_dato;
}
Mensaje::Mensaje(std::string Nombre, int codigo){
    this->codigo = codigo;
}
Mensaje::~Mensaje(){
    try{
        if(std::filesystem::remove("./" + Nombre)){
            std::cout << Nombre << " eliminado" << std::endl;
        }else{
            std::cout << "No se pudo eliminar (no existe?): " << Nombre << "\n";
        } 
    }catch(const std::filesystem::filesystem_error& e) {
        std::cerr << "Error al borrar: " << e.what() << std::endl;
    }
}

//--------------------------------------------------------------------------------------------------------------------
void Mensaje::SetName(std::string Nombre){
    this->Nombre = Nombre;
}

int Mensaje::GetCode(){
    return this->codigo;
}
void Mensaje::SetCode(int codigo){
    this->codigo = codigo;
}
//====================================================================================================================

void Mensaje::EscribirArchivo(int linea, std::string &frase) {
    if (linea < 1) {
        std::cerr << "Linea invalida: " << linea << std::endl;
        return;
    }

    // Abrir para lectura
    std::ifstream in("./" + Nombre);
    if (!in.is_open()) {
        std::cerr << "No se puede abrir archivo para lectura: " << Nombre << std::endl;
        return;
    }

    // Leer todo el archivo en un vector de lineas
    std::vector<std::string> lines;
    std::string tmp;
    while (std::getline(in, tmp)) {
        lines.push_back(tmp); // getline elimina el '\n'
    }
    in.close();

    // La linea solicitada debe existir (segun tu requisito original)
    if ((int)lines.size() < linea) {
        std::cerr << "No se puede sobreescribir la linea porque no existe (lineas=" 
                  << lines.size() << ", solicitada=" << linea << ")" << std::endl;
        return;
    }

    // Preparar la nueva linea: escribir frase y, si es mas corta, rellenar con espacios
    std::string nueva = frase;
    std::size_t oldlen = lines[linea-1].size();
    if (nueva.size() < oldlen) {
        nueva.append(oldlen - nueva.size(), ' ');
    }
    // Si nueva.size() > oldlen dejamos que crezca; si quieres truncar:
    // if (nueva.size() > oldlen) nueva.resize(oldlen);

    // Reemplazar la linea en memoria
    lines[linea-1] = nueva;

    // Reescribir todo el archivo (modo trunc)
    std::ofstream out("./" + Nombre, std::ios::out | std::ios::trunc);
    if (!out.is_open()) {
        std::cerr << "No se pudo abrir archivo para escritura: " << Nombre << std::endl;
        return;
    }

    for (size_t i = 0; i < lines.size(); ++i) {
        out << lines[i];
        if (i + 1 < lines.size()) out << '\n';
    }
    out.close();
}
void Mensaje::EscribirArchivo(std::string frase){
    std::fstream fs("./" + Nombre, std::ios::app | std::ios::out | std::ios::in);
    fs << frase << std::endl;
    fs.close();
}

//------------------------------------------------------------------------------------------------------------------------------------------------
void Mensaje::BuscarDato(){// Se necesita que el archivo exista
    std::fstream fs("./" + Nombre, std::ios::in);

    if (!fs) {
        std::cerr << "No se puede abrir archivo para lectura: " + Nombre;

    }else{
        std::string str_aux = "";
        size_t pos = 0;

        std::string Palabra = "";
        int valor = 0;
        std::string value_str;
        V_dato.clear();
        while(getline(fs, str_aux)){
            
            pos = str_aux.find(":");
            if(pos != std::string::npos){
                Palabra = str_aux.substr(0,pos);
                
                value_str = str_aux.substr(pos+1, str_aux.size());
                valor = std::stoi(value_str);

                V_dato.push_back(Palabra);
                V_dato.push_back(valor);
            }
        }
        fs.close();
    }
}

void Mensaje::CargarInfo(const std::string &Ruta){// Se necesita que el archivo exista
    this->BuscarDato();

    std::fstream fs(Ruta, std::ios::in | std::ios::out | std::ios::app);

    if(!fs){
        std::cerr << "No se puede abrir archivo para lectura: " + Nombre;
    
    }else if(V_dato.size() > 1){
        std::string Mensaje;
        int j = 0;

        for(int i = 0; i < V_dato.size(); i++){
            
            if(std::holds_alternative<int>(V_dato[i])){
                Mensaje = std::to_string(std::get<int>(V_dato[i]));
            }else{
                Mensaje = std::get<std::string>(V_dato[i]);
            }

            if(i>0){
                j = std::pow(-1, i);
                if(j<0){
                    fs << ":";
                }else if(j>0){
                    fs << std::endl;
                }
            }
            fs << Mensaje;
        }
        fs.close();
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------
// Imprime el contenido
void Mensaje::PrintFile() {

    std::string str_aux;
    std::fstream fs("./" + Nombre, std::ios::app | std::ios::in);

    while(getline(fs, str_aux)) {
        std::cout << str_aux << std::endl;
    }
    fs.close();
    
}

void Mensaje::VerParametros(){

    this->BuscarDato();
    std::string Mensaje = "";

    for (int i = 0; i < V_dato.size() ; i++){

        if(std::holds_alternative<int>(V_dato[i])){
            Mensaje = std::to_string(std::get<int>(V_dato[i]));
        }else{
            Mensaje = std::get<std::string>(V_dato[i]);

            if(Mensaje == "Codigo" || Mensaje == "codigo"){
                this->codigo = std::get<int>(V_dato[i+1]);
            }
        }

        if(i>0){
            int j = std::pow(-1, i);
            if(j<0){
                std::cout << ":";
            }else if(j>0){
                std::cout << std::endl;
            }
        }
        std::cout << Mensaje;

        
    }
    std::cout << std::endl << std::endl << "Los atributos propios de la clase son: " << std::endl;
    std::cout << "Codigo: " << codigo << std::endl;
}