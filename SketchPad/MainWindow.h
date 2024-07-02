#pragma once

#include "ui_MainWindow.h"
#include <string>
#include <qobjectdefs.h>
#include <qstring.h>
#include <qcolor.h>
#include <qactiongroup.h>
#include <qmainwindow.h>
#include <qwidget.h>

class Editor;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow* GetInstance();

    Editor* GetEditor() const { return ui.widget; };

    QString GetText() const { return ui.lineEdit->text(); };

signals:
    void CommandSelected(std::string);
    void ColorChanged(QColor&);
    void SelectLine();

public slots:
    void OpenColorDialog();
    void ChangeButtonColor(QColor&);
    void OnDrawSelected();
    void OnSelectSelected();
    void UncheckShapeAction();

private:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    Ui::MainWindowClass ui;
    void Init();
    void SetupConnections();

    QActionGroup* m_pActionGroup;
    QActionGroup* m_pModeGroup;
};