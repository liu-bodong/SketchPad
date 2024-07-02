#pragma once
#include "CommandBase.h"
#include "LineItem.h"
#include <QMouseEvent>
#include <vector>

class LineCommand :
    public CommandBase
{
public:
    LineCommand(Canvas* c);
    ~LineCommand() = default;

    void Execute() override;

    void AddPoint(QPointF p) override { m_points.push_back(p); };
    void Clear() override { m_points.clear(); };
    bool IsReady() const override { return m_points.size() == 2; };

    void AddTempPoint(QPointF p) override { m_tempPoints.push_back(p); };
    void ModifyTempPoint(QPointF p) override { m_tempPoints[1] = p; };
    void ClearTemp() override { m_tempPoints.clear(); };
    bool IsTempReady() const override { return m_tempPoints.size() == 2; };
    void TempExecute() override;

    std::vector<ShapeBase*> GetTempShapes() const override { return m_tempShapes; };

private:
    LineItem* m_pTempLine = nullptr;
    LineItem* m_pTempText = nullptr;

    std::vector<ShapeBase*> m_tempShapes;

    QList<QPointF> m_points;
    QList<QPointF> m_tempPoints;
};

