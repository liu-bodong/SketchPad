#include "MainWindow.h"
#include "Canvas.h"
#include "CommandBase.h"
#include "LineCommand.h"
#include "CircleCommand.h"
#include "CommandRegister.h"
#include "RectCommand.h"
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

    connect(ui.actionLine, &QAction::triggered, ui.widget, &Editor::OnLineSelected);
    connect(ui.actionRect, &QAction::triggered, ui.widget, &Editor::OnRectSelected);
    connect(ui.actionCircle, &QAction::triggered, ui.widget, &Editor::OnCircleSelected);

    auto actionGroup = new QActionGroup(this);
    actionGroup->addAction(ui.actionLine);
    actionGroup->addAction(ui.actionRect);
    actionGroup->addAction(ui.actionCircle);
    actionGroup->setExclusive(true);
}

MainWindow::~MainWindow()
{}

void MainWindow::SetupConnections()
{
    // connect(this, &MainWindow::CommandSelected, this, &Editor::OnLineSelected);
    return;
}

