#ifndef MENSAJE_EX
#define MENSAJE_EX

#include <iostream>
#include <string>
#include <vector>
#include <variant>

#include "Mensaje.h"

class MensajeExtendido : public Mensaje {
private:
    std::string userId;
    std::string deviceId;

public:
    MensajeExtendido(std::string Nombre, int codigo, std::vector<datos> dato, std::string userId, std::string deviceId);
    MensajeExtendido(std::string Nombre = "Nodo_n", int codigo = 0, std::string userId = "0", std::string deviceId = "0");

    void setUserId(const std::string& u);

    std::string getUserId();

    void setDeviceId(const std::string& d);

    std::string getDeviceId();


    void LoadFromFile();
};


#endif