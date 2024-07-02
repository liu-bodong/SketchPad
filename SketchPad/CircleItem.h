#pragma once
#include "ShapeBase.h"
class CircleItem :
    public ShapeBase
{
public:
    CircleItem();
    ~CircleItem() = default;

    void Paint(QPainter&) override;

    bool Selectable(QPointF) const override;
    bool Transform(QPoint) override;
    void Serialize(QDataStream&) const override;
    void Deserialize(QDataStream&) override;

    CircleItem* Clone() const final;

    void SetCenter(QPointF pt) { m_center = pt; }
    void SetRadius(double r) { m_radius = r; }

    QString GetType() override { return "Circle"; }

private:
    QPointF m_center;
    double m_radius;

    static int m_idGenerator;
    int id;

    std::string Name() override { return "Circle"; }
    int Id() override { return id; }
};

