#pragma once
#include <vector>
#include <stack>

class Memento;

class History
{
public:
    static History* GetInstance();
    static void DeleteInstance();

    void Undo();
    void Redo();
    void Save(Memento*);

    bool IsUndoEmpty() const { return m_undoStack.empty(); }

    void ClearRedo() { while (!m_redoStack.empty()) { m_redoStack.pop(); } }

    void ClearUndo() { while (!m_undoStack.empty()) { m_undoStack.pop(); } }

    Memento* GetLast() { return m_pLast; }
    void SetLast(Memento* memento) { m_pLast = memento; }

private:
    History() = default;
    ~History() = default;

    static History* g_pInstance;

    Memento* m_pLast = nullptr;
    std::stack<Memento*> m_undoStack;
    std::stack<Memento*> m_redoStack;
};

