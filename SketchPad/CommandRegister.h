#pragma once
#include <string>
#include <map>

class CommandBase;

class CommandRegister
{
    //a singleton class that registers CommandBase pointers
    //and provides a method to get a CommandBase pointer by name

public:
    static CommandRegister* GetInstance();
    static void DeleteInstance();

    void RegisterCommand(const std::string&, CommandBase*);
    void UnRegisterCommand(const std::string&);

    void ExecuteCommand(const std::string&);
    CommandBase* GetCommand(const std::string&);


private:
    CommandRegister();
    CommandRegister(const CommandRegister&);
    ~CommandRegister() = default;

    static CommandRegister* g_pInstance;
    std::map<std::string, CommandBase*> m_commands;
};

