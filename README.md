# Threads

## Propósito del proyecto

Este trabajo propone implementar una interacción entre un cliente y un servidor a través de un socket. 
A su vez, el servidor deberá poder responder a múltiples clientes por medio de threads.

Los clientes enviarán mensajes para activar el nitro. El servidor informará cada vez que un cliente active su nitro.
El mismo tendrá una duración de 3 segundos, luego de los cuales el servidor avisará a todos los clientes que un nitro 
se agotó.

Los clientes tendrán encolados dichos mensajes y podrán acceder a ellos cuando lo soliciten.

---

## Contenido Externo

Los archivos correspondientes al Socket y demás librerías (common_socket, common_resolver, common_liberror,
common_resolvererror) fueron extraídos del repositorio https://github.com/eldipa/hands-on-sockets-in-cpp

Los archivos correspondientes a Threads y Queue fueron extraídos del repositorio 
https://github.com/eldipa/hands-on-threads.git

---

## Compilación y ejecución

### Compilar
- Se debe compilar con: make -f MakefileThreads

### Ejecutar Server
- Se ejecuta el servidor con:    ./server \<puerto>

- Ejemplo de ejecución:        ./server 9090

- Ejecución con Valgrind:     valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./server 9090

### Ejecutar Client

- Se ejecuta el cliente con:    ./client \<hostname> \<servicio>

- Ejemplo de ejecución:        ./client 127.0.0.1 9090

- Ejecución con Valgrind:     valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./client 127.0.0.1 9090

---

## Interacción Client / Server

- El cliente ingresará por entrada estandar uno de los siguientes mensajes:
  - nitro: solicita al server que active su nitro.
  - read \<N>: lee los siguientes N mensajes que el server envió.
  - exit: finalizar conexión.
- El servidor va a imprimir por pantalla las acciones recibidas:
  - Por cada cliente que solicitó activar su nitro imprime: "A car hit the nitro!"
  - Cada vez que se agota el nitro de un cliente (3 segundos desde su activación) imprime: "A car is out of juice."