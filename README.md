# Need for speed

## Propósito del proyecto

Este trabajo propone implementar una interacción entre un cliente y un servidor a través de un socket. 
A su vez, el servidor deberá poder responder a múltiples clientes por medio de threads.

Los clientes enviarán mensajes para activar el nitro. El servidor recolectará estos mensajes en una cola para luego procesarlos e informar cada vez que un cliente active su nitro.
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

---

## Diseño implementado

### Monitor

El Monitor se encarga de gestionar la lista de clientes. Para garantizar la consistencia de los datos se utiliza un
mutex que protege los métodos críticos, tales como agregar o eliminar clientes, realizar un broadcast, limpiar la lista
o recorrerla para detectar clientes inactivos. 

Esto evita race condition cuando múltiples
hilos acceden simultáneamente a la misma estructura.

### Threads (hilos)

- Cliente: sólo utilizará el hilo main.
- Servidor: utiliza un modelo multithreaded para manejar concurrencia:
  - Hilo principal: inicializa los componentes del servidor.
  - Hilo aceptador (acceptor): escucha nuevas conexiones y lanza dos hilos por cliente.
  - Hilos por cliente:
    - un hilo para recibir mensajes (ReceiverThread)
    - un hilo para enviar mensajes (SenderThread)
  - Hilo GameLoop: simula los ciclos de juego y procesa los eventos recibidos.

Cada hilo se comunica con los demás mediante colas thread-safe, lo que elimina la necesidad de
sincronización directa entre ellos.

### Queues (colas)

El servidor utiliza dos tipos de colas:
- Cola global: el GameLoop procesa una cola no bloqueante, donde se encolan los mensajes recibidos desde todos los
  clientes.

  Se usa una cola no bloqueante (try_pop) porque el GameLoop no debe quedar bloqueado si la cola está vacía: el juego
  debe seguir corriendo aun sin nuevos eventos. De esta forma se mantiene la simulación fluida sin consumir recursos
  innecesarios ni detener la lógica del juego.


- Cola por cliente: cada cliente posee su propia cola bloqueante, usada por el SenderThread para enviar mensajes. Si no hay mensajes encolados, el hilo permanece bloqueado hasta que se agregue uno nuevo. Esto evita que haya un "busy
waiting" y permite que el hilo se despierte solo cuando haya datos listos para enviar.