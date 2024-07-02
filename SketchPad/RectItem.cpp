#include "RectItem.h"
#include <qpainter.h>
#include <qlist.h>
#include <qline.h>

RectItem::RectItem()
{
}

void RectItem::Paint(QPainter& painter)
{
    auto path = QPainterPath(m_upperLeft);
    path.addRect(QRectF(m_upperLeft, m_lowerRight));
    painter.drawPath(path);
}

bool RectItem::Selectable(QPointF point) const
{
    // Cursor boundaries
    QLineF top(point, QPointF(point.x() + 10, point.y()));
    QLineF bottom(QPointF(point.x(), point.y() + 10), QPointF(point.x() + 10, point.y() + 10));
    QLineF left(point, QPointF(point.x(), point.y() + 10));
    QLineF right(QPointF(point.x() + 10, point.y()), QPointF(point.x() + 10, point.y() + 10));
    QList<QLineF> cursorLines = { top, bottom, left, right };

    QRectF rect(m_upperLeft, m_lowerRight);
    QLineF line1(rect.topLeft(), rect.topRight());
    QLineF line2(rect.topRight(), rect.bottomRight());
    QLineF line3(rect.bottomLeft(), rect.bottomRight());
    QLineF line4(rect.topLeft(), rect.bottomLeft());
    QList<QLineF> rectLines = { line1, line2, line3, line4 };

    // Check if thisLine interesects with any of the four lines
    for (auto cLine : cursorLines)
    {
        for (auto rLine : rectLines)
        {
            if (rLine.intersect(cLine, nullptr) == QLineF::BoundedIntersection)
                return true;
        }
    }
    return false;
}

bool RectItem::Transform(QPoint point)
{
    return false;
}

void RectItem::Serialize(QDataStream& stream) const
{
    stream << m_upperLeft << m_lowerRight << m_pen;
}

void RectItem::Deserialize(QDataStream& stream)
{
    stream >> m_upperLeft >> m_lowerRight >> m_pen;
}

RectItem* RectItem::Clone() const
{
    auto rect = new RectItem();
    rect->m_upperLeft = m_upperLeft;
    rect->m_lowerRight = m_lowerRight;
    return rect;
}