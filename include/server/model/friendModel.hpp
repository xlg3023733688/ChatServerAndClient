#pragma once
#include <vector>
using namespace std;
#include "user.hpp"

//维护好友信息
class FriendModel
{
public:
    //添加好友关系
    void insert(int userid,int friendid);
    //返回用户好友列表
    vector<User> query(int userid);
};