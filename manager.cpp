#include "manager.h"
#include "ui_manager.h"
#include"inputlicense.h"
#include"global.h"
#include<QDateEdit>
#include <QDebug>
#include<QDate>
#include <QMessageBox>
#include<QSqlQuery >
#include <QSqlQueryModel>
#include <QSqlTableModel>
manager::manager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manager)
{
    ui->setupUi(this);
    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_2->setCalendarPopup(true);
    ui->dateEdit->setDisplayFormat("yyyy-MM-dd");
    ui->dateEdit_2->setDisplayFormat("yyyy-MM-dd");
    ui->dateEdit->setMinimumDate(QDate::currentDate().addDays(0));  //限制有效日期的范围
    ui->dateEdit_2->setMinimumDate(QDate::currentDate().addDays(0));  // -365天
    model = new QSqlQueryModel(this);
    model->setHeaderData(0, Qt::Horizontal, tr("车牌"));
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(46,46,46),stop:1 rgb(66,66,66));color: rgb(210,210,210);;padding-left: 4px;border: 1px solid #383838;}"); //设置表头背景色
    ui->tableView->setAlternatingRowColors(true); //使用交替行颜色
    ui->tableView->horizontalHeader()->setVisible(false);
    ui->tableView->verticalHeader()->setVisible(false);
    qDebug()<<ui->dateEdit->date().daysTo(ui->dateEdit_2->date())<<"oooo"<<ui->dateEdit_2->text()<<ui->dateEdit_2->text().mid(0,4).toInt()<<ui->dateEdit_2->text().mid(5,2).toInt()<<ui->dateEdit_2->text().mid(8,2).toInt();
    connect(ui->tableView, SIGNAL(clicked ( const QModelIndex &)), this,SLOT(show3()));
 }
void manager::show3()
{
    int curRow = ui->tableView->currentIndex().row();
    qDebug()<<model->index(curRow,0).data().toInt()<<model->index(curRow,1).data().toString();
    showinfo3(model->index(curRow,0).data().toInt());

}

void manager::showinfo3(int row)
{
    QSqlQuery query;
    query.exec(QString("select * from carinfo where carid='%1'").arg(row));
    while(query.next())
    {
        //ui->label->setText(query.value(0).toString());   //车型id
        QSqlQuery query9;
        query9.exec(QString("select insurancenum,insurancecompany from insuranceinfo where insuranceid='%1'").arg(query.value(0).toInt()));
        while(query9.next())
        {
            ui->label->setText(QString(query9.value(1).toString()+query9.value(0).toString()));   //车型id
        }

        QSqlQuery query8;
        query8.exec(QString("select carmodel from carmodel where cartypeid='%1'").arg(query.value(1).toInt()));
        while(query8.next())
        {
            ui->label_2->setText(query8.value(0).toString());   //车型id
        }
       // ui->label_2->setText(query.value(1).toString()); //车牌
        ui->label_3->setText(query.value(3).toString());//保险id
        ui->label_4->setText(query.value(4).toString()); //车龄
        ui->label_5->setText(query.value(5).toString());//燃油编号
        ui->label_6->setText(query.value(6).toString()); //购买日期
        ui->label_7->setText(query.value(7).toString());  //颜色
        //ui->label_8->setText(query.value(8).toString()); //zhuang
        ui->label_9->setText(query.value(9).toString());   //产地
        //ui->label_10->setText(query.value(10).toString());
       // ui->label_11->setText(query.value(11).toString());
        QPixmap photo2;
        int g=query.value(1).toInt();
        QSqlQuery query2;
        query2.exec(QString("select carphoto from carmodel where cartypeid='%1'").arg(g));
        while(query2.next())
        {
        photo2.loadFromData(query2.value(0).toByteArray(), "jpg");
        if(photo2.isNull())
        {
            QPixmap pixmap2;
            pixmap2=QPixmap(":/1.png");
            //m_pLabel->setPixmap(pixmap);
            //QPixmap *pixmap=new QPixmap(:/1.png);
            ui->label_12->setPixmap(pixmap2);
            pixmap2.scaled(ui->label_12->size());//图像适应label大小

        }
        else
        {
            ui->label_12->setPixmap(photo2);
        }
        }
    }
}

manager::~manager()
{
    delete ui;
}
void manager::getcar()    //和inputlicense类传递消息
{

    qDebug()<<"你到底买不买车啊";
    qDebug()<<model->index(1,0).data().toInt()<<model->index(1,1).data().toString();

}
void manager::on_pushButton_clicked()
{
    qDebug()<<ui->dateEdit->date().daysTo(ui->dateEdit_2->date())<<"oooo"<<ui->dateEdit_2->text()<<ui->dateEdit_2->text().mid(0,4).toInt()<<ui->dateEdit_2->text().mid(5,2).toInt()<<ui->dateEdit_2->text().mid(8,2).toInt();
  if(ui->dateEdit->date().daysTo(ui->dateEdit_2->date())<=0)
  {
      QMessageBox::information(this,tr("提示"),tr("请输入正确时间间隔！      \n\n     "));
  }
  else     //显示可以被租出去的车
  {
      if(ui->dateEdit->date()<ui->dateEdit_2->date())
      {
      qDebug()<<"jsjsajcjs";
      }
      model->setQuery(QString("select carid,carnumber from carinfo where carid not in(select carid from rentinfo where ( rentbegin<'%1'and preend>'%2') or ('%3'<preend and preend<'%4'))").arg(ui->dateEdit->text()).arg(ui->dateEdit->text()).arg(ui->dateEdit->text()).arg(ui->dateEdit_2->text()));
      ui->tableView->hideColumn(0);
      //先查所有车辆，然后在订单表子查询结束时间比订单表开始时间早或者开始时间比结束时间晚
  }
}

void manager::on_pushButton_2_clicked()
{
    int flag=0;
    QString license=ui->lineEdit->text();
    licensenumber=license;//将驾照号码传递给全局变量
    if(license.length()==2)
    {
    int curRow = ui->tableView->currentIndex().row();
    int h=model->index(curRow,0).data().toInt();
    if(h!=0)
    {
       //查询驾照是否已经有了
        QSqlQuery query;//model2->index(curRow,0).data().toInt()
        qDebug()<<model->index(curRow,0).data().toString()<<"fdvdfsdfsd"<<h;
        query.exec(QString("select licenseid from licenseid where licensenum='%1'").arg(license)) ;//"delete from carmodel where carmodelid=")
        while(query.next())
        {
            flag=1;
            qDebug()<<query.value(0).toInt()<<"HEHEHHEHHEEH";//如果查到那人的驾驶证号，
            /*下面是租车操作，同inputlicense类
             *
             *
             *
             */
        }
        if(flag==0)   //flag=0时说明没有该驾驶证
        {
            inputlicense license1;
            license1.exec();
        }
    }
    else
    {
        QMessageBox::information(this,tr("提示"),tr("请选择要删除的车型！      \n\n     "));
    }
    }
    else
    {
        QMessageBox::information(this,tr("提示"),tr("请输入18位驾驶证号      \n\n     "));
    }
}
