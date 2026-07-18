#pragma once

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
using namespace muduo;
using namespace muduo::net;

class ChatServer{
public:
    ChatServer(EventLoop* loop,
    const InetAddress& listenAddr,
    const string& nameArg);
    void start();
private:
    //上报链接相关信息的回调函数
    void onConnection(const TcpConnectionPtr&);
    //上报读写事件相关的回调函数
    void onMessage(const TcpConnectionPtr&,
    Buffer*,
    Timestamp);
    TcpServer _server;//z组合的muduo库，实现服务器功能的类对象
    EventLoop* _loop;//指向事件循环对象的指针
};
