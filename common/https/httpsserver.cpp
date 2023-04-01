#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

#include "openssl/ssl.h"
#include <openssl/err.h>

using tcp = boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;

class HttpsServer
{
public:
    HttpsServer(boost::asio::io_context &io_context, short port, const std::string &cert_file, const std::string &key_file)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), context_(ssl::context::tlsv12)
    {
        // 加载 SSL 证书
        context_.use_certificate_chain_file(cert_file);
        context_.use_private_key_file(key_file, boost::asio::ssl::context::pem);

        // 设置路由
        router_["/healthcheck"] = [this](auto request)
        {
            return this->handle_healthcheck(request);
        };
        router_["/metrics"] = [this](auto request)
        {
            return this->handle_metrics(request);
        };

        // 接收连接
        do_accept();
    }

private:
    void do_accept()
    {
        auto socket = std::make_shared<ssl::stream<tcp::socket>>(acceptor_.get_executor(), context_);
        acceptor_.async_accept(socket->lowest_layer(), [this, socket](const boost::system::error_code &error)
                               {
            if (!error) {
                // 完成 SSL 握手
                socket->async_handshake(ssl::stream_base::server, [this, socket](const boost::system::error_code& error) {
                    if (!error) {
                        // 处理请求
                        do_read(socket);
                    }
                });
            }

            // 接收下一个连接
            do_accept(); });
    }

    void do_read(std::shared_ptr<ssl::stream<tcp::socket>> socket)
    {
        auto request = std::make_shared<boost::beast::http::request<boost::beast::http::string_body>>();
        boost::beast::http::async_read(*socket, buffer_, *request, [this, socket, request](const boost::system::error_code &error, size_t bytes_transferred)
                                       {
            if (!error) {
                // 处理请求
                handle_request(socket, request);
            } });
    }

    void handle_request(std::shared_ptr<ssl::stream<tcp::socket>> socket, std::shared_ptr<boost::beast::http::request<boost::beast::http::string_body>> request)
    {
        // 查找路由处理器
        auto it = router_.find(request->target().to_string());
        if (it != router_.end())
        {
            // 调用路由处理器
            auto response = it->second(request);

            // 发送响应
            boost::beast::http::async_write(*socket, response, [this, socket](const boost::system::error_code &error, size_t bytes_transferred)
                                            {
                if (!error) {
                    // 关闭连接
                    socket->async_shutdown([this, socket](const boost::system::error_code& error) {
                        if (!error) {
                            socket->lowest_layer().close();
                        }
                    });
                } });
        }
    }

    boost::beast::http::response<boost::beast::http::string_body> handle_healthcheck(std::shared_ptr<boost::beast::http::request<boost::beast::http::string_body>> request)
    {
        // 响应健康检查请求
        boost::beast::http::response<boost::beast::http::string_body> response(boost::beast::http::status::ok, request->version());
        response.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
        response.set(boost::beast::http::field::content_type, "text/plain");
        response.keep_alive(request->keep_alive());
        response.body() = "OK\n";
        response.prepare_payload();
        return response;
    }

    boost::beast::http::response<boost::beast::http::string_body> handle_metrics(std::shared_ptr<boost::beast::http::request<boost::beast::http::string_body>> request)
    {
        // 响应指标请求
        boost::beast::http::response<boost::beast::http::string_body> response(boost::beast::http::status::ok, request->version());
        response.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
        response.set(boost::beast::http::field::content_type, "text/plain");
        response.keep_alive(request->keep_alive());

        // 获取当前时间戳
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

        // 构造指标响应
        std::stringstream ss;
        ss << "# HELP server_timestamp_seconds The timestamp of the server in seconds since epoch.\n";
        ss << "# TYPE server_timestamp_seconds gauge\n";
        ss << "server_timestamp_seconds " << (timestamp / 1000.0) << "\n";
        response.body() = ss.str();
        response.prepare_payload();
        return response;
    }

private:
    tcp::acceptor acceptor_;
    ssl::context context_;
    boost::asio::streambuf buffer_;
    std::map<std::string, std::function<boost::beast::http::responseboost::beast::http::string_body(std::shared_ptr<boost::beast::http::requestboost::beast::http::string_body>)>> router_;
};

int test_https_server(int argc, char *argv[])
{
    try
    {
        if (argc != 4)
        {
            std::cerr << "Usage: https_server <port> <cert_file> <key_file>\n";
            return 1;
        }

        // 初始化 OpenSSL 库
        SSL_library_init();
        ERR_load_crypto_strings();

        // 创建 IO 上下文和服务器对象
        boost::asio::io_context io_context;
        HttpsServer server(io_context, std::atoi(argv[1]), argv[2], argv[3]);

        // 启动服务器
        boost::thread_group thread_group;
        for (int i = 0; i < 4; ++i)
        {
            thread_group.create_thread(boost::bind(&boost::asio::io_context::run, &io_context));
        }
        thread_group.join_all();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
