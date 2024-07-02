#include "LineItem.h"
#include <qpainter.h>

LineItem::LineItem()
{
}

void LineItem::Paint(QPainter& painter)
{
    auto path = QPainterPath(m_start);
    path.lineTo(m_end);
    painter.drawPath(path);
}

bool LineItem::Transform(QPoint point)
{
    if (Selectable(point))
    {
        m_start += point;
        m_end += point;
        return true;
    }
    return false;
}

bool LineItem::Selectable(QPointF point) const
{
    QLineF top(point, QPointF(point.x() + 10, point.y()));
    QLineF bottom(QPointF(point.x(), point.y() + 10), QPointF(point.x() + 10, point.y() + 10));
    QLineF left(point, QPointF(point.x(), point.y() + 10));
    QLineF right(QPointF(point.x() + 10, point.y()), QPointF(point.x() + 10, point.y() + 10));

    QLineF thisLine(m_start, m_end);

    // Check if thisLine interesects with any of the four lines
    return (thisLine.intersect(top, nullptr) == QLineF::BoundedIntersection ||
        thisLine.intersect(bottom, nullptr) == QLineF::BoundedIntersection ||
        thisLine.intersect(left, nullptr) == QLineF::BoundedIntersection ||
        thisLine.intersect(right, nullptr) == QLineF::BoundedIntersection);

}

void LineItem::Serialize(QDataStream& stream) const
{
    stream << int(0) << m_start << m_end << m_pen;
}

void LineItem::Deserialize(QDataStream& stream)
{
    stream >> m_start >> m_end >> m_pen;
}

LineItem* LineItem::Clone() const
{
    auto line = new LineItem();
    line->m_start = m_start;
    line->m_end = m_end;
    return line;
}
