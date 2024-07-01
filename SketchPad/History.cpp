#include "History.h"
#include "Memento.h"

History* History::g_pInstance = nullptr;

// #################### Public ####################

History* History::GetInstance()
{
    if (g_pInstance == nullptr)
    {
        g_pInstance = new History();
    }
    return g_pInstance;
}

void History::DeleteInstance()
{
    if (g_pInstance != nullptr)
    {
        delete g_pInstance;
        g_pInstance = nullptr;
    }
}

void History::Undo()
{
    if (!m_undoStack.empty() && m_pLast)
    {
        m_redoStack.push(m_pLast);
        m_pLast = m_undoStack.top();
        m_undoStack.pop();
        if (m_pLast) { m_pLast->Restore(); }
    }
}

void History::Redo()
{
    if (!m_redoStack.empty() && m_pLast)
    {
        m_undoStack.push(m_pLast);
        m_pLast = m_redoStack.top();
        m_redoStack.pop();
        m_pLast->Restore();
    }
}

void History::Save(Memento* memento)
{
    m_undoStack.push(m_pLast);
    m_pLast = memento;
    ClearRedo();
}