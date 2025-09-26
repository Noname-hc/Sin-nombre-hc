#ifndef TRANS_REC_H
#define TRANS_REC_H

#include <iostream>
#include <string>
#include <cstdint>   // para uint8_t

namespace Tp2_Act_1 {
    class Trans_Rec {
    protected:
        std::string cadena;
        bool T_r;
        int fd; // descriptor de archivo del puerto serie

    public:
        Trans_Rec(bool T_r);
        ~Trans_Rec();

        // Brate ahora acepta un entero (ej. 19200) y el cpp lo mapea internamente
        void T_R_Init(int Brate, uint8_t Stop_bits, std::string Port);

        // Lectura de una línea completa hasta '\n'
        void Recepcion(char* Buffer, int Buff_Len, int timeout_ms = 500);
        void SetCadena(const std::string& nuevaCadena);
        void Transmision(std::string& Mensaje);
        void Show_Str(std::string Mensaje);
        std::string GetCadena();

        // limpia el buffer de entrada del puerto (tcflush)
        void ClearInput();
    };
}

#endif