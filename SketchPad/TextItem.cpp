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
    stream << m_center << m_text << m_pen << m_font;
}

void TextItem::Deserialize(QDataStream& stream)
{
    stream >> m_center >> m_text >> m_pen >> m_font;
}

TextItem* TextItem::Clone() const
{
    auto text = new TextItem();
    text->m_center = m_center;
    text->m_text = m_text;
    text->m_pen = m_pen;
    text->m_font = m_font;
    return text;
}
