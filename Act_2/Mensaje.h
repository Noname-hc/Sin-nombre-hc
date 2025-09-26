#ifndef MENSAJE
#define MENSAJE

#include <iostream>
#include <string>
#include <variant>
#include <vector>

using datos = std::variant<int, std::string>; 
//vamos a guardar la cantidad de caracteres en una linea con el int

class Mensaje{
    protected:
        int codigo; 
        std::vector<datos> V_dato;
        std::string Nombre;

    public:
        Mensaje(std::string Nombre, int codigo, std::vector<datos> V_dato);
        Mensaje(std::string Nombre = "Nodo_n.txt", int codigo = 0);
        ~Mensaje();

        std::vector<datos> GetMensaje();

        void SetName(std::string Nombre);

        void SetCode(int codigo);

        int GetCode();

        void EscribirArchivo(int linea, std::string &frase);
        void EscribirArchivo(std::string frase);

        void CargarInfo(const std::string &Ruta);
        
        void BuscarDato();

        void PrintFile();

        virtual void VerParametros();
};




#endif