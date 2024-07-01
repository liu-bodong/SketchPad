#include "Editor.h"
#include "CommandRegister.h"
#include "CommandBase.h"
#include "Canvas.h"
#include "LineCommand.h"
#include <qgraphicsview.h>
#include <qwidget.h>
#include <qpen.h>
#include <qobjectdefs.h>
#include <qdebug.h>
#include <qwidget.h>


// ##################### Public #####################
Editor::Editor(QWidget* parent)
    : QWidget(parent)
{
    m_pCanvas = Canvas::GetInstance();
}

void Editor::SetMode(Mode mode)
{
    m_mode = mode;
}

// ##################### Public Slots #################

void Editor::OnLineSelected()
{
    m_pCommand = CommandRegister::GetInstance()->GetCommand("Line");
    m_mode = eDrawing;
}

void Editor::OnRectSelected()
{
    m_pCommand = CommandRegister::GetInstance()->GetCommand("Rectangle");
    m_mode = eDrawing;
}

void Editor::OnCircleSelected()
{
    m_pCommand = CommandRegister::GetInstance()->GetCommand("Circle");
    m_mode = eDrawing;
}

// ##################### Private #####################


void Editor::paintEvent(QPaintEvent* event)
{
    qDebug() << "Paint Event";
    m_pCanvas = Canvas::GetInstance();
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue, 3));
    m_shapes = m_pCanvas->GetShapes();
    for (auto item : m_shapes)
    {
        item->Paint(painter);
        qDebug() << "Painted";
    }
    if (m_perm && m_pCommand->IsTempReady())
    {
        m_pCommand->TempExecute();
        for (auto item : m_pCommand->GetTempShapes())
        {
            item->Paint(painter);
        }
        qDebug() << "Temp Painted";
    }
    return;
}

void Editor::mousePressEvent(QMouseEvent* event)
{
    qDebug() << "Mouse Pressed";
    switch (m_mode)
    {
    case eIdle:
    {
        break;
    }
    case eDrawing:
    {
        if (event->button() == Qt::MouseButton::LeftButton)
        {
            m_perm = true;
            m_pCommand->AddPoint(event->pos());
            m_pCommand->AddTempPoint(event->pos());
            if (m_pCommand->IsReady()) // If the shape has enough number of points to be drawn
            {
                m_pCommand->Execute();
                m_perm = false;
                update();
                m_pCommand->ClearTempPoints();
                m_pCommand->Clear();
            }
        }
        else if (event->button() == Qt::MouseButton::RightButton)
        {
            // Click Right Button to cancel the drawing
            m_perm = false;
            update();
            m_pCommand->ClearTempPoints();
            m_pCommand->Clear();
        }
        else
        {
            // Do nothing
        }
        break;
    }
    case eSelecting:
    {
        break;
    }
    }
}

void Editor::mouseMoveEvent(QMouseEvent* event)
{
    switch (m_mode)
    {
    case eIdle:
    {
        break;
    }
    case eDrawing:
    {
        if (m_perm)
        {
            if (m_pCommand->IsTempReady()) { m_pCommand->ModifyTempPoint(event->pos()); }
            else { m_pCommand->AddTempPoint(event->pos()); }
            update();
        }
        break;
    }
    case eSelecting:
    {
        break;
    }
    }
}

void Editor::mouseReleaseEvent(QMouseEvent* event)
{
    qDebug() << "Mouse Released";
}

