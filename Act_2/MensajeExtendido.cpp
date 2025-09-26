#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <cmath>

#include <fstream>
#include <filesystem>

#include "MensajeExtendido.h"


MensajeExtendido::MensajeExtendido(std::string Nombre, int codigo, std::vector<datos> dato, std::string userId, std::string deviceId):Mensaje(Nombre, codigo, dato){

    this->deviceId = deviceId;
    this->userId = userId;
} 
MensajeExtendido::MensajeExtendido(std::string Nombre, int codigo, std::string userId, std::string deviceId):Mensaje(Nombre, codigo){

    this->deviceId = deviceId;
    this->userId = userId;
} 
MensajeExtendido::~MensajeExtendido(){
    //El destructor es vacio porque cuando llame delete Nodo_1, por ejemplo, se van a eliminar 2 veces ya que se llama primero 
    //Al destructor este y luego al de la clase padre, lo que pasa es que eso da error
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



void MensajeExtendido::VerParametros(){

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
            if(Mensaje == "UserId" || Mensaje == "userId"){
                this->userId = std::get<int>(V_dato[i+1]);
            }
            if(Mensaje == "DeviceId" || Mensaje == "deviceId"){
                this->deviceId = std::get<int>(V_dato[i+1]);
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
    std::cout << "UserId: " << userId << std::endl;
    std::cout << "DeviceId: " << deviceId << std::endl;
}
