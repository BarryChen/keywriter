#ifndef ADBWATCH_H
#define ADBWATCH_H
#include <QTimer>
#include "baseprocess.h"

class AdbWatch : public BaseProcess
{
    Q_OBJECT
public:
    AdbWatch();
    ~AdbWatch();

private:
    QTimer *mTimer;
    QString mAdbPath;
    bool mAdbIsConnected;

    void InitTimer();
    void StartAdbWatch();

signals:
    void onUsbConnect();
    void onUsbDisconnect();

public slots:
    void SlotTimer();
    void AdbWatchStdOut();//adb守护程序的标准输出
    void AdbWatchStdErr();//adb守护程序的错误输出

    void AdbPathChanged(QString);
};

#endif // ADBWATCH_H
