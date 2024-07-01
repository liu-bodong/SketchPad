#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <string>
#include <qgraphicsscene.h>

class Editor;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow* GetInstance();

    Editor* GetEditor() const { return ui.widget; };

signals:
    void CommandSelected(std::string);

public slots:
    // void OnLineSelected();

private:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    Ui::MainWindowClass ui;
    void Init();
    void SetupConnections();
};