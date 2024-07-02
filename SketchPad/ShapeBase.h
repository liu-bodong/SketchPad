#pragma once
#include <qpoint.h>
#include <qdatastream.h>
#include <qpainter.h>
#include <string>
#include <qpen.h>
#include <qstring.h>
#include <qcolor.h>
#include <qfont.h>


class ShapeBase
{
public:
    ShapeBase() = default;
    virtual ~ShapeBase() = default;

    virtual void Paint(QPainter&) = 0;

    virtual bool Selectable(QPointF) const = 0;
    virtual bool Transform(QPoint) = 0;
    virtual ShapeBase* Clone() const = 0;
    virtual void Serialize(QDataStream&) const = 0;
    virtual void Deserialize(QDataStream&) = 0;

    void SetPen(QPen const& pen) { m_pen = pen; }
    void SetPenColor(QColor const& color) { m_pen.setColor(color); }
    void SetPenWidth(int width) { m_pen.setWidth(width); }

    void SetFont(QFont font) { m_font = font; }

    // GetType
    virtual QString GetType() = 0;

    QPen& GetPen() { return m_pen; }
    QColor GetPenColor() const { return m_pen.color(); }

    QFont& GetFont() { return m_font; }

protected:
    QPen m_pen;
    QFont m_font;

private:
    virtual std::string Name() = 0;
    virtual int Id() = 0;
};


