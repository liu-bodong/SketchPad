#include "RectItem.h"
#include <qpainter.h>

RectItem::RectItem()
{
}

void RectItem::Paint(QPainter& painter)
{
    auto path = QPainterPath(m_upperLeft);
    path.addRect(QRectF(m_upperLeft, m_lowerRight));
    painter.drawPath(path);
}

bool RectItem::Selectable(QPoint point) const
{
    return false;
}

bool RectItem::Transform(QPoint point)
{
    return false;
}

void RectItem::Serialize(QDataStream& stream) const
{
    stream << m_upperLeft << m_lowerRight;
}

void RectItem::Deserialize(QDataStream& stream)
{
    stream >> m_upperLeft >> m_lowerRight;
}

RectItem* RectItem::Clone() const
{
    auto rect = new RectItem();
    rect->m_upperLeft = m_upperLeft;
    rect->m_lowerRight = m_lowerRight;
    return rect;
}