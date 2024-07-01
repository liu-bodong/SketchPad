#pragma once
#include "CommandBase.h"
#include "CircleItem.h"

class LineItem;

class CircleCommand :
    public CommandBase
{
public:
    CircleCommand(Canvas* c) : CommandBase(c) { m_name = "Circle"; };
    ~CircleCommand() = default;

    void Execute() override;

    void AddPoint(QPointF p) override { m_points.push_back(p); };
    void Clear() override { m_points.clear(); };
    bool IsReady() const override { return m_points.size() == 2; };

    void AddTempPoint(QPointF p) override { m_tempPoints.push_back(p); };
    void ModifyTempPoint(QPointF p) override { m_tempPoints[1] = p; };
    void ClearTempPoints() override { m_tempPoints.clear(); };
    bool IsTempReady() const override { return m_tempPoints.size() == 2; };
    void TempExecute() override;

    std::vector<ShapeBase*> GetTempShapes() const override { return m_tempShapes; }

private:
    CircleItem* m_pCircle = nullptr;

    CircleItem* m_pTempCircle = nullptr;
    LineItem* m_pTempLine = nullptr;

    std::vector<ShapeBase*> m_tempShapes;

    QList<QPointF> m_points;
    QList<QPointF> m_tempPoints;
};

