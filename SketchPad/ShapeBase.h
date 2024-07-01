#pragma once

#include <qgraphicsitem.h>
#include <qpoint.h>
#include <qdatastream.h>
#include <qpainter.h>
#include <string>
#include <qpen.h>


class ShapeBase
{
public:
    ShapeBase() {};
    virtual ~ShapeBase() = default;

    virtual void Paint(QPainter&) = 0;

    virtual bool Selectable(QPoint) const = 0;
    virtual bool Transform(QPoint) = 0;
    virtual ShapeBase* Clone() const = 0;
    virtual void Serialize(QDataStream&) const = 0;
    virtual void Deserialize(QDataStream&) = 0;

    void SetPen(QPen pen) { m_pen = pen; }
    void SetPenColor(QColor color) { m_pen.setColor(color); }
    void SetPenWidth(int width) { m_pen.setWidth(width); }

    QPen GetPen() { return m_pen; }

protected:
    QPen m_pen;

private:
    virtual std::string Name() = 0;
    virtual int Id() = 0;
};


