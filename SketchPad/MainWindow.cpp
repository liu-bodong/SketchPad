#include "MainWindow.h"
#include "Canvas.h"

#include "CommandRegister.h"
#include "CommandBase.h"
#include "LineCommand.h"
#include "CircleCommand.h"
#include "RectCommand.h"
#include "TextCommand.h"
#include "UndoCommand.h"
#include "RedoCommand.h"
#include "ClearCommand.h"
#include "SaveCommand.h"
#include "LoadCommand.h"
#include "SelectCommand.h"

#include "Editor.h"
#include <qactiongroup.h>
#include <qcolordialog.h>
#include <qpalette.h>
#include <qcursor.h>


// ##################### Public #####################

MainWindow* MainWindow::GetInstance()
{
    static MainWindow g_pInstance;
    return &g_pInstance;
}


// ##################### Public Slots #################

void MainWindow::OpenColorDialog()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if (color.isValid())
    {
        emit ColorChanged(color);
    }
}

void MainWindow::ChangeButtonColor(QColor& color)
{
    // change the button's color
    QPalette pal = ui.colorButton->palette();
    pal.setColor(QPalette::Button, color);
    ui.colorButton->setPalette(pal);
    ui.colorButton->update();
}

void MainWindow::OnDrawSelected()
{
    m_pActionGroup->setEnabled(true);
    ui.widget->setCursor(Qt::CrossCursor);
    ui.actionLine->setChecked(true);
}

void MainWindow::OnSelectSelected()
{
    m_pActionGroup->setDisabled(true);
    ui.widget->setCursor(QCursor(QPixmap(":/SketchPad/Resource/pixil-frame-0.png"), 0, 0));
    // :/SketchPad/Resource/pixil-frame-0.png
}

void MainWindow::UncheckShapeAction()
{
    if (m_pActionGroup->checkedAction())
    { m_pActionGroup->checkedAction()->setChecked(false); }
}

void MainWindow::SetLineEditVisible()
{
    ui.lineEdit->setVisible(true);
}

// ##################### Protected #####################



// ##################### Private #####################

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    Init();
    SetupConnections();
    emit SelectLine();
}

void MainWindow::Init()
{
    CommandRegister::GetInstance()->RegisterCommand("Line", new LineCommand(Canvas::GetInstance()));
    CommandRegister::GetInstance()->RegisterCommand("Rectangle", new RectCommand(Canvas::GetInstance()));
    CommandRegister::GetInstance()->RegisterCommand("Circle", new CircleCommand(Canvas::GetInstance()));
    CommandRegister::GetInstance()->RegisterCommand("Text", new TextCommand(Canvas::GetInstance()));
    CommandRegister::GetInstance()->RegisterCommand("Undo", new UndoCommand(Canvas::GetInstance()));
    CommandRegister::GetInstance()->RegisterCommand("Redo", new RedoCommand(Canvas::GetInstance()));
    CommandRegister::GetInstance()->RegisterCommand("Clear", new ClearCommand(Canvas::GetInstance()));
    CommandRegister::GetInstance()->RegisterCommand("Save", new SaveCommand(Canvas::GetInstance()));
    CommandRegister::GetInstance()->RegisterCommand("Load", new LoadCommand(Canvas::GetInstance()));
    CommandRegister::GetInstance()->RegisterCommand("Select", new SelectCommand(Canvas::GetInstance()));

    m_pActionGroup = new QActionGroup(this);
    m_pActionGroup->addAction(ui.actionLine);
    m_pActionGroup->addAction(ui.actionRect);
    m_pActionGroup->addAction(ui.actionCircle);
    m_pActionGroup->addAction(ui.actionText);
    ui.actionLine->setChecked(true);

    m_pActionGroup->setExclusive(true);

    m_pModeGroup = new QActionGroup(this);
    m_pModeGroup->addAction(ui.actionSelect);
    m_pModeGroup->addAction(ui.actionDraw);
    ui.actionDraw->setChecked(true);
    m_pModeGroup->setExclusive(true);

    ui.lineEdit->setVisible(false);

    auto pal = QPalette();
    pal.setColor(QPalette::Window, Qt::white);
    ui.widget->setAutoFillBackground(true);
    ui.widget->setPalette(pal);
}

MainWindow::~MainWindow()
{}

void MainWindow::SetupConnections()
{
    // Shape actions
    connect(ui.actionLine, &QAction::triggered, ui.widget, &Editor::OnLineSelected);
    connect(ui.actionRect, &QAction::triggered, ui.widget, &Editor::OnRectSelected);
    connect(ui.actionCircle, &QAction::triggered, ui.widget, &Editor::OnCircleSelected);
    connect(ui.actionText, &QAction::triggered, ui.widget, &Editor::OnTextSelected);
    // default draw behavior
    connect(ui.actionDraw, &QAction::triggered, ui.widget, &Editor::OnLineSelected);
    connect(this, &MainWindow::SelectLine, ui.widget, &Editor::OnLineSelected);
    connect(ui.actionText, &QAction::triggered, this, &MainWindow::SetLineEditVisible);

    // Other actions
    connect(ui.actionUndo, &QAction::triggered, ui.widget, &Editor::OnUndoSelected);
    connect(ui.actionRedo, &QAction::triggered, ui.widget, &Editor::OnRedoSelected);
    connect(ui.actionClear, &QAction::triggered, ui.widget, &Editor::OnClearClicked);
    connect(ui.actionSelect, &QAction::triggered, ui.widget, &Editor::OnSelectSelected);

    connect(ui.actionUndo, &QAction::triggered, this, &MainWindow::UncheckShapeAction);
    connect(ui.actionRedo, &QAction::triggered, this, &MainWindow::UncheckShapeAction);
    connect(ui.actionClear, &QAction::triggered, this, &MainWindow::UncheckShapeAction);
    connect(ui.actionSelect, &QAction::triggered, this, &MainWindow::UncheckShapeAction);

    // change color and width
    connect(ui.colorButton, &QToolButton::clicked, this, &MainWindow::OpenColorDialog);
    connect(this, &MainWindow::ColorChanged, this, &MainWindow::ChangeButtonColor);
    connect(this, &MainWindow::ColorChanged, ui.widget, &Editor::OnColorChanged);
    connect(ui.spinBox, SIGNAL(valueChanged(int)), ui.widget, SLOT(OnWidthChanged(int)));

    // save load
    connect(ui.actionSave, &QAction::triggered, ui.widget, &Editor::OnSaveClicked);
    connect(ui.actionLoad, &QAction::triggered, ui.widget, &Editor::OnLoadClicked);

    // mode
    connect(ui.actionDraw, &QAction::triggered, this, &MainWindow::OnDrawSelected);
    connect(ui.actionSelect, &QAction::triggered, this, &MainWindow::OnSelectSelected);
    connect(ui.actionSelect, &QAction::triggered, this, &MainWindow::UncheckShapeAction);
}

