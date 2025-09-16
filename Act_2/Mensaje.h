#ifndef MENSAJE
#define MENSAJE


#include <iostream>
#include <string>
#include <variant>
#include <vector>

using datos = std::variant<int, std::string>;

class Mensaje{
    protected:
        int codigo; 
        std::vector<datos> V_dato;

    public:
        Mensaje(int codigo, std::vector<datos> dato);
        


        std::vector<datos> GetMensaje();

        void SetMensaje(std::vector<datos> V_dato);

        void EscribirLinea(int linea, datos cadena);

        void BorrarLinea(int linea);



        void SetCode(int codigo);

        int GetCode();

};




#endif