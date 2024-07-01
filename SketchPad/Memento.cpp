#include "Memento.h"
#include "Canvas.h"

Memento::Memento(Canvas* c)
    : m_pCanvas(c)
{
    m_shapes = m_pCanvas->GetShapes();
}

void Memento::Restore()
{
    m_pCanvas->SetShapes(m_shapes);
}