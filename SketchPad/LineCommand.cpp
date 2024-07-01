#include "LineCommand.h"
#include "Canvas.h"
#include <qdebug.h>
#include "History.h"
#include "Editor.h"
#include "MainWindow.h"

LineCommand::LineCommand(Canvas* c) : CommandBase(c)
{
    m_name = "Line";
}

void LineCommand::Execute()
{
    auto pEditor = MainWindow::GetInstance()->GetEditor();

    bool isFirstSave = m_pHistory->IsUndoEmpty();

    auto line = new LineItem();
    line->SetStart(m_points[0]);
    line->SetEnd(m_points[1]);

    if (isFirstSave)
    {
        auto pMem = m_pCanvas->CreateMemento();
        m_pHistory->Save(pMem);
        isFirstSave = false;
    }

    line->SetPen(pEditor->GetPen());

    m_pCanvas->AddShape(line);

    if (!isFirstSave)
    {
        auto pMem = m_pCanvas->CreateMemento();
        m_pHistory->Save(pMem);
    }
}

void LineCommand::TempExecute()
{
    if (m_pTempLine == nullptr)
    {
        m_pTempLine = new LineItem();
    }

    if (m_tempShapes.empty())
    {
        m_tempShapes.push_back(m_pTempLine);
    }

    m_pTempLine->SetStart(m_tempPoints[0]);
    m_pTempLine->SetEnd(m_tempPoints[1]);
}
