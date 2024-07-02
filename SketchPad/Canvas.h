#pragma once
#include <qgraphicsview.h>
#include <qpoint.h>
#include <string>
#include <vector>

class ShapeBase;
class Memento;

class Canvas
{

public:
    static Canvas* GetInstance();
    static void DeleteInstance();

    void AddShape(ShapeBase*);
    void DeleteShape(ShapeBase*);

    ShapeBase* GetShape(QPointF);

    std::vector<ShapeBase*> GetShapes() const { return m_shapes; }
    void SetShapes(const std::vector<ShapeBase*>& shapes) { m_shapes = shapes; }

    bool LoadFromFile();
    bool SaveToFile();

    Memento* CreateMemento();

    void Clear();

    bool IsEmpty() const { return m_shapes.empty(); }

    void SetPen(QPen& pen) { m_pen = pen; }
    QPen& GetPen() { return m_pen; }

private:
    Canvas();
    Canvas(const Canvas&);
    ~Canvas() = default;

    static Canvas* g_pInstance;

    QPen m_pen;

    std::string m_fileName = "shapes.dat";

    std::vector<ShapeBase*> m_shapes;
};