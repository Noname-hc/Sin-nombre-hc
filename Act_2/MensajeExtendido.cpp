#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <fstream>

#include "MensajeExtendido.h"


MensajeExtendido::MensajeExtendido(std::string Nombre, int codigo, std::vector<datos> dato, std::string userId, std::string deviceId):Mensaje(Nombre, codigo, dato){

    this->deviceId = deviceId;
    this->userId = userId;
} 
MensajeExtendido::MensajeExtendido(std::string Nombre, int codigo, std::string userId, std::string deviceId):Mensaje(Nombre, codigo){

    this->deviceId = deviceId;
    this->userId = userId;
} 

void MensajeExtendido::setUserId(const std::string& u) { 
    userId = u; 
}

std::string MensajeExtendido::getUserId() {
     return userId; 
}

void MensajeExtendido::setDeviceId(const std::string& d) { 
    deviceId = d; 

}

std::string MensajeExtendido::getDeviceId() { 
    return deviceId;
}

void MensajeExtendido::LoadFromFile() {
    std::fstream fs("./" + Nombre, std::ios::ate | std::ios::out | std::ios::in);
    if (!fs) throw std::runtime_error("No se puede abrir archivo para lectura: " + Nombre);

    V_dato.clear();
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
        } else if (key == "UserId") {
            try {
                int v = std::stoi(value);
                V_dato.push_back(v);
            } catch (...) {
                // si no se puede convertir, ignorar o añadir 0
                V_dato.push_back(0);
            }
        } else if (key == "DeviceId") {
            V_dato.push_back(value);
        } else {
            // desconocido -> ignorar
        }
    }
    fs.close();
}