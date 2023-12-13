#include "ckernel.h"
#include <QDebug>
#include <QCoreApplication>//获取核心路径
#include <QFileInfo>
#include <QSettings>
#include "TcpClientMediator.h"
#include "TcpServerMediator.h"
#include <QMessageBox>

CKernel::CKernel(QObject *parent) : QObject(parent)
{
    //加载配置文件
    loadIniFile();
#ifdef USE_SERVER
    //开启服务器
    m_tcpServer = new TcpServerMediator;
    connect(m_tcpServer,SIGNAL(SIG_ReadyData(unsigned int, char *, int)),
            this,SLOT(slot_dealServerData(unsigned int, char *, int)));
    //开启网络
    m_tcpServer->OpenNet();//默认0.0.0.0 连接所有网络卡
#endif
    //开启客户端
    m_tcpClient = new TcpClientMediator;
    connect(m_tcpClient,SIGNAL(SIG_ReadyData(unsigned int, char *, int)),
            this,SLOT(slot_dealClientData(unsigned int, char *, int)));
    //客户端应该从配置文件读取服务端的ip
    //暂时
    //测试
    //使用实体机真实地址
    m_tcpClient->OpenNet("192.168.159.129");

    m_mainDialog = new MainDialog;
    connect(m_mainDialog,SIGNAL(SIG_close()),
            this,SLOT(slot_destory()));
    m_mainDialog->show();
#ifdef USE_TEST
    //测试 客户端向服务端传数据
    char strBuf[100] = "hello server";
    int len = strlen("hello server")+1;
    m_tcpClient->SendData(0,strBuf,len);
#endif
    //sizeof(数组名)   整个数组长度
    //strlen()   内容长
    STRU_LOGIN_RQ rq;
    m_tcpClient->SendData(0,(char*)&rq,sizeof(rq));
    qDebug()<<"客户端发送成功";
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
#include <QDebug>
void CKernel::slot_dealClientData(unsigned int lSendIP, char *buf, int nlen)
{
//    QString str = QString("来自服务端的：%1").arg(QString::fromStdString(buf));
//    QMessageBox::about(NULL,"提示",str);//about是阻塞函数，是模态窗口
    int type  = *(int*)buf;
    qDebug()<<__func__;
    //回收空间
    delete[] buf;
}
#ifdef USE_SERVER
void CKernel::slot_dealServerData(unsigned int lSendIP, char *buf, int nlen)
{
    QString str = QString("来自客户端的：%1").arg(QString::fromStdString(buf));
    QMessageBox::about(NULL,"提示",str);//about是阻塞函数，是模态窗口
    //测试
    //服务端直接返回这个数据
    m_tcpServer->SendData(lSendIP,buf,nlen);
    //回收空间
    delete[] buf;
}
#endif
