#include "LineCommand.h"
#include "Canvas.h"
#include <qdebug.h>
#include "History.h"

LineCommand::LineCommand(Canvas* c) : CommandBase(c)
{
    m_name = "Line";
}

void LineCommand::Execute()
{
    auto pCanvas = Canvas::GetInstance();
    auto pHistory = History::GetInstance();

    bool isFirstSave = pHistory->IsUndoEmpty();

    auto start = m_points[0];
    auto end = m_points[1];

    auto line = new LineItem();
    line->SetStart(start);
    line->SetEnd(end);

    if (isFirstSave)
    {
        auto pMem = pCanvas->CreateMemento();
        pHistory->Save(pMem);
        isFirstSave = false;
    }

    pCanvas->AddShape(line);

    if (!isFirstSave)
    {
        auto pMem = pCanvas->CreateMemento();
        pHistory->Save(pMem);
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
