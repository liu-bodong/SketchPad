#include "SelectCommand.h"
#include "Canvas.h"
#include "ShapeBase.h"
#include <QDebug>

void SelectCommand::Execute()
{
    m_pSelected = m_pCanvas->GetShape(m_tempPoints[0]);;
    m_pSelected->SetPenColor(Qt::blue);
}

void SelectCommand::TempExecute()
{
    m_pTemp = m_pCanvas->GetShape(m_tempPoints[0]);
    if (m_pCanvas->GetShape(m_tempPoints[0]))
    {
        m_pTemp = m_pCanvas->GetShape(m_tempPoints[0])->Clone();
    }

    if (m_tempShapes.empty() && m_pTemp)
    {
        m_tempShapes.push_back(m_pTemp);
    }

    if (m_pTemp && (m_pLastTemp != m_pTemp))
    {
        m_color = m_pTemp->GetPenColor();
        qDebug() << "save original color: " << m_color.name();
    }

    if (m_pLastTemp)
    {
        m_pLastTemp->SetPenColor(m_color);
        qDebug() << "restore original color";
    }

    if (m_pTemp)
    {
        m_pLastTemp = m_pTemp; // Save the last selected shape
        qDebug() << "save last selected shape";
    }

    if (m_pTemp)
    {
        m_pTemp->SetPenColor(Qt::blue);
        qDebug() << "set pen color to blue";
    }
}

bool SelectCommand::IsTempReady() const
{
    return m_tempPoints.size() == 1;
};


bool SelectCommand::IsReady() const
{
    return (m_pTemp) && (m_points.size() == 1);
}

void SelectCommand::ClearTemp()
{
    m_tempPoints.clear();
    m_tempShapes.clear();
    m_pTemp = nullptr;
}