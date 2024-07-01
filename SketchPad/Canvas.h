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

    ShapeBase* GetShape(QPoint);

    std::vector<ShapeBase*> GetShapes() const { return m_shapes; }
    void SetShapes(const std::vector<ShapeBase*>& shapes) { m_shapes = shapes; }

    bool LoadFromFile(std::string);
    bool SaveToFile(std::string);

    Memento* CreateMemento();

private:
    Canvas();
    Canvas(const Canvas&);
    ~Canvas() = default;

    static Canvas* g_pInstance;

    std::vector<ShapeBase*> m_shapes;
};