#include <iostream>
#include <string>
#include <unistd.h>   // usleep
#include "File.h"
#include "Trans_Rec.h"
#include "App.h"
#include "termios.h"

using namespace Tp2_Act_1;

int main(int argc, char* argv[]) {
    char modo = ' ';
    char tipo = ' ';
    int numLecturas = 0;
    std::string nombreArchivo;

    if (argc == 9) {
        for (int i = 1; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "-m" && i + 1 < argc) modo = argv[++i][0];
            else if (arg == "-t" && i + 1 < argc) tipo = argv[++i][0];
            else if (arg == "-n" && i + 1 < argc) numLecturas = std::stoi(argv[++i]);
            else if (arg == "-f" && i + 1 < argc) nombreArchivo = argv[++i];
        }
    } else {
        std::cout << "Ingrese nombre del archivo (ej: datos.csv): ";
        std::cin >> nombreArchivo;

        std::cout << "Ingrese modo (r = leer, w = escribir): ";
        std::cin >> modo;

        std::cout << "Ingrese formato (c = CSV, j = JSON, x = XML): ";
        std::cin >> tipo;

        if (modo == 'w') {
            std::cout << "Ingrese cantidad de lecturas: ";
            std::cin >> numLecturas;
        }
    }

    // --- Inicializar comunicación
    Trans_Rec comunicacion(true);
    comunicacion.T_R_Init(19200, 1, "/dev/ttyACM0");
    comunicacion.ClearInput(); 

    // --- Inicializar archivo
    std::fstream archivoStream;
    File archivo(archivoStream, "./mios/" + nombreArchivo, tipo, &comunicacion);

    App app(&archivo, &comunicacion);

    if (modo == 'w') {
        std::cout << ">>> Escribiendo " << numLecturas
                  << " lecturas en archivo: ./mios/" << nombreArchivo << std::endl;

        if (!archivo.abrir(std::ios::out)) {
            std::cerr << "No se pudo abrir el archivo para escritura." << std::endl;
            return 1;
        }

        std::string ultimaCadena = "";
        for (int i = 0; i < numLecturas; i++) {
            comunicacion.ClearInput(); // Limpiar buffer antes de cada lectura
            comunicacion.SetCadena(""); // Limpiar cadena antes de cada lectura
            std::string comando(1, tipo);
            comando += "\n";
            comunicacion.Transmision(comando);

            // Leer hasta fin de bloque y asegurarse que la cadena sea nueva
            std::string bloque;
            while (true) {
                char buffer[512];
                comunicacion.Recepcion(buffer, sizeof(buffer), 2000); // timeout 2s
                std::string linea(buffer);
                if (linea.empty()) break;
                // condición de fin de bloque
                if (tipo == 'c') break;
                if (tipo == 'j' && linea.find("}") != std::string::npos) break;
                if (tipo == 'x' && linea.find("</registro>") != std::string::npos) break;
            }
            std::string actualCadena = comunicacion.GetCadena();
            // Esperar hasta que la cadena sea distinta a la anterior
            int intentos = 0;
            while (actualCadena == ultimaCadena && intentos < 10) {
                usleep(200000); // Esperar 0.2 segundos
                comunicacion.ClearInput();
                comunicacion.SetCadena("");
                comunicacion.Transmision(comando);
                while (true) {
                    char buffer[512];
                    comunicacion.Recepcion(buffer, sizeof(buffer), 2000);
                    std::string linea(buffer);
                    if (linea.empty()) break;
                    if (tipo == 'c') break;
                    if (tipo == 'j' && linea.find("}") != std::string::npos) break;
                    if (tipo == 'x' && linea.find("</registro>") != std::string::npos) break;
                }
                actualCadena = comunicacion.GetCadena();
                intentos++;
            }
            std::cout << "Cadena" << actualCadena << std::endl;
            archivo.Formato();
            ultimaCadena = actualCadena;
            usleep(300000); // Espera corta entre lecturas para asegurar nuevos datos
        }

        std::cout << ">>> Escritura finalizada." << std::endl;
        app.Mostrar_Archivo();

            } else if (modo == 'r') {
                app.Mostrar_Archivo();
            } else {
                std::cerr << "Modo no reconocido. Use -m [r/w]" << std::endl;
                return 1;
            }

    return 0;
}