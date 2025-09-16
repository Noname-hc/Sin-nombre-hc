#include <iostream>
#include <string>
#include <variant>
#include <vector>

#include "MensajeExtendido.h"


MensajeExtendido::MensajeExtendido(int codigo = 0, std::vector<datos> dato, std::string userId, std::string deviceId):Mensaje(codigo, dato){

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