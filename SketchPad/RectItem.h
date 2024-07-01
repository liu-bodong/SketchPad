#pragma once
#include "ShapeBase.h"

class RectItem :
    public ShapeBase
{
public:
    RectItem();
    ~RectItem() = default;

    void Paint(QPainter&) override;

    bool Selectable(QPoint) const override;
    bool Transform(QPoint) override;
    void Serialize(QDataStream&) const override;
    void Deserialize(QDataStream&) override;

    RectItem* Clone() const final;

    void SetUpperLeft(QPointF pt) { m_upperLeft = pt; }
    void SetLowerRight(QPointF pt) { m_lowerRight = pt; }

    void SetLowerRight(double x, double y)
    { m_lowerRight = QPointF(m_upperLeft + QPointF(x, y)); }

private:
    QPointF m_upperLeft;
    QPointF m_lowerRight;
    double m_height;
    double m_width;

    static int m_idGenerator;
    int id;

    std::string Name() override { return "Rectangle"; }
    int Id() override { return id; }

};

