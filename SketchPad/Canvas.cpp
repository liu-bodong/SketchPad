#include "Canvas.h"
#include <qgraphicsview.h>
#include <qpainter.h>
#include <qgraphicsscene.h>
#include <qpoint.h>
#include <qevent.h>
#include <iostream>
#include "ShapeBase.h"
#include "Memento.h"

Canvas* Canvas::g_pInstance = new (std::nothrow) Canvas();

//#################################### Public ########################################

Canvas* Canvas::GetInstance()
{
    return g_pInstance;
}

void Canvas::DeleteInstance()
{
    if (g_pInstance)
    {
        delete g_pInstance;
        g_pInstance = nullptr;
    }
}

void Canvas::AddShape(ShapeBase* shape)
{
    m_shapes.push_back(shape);
}

void Canvas::DeleteShape(ShapeBase* shape)
{
    for (auto it = m_shapes.begin(); it != m_shapes.end(); ++it)
    {
        if (*it == shape)
        {
            m_shapes.erase(it);
            break;
        }
    }
}

Memento* Canvas::CreateMemento()
{
    auto* memento = new Memento(this);
    return memento;
}

bool Canvas::LoadFromFile(std::string)
{
    // TODO
    return false;
}

bool Canvas::SaveToFile(std::string)
{
    // TODO
    return false;
}

ShapeBase* Canvas::GetShape(QPoint point)
{
    // TODO
    return nullptr;
}

void Canvas::Clear()
{

    m_shapes.clear();
}

//#################################### Private ########################################


Canvas::Canvas()
{
    std::cout << "Canvas" << std::endl;
}

