#include "SelectCommand.h"
#include "Canvas.h"
#include "ShapeBase.h"
#include <QDebug>

void SelectCommand::Execute()
{
    m_pSelectedShape = m_pTempSelectedShape;
    m_pSelectedShape->SetPenColor(Qt::blue);
}

void SelectCommand::TempExecute()
{
    m_pTempSelectedShape = m_pCanvas->GetShape(m_tempPoints[0]);

    if (m_tempShapes.empty() && m_pTempSelectedShape)
    {
        m_tempShapes.push_back(m_pTempSelectedShape);
    }

    if (m_pTempSelectedShape && (m_pLastTempSelectedShape != m_pTempSelectedShape))
    {
        m_originalColor = m_pTempSelectedShape->GetPenColor();
        qDebug() << "save original color: " << m_originalColor.name();
    }

    if (m_pLastTempSelectedShape)
    {
        m_pLastTempSelectedShape->SetPenColor(m_originalColor);
        qDebug() << "restore original color";
    }

    if (m_pTempSelectedShape)
    {
        m_pLastTempSelectedShape = m_pTempSelectedShape; // Save the last selected shape
        qDebug() << "save last selected shape";
    }

    if (m_pTempSelectedShape)
    {
        m_pTempSelectedShape->SetPenColor(Qt::blue);
        qDebug() << "set pen color to blue";
    }
}

bool SelectCommand::IsTempReady() const
{
    return m_tempPoints.size() == 1;
};


bool SelectCommand::IsReady() const
{
    return (m_pTempSelectedShape) && (m_points.size() == 1);
}

void SelectCommand::ClearTemp()
{
    m_tempPoints.clear();
    m_tempShapes.clear();
    m_pTempSelectedShape = nullptr;
}