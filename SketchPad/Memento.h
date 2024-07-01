#pragma once
#include <vector>

class Canvas;
class ShapeBase;

class Memento
{
public:
    Memento(Canvas*);
    ~Memento() = default;
    void Restore();

private:
    Canvas* m_pCanvas;
    std::vector<ShapeBase*> m_shapes;
};

