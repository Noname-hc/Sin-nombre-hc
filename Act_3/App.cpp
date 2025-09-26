#include "App.h"
#include <iostream>

namespace Tp2_Act_1 {

    App::App(File* file, Trans_Rec* comunicacion) {
        this->file = file;
        this->comunicacion = comunicacion;
    }

    void App::Mostrar_Archivo() {
        if (file->abrir(std::ios::in)) {
            std::string contenido = file->leer();
            file->cerrar();
            char tipo = file->GetFileType();
            if (tipo == 'c') {
                std::cout << "[CSV]\n" << contenido;
            } else if (tipo == 'j') {
                std::cout << "[JSON]\n";
                // Simple: cada fila como objeto json
                std::istringstream iss(contenido);
                std::string linea;
                while (std::getline(iss, linea)) {
                    if (linea.empty() || linea.find("Id Dispositivo") != std::string::npos) continue;
                    std::istringstream ls(linea);
                    std::string id, apertura, nivel, caudal;
                    ls >> id >> apertura >> nivel >> caudal;
                    std::cout << "{\"dispositivo_id\": " << id << ", \"porcentaje_valvula\": " << apertura << ", \"estado_nivel\": \"" << nivel << "\", \"caudal\": " << caudal << "},\n";
                }
            } else if (tipo == 'x') {
                std::cout << "[XML]\n";
                std::istringstream iss(contenido);
                std::string linea;
                while (std::getline(iss, linea)) {
                    if (linea.empty() || linea.find("Id Dispositivo") != std::string::npos) continue;
                    std::istringstream ls(linea);
                    std::string id, apertura, nivel, caudal;
                    ls >> id >> apertura >> nivel >> caudal;
                    std::cout << "<registro><dispositivo_id>" << id << "</dispositivo_id><porcentaje_valvula>" << apertura << "</porcentaje_valvula><estado_nivel>" << nivel << "</estado_nivel><caudal>" << caudal << "</caudal></registro>\n";
                }
            } else {
                std::cout << contenido;
            }
        } else {
            std::cout << "No se pudo abrir el archivo para lectura." << std::endl;
        }
    }

    void App::Pedir_Datos() {
        char buffer[256];
        comunicacion->Recepcion(buffer, sizeof(buffer));
        std::cout << "Datos recibidos desde Trans_Rec: " << buffer << std::endl;
    }

}