#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace Tp2_Act_1 {

    enum class LogLevel { DEBUG, INFO, WARNING, ERROR };

    struct LogEvent {
        std::string fechaHora;
        LogLevel nivel;
        std::string mensaje;
        std::string modulo;    // módulo interno
        int linea;             // opcional
        std::string usuarioID; // para eventos externos
        std::string dispositivoID; 
    };

    class Logger {
    private:
        std::string rutaArchivo;
        std::vector<LogEvent> eventos;
    public:
        Logger(const std::string& rutaArchivo);
        void mostrarLogs();
        void log(LogLevel nivel,
                 const std::string& mensaje,
                 const std::string& modulo = "",
                 int linea = -1,
                 const std::string& usuarioID = "",
                 const std::string& dispositivoID = "");

        void exportar(const std::string& formato, 
                      const std::string& destino = "logs.txt");

        std::string nivelToString(LogLevel nivel) const;

        // Filtrado
        std::vector<LogEvent> filtrarPorFecha(const std::string& desde, const std::string& hasta);
        std::vector<LogEvent> filtrarPorUsuario(const std::string& usuarioID);
        std::vector<LogEvent> filtrarPorNivel(LogLevel nivel);

    private:
        std::string ahoraComoString();
    };

}

#endif