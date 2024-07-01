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

bool LineItem::Selectable(QPoint point) const
{
    return false;
}

bool LineItem::Transform(QPoint point)
{
    return false;
}

void LineItem::Serialize(QDataStream& stream) const
{
    stream << m_start << m_end;
}

void LineItem::Deserialize(QDataStream& stream)
{
    stream >> m_start >> m_end;
}

LineItem* LineItem::Clone() const
{
    auto line = new LineItem();
    line->m_start = m_start;
    line->m_end = m_end;
    return line;
}
