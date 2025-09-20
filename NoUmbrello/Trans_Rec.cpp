#include <iostream>
#include <string>
#include <vector>

// Includes para manejo del puerto serie en POSIX
#include <fcntl.h>
#include <termios.h>
#include <unistd.h> //Para read() y write()

#include "Trans_Rec.h"


namespace Tp2_Act_1{

    Trans_Rec::Trans_Rec(std::string cadena, bool T_r){ //Constructor
        this->cadena = cadena;
        this->T_r = T_r;
        this->fd = -1; //Empiza con un valor invalido
    }

    Trans_Rec::~Trans_Rec(){ // Destructor que solo se encarga de cerrar el puerto
        if(fd >= 0){
            close(fd);
        }
    }

    void Trans_Rec::T_R_Init(int Brate, u_int8_t Stop_bits, std::string Port){

        bool Iniciar = false;// Bandera que indica si se abrio el puerto de manera correcta

        // Sector en donde abrimos el puerto
        if(Port.size() == 4 && Port.substr(0, 3) == "com" && isdigit(Port[3])){
            int num = Port[3] - '0'; // por como es el codi ASCII si le restamos el caracter 0 (48)
                                     // a algun caracter de numero, obtenemos su valor real al convertirlo a entero
                                     // ya que despues del 48 van en orden e int devuelve el valor en ASCII 
            if(num >= 1 && num <= 9){

                std::string PortFile = "/dev/ttyS" + std::to_string(num-1);
                fd = open(PortFile.c_str(), O_NOCTTY | O_NDELAY | O_RDWR); // Abrimos el archivo del puerto para que se pueda 
                                                                               // Leer y escribir, que no se bloquee si no hay datos
                                                                               // y evitamos que se convierta en la terminal

                if (fd > 0){
                    Iniciar = true;
                }
            }else{
                std::cout << "número fuera de rango" << std::endl;
            }
        }else{
            std::cout << "puerto invalido" << std::endl;
        }

        // Inicializamos el puerto
        // Primero obtenemos el puntero a la estructura de condiguracion del puerto
        if (Iniciar){

            struct termios options;
            if(tcgetattr(fd, &options) == -1){ // Con esto options toma el valor del puntero a la struct de la configuracion
                std::cerr << ("Error al obtener la configuracion") << std::endl;
            }

            options.c_cflag |= CS8; // Palabra de 8 bits
            options.c_cflag |= CREAD; //Habilita lectura
            options.c_cflag |= CLOCAL; // No se para si no hay control de modem
            options.c_cflag &= ~PARENB; // Deshabilitamos paridad
            if (Stop_bits == 1){
                options.c_cflag &= ~CSTOPB; // Desabilitamos los 2 bits de stop para que quede en 1 solo
            }else{
                options.c_cflag |= CSTOPB;
            } 

            options.c_cc[VMIN] = 1; // Lectura bloquente hasta que llegue 1 byte
            options.c_cc[VTIME] = 0; // Lectura no bloqueante por tiempo
            tcsetattr(fd, TCSANOW, &options); // TCSANOW hace que se setee la configuracion al instante

            cfsetispeed(&options, Brate); // Velocidad de entrada
            cfsetospeed(&options, Brate); // Velocidad de salida
        }

    }

    void Trans_Rec::Recepcion(char* Buffer, int Buff_Len){ //Pasamos el buffer por referencia
        int n = read(fd, Buffer, Buff_Len-1); // n funciona como bandera y a la vez da la cantidad de bits recibidos
                                 // El -1 es para '\0'

        if (n < 0){
            perror("error al leer");
        } else if(n == 0){
            //No llegaron datos
        } else if(n > 0 ){
            Buffer[n] = '\0'; //Termina como string
            cadena += Buffer;
            //Se recibieron los datos pero esto se trabaja en la clase File
        }
    }

    void Trans_Rec::Transmision(std::string& Mensaje){

        int n = write(fd, Mensaje.c_str(), Mensaje.size());
        
        if (n < 0){
            perror("error al enviar el mensaje");
        }
    }

    void Trans_Rec::Show_Str(std::string Mensaje){
        std::cout << Mensaje << std::endl;
    }

    std::string Trans_Rec::GetCadena(){
        return cadena;
    }
}