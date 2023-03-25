#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

// 1.创建套接字并绑定端口。在代码中创建套接字，设置监听端口，并启动监听服务。
int create_socket(int port) {
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;

    // 创建套接字
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 套接字选项
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // 地址和端口绑定
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听套接字
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

#include <unistd.h>
#include <cstring>
#include <sstream>
#include <arpa/inet.h>

// 2.接受连接并处理请求。在代码中接受客户端的连接，并读取并解析 HTTP 请求报文，然后根据请求内容作出响应。
void handle_client(int client_fd) {
    char buffer[1024] = {0};
    int valread = read(client_fd, buffer, sizeof(buffer));

    // 解析 HTTP 请求报文
    std::istringstream iss(buffer);
    std::string request_line;
    std::getline(iss, request_line);

    std::string method;
    std::string path;
    std::istringstream(request_line) >> method >> path;

    std::string response_body = "Hello, World!";
    std::string status_line = "HTTP/1.1 200 OK\r\n";
    std::string content_length = "Content-Length: " + std::to_string(response_body.length()) + "\r\n";

    // 发送 HTTP 响应报文
    std::string response = status_line + content_length + "\r\n" + response_body;
    send(client_fd, response.c_str(), response.length(), 0);
    close(client_fd);
}

void accept_http_connections(int server_fd) {
    struct sockaddr_in client_address;
    socklen_t len = sizeof(client_address);

    while (1) {
        int client_fd = accept(server_fd, (struct sockaddr *)&client_address, &len);
        if (client_fd < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        std::string ip = inet_ntoa(client_address.sin_addr);
        int port = ntohs(client_address.sin_port);
        printf("Connection from %s:%d\n", ip.c_str(), port);
        handle_client(client_fd);
    }
}

// 3.启用服务。在代码中调用上述函数，启动 HTTP 监听服务
void http_server_run(int port)
{
    int server_fd = create_socket(port);
    accept_http_connections(server_fd);
}
