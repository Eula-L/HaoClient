#ifndef CKERNEL_H
#define CKERNEL_H
#include "maindialog.h"
#include <QObject>
#include <QString>
//核心处理类
//单例
//1、构造 拷贝、构造、析构  私有化
//2、提供静态公有的获取对象的方法

#include <INetMediator.h>
//class INetMediator;
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
    void slot_dealClientData(unsigned int lSendIP , char* buf , int nlen);
    void slot_dealServerData(unsigned int lSendIP , char* buf , int nlen);
private:
    MainDialog * m_mainDialog;
    QString m_ip;
    QString m_port;
    INetMediator * m_tcpClient;
    INetMediator * m_tcpServer;

};

#endif // CKERNEL_H
