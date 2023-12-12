#include "ckernel.h"
#include <QDebug>
#include <QCoreApplication>//获取核心路径
#include <QFileInfo>
#include <QSettings>
CKernel::CKernel(QObject *parent) : QObject(parent)
{
    //加载配置文件
    loadIniFile();
    m_mainDialog = new MainDialog;

    connect(m_mainDialog,SIGNAL(SIG_close()),
            this,SLOT(slot_destory()));

    m_mainDialog->show();
}

void CKernel::loadIniFile()
{
    qDebug()<<__func__;
    //设置一个默认值
    m_ip = "192.168.159.129";
    m_port = "8000";
    //获取exe目录
    QString path = QCoreApplication::applicationDirPath()+="/config.ini";
    //根据目录
    //查看文件是否存在，存在加载，不存在创建并写入默认值
    QFileInfo info(path);
    if(info.exists())
    {
        qDebug()<<"存在";
        //存在
        QSettings setting(path,QSettings::IniFormat);
        //打开组
        setting.beginGroup("net");
        //读取
        auto strIP = setting.value("ip","");
        auto strPort = setting.value("port","");
        if(!strIP.toString().isEmpty())
        {
            m_ip = strIP.toString();
        }
        if(!strPort.toString().isEmpty())
        {
            m_port = strPort.toString();
        }
        //关闭组
        setting.endGroup();
    }
    else
    {
        qDebug()<<"不存在";
        //不存在
        QSettings setting(path,QSettings::IniFormat);//创建
        //打开组
        setting.beginGroup("net");
        //设置
        setting.setValue("ip",m_ip);
        setting.setValue("port",m_port);
        //关闭组
        setting.endGroup();
    }
    qDebug()<<"ip: "<<m_ip<<"port: "<<m_port;
}

void CKernel::slot_destory()
{
    qDebug()<<__func__;
    delete m_mainDialog;
}
