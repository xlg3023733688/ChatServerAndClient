#include "chatserver.hpp"
#include "nlohmann/json.hpp"
#include "chatservice.hpp"
#include <functional>
#include "chatservice.hpp"
#include <muduo/base/Logging.h>
#include <string>
using namespace std;
using namespace placeholders;
using json = nlohmann::json;

ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameArg)
    : _server(loop, listenAddr, nameArg),
      _loop(loop)
{
    // 注册链接回调
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
    // 注册消息回调
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));
    // 设置线程数量
    _server.setThreadNum(4);
}

// 启动服务
void ChatServer::start()
{
    _server.start();
}

// 链接回调函数
void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    // 用户断开连接
    if (!conn->connected())
    {
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
    }
}

// 读写回调函数
void ChatServer::onMessage(const TcpConnectionPtr &conn,
                           Buffer *buffer,
                           Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    // 反序列化
    json js = json::parse(buf);
    // 通过js["msgid"]来获取业务handler
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    // 回调对应事件处理器
    msgHandler(conn, js, time);
}

