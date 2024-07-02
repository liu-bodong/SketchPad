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
    // Cursor boundaries
    QLineF top(point, QPointF(point.x() + 10, point.y()));
    QLineF bottom(QPointF(point.x(), point.y() + 10), QPointF(point.x() + 10, point.y() + 10));
    QLineF left(point, QPointF(point.x(), point.y() + 10));
    QLineF right(QPointF(point.x() + 10, point.y()), QPointF(point.x() + 10, point.y() + 10));
    QList<QLineF> cursorLines = { top, bottom, left, right };

    for (auto i = 0; i < 360; ++i)
    {
        double theta1 = i * 3.14159265358979323846 / 180;
        double theta2 = (i + 1) * 3.14159265358979323846 / 180;
        auto x1 = m_center.x() + m_radius * cos(theta1);
        auto y1 = m_center.y() + m_radius * sin(theta1);
        auto x2 = m_center.x() + m_radius * cos(theta2);
        auto y2 = m_center.y() + m_radius * sin(theta2);
        auto p1 = QPointF(x1, y1);
        auto p2 = QPointF(x2, y2);
        QLineF tangent(p1, p2);
        for (auto const& cLine : cursorLines)
        {
            if (tangent.intersect(cLine, nullptr) == QLineF::BoundedIntersection)
                return true;
        }
    }
    return false;
}

bool CircleItem::Transform(QPoint point)
{
    return false;
}

void CircleItem::Serialize(QDataStream& stream) const
{
    stream << m_center << m_radius << m_pen;
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
