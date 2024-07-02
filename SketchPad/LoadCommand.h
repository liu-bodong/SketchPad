#pragma once
#include "CommandBase.h"
class LoadCommand :
    public CommandBase
{
public:
    LoadCommand(Canvas* c) : CommandBase(c) {};
    void Execute() override { m_pCanvas->LoadFromFile(); }

    void AddPoint(QPointF) override { /* No Effect */ };
    void Clear() override { /* No Effect */ };
    bool IsReady() const override { return true; };
    void AddTempPoint(QPointF) override { /* No Effect */ };
    void ModifyTempPoint(QPointF) override { /* No Effect */ };
    void ClearTemp() override { /* No Effect */ };
    bool IsTempReady() const override { return true; };
    void TempExecute() override { /* No Effect */ };
    std::vector<ShapeBase*> GetTempShapes() const override { return std::vector<ShapeBase*>(); };

private:
    std::vector<ShapeBase*> m_tempShapes = std::vector<ShapeBase*>();
};

