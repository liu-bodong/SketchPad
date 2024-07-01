#include "RectCommand.h"
#include "Canvas.h"

void RectCommand::Execute()
{
    auto pCanvas = Canvas::GetInstance();

    auto start = m_points[0];
    auto end = m_points[1];
    auto rect = new RectItem();

    rect->SetUpperLeft(start);
    rect->SetLowerRight(end);

    pCanvas->AddShape(rect);
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