/*
 * Project name hardcoded in function "on_approve_b_clicked"
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSettings>
#include <QTime>
#include "python2.7/Python.h"
#include <stdlib.h>
// Testing pupose libs
#include <QtDebug>
#include <QDir>

int vaildate(QString password, QString username)
{
    /*
     * validate the username and password in the textBox.
     * Pop error ig textBox is empty.
     *
     * return value:
     *      0: Credentials succesfuly validated.
     *      2: Credentials are invalid
     *      1: Validation failed. Possibly connection problem
     *     -1: Validation failed due to bug in program
     *
     */

    Py_Initialize();
    PyRun_SimpleString("import sys\n"
                       "import os");
    PyRun_SimpleString("sys.path.append( os.path.dirname(os.getcwd()) +'/EasyNetIITM/')");

    PyObject *pName, *pModule, *pFunc, *pArgs;
    pName = PyString_FromString("UsrValidation");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if(pModule!=NULL){
        qDebug()<<"validate module found"<<endl;
        pFunc = PyObject_GetAttrString(pModule, (char*)"validate");
        if(pFunc==NULL){
            qDebug()<<"Validation Failed"<<endl;
            Py_Finalize();
            return -1;
        }
        pArgs = PyTuple_New(2);
        PyTuple_SetItem(pArgs, 0, PyString_FromString(username.toStdString().c_str()));
        PyTuple_SetItem(pArgs, 1, PyString_FromString(password.toStdString().c_str()));
        PyObject_CallObject(pFunc, pArgs);
    }
    else{
        qDebug()<<"Validation failed"<<endl;
        PyErr_Print();
        qDebug()<<endl;
        Py_Finalize();
        return -1;
    }

    Py_Finalize();
    return 1;

}



int approve(QString password, QString username)
{
    Py_Initialize();
    PyRun_SimpleString("import sys\n"
                       "import os");
    PyRun_SimpleString("sys.path.append( os.path.dirname(os.getcwd()) +'/EasyNetIITM/')");

    PyObject *pName, *pModule, *pFunc, *pArgs, *pRet;
    pName = PyString_FromString("NetApprove");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if( pModule!=NULL){
        pFunc = PyObject_GetAttrString(pModule, (char*)"approve");
        pArgs = PyTuple_New(3);
        PyTuple_SetItem(pArgs, 0, PyInt_FromLong(1));
        PyTuple_SetItem(pArgs, 1, PyString_FromString(username.toStdString().c_str()));
        PyTuple_SetItem(pArgs, 2, PyString_FromString(password.toStdString().c_str()));
        pRet = PyObject_CallObject(pFunc, pArgs);
        if(PyLong_AsLong(pRet)==0){
            // Successful approval
            return 0;
        }
        else if(PyLong_AsLong(pRet)==1){
            // TODO: retry
            return 1;
        }
    }
    else{
        qDebug()<<"approve Python module not found"<<endl;
        PyErr_Print();
        qDebug()<<endl;
    }

    Py_Finalize();

    return 1;

}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void delay(int n)
{
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void MainWindow::on_save_b_clicked()
{
    QString pass = ui->password_le->text();
    QString usrn = ui->username_le->text();
//    int valid = validate_pass_usrn(pass, usrn);
    int valid = 1;
    if(valid == 1)      // valid password
    {
        QSettings settings;
        settings.setValue("username", usrn);
        settings.setValue("password", pass);
        QMessageBox::information(this,"Success",
                                 "Credentials saved successfully");
    }
    else if(valid == 2) // could not validate: possibly connection unavailable
    {
        QMessageBox::warning(this, "Validation Fail",
                             "Failed to validate Credentials\n"
                             "Check your connection");
    }
    else{
        QMessageBox::critical(this, "Invalid Credentials",
                             "Invalid username or password");
    }
}


void MainWindow::on_approve_b_clicked()
{
    QSettings settings;
    QString password = settings.value("password").toString();
    QString username = settings.value("username").toString();
    QMessageBox::information(this, "Credentials", "Pass:"+password+" User:"+username);
    approve(password, username);
}


void MainWindow::on_validate_b_clicked()
{
    QString password = ui->password_le->text();
    QString username = ui->username_le->text();
    if(password==NULL || username==NULL){
        // TODO: Disable button if password/ username field is empty
        QMessageBox::warning(this, "Empty Credentials", "Password or Username field is empty");
        return;
    }
    else{
        vaildate(password, username);
    }
}
