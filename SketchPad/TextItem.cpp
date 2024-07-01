#include "TextItem.h"

void TextItem::Paint(QPainter& painter)
{
    painter.drawText(m_center, m_text);
}

bool TextItem::Selectable(QPoint point) const
{
    return false;
}

bool TextItem::Transform(QPoint point)
{
    return false;
}

void TextItem::Serialize(QDataStream& stream) const
{
    stream << m_center << m_text;
}

void TextItem::Deserialize(QDataStream& stream)
{
    stream >> m_center >> m_text;
}

TextItem* TextItem::Clone() const
{
    auto text = new TextItem();
    text->m_center = m_center;
    text->m_text = m_text;
    return text;
}
