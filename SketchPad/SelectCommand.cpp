#include "SelectCommand.h"
#include "Canvas.h"
#include "ShapeBase.h"

void SelectCommand::Execute()
{
    m_pSelectedShape = m_pTempSelectedShape;
    m_pSelectedShape->SetPenColor(Qt::blue);
}

void SelectCommand::TempExecute()
{
    // If the temp points are valid, get the shape at the temp point
    if (m_pCanvas->GetShape(m_tempPoints[0]))
    {
        m_pTempSelectedShape = m_pCanvas->GetShape(m_tempPoints[0]);

        if (m_tempShapes.empty())
        {
            m_tempShapes.push_back(m_pTempSelectedShape);
        }

        m_originalColor = m_pTempSelectedShape->GetPenColor();

        if (m_pLastTempSelectedShape != nullptr)
        {
            m_pLastTempSelectedShape->SetPenColor(m_originalColor);
        }

        m_pLastTempSelectedShape = m_pTempSelectedShape; // Save the last selected shape

        if (m_originalColor == QColor(Qt::blue))
        {
            m_pTempSelectedShape->SetPenColor(Qt::red);
        }
        else
        {
            m_pTempSelectedShape->SetPenColor(Qt::blue);
        }
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