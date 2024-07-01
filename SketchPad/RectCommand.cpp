#include "RectCommand.h"
#include "Canvas.h"
#include "History.h"
#include "MainWindow.h"

void RectCommand::Execute()
{
    auto pEditor = MainWindow::GetInstance()->GetEditor();

    bool isFirstSave = m_pHistory->IsUndoEmpty();

    auto rect = new RectItem();
    rect->SetUpperLeft(m_points[0]);
    rect->SetLowerRight(m_points[1]);

    if (isFirstSave)
    {
        auto pMem = m_pCanvas->CreateMemento();
        m_pHistory->Save(pMem);
        isFirstSave = false;
    }

    rect->SetPen(pEditor->GetPen());

    m_pCanvas->AddShape(rect);

    if (!isFirstSave)
    {
        auto pMem = m_pCanvas->CreateMemento();
        m_pHistory->Save(pMem);
    }
}

void RectCommand::TempExecute()
{
    if (m_pTempRect == nullptr)
    {
        m_pTempRect = new RectItem();
        m_pTempLine = new LineItem();
    }

    if (m_tempShapes.empty())
    {
        m_tempShapes.push_back(m_pTempLine);
        m_tempShapes.push_back(m_pTempRect);
    }

    m_pTempRect->SetUpperLeft(m_tempPoints[0]);
    m_pTempRect->SetLowerRight(m_tempPoints[1]);

    m_pTempLine->SetStart(m_tempPoints[0]);
    m_pTempLine->SetEnd(m_tempPoints[1]);
}