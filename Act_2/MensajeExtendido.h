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
    MensajeExtendido(int codigo = 0, std::vector<datos> dato, std::string userId, std::string deviceId):Mensaje(codigo, dato) {}

    void setUserId(const std::string& u);

    std::string getUserId();

    void setDeviceId(const std::string& d);

    std::string getDeviceId();
};


#endif