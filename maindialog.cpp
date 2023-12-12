#include "maindialog.h"
#include "ui_maindialog.h"
#include <QMessageBox>
MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainDialog)
{
    ui->setupUi(this);
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::question(this,"退出提示","是否退出?")==QMessageBox::Yes)
    {
        //关闭
        event->accept();//同意退出
        Q_EMIT SIG_close();//发送关闭信号
    }
    else
    {
        event->ignore();//忽略
    }
}

