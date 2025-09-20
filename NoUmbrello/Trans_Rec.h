#ifndef TRANS_REC_H
#define TRANS_REC_H

#include <iostream>

namespace Tp2_Act_1{

    class Trans_Rec
    {
        protected:
            std::string cadena;
            bool T_r;
            int fd; //Valor de retorno que indica si se abrio correctamente (1) o no (0) el puerto
                            //No quiero que se cambie desde el constructor

        public:
            Trans_Rec(std::string cadena, bool T_r);
            ~Trans_Rec();

            void T_R_Init(int Brate, u_int8_t Stop_bits, std::string Port);

            void Recepcion(char* Buffer, int Buff_Len);

            void Transmision(std::string& Mensaje);

            void Show_Str(std::string Mensaje);

            std::string GetCadena();
    };

}


#endif