#pragma once

#include <muduo/net/TcpClient.h>
#include <unordered_map>
#include <functional>
#include <mutex>
#include "redis.hpp"
#include "groupModel.hpp"
#include "friendModel.hpp"
#include "OfflineMessageModel.hpp"
#include "UserModel.hpp"
#include "nlohmann/json.hpp"
using namespace std;
using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;

//处理消息的事件回调方法类型
using MsgHandler = std::function<void(const TcpConnectionPtr&conn,json& js,Timestamp)>;

//聊天服务器业务类
class ChatService
{
public:
    //从redis消息队列中获取消息
    void handleRedisSubscribeMessage(int userid,string msg);
    //处理注销业务
    void loginout(const TcpConnectionPtr& conn,json& js,Timestamp time);
    //创建群组业务
    void createGroup(const TcpConnectionPtr& conn,json& js,Timestamp time);
    //加入群组
    void addGroup(const TcpConnectionPtr& conn,json& js,Timestamp time);
    //群组聊天业务
    void groupChat(const TcpConnectionPtr& conn,json& js,Timestamp time);
    //添加好友业务
    void addFriend(const TcpConnectionPtr& conn,json& js,Timestamp time);
    //服务器异常业务重置
    void reset();
    //一对一聊天业务
    void oneChat(const TcpConnectionPtr& conn,json& js,Timestamp time);
    //获取单例对象接口函数
    static ChatService* instance();
    //登录业务
    void login(const TcpConnectionPtr& conn,json& js,Timestamp time);
    //注册业务
    void reg(const TcpConnectionPtr& conn,json& js,Timestamp time);
    //获取消息对应的处理器
    MsgHandler getHandler(int msgid);
    //处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr& conn);
private:
    //互斥锁保证_userConnMap线程安全
    mutex _connMutex;
    //存储在线用户的通信连接
    unordered_map<int,TcpConnectionPtr> _userConnMap;
    //数据操作对象
    Redis _redis;
    GroupModel _groupModel;
    FriendModel _friendModel;
    UserModel _userModel;
    OfflineMessageModel _offlinemessageModel;
    ChatService();
    //存储消息id和及其对应的业务处理方法
    unordered_map<int,MsgHandler> _msgHandlerMap;
};
