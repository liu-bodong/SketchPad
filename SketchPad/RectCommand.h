#pragma once
#include "CommandBase.h"
#include "RectItem.h"
#include "LineItem.h"


class RectCommand :
    public CommandBase
{
public:
    RectCommand(Canvas* c) : CommandBase(c) { m_name = "Rectangle"; };
    ~RectCommand() = default;

    void Execute() override;

    void AddPoint(QPointF p) override { m_points.push_back(p); };
    void Clear() override { m_points.clear(); };
    bool IsReady() const override { return m_points.size() == 2; };

    void AddTempPoint(QPointF p) override { m_tempPoints.push_back(p); };
    void ModifyTempPoint(QPointF p) override { m_tempPoints[1] = p; };
    void ClearTempPoints() override { m_tempPoints.clear(); };
    bool IsTempReady() const override { return m_tempPoints.size() == 2; };
    void TempExecute() override;

    std::vector<ShapeBase*> GetTempShapes() const override { return m_tempShapes; };

private:
    RectItem* m_pTempRect = nullptr;
    LineItem* m_pTempLine = nullptr;

    std::vector<ShapeBase*> m_tempShapes;

    QList<QPointF> m_points;
    QList<QPointF> m_tempPoints;
};

