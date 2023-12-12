#ifndef CKERNEL_H
#define CKERNEL_H
#include "maindialog.h"
#include <QObject>
#include <QString>
//核心处理类
//单例
//1、构造 拷贝、构造、析构  私有化
//2、提供静态公有的获取对象的方法

//#include <INetMediator.h>
class INetMediator;

//#define USE_SERVER 1
//#define USE_TEST 1

class CKernel : public QObject
{
    Q_OBJECT
private:
    explicit CKernel(QObject *parent = nullptr);
    explicit CKernel(CKernel &kernel){}
    ~CKernel(){}
    void loadIniFile();
signals:

public:
    static CKernel* GetInstance()
    {
        static CKernel kernel;
        return & kernel;
    }

private slots:
    //普通槽函数
    void slot_destory();

    //网络槽函数
    //客户端的函数，处理来自服务端的数据
    void slot_dealClientData(unsigned int lSendIP , char* buf , int nlen);
#ifdef USE_SERVER
    //服务端的函数，处理来自客户端的数据
    void slot_dealServerData(unsigned int lSendIP , char* buf , int nlen);
#endif
private:
    MainDialog * m_mainDialog;
    QString m_ip;
    QString m_port;
    INetMediator * m_tcpClient;
#ifdef USE_SERVER
    INetMediator * m_tcpServer;
#endif

};

#endif // CKERNEL_H
