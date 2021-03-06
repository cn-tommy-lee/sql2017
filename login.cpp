#include<QMessageBox>
#include<QSqlQuery>
#include<QDebug>
#include<QTime>
#include "login.h"
#include "ui_login.h"
#include"global.h"
#include"admin.h"
#include"finance.h"
#include"manager.h"
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkrequest.h>
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->password->setEchoMode( QLineEdit::Password );
    ui->user->setPlaceholderText("用户名");
    ui->password->setPlaceholderText("密码");
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    QString username = ui->user->text();
    QString creator=username;
    QString password = ui->password->text();
    if(username.isEmpty() || password.isEmpty())
    {
        QMessageBox::information(this,tr("提示%1").arg(username),
                              tr("请输入完整信息!"),QMessageBox::Ok);
    }
    else if(!ui->radio1->isChecked() && !ui->radio2->isChecked()&& !ui->radio3->isChecked()) //没选择身份
    {
        QMessageBox::information(this,tr("提示%1").arg(username),
                              tr("请选择登陆用户!"),QMessageBox::Ok);
        return;
    }
    else if(ui->radio1->isChecked()) //财务0
    {
      flag=0;
      int flag_user=1;
      QSqlQuery query2;
      query2.exec(QString("select clientid,password,type from clientinfo where clientid='%1' and type='%2'").arg(username).arg(flag));
      //query2.exec("select clientid,password,type from clientinfo");
      while(query2.next())
      {
          if(query2.value(0).toString() == username && query2.value(2).toInt() == flag)
          {
             flag_user=0;
             if(query2.value(1).toString() == password)
             {
                  //userinfo=username;
                  qDebug()<<"caiwu  "<<flag<<"";
                  accept(); //user++;
                  this->close();
             }
             else
             {
                  QMessageBox::information(this,tr("错误%1").arg(username),
                                       tr("密码错啦!"),QMessageBox::Ok);
                  ui->password->clear();
                  ui->password->setFocus();
             }
           }
      }
      if(flag_user==1)    //判断用户名是否正确
      {
          QMessageBox::information(this,tr("错误%1").arg(username),
                                tr("没这个用户!"),QMessageBox::Ok);
          ui->user->clear();
          ui->password->clear();
          ui->user->setFocus();
      }

    }
    else if (ui->radio2->isChecked())  //管理1
    {
      flag=1;
      int flag_admin=1;
      QSqlQuery query2;
      query2.exec(QString("select clientid,password,type from clientinfo where clientid='%1' and type='%2'").arg(username).arg(flag));

      //query2.exec("select clientid,password,type from clientinfo");
      while(query2.next())
      {

         if(query2.value(0).toString() == username && query2.value(2).toInt() == flag)
          {
             flag_admin=0;
             if(query2.value(1).toString() == password)
             {
                  //userinfo=username;
                  qDebug()<<"guanli "<<flag<<"";
                  accept(); //user++;
                  this->close();
             }
             else
             {
                  QMessageBox::information(this,tr("错误%1").arg(username),
                                       tr("密码错啦!"),QMessageBox::Ok);
                  ui->password->clear();
                  ui->password->setFocus();
             }
           }
      }
      if(flag_admin==1)    //判断用户名是否正确
      {
          QMessageBox::information(this,tr("错误%1").arg(username),
                                tr("没这个用户!"),QMessageBox::Ok);
          ui->user->clear();
          ui->password->clear();
          ui->user->setFocus();
      }



    }
    else if(ui->radio3->isChecked())    //分店
    {
       flag=2;
       int flag_manager=1;
       QSqlQuery query2;
       query2.exec(QString("select clientid,password,type from clientinfo where clientid='%1' and type='%2'").arg(username).arg(flag));

       //query2.exec("select clientid,password,type from clientinfo");
       while(query2.next())
       {

          if(query2.value(0).toString() == username && query2.value(2).toInt() == flag)
           {
              flag_manager=0;
              if(query2.value(1).toString() == password)
              {
                   //userinfo=username;
                   qDebug()<<"dendian  "<<flag<<"";
                   //需要把shopid赋值
                   QSqlQuery query3;
                   query3.exec(QString("select shopid from shopinfo where shopkeeper='%1'").arg(creator));
                   while(query3.next())
                   {
                        qDebug()<<shopid<<query3.value(0).toString()<<"zheliasdmkasjdkasd";
                        shopid=query3.value(0).toInt();
                        qDebug()<<shopid;
                   }
                   accept(); //user++;
                   this->close();
              }
              else
              {
                   QMessageBox::information(this,tr("错误%1").arg(username),
                                        tr("密码错啦!"),QMessageBox::Ok);
                   ui->password->clear();
                   ui->password->setFocus();
              }
            }
       }
       if(flag_manager==1)    //判断用户名是否正确
       {
           QMessageBox::information(this,tr("错误%1").arg(username),
                                 tr("没这个用户!"),QMessageBox::Ok);
           ui->user->clear();
           ui->password->clear();
           ui->user->setFocus();
       }
    }

}

