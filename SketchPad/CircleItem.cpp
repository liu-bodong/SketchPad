#include "CircleItem.h"
#include <qpainter.h>   

CircleItem::CircleItem()
{
}

void CircleItem::Paint(QPainter& painter)
{
    auto path = QPainterPath(m_center);
    path.addEllipse(QRectF(m_center.x() - m_radius, m_center.y() - m_radius, 2 * m_radius, 2 * m_radius));
    painter.drawPath(path);
}

bool CircleItem::Selectable(QPointF point) const
{
    return false;
}

bool CircleItem::Transform(QPoint point)
{
    return false;
}

void CircleItem::Serialize(QDataStream& stream) const
{
    stream << int(2) << m_center << m_radius << m_pen;
}

void CircleItem::Deserialize(QDataStream& stream)
{
    stream >> m_center >> m_radius >> m_pen;
}

CircleItem* CircleItem::Clone() const
{
    auto circle = new CircleItem();
    circle->m_center = m_center;
    circle->m_radius = m_radius;
    return circle;
}
