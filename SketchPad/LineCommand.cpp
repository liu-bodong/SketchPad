#include "LineCommand.h"
#include "Canvas.h"
#include <qpainter.h>
#include "MainWindow.h"
#include <qdebug.h>

LineCommand::LineCommand(Canvas* c) : CommandBase(c)
{
    m_name = "Line";
}

void LineCommand::Execute()
{
    auto pCanvas = Canvas::GetInstance();

    auto start = m_points[0];
    auto end = m_points[1];
    auto line = new LineItem();

    line->SetStart(start);
    line->SetEnd(end);

    pCanvas->AddShape(line);
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
