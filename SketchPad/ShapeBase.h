#pragma once

#include <qgraphicsitem.h>
#include <qpoint.h>
#include <qdatastream.h>
#include <qpainter.h>
#include <string>

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

private:
    virtual std::string Name() = 0;
    virtual int Id() = 0;
};


