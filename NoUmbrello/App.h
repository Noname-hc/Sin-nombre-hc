#ifndef APP_H
#define APP_H

#include <iostream>

#include "Trans_Rec.h"
#include "File.h"



namespace Tp2_Act_1{

    class App{ 
        private:
            File file;
            Trans_Rec Comunicacion;

        public:
            App(File _file, Trans_Rec _Comunicacion);
            void Mostrar_Archivo();
            void Pedir_Datos();


    };

}

#endif