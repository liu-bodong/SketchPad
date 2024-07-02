#pragma once
#include "CommandBase.h"
class SelectCommand :
    public CommandBase
{
public:
    SelectCommand(Canvas* c) : CommandBase(c) {};
    void Execute() override;

    void AddPoint(QPointF p) override { m_points.push_back(p); };
    void Clear() override { m_points.clear(); };
    bool IsReady() const override;

    void AddTempPoint(QPointF p) override { m_tempPoints.push_back(p); };
    void ModifyTempPoint(QPointF p) override { m_tempPoints[0] = p; };
    void ClearTemp() override;
    bool IsTempReady() const override;
    void TempExecute() override;

    std::vector<ShapeBase*> GetTempShapes() const override { return m_tempShapes; };

private:
    std::vector<ShapeBase*> m_tempShapes;
    QList<QPointF> m_points;
    QList<QPointF> m_tempPoints;
    ShapeBase* m_pSelectedShape = nullptr;
    ShapeBase* m_pTempSelectedShape = nullptr;
    ShapeBase* m_pLastTempSelectedShape = nullptr;
    QColor m_originalColor;

};

