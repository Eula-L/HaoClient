#include "ckernel.h"
#include <QDebug>
CKernel::CKernel(QObject *parent) : QObject(parent)
{
    m_mainDialog = new MainDialog;

    connect(m_mainDialog,SIGNAL(SIG_close()),
            this,SLOT(slot_destory()));

    m_mainDialog->show();
}

void CKernel::slot_destory()
{
    qDebug()<<__func__;
    delete m_mainDialog;
}
