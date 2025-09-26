#ifndef APP_H
#define APP_H

#include "File.h"
#include "Trans_Rec.h"

namespace Tp2_Act_1 {

    class App {
    private:
        File* file;
        Trans_Rec* comunicacion;

    public:
        App(File* file, Trans_Rec* comunicacion);
        void Mostrar_Archivo();
        void Pedir_Datos();
    };

}

#endif