#include "Canvas.h"
#include <qgraphicsview.h>
#include <qpoint.h>
#include <qevent.h>
#include <iostream>
#include "ShapeBase.h"
#include "Memento.h"
#include "MainWindow.h"
#include <qfiledialog.h>
#include <qfile.h>
#include <qdatastream.h>
#include "History.h"
#include <qglobal.h>
#include <qiodevice.h>
#include <qmetatype.h>
#include <qstring.h>
#include <new>


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
    quint16 size;
    in >> size;
    for (int i = 0; i < size; i++)
    {
        QString type;
        in >> type;
        int id = QMetaType::type(type.toStdString().c_str());
        ShapeBase* shape = nullptr;
        if (id > 0)
        {
            shape = static_cast<ShapeBase*>(QMetaType::create(id));
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
    auto size = quint16(m_shapes.size());
    out << size;
    for (int i = 0; i < size; i++)
    {
        out << m_shapes[i]->GetType();
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

