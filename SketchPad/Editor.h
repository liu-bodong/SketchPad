#pragma once
#include <qgraphicsview.h>
#include <qwidget.h>
#include <qpen.h>
#include <qobjectdefs.h>
#include <qevent.h>
#include <memory>
#include "ShapeBase.h"
#include <vector>

class Canvas;

class CommandBase;

class Editor :
    public QWidget
{
    Q_OBJECT

public:
    enum Mode
    {
        eIdle,
        eDrawing,
        eSelecting,
    };

    Editor(QWidget* parent = nullptr);
    ~Editor() = default;

    void SetMode(Mode);

public slots:
    void OnLineSelected();
    void OnRectSelected();
    void OnCircleSelected();

private:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;

    CommandBase* m_pCommand = nullptr;
    Canvas* m_pCanvas = nullptr;
    std::vector<ShapeBase*> m_shapes;

    Mode m_mode = eIdle;
    bool m_perm = false;
};

