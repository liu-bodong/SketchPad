#include "TextItem.h"

void TextItem::Paint(QPainter& painter)
{
    painter.drawText(m_center, m_text);
}

bool TextItem::Selectable(QPointF point) const
{
    return false;
}

bool TextItem::Transform(QPoint point)
{
    return false;
}

void TextItem::Serialize(QDataStream& stream) const
{
    stream << m_center << m_text << m_pen;
}

void TextItem::Deserialize(QDataStream& stream)
{
    stream >> m_center >> m_text >> m_pen;
}

TextItem* TextItem::Clone() const
{
    auto text = new TextItem();
    text->m_center = m_center;
    text->m_text = m_text;
    return text;
}
