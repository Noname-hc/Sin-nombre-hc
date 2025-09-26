#include <iostream>
#include <vector>
#include <string>

#include "Mensaje.h"
#include "MensajeExtendido.h"

void ComandoEscritura(std::string nodo, Mensaje *Nodo_1, MensajeExtendido *Nodo_2);

int main(int argc, char* argv[]) {
    Mensaje* Nodo_1 = new Mensaje();
    Nodo_1->SetName("Nodo_1.txt");

    MensajeExtendido* Nodo_2 = new MensajeExtendido();
    Nodo_2->SetName("Nodo_2.txt");

    bool interpretar = true;
    std::string comando = " ";

    if (argc >= 3){
        comando = std::string(argv[argc-3]) + " " + std::string(argv[argc-2]) + " " + std::string(argv[argc-1]);
        std::cout << std::endl;
    }

    while (interpretar){
        std::cout << ("Comandos:") << std::endl;
        std::cout << "__________" << std::endl << std::endl;

        std::cout << ("ver nodo 1") << std::endl;
        std::cout << ("ver nodo 2") << std::endl << std::endl;

        std::cout << ("ver atributos 1") << std::endl;
        std::cout << ("ver atributos 2") << std::endl << std::endl;

        std::cout << ("escribir nodo 1") << std::endl;
        std::cout << ("escribir nodo 2") << std::endl << std::endl;

        std::cout << ("eliminar nodo 1") << std::endl;
        std::cout << ("eliminar nodo 2") << std::endl << std::endl;

        std::cout << ("cargar nodo 1") << std::endl;
        std::cout << ("(Se encarga de copiar los valores del nodo 2 en el 1, pero al final del archivo)") << std::endl <<std::endl;

        std::cout << ("cargar nodo 2") << std::endl;
        std::cout << ("(Se encarga de copiar los valores del nodo 1 en el 2, pero al final del archivo)") << std::endl << std::endl;

        //-------------------------------------------------------------------------------------------

        if(comando == "ver nodo 1"){
            Nodo_1->PrintFile();

        }else if(comando == "ver nodo 2"){
            Nodo_2->PrintFile();

        }else if(comando == "ver atributos 1"){
            Nodo_1->VerParametros();
            
        }else if(comando == "ver atributos 2"){
            Nodo_2->VerParametros();
            
        }else if(comando == "escribir nodo 1"){
            ComandoEscritura("Nodo_1", Nodo_1, Nodo_2);

        }else if(comando == "escribir nodo 2"){
            ComandoEscritura("Nodo_2", Nodo_1, Nodo_2);

        }else if(comando == "eliminar nodo 1"){
            delete Nodo_1;
            
        }else if(comando == "eliminar nodo 2"){
            delete Nodo_2;
            
        }else if(comando == "cargar nodo 1"){
            Nodo_2->CargarInfo("./Nodo_1.txt");
            
        }else if(comando == "cargar nodo 2"){
            Nodo_1->CargarInfo("./Nodo_2.txt");
        }
        
        getline(std::cin, comando);
        std::cout << std::endl;
    }
    

    return 0;
}



//======================================================  Funciones Auxiliares  ================================================================
void ComandoEscritura(std::string nodo, Mensaje *Nodo_1, MensajeExtendido *Nodo_2){
    std::string comando = "";
    std::string str_aux = "";

    std::cout << "Ingrese la linea (1, 2, ...), si no lo hace se escribira al final del codigo" << std::endl;
    std::cout << "No esta permitido acceder a lineas no escritas previamente" << std::endl;
    std::getline(std::cin, comando);

    bool Escribir_L = true;
    int linea = 1;
    bool stop = false; 

    try{
        linea = std::stoi(comando);
        
    }catch(...){
        while(!stop){
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
            std::cout << "Ya puede escribir, para parar ingrese enter y 'stop' " << std::endl;
            Escribir_L = false;
        }
    }

    if(Escribir_L){
        std::cout << "Puede escribir la linea" << std::endl;
        //std::getline(std::cin, str_aux); // Es para que no se guarde un enter indeseado 
        std::getline(std::cin, str_aux);// Guarda una linea de la terminal
        
        if(nodo == "Nodo_1"){
            Nodo_1->EscribirArchivo(linea, str_aux);

        }else if(nodo == "Nodo_2"){
            Nodo_2->EscribirArchivo(linea, str_aux);

        }
    }
}