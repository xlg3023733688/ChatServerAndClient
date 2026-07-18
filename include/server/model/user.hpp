#pragma once

#include <string>
using namespace std;

//User表的ORM类
class User {
public:
    User(int id=-1,string name="",string password="",string state="offline")
    {
        this->_id=id;
        this->_name=name;
        this->_password=password;
        this->_state=state;
    }
    void setId(int id){
        this->_id=id;
    }
    void setName(string name){
        this->_name=name;
    }
    void setPwd(string password)
    {
        this->_password=password;
    }
    void setState(string state)
    {
        this->_state=state;
    }
    int getId(){
        return this->_id;
    }
    string getName(){
        return this->_name;
    }
    string getPwd()
    {
        return this->_password;
    }
    string getState()
    {
        return this->_state;
    }

private: 
    int _id;
    string _name;
    string _password;
    string _state;
};