#include "Canvas.h"
#include <qgraphicsview.h>
#include <qpainter.h>
#include <qgraphicsscene.h>
#include <qpoint.h>
#include <qevent.h>
#include <iostream>
#include "ShapeBase.h"
#include "Memento.h"
#include "MainWindow.h"
#include <qfiledialog.h>
#include <qfile.h>
#include <qdatastream.h>
#include "LineItem.h"
#include "RectItem.h"
#include "CircleItem.h"
#include "TextItem.h"
#include <qdebug.h>
#include "History.h"


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

bool Canvas::LoadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(MainWindow::GetInstance(), "Open File", "", "Data Files (*.dat)");
    if (fileName.isEmpty()) {
        return false;
    }
    Clear();
    History::GetInstance()->ClearUndo();
    History::GetInstance()->ClearRedo();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }
    QDataStream in(&file);
    unsigned size;
    in >> size;
    for (int i = 0; i < size; i++)
    {
        int type;
        in >> type;
        ShapeBase* shape = nullptr;
        switch (type)
        {
        case 0:
            shape = new LineItem();
            break;
        case 1:
            shape = new RectItem();
            break;
        case 2:
            shape = new CircleItem();
            break;
        case 3:
            shape = new TextItem();
            break;
        default:
            break;
        }
        if (shape)
        {
            shape->Deserialize(in);
            m_shapes.push_back(shape);
        }
    }

    file.close();
    return true;
}

bool Canvas::SaveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(MainWindow::GetInstance(), "Save File", "", "Data Files (*.dat)");
    if (fileName.isEmpty()) {
        return false;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }
    QDataStream out(&file);
    unsigned size = m_shapes.size();
    out << size;
    for (int i = 0; i < size; i++)
    {
        m_shapes[i]->Serialize(out);
    }
    file.close();
    return true;
}

ShapeBase* Canvas::GetShape(QPointF point)
{
    for (auto it = m_shapes.rbegin(); it != m_shapes.rend(); ++it)
    {
        if ((*it)->Selectable(point))
        {
            return *it;
        }
    }
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

