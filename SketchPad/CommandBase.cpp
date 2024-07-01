#include "CommandBase.h"

#include "Memento.h"
#include "Canvas.h"

void CommandBase::Undo()
{
    m_pMemento->Restore();
}

void CommandBase::Redo()
{
    m_pMemento->Restore();
}

void CommandBase::Save()
{
    m_pMemento = m_pCanvas->CreateMemento();
}