#ifndef COMMON_CONSTANTS_H
#define COMMON_CONSTANTS_H

#include <string>

namespace  Constants {

    // constantes salida de programa
    static constexpr int SUCCESS = 0;
    static constexpr int ERROR = -1;

    // constantes de parámetros de línea de comandos
    static constexpr int EXPECTED_CLIENT_ARGC = 3;
    static constexpr int EXPECTED_SERVER_ARGC = 2;
    static constexpr int HOST_CLIENT_ARG_INDEX = 1;
    static constexpr int PORT_CLIENT_ARG_INDEX = 2;
    static constexpr int PORT_SERVER_ARG_INDEX = 1;

    // constantes de valores enteros
    static constexpr float NITRO_TIME_ITERATIONS = 12;
    static const unsigned int CLIENT_QUEUE_MAXSIZE = 20;
    static const unsigned int SERVER_QUEUE_MAXSIZE = 50;

    // constantes de ingresos del cliente
    static const std::string INPUT_NITRO = "nitro";
    static const std::string INPUT_READ = "read";
    static const std::string INPUT_EXIT = "exit";

    // constantes de mensajes
    static const std::string MSG_NITRO_ON = "A car hit the nitro!";
    static const std::string MSG_NITRO_OFF = "A car is out of juice.";

    // constantes de codigo de acciones
    static constexpr unsigned char CLIENT_ACTIVATE_NITRO = 0x04;
    static constexpr unsigned char SERVER_NITRO_ACTIVATE = 0x07;
    static constexpr unsigned char SERVER_NITRO_EXPIRED = 0x08;
    static constexpr unsigned char SERVER_RESPONSE = 0x10;
    static constexpr unsigned char DEFAULT_MESSAGE_CODE = 0x00;

    // constante tiempo sleep de loop
    static constexpr int THREAD_SLEEP_MS = 250;

    // constantes de errores
    static const std::string ERROR_READN = "ERROR: Falta el número en read <n>";
    static const std::string ERROR_UNKNOWN_COMMAND = "Error: Comando desconocido: ";
    static const std::string ERROR_PARAMETERS_QUANTITY = "Error: La cantidad de parametros no es correcta";

}

#endif // COMMON_CONSTANTS_H
