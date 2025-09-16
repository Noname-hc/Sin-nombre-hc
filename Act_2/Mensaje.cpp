#include <iostream>
#include <string>
#include <variant>

#include "Mensaje.h"

Mensaje::Mensaje(int codigo, std::vector<datos> V_dato){
    this->codigo = codigo;
    this->V_dato = V_dato;
}


//====================================================================================================================
std::vector<datos> Mensaje::GetMensaje(){
    return V_dato;
}

void Mensaje::SetMensaje(std::vector<datos> V_dato){
    this->V_dato = V_dato;
}

void Mensaje::EscribirLinea(int linea, datos cadena){
    V_dato[linea + 1] = cadena;
}

void Mensaje::BorrarLinea(int linea){
    V_dato.erase(V_dato.begin() + linea );
}

//===================================================================================================================
void Mensaje::SetCode(int codigo){
    this->codigo = codigo;
}
int Mensaje::GetCode(){
    return codigo;
}