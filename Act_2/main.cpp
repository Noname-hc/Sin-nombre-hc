#include <iostream>
#include <vector>
#include <string>

#include "Mensaje.h"
#include "MensajeExtendido.h"

void ComandoEscritura(std::string nodo, Mensaje *Nodo_1, MensajeExtendido *Nodo_2);

int main(int argc, char* argv[]) {
    Mensaje* Nodo_1 = new Mensaje();
    Nodo_1->SetName("Nodo_1");

    MensajeExtendido* Nodo_2 = new MensajeExtendido();
    Nodo_2->SetName("Nodo_2");


    std::cout << ("Comandos:") << std::endl;

    std::cout << ("ver nodo 1") << std::endl;
    std::cout << ("ver nodo 2") << std::endl;

    std::cout << ("escribir nodo 1") << std::endl;
    std::cout << ("escribir nodo 2") << std::endl;
    std::cout << std::endl;

    bool interpretar = false;
    std::string comando = " ";

    while(~interpretar){
        if (argc >= 3){
            comando = std::string(argv[argc-3]) + " " + std::string(argv[argc-2]) + " " + std::string(argv[argc-1]);
            interpretar = true;
            std::cout << std::endl;
        }
    }

    while (interpretar){

        if(comando == "ver nodo 1"){
            Nodo_1->PrintFile();

        }else if(comando == "ver nodo 2"){
            Nodo_2->PrintFile();

        }else if(comando == "escribir nodo 1"){
            ComandoEscritura("Nodo_1", Nodo_1, Nodo_2);

        }else if(comando == "escribir nodo 2"){
            ComandoEscritura("Nodo_2", Nodo_1, Nodo_2);
        }
        
        comando = std::string(argv[argc-3]) + " " + std::string(argv[argc-2]) + " " + std::string(argv[argc-1]);
    }
    

    return 0;
}



//======================================================  Funciones Auxiliares  ================================================================
void ComandoEscritura(std::string nodo, Mensaje *Nodo_1, MensajeExtendido *Nodo_2){
    std::string comando = " ";
    std::string str_aux = " ";

    std::cout << "Ingrese la linea (1, 2, ...), si no lo hace se escribira al final del codigo" << std::endl;
    std::cin >> comando;

    bool Escribir_L = true;
    int linea = 1;
    bool stop = false; 

    try{
        linea = std::stoi(comando);
        
    }catch(...){
        while(!stop){
            std::cout << "Ya pauede escribir, para parar ingrese enter y 'stop' " << std::endl;
            std::getline(std::cin, str_aux); // Guarda una linea de la terminal 

            if(str_aux == "stop"){
                stop = true;// La condicion para el while se hace invalida
                continue;// Saltamos a la siguiete iteracion del while, que sale de este porque stop = true
            }
            if(nodo == "Nodo_1"){
                Nodo_1->EscribirArchivo(str_aux);

            }else if(nodo == "Nodo_2"){
                Nodo_2->EscribirArchivo(str_aux);

            }
            Escribir_L = false;
        }
    }

    if(Escribir_L){
        std::cout << "Puede escribir la linea" << std::endl;
        std::getline(std::cin, str_aux);// Guarda una linea de la terminal
        if(nodo == "Nodo_1"){
            Nodo_1->EscribirArchivo(linea, str_aux);

        }else if(nodo == "Nodo_2"){
            Nodo_2->EscribirArchivo(linea, str_aux);

        }
    }
}