#pragma once
#include "group.hpp"
#include <string>
#include <vector>
using namespace std;

class GroupModel
{
public:
    //创建群组
    bool createGroup(Group& group);
    //加入群组
    void addGroup(int userid,int groupid,string role);
    //查询用户所在群组消息
    vector<Group> queryGroup(int userid);
    //依据指定group查询群组用户id列表
    vector<int> queryGroupUsers(int userid,int groupid);
};