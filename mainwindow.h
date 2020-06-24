#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "adbwatch.h"
#include "baseprocess.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
    Ui::MainWindow  *ui;
    AdbWatch        *mAdbWatch;
    BaseProcess     *mKeyCmd;
    QString         mAdbPath;
    QPalette label_palette;

    void ClearBackground();
    void setLableBackcolor(QLabel *lable);
    void SyncTestResult();

public slots:
    void AdbConnected();
    void AdbDisconnected();
    void KeyEvent();
    void ExeCmdError();

private slots:
    void on_actions_triggered();

signals:
    void onAdbPathChanged(QString);
};
#endif // MAINWINDOW_H
