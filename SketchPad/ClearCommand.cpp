#pragma once
#include "ClearCommand.h"
#include "Canvas.h"
#include "History.h"

void ClearCommand::Execute()
{
    if (!m_pCanvas->IsEmpty())
    {
        m_pCanvas->Clear();
        auto pMem = m_pCanvas->CreateMemento();
        m_pHistory->Save(pMem);
    }
}