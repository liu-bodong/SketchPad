#include "MainWindow.h"
#include "Canvas.h"

#include "CommandRegister.h"
#include "CommandBase.h"
#include "LineCommand.h"
#include "CircleCommand.h"
#include "RectCommand.h"
#include "UndoCommand.h"
#include "RedoCommand.h"

#include "Editor.h"
#include <qactiongroup.h>


// ##################### Public #####################

MainWindow* MainWindow::GetInstance()
{
    static MainWindow g_pInstance;
    return &g_pInstance;
}


// ##################### Public Slots #################



// ##################### Protected #####################



// ##################### Private #####################

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    Init();
}

void MainWindow::Init()
{
    CommandRegister::GetInstance()->RegisterCommand("Line", new LineCommand(Canvas::GetInstance()));
    CommandRegister::GetInstance()->RegisterCommand("Rectangle", new RectCommand(Canvas::GetInstance()));
    CommandRegister::GetInstance()->RegisterCommand("Circle", new CircleCommand(Canvas::GetInstance()));
    CommandRegister::GetInstance()->RegisterCommand("Undo", new UndoCommand(Canvas::GetInstance()));
    CommandRegister::GetInstance()->RegisterCommand("Redo", new RedoCommand(Canvas::GetInstance()));



    connect(ui.actionLine, &QAction::triggered, ui.widget, &Editor::OnLineSelected);
    connect(ui.actionRect, &QAction::triggered, ui.widget, &Editor::OnRectSelected);
    connect(ui.actionCircle, &QAction::triggered, ui.widget, &Editor::OnCircleSelected);
    // connect(ui.actionText, &QAction::triggered, ui.widget, &Editor::OnTextSelected);
    connect(ui.actionUndo, &QAction::triggered, ui.widget, &Editor::OnUndoSelected);
    connect(ui.actionRedo, &QAction::triggered, ui.widget, &Editor::OnRedoSelected);

    auto actionGroup = new QActionGroup(this);
    actionGroup->addAction(ui.actionLine);
    actionGroup->addAction(ui.actionRect);
    actionGroup->addAction(ui.actionCircle);
    actionGroup->addAction(ui.actionText);
    actionGroup->addAction(ui.actionUndo);
    actionGroup->addAction(ui.actionRedo);



    actionGroup->setExclusive(true);
}

MainWindow::~MainWindow()
{}

void MainWindow::SetupConnections()
{
    // connect(this, &MainWindow::CommandSelected, this, &Editor::OnLineSelected);
    return;
}

