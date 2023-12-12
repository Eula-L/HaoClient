#ifndef CKERNEL_H
#define CKERNEL_H
#include "maindialog.h"
#include <QObject>
//核心处理类
//单例
//1、构造 拷贝、构造、析构  私有化
//2、提供静态公有的获取对象的方法

class CKernel : public QObject
{
    Q_OBJECT
private:
    explicit CKernel(QObject *parent = nullptr);
    explicit CKernel(CKernel &kernel){}
    ~CKernel(){}

signals:

public:
    static CKernel* GetInstance()
    {
        static CKernel kernel;
        return & kernel;
    }

private slots:

    void slot_destory();
private:
    MainDialog * m_mainDialog;

};

#endif // CKERNEL_H
