#pragma once

#include <string>
#include <qpoint.h>
#include <vector>
#include "History.h"
#include "Canvas.h"

class Memento;
class Canvas;
class ShapeBase;

class CommandBase
{
public:
    CommandBase(Canvas* c) : m_pCanvas(c) {};
    virtual ~CommandBase() = default;

    virtual void Execute() = 0;

    //void Undo();
    //void Redo();
    //void Save();

    virtual void AddPoint(QPointF) = 0;
    virtual void Clear() = 0;
    virtual bool IsReady() const = 0;

    virtual void AddTempPoint(QPointF) = 0;     // Add a point to the temporary shape
    virtual void ModifyTempPoint(QPointF) = 0;  // Modify the last point of the temporary shape
    virtual void ClearTemp() = 0;         // Clear the temporary shape points
    virtual bool IsTempReady() const = 0;       // Check if the number of points has reached the required count
    virtual void TempExecute() = 0;             // Execute to see temporary effect for preview

    virtual std::vector<ShapeBase*> GetTempShapes() const = 0;

protected:
    Memento* m_pMemento;
    Canvas* m_pCanvas = Canvas::GetInstance();
    History* m_pHistory = History::GetInstance();

    std::string m_name;
};

