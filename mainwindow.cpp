#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windows.h"
#include <dbt.h>

#include <QFile>
#include <QDateTime>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->mAdbWatch = new AdbWatch();
    connect(this->mAdbWatch, SIGNAL(onUsbConnect()), this, SLOT(AdbConnected()));
    connect(this->mAdbWatch, SIGNAL(onUsbDisconnect()), this, SLOT(AdbDisconnected()));
    connect(this->mAdbWatch, SIGNAL(onExeCmdError()), this, SLOT(ExeCmdError()));
    connect(this, SIGNAL(onAdbPathChanged(QString)), this->mAdbWatch, SLOT(AdbPathChanged(QString)));

    this->mKeyCmd = new BaseProcess;
    connect(this->mKeyCmd->mProcess, SIGNAL(readyReadStandardOutput()), SLOT(KeyEvent()));

    label_palette.setColor(QPalette::Background, QColor(0xcc,0xff,0xcc));

}

MainWindow::~MainWindow()
{
    delete this->mAdbWatch;
    delete this->mKeyCmd;

    delete ui;    
}

void MainWindow::AdbConnected()
{
    QStringList options;
    options << "shell";
    options << "getevent -l";
    QString adb = "adb.exe";

    if(this->mAdbPath.right(7) == adb)
    {
        qDebug("use mAdbPath");
        this->mKeyCmd->ExeCmd(this->mAdbPath, options);
    } else {
        this->mKeyCmd->ExeCmd("adb.exe", options);
    }
}

void MainWindow::ClearBackground()
{
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0, 0, 0, 0));
    ui->label_0->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_0->setPalette(palette);

    ui->label_1->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_1->setPalette(palette);

    ui->label_2->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_2->setPalette(palette);

    ui->label_3->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_3->setPalette(palette);

    ui->label_4->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_4->setPalette(palette);

    ui->label_5->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_5->setPalette(palette);

    ui->label_6->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_6->setPalette(palette);

    ui->label_7->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_7->setPalette(palette);

    ui->label_8->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_8->setPalette(palette);

    ui->label_9->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_9->setPalette(palette);

    ui->label_0->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_0->setPalette(palette);

    ui->label_recall->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_recall->setPalette(palette);

    ui->label_call->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_call->setPalette(palette);

    ui->label_endcall->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_endcall->setPalette(palette);

    ui->label_spk->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_spk->setPalette(palette);

    ui->label_del->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_del->setPalette(palette);

    ui->label_qingqing->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_qingqing->setPalette(palette);

    ui->label_xin->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_xin->setPalette(palette);

    ui->label_jing->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_jing->setPalette(palette);

    ui->label_0->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_0->setPalette(palette);

    ui->label_0->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_0->setPalette(palette);

    ui->label_0->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_0->setPalette(palette);

    ui->label_status->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_status->setPalette(palette);
    ui->label_status->setText("USB连接状态：未连接");
}
void MainWindow::AdbDisconnected()
{
    ClearBackground();
}

void MainWindow::setLableBackcolor(QLabel *lable)
{
    lable->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    lable->setPalette(label_palette);
}

void MainWindow::KeyEvent()
{
    QString data,tmp;
    QString str_start = "/dev/input/event1: EV_KEY       ";
    QString key_start = "KEY_";
    QStringList save_list;

//    ui->label_status->setStyleSheet("background-color: rgb(250, 0, 0);font-size:60px;color:blue");
//    ui->label_status->setStyleSheet("background-color: rgb(250, 0, 0);color:blue");
    ui->label_status->setText("USB连接状态：连接成功");
    while (this->mKeyCmd->mProcess->canReadLine()) {

        data = this->mKeyCmd->mProcess->readLine();
        //ui->textEdit_Output->append(data);

        if(data.contains("UP"))
        {
            tmp = data.mid(str_start.size()).simplified().remove("UP").trimmed().remove(key_start);

            qDebug() << "str:" << tmp;
            if(tmp == "0") {
                setLableBackcolor(ui->label_0);
            } else if(tmp == "1") {
                setLableBackcolor(ui->label_1);
            } else if(tmp == "2") {
                setLableBackcolor(ui->label_2);
            } else if(tmp == "3") {
                setLableBackcolor(ui->label_3);
            } else if(tmp == "4") {
                setLableBackcolor(ui->label_4);
            } else if(tmp == "5") {
                setLableBackcolor(ui->label_5);
            } else if(tmp == "6") {
                setLableBackcolor(ui->label_6);
            } else if(tmp == "7") {
                setLableBackcolor(ui->label_7);
            } else if(tmp == "8") {
                setLableBackcolor(ui->label_8);
            } else if(tmp == "9") {
                setLableBackcolor(ui->label_9);
            } else if(tmp == "F18") {
                setLableBackcolor(ui->label_xin);
            } else if(tmp == "F19") {
                setLableBackcolor(ui->label_jing);
            } else if(tmp == "F20") {
                setLableBackcolor(ui->label_qingqing);
            } else if(tmp == "F21") {
                setLableBackcolor(ui->label_spk);
            } else if(tmp == "F22") {
                setLableBackcolor(ui->label_recall);
            } else if(tmp == "BACKSPACE") {
                setLableBackcolor(ui->label_del);
            } else if(tmp == "F23") {
                setLableBackcolor(ui->label_endcall);
            } else if(tmp == "F24") {
                setLableBackcolor(ui->label_call);
            }
        }

    }

}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    unsigned int msgType = msg->message;

    if(msgType == WM_DEVICECHANGE) {
        //emit DeviceChangeCbk();
        if(msg->wParam == DBT_DEVICEARRIVAL)
        {
            qDebug("usb in");
            //this->mUsbIsConnected = true;
        }
        if(msg->wParam == DBT_DEVICEREMOVECOMPLETE)
        {
            qDebug("usb out");
            //this->mUsbIsConnected = false;
        }
    }
    return QWidget::nativeEvent(eventType, message, result);
}


void MainWindow::SyncTestResult()
{

    static unsigned int index = 1;
    //保存为TXT文件
//    bool exist;
    QString fileName;

//    QDir *folder = new QDir;
//    exist = folder->exists("C:/Users/no2/Desktop");//查看目录是否存在（例子是保存到桌面）

//    if(!exist){//不存在就创建
//        bool ok = folder->mkdir("C:/Users/no2/Desktop");
//        if(ok){
//            QMessageBox::warning(this,tr("创建目录"),tr("创建成功!"));//添加提示方便查看是否成功创建
//        }else{
//            QMessageBox::warning(this,tr("创建目录"),tr("创建失败"));
//        }
//    }
    fileName = "测试结果.txt";

    QFile f(fileName);
    if(!f.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)){//追加写入 添加结束符\r\n
        qDebug() << "打开文件失败,数据保存失败";
        return ;
    }else{
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QStringList list;

        list << QString::number(index++);
        list << time;

//        if(testResult.contains("powerup") && testResult.contains("powerdown"))
//            list << "powerOK";
//        else
//            list << "powerER";

//        if(testResult.contains("v+up") && testResult.contains("v+down"))
//            list << "vol+OK";
//        else
//            list << "vol+ER";

//        if(testResult.contains("v-up") && testResult.contains("v-down"))
//            list << "vol-OK";
//        else
//            list << "vol-ER";

//        if(testResult.contains("gpsok"))
//            list << "gpsOK";
//        else
//            list << "gpsER";

        list << "\r\n";
        //testResult.clear();

        f.write(list.join("\t").toLatin1().data());
    }
    f.close();
}


void MainWindow::on_actions_triggered()
{
    QStringList title;
    title << "按键板测试工具";
    title << " - ";

    QString fileName = QFileDialog::getOpenFileName(this,tr("文件对话框！"), ".", tr("ALL(* .*);;"));
    qDebug()<<"filename : "<<fileName;

    title << fileName;

    this->setWindowTitle(title.join(" "));
    this->mAdbPath = fileName;
    emit onAdbPathChanged(this->mAdbPath);
}

void MainWindow::ExeCmdError()
{
    QStringList title;
    title << "按键板测试工具";
    title << " - ";
    title << "请设置adb.exe文件~~";
    this->setWindowTitle(title.join(" "));
}
