#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>

#include "Trans_Rec.h"
#include "File.h"


namespace Tp2_Act_1{

    File::File(std::fstream Archivo, std::string ruta, char FileType, Tp2_Act_1::Trans_Rec &Mje){
        this->Archivo = Archivo;
        this->ruta = ruta;
        this->FileType = FileType;
        this->ruta = ruta;
        this->Mje = Mje;
        
    }

    bool File::abrir(std::ios::openmode modo){
        // Los modos posibles son: in, out, app, binary
        Archivo.open(ruta, modo);
        return Archivo.is_open();
    }

    void File::escribir(const std::string& data, int Saltos_de_Linea){
        if (Archivo.is_open()) {
            Archivo << data;

            for (int i = 0; i <= Saltos_de_Linea; i++){
                std::cout << std::endl;
            }
        }
    }


    std::uintmax_t File::getTamano() {
        try {
            return std::filesystem::file_size(ruta);
        } catch (std::filesystem::filesystem_error& e) {
            std::cerr << "Error obteniendo tamaño: " << e.what() << std::endl;
            return 0;
        }
    }


    std::string File::getFechaDeCreacion() {
        try {
            auto ftime = std::filesystem::last_write_time(ruta);
            auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                ftime - decltype(ftime)::clock::now() + std::chrono::system_clock::now()
            );

            std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);

            std::stringstream ss;
            ss << std::put_time(std::localtime(&cftime), "%Y-%m-%d %H:%M:%S");
            return ss.str();
        } catch (std::filesystem::filesystem_error& e) {
            std::cerr << "Error obteniendo fecha: " << e.what() << std::endl;
            return "Fecha no disponible";
        }
    }


    std::string interpretar(const std::string& input, char formato){
        std::string key, value;

        switch(formato) {
            case 'x': { // XML <key>value</key>
                size_t ini = input.find('<');
                size_t fin = input.find('>');
                size_t cierre = input.rfind('<');
                if (ini != std::string::npos && fin != std::string::npos && cierre != std::string::npos) {
                    key = input.substr(ini + 1, fin - ini - 1);
                    value = input.substr(fin + 1, cierre - fin - 1);
                }
                break;
            }
            case 'j': { // JSON { "key": value }
                size_t ini = input.find('"');
                size_t fin = input.find('"', ini + 1);
                size_t colon = input.find(':', fin);
                if (ini != std::string::npos && fin != std::string::npos && colon != std::string::npos) {
                    key = input.substr(ini + 1, fin - ini - 1);
                    value = input.substr(colon + 1);
                    // limpiar espacios
                    if (!value.empty() && value[0] == ' ') value.erase(0,1);
                    if (!value.empty() && value.back() == '}') value.pop_back();
                }
                break;
            }
            case 'c': { // CSV key,value
                size_t pos = input.find(',');
                if (pos != std::string::npos) {
                    key = input.substr(0, pos);
                    value = input.substr(pos + 1);
                }
                break;
            }
            default:
                return "Formato no reconocido";
        }

        //return key + ": " + value;
        return value;
    }


    std::vector<std::string> File::Separador(std::string str){ // Separa un string por sus \n
        bool NotEnd = true;
        int i = -1; 

        std::vector<std::string> listas;
        std::string lista = ""; 

        while (NotEnd){

            size_t j = str.find('\n');
                            
            if(j > 10000){ //Parada
                NotEnd = false;
            } else {
                lista.append(str.substr(i+1, j-(i+1) ) );

                //Recurrencia
                i = j;
            }
        }

        return listas;

    }

    void File::Formato(){
        std::string str_file = "";
        std::vector<std::string> Vec;

        int n = 0;
        std::string espacios = "";
        int TamDeLinea = 0;
        std::string str_aux;


        str_file = "Directorio: ./mios/";
        escribir(str_file, 0);

        str_file = "Archivo: Datos1.csv";
        escribir(str_file, 1);

        str_file = "Fecha de modificacion: " + getFechaDeCreacion();
        escribir(str_file, 1);

        str_file = "Tamaño: " + std::to_string(getTamano());
        escribir(str_file,1);

        str_file = "Contenido: ";
        escribir(str_file,1);

        str_file = "Id Dispositivo     Apertura     Nivel     Caudal";
        escribir(str_file, 1);

        Vec = Separador(Mje.GetCadena());

        for (int i = 2; i < Vec.size()-1; i++){

            if (i = 2){
                str_aux = interpretar(Vec[i], FileType);
                escribir("     " + str_aux, 0);

            } else if(i = 3){
                str_aux = interpretar(Vec[i], FileType);
                TamDeLinea = str_aux.size();
                espacios = "";
                

                n = str_file.find("Apertura");
                for (int j = 0; j < (n - TamDeLinea);j++){ 
                    espacios += " ";
                }
                escribir(espacios + str_aux, 0);

            } else if(i = 4){
                str_aux = interpretar(Vec[i], FileType);
                TamDeLinea = str_aux.size();
                espacios = "";
                
                n = str_file.find("Nivel");
                for (int j = 0; j < (n - TamDeLinea);j++){ 
                    espacios += " ";
                }
                escribir(espacios + str_aux, 0);

            } else if(i = 5){
                str_aux = interpretar(Vec[i], FileType);
                TamDeLinea = str_aux.size();
                espacios = "";
                
                n = str_file.find("Caudal");
                for (int j = 0; j < (n - TamDeLinea);j++){ 
                    espacios += " ";
                }
                escribir(espacios + str_aux, 0);
            }

        }
    }

    std::string File::leer(){
        std::string linea, contenido;
        if (Archivo.is_open()){
            while (std::getline(Archivo, linea)){
                contenido += linea + "\n";
            }
        }
        return contenido;
    }

    void File::cerrar(){
        if (Archivo.is_open()) {
            Archivo.close();
        }
    }
}