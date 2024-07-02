#pragma once
#include "ShapeBase.h"

class LineItem :
    public ShapeBase
{
public:
    LineItem();
    ~LineItem() = default;

    void Paint(QPainter&) override;

    bool Selectable(QPointF) const override;
    bool Transform(QPoint) override;

    void Serialize(QDataStream&) const override;
    void Deserialize(QDataStream&) override;

    LineItem* Clone() const final;

    QPointF GetStart() const { return m_start; }
    QPointF GetEnd() const { return m_end; }

    void SetStart(QPointF pt) { m_start = pt; }
    void SetEnd(QPointF pt) { m_end = pt; }

private:
    QPointF m_start;
    QPointF m_end;

    static int m_idGenerator;
    int id;

    std::string Name() override { return "Line"; }
    int Id() override { return id; }
};

//int LineItem::m_idGenerator = 0;

