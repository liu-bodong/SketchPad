#include "Memento.h"
#include "Canvas.h"
#include <qdebug.h>

Memento::Memento(Canvas* c)
    : m_pCanvas(c)
{
    m_shapes = m_pCanvas->GetShapes();
    qDebug() << m_pCanvas;
}

void Memento::Restore()
{
    m_pCanvas->SetShapes(m_shapes);
}