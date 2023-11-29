#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "spleeterconfig.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class AboutWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);
    void dragEnterEvent(QDragEnterEvent*event);
    void dropEvent(QDropEvent*event);

private:
    void InitConfig();
    void InitView();
    void InitSigSlot();

private:
    Ui::MainWindow *ui;

    AboutWidget *_aboutWidget;

    bool        _isProcessing{false};
    QStringList _items;
};
#endif // MAINWINDOW_H
