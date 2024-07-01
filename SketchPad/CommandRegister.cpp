#include "CommandRegister.h"
#include "CommandBase.h"
#include "Canvas.h"


CommandRegister* CommandRegister::g_pInstance = new (std::nothrow) CommandRegister();

// ##################### Public #####################

CommandRegister* CommandRegister::GetInstance()
{
    return g_pInstance;
}

void CommandRegister::DeleteInstance()
{
    if (g_pInstance)
    {
        delete g_pInstance;
        g_pInstance = nullptr;
    }
}

void CommandRegister::RegisterCommand(const std::string& name, CommandBase* command)
{
    m_commands[name] = command;
}

void CommandRegister::UnRegisterCommand(const std::string& name)
{
    m_commands.erase(name);
}

void CommandRegister::ExecuteCommand(const std::string& name)
{
    GetCommand(name)->Execute();
}

CommandBase* CommandRegister::GetCommand(const std::string& name)
{
    if (m_commands.find(name) != m_commands.end())
    {
        return m_commands[name];
    }
    return nullptr;
}

// ##################### Private #####################

CommandRegister::CommandRegister()
{
}

CommandRegister::CommandRegister(const CommandRegister&)
{
}
