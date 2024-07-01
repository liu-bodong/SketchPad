#include "CircleCommand.h"
#include "LineItem.h"
#include "Canvas.h"

void CircleCommand::Execute()
{
    auto pCanvas = Canvas::GetInstance();

    auto center = m_points[0];
    auto radius = sqrt(pow(m_points[1].x() - m_points[0].x(), 2) + pow(m_points[1].y() - m_points[0].y(), 2));
    auto circle = new CircleItem();

    circle->SetCenter(center);
    circle->SetRadius(radius);

    pCanvas->AddShape(circle);
}

void CircleCommand::TempExecute()
{
    if (m_pTempCircle == nullptr)
    {
        m_pTempCircle = new CircleItem();
        m_pTempLine = new LineItem();
    }

    if (m_tempShapes.empty())
    {
        m_tempShapes.push_back(m_pTempCircle);
        m_tempShapes.push_back(m_pTempLine);
    }

    auto radius = sqrt(pow(m_tempPoints[1].x() - m_tempPoints[0].x(), 2) + pow(m_tempPoints[1].y() - m_tempPoints[0].y(), 2));

    m_pTempCircle->SetCenter(m_tempPoints[0]);
    m_pTempCircle->SetRadius(radius);

    m_pTempLine->SetStart(m_tempPoints[0]);
    m_pTempLine->SetEnd(m_tempPoints[1]);
}