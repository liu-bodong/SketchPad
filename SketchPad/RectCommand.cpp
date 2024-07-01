#include "RectCommand.h"
#include "Canvas.h"
#include "History.h"

void RectCommand::Execute()
{
    auto pCanvas = Canvas::GetInstance();
    auto pHistory = History::GetInstance();

    bool isFirstSave = pHistory->IsUndoEmpty();

    auto start = m_points[0];
    auto end = m_points[1];

    auto rect = new RectItem();
    rect->SetUpperLeft(start);
    rect->SetLowerRight(end);

    if (isFirstSave)
    {
        auto pMem = pCanvas->CreateMemento();
        pHistory->Save(pMem);
        isFirstSave = false;
    }

    pCanvas->AddShape(rect);

    if (!isFirstSave)
    {
        auto pMem = pCanvas->CreateMemento();
        pHistory->Save(pMem);
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