#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Trans_Rec.h"

namespace Tp2_Act_1{
    
    class File {
        protected:
            std::fstream Archivo;
            std::string ruta;
            char FileType;
            Tp2_Act_1::Trans_Rec Mje; 

        public:
            File(std::fstream Archivo, std::string ruta, char FileType, Tp2_Act_1::Trans_Rec &Mje);

            bool abrir( std::ios::openmode modo);

            void File::Formato();

            std::uintmax_t File::getTamano();

            std::string interpretar(const std::string& input, char formato);

            std::string getFechaDeCreacion(); 

            std::vector<std::string> File::Separador(std::string str);

            void File::escribir(const std::string& data, int Saltos_de_Linea);

            void escribir(std::string& data, int Linea);

            std::string leer();

            void cerrar();
    };
}

#endif