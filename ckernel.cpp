#include "ckernel.h"

CKernel::CKernel(QObject *parent) : QObject(parent)
{
    m_mainDialog = new MainDialog;
    m_mainDialog->show();
}

