#include "Logger.h"

namespace Tp2_Act_1 {
    Logger::Logger(const std::string& rutaArchivo) {
        this->rutaArchivo = rutaArchivo;
    }

    std::string Logger::ahoraComoString() {
        auto ahora = std::chrono::system_clock::now();
        std::time_t tiempo = std::chrono::system_clock::to_time_t(ahora);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&tiempo), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    void Logger::log(LogLevel nivel, const std::string& mensaje,
                     const std::string& modulo, int linea,
                     const std::string& usuarioID, const std::string& dispositivoID) {
        LogEvent evento { ahoraComoString(), nivel, mensaje, modulo, linea, usuarioID, dispositivoID };
        eventos.push_back(evento);

        std::ofstream out(rutaArchivo, std::ios::app);
        if (!out.is_open()) {
            throw std::runtime_error("No se pudo abrir archivo de log.");
        }
        out << evento.fechaHora << " [" << nivelToString(nivel) << "] "
            << (modulo.empty() ? "" : ("(" + modulo + ":" + std::to_string(linea) + ") "))
            << mensaje
            << (usuarioID.empty() ? "" : (" Usuario=" + usuarioID))
            << (dispositivoID.empty() ? "" : (" Dispositivo=" + dispositivoID))
            << "\n";
    }

    std::string Logger::nivelToString(LogLevel nivel) const {
        switch (nivel) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARNING";
            case LogLevel::ERROR: return "ERROR";
        }
        return "UNKNOWN";
    }

    void Logger::exportar(const std::string& formato, const std::string& destino) {
        std::ofstream out(destino);
        if (!out.is_open()) {
            throw std::runtime_error("No se pudo abrir archivo destino.");
        }

        if (formato == "csv") {
            out << "Fecha, Nivel, Mensaje, Modulo, Linea, Usuario, Dispositivo\n";
            for (const auto& e : eventos) {
                out << e.fechaHora << ","
                    << nivelToString(e.nivel) << ","
                    << e.mensaje << ","
                    << e.modulo << ","
                    << e.linea << ","
                    << e.usuarioID << ","
                    << e.dispositivoID << "\n";
            }
        } 
        else if (formato == "json") {
            out << "[\n";
            for (size_t i = 0; i < eventos.size(); ++i) {
                const auto& e = eventos[i];
                out << "  {\"fecha\": \"" << e.fechaHora << "\", "
                    << "\"nivel\": \"" << nivelToString(e.nivel) << "\", "
                    << "\"mensaje\": \"" << e.mensaje << "\", "
                    << "\"modulo\": \"" << e.modulo << "\", "
                    << "\"linea\": " << e.linea << ", "
                    << "\"usuario\": \"" << e.usuarioID << "\", "
                    << "\"dispositivo\": \"" << e.dispositivoID << "\"}";
                if (i != eventos.size() - 1) out << ",";
                out << "\n";
            }
            out << "]";
        }
        else if (formato == "xml") {
            out << "<logs>\n";
            for (const auto& e : eventos) {
                out << "  <evento>\n"
                    << "    <fecha>" << e.fechaHora << "</fecha>\n"
                    << "    <nivel>" << nivelToString(e.nivel) << "</nivel>\n"
                    << "    <mensaje>" << e.mensaje << "</mensaje>\n"
                    << "    <modulo>" << e.modulo << "</modulo>\n"
                    << "    <linea>" << e.linea << "</linea>\n"
                    << "    <usuario>" << e.usuarioID << "</usuario>\n"
                    << "    <dispositivo>" << e.dispositivoID << "</dispositivo>\n"
                    << "  </evento>\n";
            }
            out << "</logs>";
        } 
        else {
            throw std::invalid_argument("Formato de exportación no soportado.");
        }
    }

    std::vector<LogEvent> Logger::filtrarPorFecha(const std::string& desde, const std::string& hasta) {
        std::vector<LogEvent> filtrados;
        for (const auto& e : eventos) {
            if (e.fechaHora >= desde && e.fechaHora <= hasta) {
                filtrados.push_back(e);
            }
        }
        return filtrados;
    }

    std::vector<LogEvent> Logger::filtrarPorUsuario(const std::string& usuarioID) {
        std::vector<LogEvent> filtrados;
        for (const auto& e : eventos) {
            if (e.usuarioID == usuarioID) filtrados.push_back(e);
        }
        return filtrados;
    }

    std::vector<LogEvent> Logger::filtrarPorNivel(LogLevel nivel) {
        std::vector<LogEvent> filtrados;
        for (const auto& e : eventos) {
            if (e.nivel == nivel) filtrados.push_back(e);
        }
        return filtrados;
    }
    void Logger::mostrarLogs() {
    std::ifstream in(rutaArchivo);
    if (!in.is_open()) {
        std::cerr << "No se pudo abrir el archivo de logs." << std::endl;
        return;
    }
    std::cout << "\n===== CONTENIDO DE LOS LOGS =====\n";
    std::string linea;
    while (std::getline(in, linea)) {
        std::cout << linea << std::endl;
    }
    in.close();
}
}