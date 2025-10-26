cmake_minimum_required(VERSION 4.0)
project(threads_2025c2_alexguttlein)

set(CMAKE_CXX_STANDARD 14)

include_directories(client_src)
include_directories(common_src)
include_directories(server_src)

add_executable(threads_2025c2_alexguttlein
        client_src/client_class.cpp
        client_src/client_class.h
        client_src/client_main.cpp
        client_src/client_protocol.cpp
        client_src/client_protocol.h
        common_src/common_constants.h
        common_src/common_liberror.cpp
        common_src/common_liberror.h
        common_src/common_queue.h
        common_src/common_resolver.cpp
        common_src/common_resolver.h
        common_src/common_resolvererror.cpp
        common_src/common_resolvererror.h
        common_src/common_socket.cpp
        common_src/common_socket.h
        common_src/common_thread.h
        server_src/server_acceptor.cpp
        server_src/server_acceptor.h
        server_src/server_class.cpp
        server_src/server_class.h
        server_src/server_clientData.cpp
        server_src/server_clientData.h
        server_src/server_gameLoop.cpp
        server_src/server_gameLoop.h
        server_src/server_main.cpp
        server_src/server_monitorClients.cpp
        server_src/server_monitorClients.h
        server_src/server_receiverThread.cpp
        server_src/server_receiverThread.h
        server_src/server_senderThread.cpp
        server_src/server_senderThread.h
        common_src/common_messageBuilder.cpp
        common_src/common_messageBuilder.h
        common_src/common_message.h
        server_src/server_protocol.cpp
        client_src/client_commandDispatcher.cpp
        client_src/client_commandDispatcher.h)
