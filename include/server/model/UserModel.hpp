#pragma once
#include "user.hpp"
 
//User表的数据操作类
class UserModel
{
public:
    //增加用户
    bool insert(User& user);
    //依据用户id查找用户信息
    User query(int id);    
    //更新用户状态
    bool updateState(User user);
    //重置用户状态信息
    void resetState();
private:
};