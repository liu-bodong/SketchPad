#include "Editor.h"
#include "CommandRegister.h"
#include "CommandBase.h"
#include "Canvas.h"
#include <qgraphicsview.h>
#include <qwidget.h>
#include <qpen.h>
#include <qdebug.h>
#include "SelectCommand.h"
#include <memory>


// ##################### Public #####################
Editor::Editor(QWidget* parent)
    : QWidget(parent)
{
    m_pCanvas = Canvas::GetInstance();
    m_pen.setColor(Qt::black);
    m_pen.setWidth(3);
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

void Editor::OnTextSelected()
{
    m_pCommand = CommandRegister::GetInstance()->GetCommand("Text");
    m_mode = eDrawing;
}

void Editor::OnUndoSelected()
{
    m_pCommand = CommandRegister::GetInstance()->GetCommand("Undo");
    m_mode = eIdle;
    m_pCommand->Execute();
    update();
}

void Editor::OnRedoSelected()
{
    m_pCommand = CommandRegister::GetInstance()->GetCommand("Redo");
    m_mode = eIdle;
    m_pCommand->Execute();
    update();
}

void Editor::OnClearClicked()
{
    m_pCommand = CommandRegister::GetInstance()->GetCommand("Clear");
    m_mode = eIdle;
    m_pCommand->Execute();
    update();
}

void Editor::OnSaveClicked()
{
    m_pCommand = CommandRegister::GetInstance()->GetCommand("Save");
    m_mode = eIdle;
    m_pCommand->Execute();
}

void Editor::OnLoadClicked()
{
    m_pCommand = CommandRegister::GetInstance()->GetCommand("Load");
    m_mode = eIdle;
    m_pCommand->Execute();
    update();
}

void Editor::OnSelectSelected()
{
    m_pCommand = CommandRegister::GetInstance()->GetCommand("Select");
    m_mode = eSelecting;
    m_perm = true;
}

// ##################### Private #####################

void Editor::paintEvent(QPaintEvent* event)
{
    m_pCanvas = Canvas::GetInstance();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    m_shapes = m_pCanvas->GetShapes();
    for (auto item : m_shapes)
    {
        painter.setPen(item->GetPen());
        item->Paint(painter);
    }
    if (m_perm && m_pCommand->IsTempReady())
    {
        m_pCommand->TempExecute();
        switch (m_mode) {
        case eDrawing:
        {
            for (auto item : m_pCommand->GetTempShapes())
            {
                painter.setPen(m_pen);
                item->Paint(painter);
            }
            break;
        }
        case eSelecting:
        {
            for (auto item : m_pCommand->GetTempShapes())
            {
                painter.setPen(item->GetPen());
                item->Paint(painter);
            }
            break;
        }
        case eIdle:
        {
            break;
        }
        }
        return;
    }
}

void Editor::mousePressEvent(QMouseEvent* event)
{
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
                m_pCommand->ClearTemp();
                m_pCommand->Clear();
            }
        }
        else if (event->button() == Qt::MouseButton::RightButton)
        {
            // Click Right Button to cancel the drawing
            m_perm = false;
            update();
            m_pCommand->ClearTemp();
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
        m_pCommand->AddPoint(event->pos());
        if (m_pCommand->IsReady())
        {
            m_pCommand->Execute();
            m_perm = false;
            update();
            m_pCommand->ClearTemp();
            m_pCommand->Clear();
        }
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
        if (m_perm)
        {
            if (m_pCommand->IsTempReady()) { m_pCommand->ModifyTempPoint(event->pos()); }
            else { m_pCommand->AddTempPoint(event->pos()); }
            update();
        }
        break;
    }
    }
}

void Editor::mouseReleaseEvent(QMouseEvent* event)
{
}

