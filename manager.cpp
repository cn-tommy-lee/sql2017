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
#include<QStandardItemModel>
#include"rotatedproxymodel.h"
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
    //ui->tableView->hideColumn(0);
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(46,46,46),stop:1 rgb(66,66,66));color: rgb(210,210,210);;padding-left: 4px;border: 1px solid #383838;}"); //设置表头背景色
    ui->tableView->setAlternatingRowColors(true); //使用交替行颜色
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //设置表格列宽度自适应
    //ui->tableView->horizontalHeader()->setVisible(false);
    ui->tableView->verticalHeader()->setVisible(false);
    qDebug()<<ui->dateEdit->date().daysTo(ui->dateEdit_2->date())<<"oooo"<<ui->dateEdit_2->text()<<ui->dateEdit_2->text().mid(0,4).toInt()<<ui->dateEdit_2->text().mid(5,2).toInt()<<ui->dateEdit_2->text().mid(8,2).toInt();
    //ui->spinBox->setMinimum(500);
    //connect(ui->tableView, SIGNAL(clicked ( const QModelIndex &)), this,SLOT(show3()));
    connect(ui->checkBox,SIGNAL(stateChanged(int)),this,SLOT(show5(int)));
    connect(ui->checkBox_2,SIGNAL(stateChanged(int)),this,SLOT(show6(int)));

    /*
     *续租
     *show4()  为续租
     */
     model2 = new QSqlQueryModel(this);
     //model2->setQuery(QString("select * from rentinfo where licenseid='%1' and rentstatus='0'").arg(licenidflag));//
     ui->tableView_2->setModel(model2);
     model2->setQuery(QString("select * from rentinfo where rentstatus='0'"));
     // model2->setQuery(QString("select * from rentinfo"));



    // ui->tableView_2->setModel(model2);
     ui->tableView_2->setSelectionBehavior ( QAbstractItemView::SelectRows);
     ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
     //ui->tableView_2->setSelectionBehavior(SelectRows);
     ui->tableView_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(46,46,46),stop:1 rgb(66,66,66));color: rgb(210,210,210);;padding-left: 4px;border: 1px solid #383838;}"); //设置表头背景色
     ui->tableView_2->setAlternatingRowColors(true); //使用交替行颜色
     ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //设置表格列宽度自适应

     ui->tableView_2->hideColumn(0);
     ui->tableView_2->hideColumn(2);
     ui->tableView_2->hideColumn(3);
     ui->tableView_2->hideColumn(4);
     ui->tableView_2->hideColumn(5);
     ui->tableView_2->hideColumn(7);
     ui->tableView_2->hideColumn(8);
     ui->tableView_2->hideColumn(9);
     ui->tableView_2->hideColumn(10);
     ui->tableView_2->hideColumn(11);
     ui->tableView_2->hideColumn(12);
     ui->tableView_2->hideColumn(13);

     ui->dateEdit_3->setDate(QDate::currentDate());
     ui->dateEdit_3->setCalendarPopup(true);
     ui->dateEdit_3->setDisplayFormat("yyyy-MM-dd");
     ui->dateEdit_4->setDate(QDate::currentDate());
     ui->dateEdit_4->setCalendarPopup(true);
     ui->dateEdit_4->setDisplayFormat("yyyy-MM-dd");
     ui->dateEdit_5->setDate(QDate::currentDate());
     ui->dateEdit_5->setCalendarPopup(true);
     ui->dateEdit_5->setDisplayFormat("yyyy-MM-dd");
     connect(ui->tableView_2, SIGNAL(clicked ( const QModelIndex &)), this,SLOT(show4()));
     connect(ui->tableView, SIGNAL(clicked ( const QModelIndex &)), this,SLOT(show3()));

     QSqlQuery query11;
     query11.exec(QString("select cartypeid,carmodel from carmodel"));
     while(query11.next())
     {
        ui->comboBox->addItem(query11.value(0).toString()+'-'+query11.value(1).toString());

     }
     ui->tableWidget_2->verticalHeader()->setVisible(false); //设置垂直头不可见
     ui->tableWidget_2->horizontalHeader()->setVisible(false);
     ui->tableWidget->verticalHeader()->setVisible(false); //设置垂直头不可见
     ui->tableWidget->horizontalHeader()->setVisible(false);
     //ui->tableWidget_2->horizontalHeader()->resizeSection(0,50); //设置表头第一列的宽度为150


     // QString a="1920x1080";
     //QString first = a.split('x', QString::SkipEmptyParts).first();
     // QString second = a.split('x', QString::SkipEmptyParts).last();
     //qDebug()<<first<<second<<"hehhehe";
 }
void manager::show3()
{
     int curRow = ui->tableView->currentIndex().row();
     qDebug()<<model->index(curRow,0).data().toInt()<<model->index(curRow,1).data().toString();
     showinfo3(model->index(curRow,0).data().toInt());

}
void manager::show4()
{
     int curRow = ui->tableView_2->currentIndex().row();
     /*获得驾驶证号
     *
     *
     *
     */
     //qDebug()<<model2->index(curRow,3).data().toInt()<<model2->index(curRow,1).data().toString();
     //showinfo4(model2->index(curRow,0).data().toInt());

}
void manager::show5(int state)
{
     //ui->dateEdit_4->setEnabled(0);
     // ui->dateEdit_5->setEnabled(1);
     if (state == Qt::Checked) // "选中"
     {
        ui->dateEdit_4->setEnabled(0);
        ui->dateEdit_5->setEnabled(0);
        }
        else if(state == Qt::PartiallyChecked) // "半选"
        {
            ui->dateEdit_4->setEnabled(0);
            ui->dateEdit_5->setEnabled(0);
        }
        else // 未选中 - Qt::Unchecked
        {
           ui->dateEdit_4->setEnabled(1);
           ui->dateEdit_5->setEnabled(1);
        }

    qDebug()<<"响应时间";

}
void manager::show6(int state)
{
    //ui->dateEdit_4->setEnabled(0);
    // ui->dateEdit_5->setEnabled(1);
    if (state == Qt::Checked) // "选中"
    {
         ui->comboBox->setEnabled(0);
         //ui->dateEdit_5->setEnabled(0);
    }
    else if(state == Qt::PartiallyChecked) // "半选"
    {
        ui->comboBox->setEnabled(0);
    }
    else // 未选中 - Qt::Unchecked
    {
        ui->comboBox->setEnabled(1);
    }

}
void manager::showinfo4(int row)
{

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
            ui->label->setText(QString(query9.value(1).toString()+query9.value(0).toString()));   //保险信息
        }

        QSqlQuery query8;
        query8.exec(QString("select carmodel,fuelid,rentmoney,dayrentmoney from carmodel where cartypeid='%1'").arg(query.value(1).toInt()));
        while(query8.next())
        {
            ui->label_2->setText(query8.value(0).toString());   //车型id
            ui->label_25->setText((query8.value(2)).toString());
            int g=(ui->dateEdit->date().daysTo(ui->dateEdit_2->date())*1.5*(query8.value(3).toInt()));
            // qRound(g)

            ui->label_26->setText(QString::number(g));
           ui->label_28->setText(QString::number(g+query8.value(2).toInt()));
            premon=g+query8.value(2).toInt();
            qDebug()<<g<<"钱多少"<<g<<g%10<<(g%100)*100<<query8.value(2).toInt();
        }
        // ui->label_2->setText(query.value(1).toString()); //车牌
        ui->label_3->setText(query.value(3).toString());//保险id
        ui->label_4->setText(query.value(4).toString()); //车龄
        ui->label_5->setText(query.value(5).toString());//车身编号
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
         model->setQuery(QString("select carid,carnumber from carinfo where carid not in(select carid from rentinfo where ( rentbegin<='%1'and preend>='%2' and remark='0') or ('%3'>preend and preend>='%4' and remark='0'))").arg(ui->dateEdit_2->text()).arg(ui->dateEdit_2->text()).arg(ui->dateEdit_2->text()).arg(ui->dateEdit->text()));
         ui->tableView->hideColumn(0);
         //先查所有车辆，然后在订单表子查询结束时间比订单表开始时间早或者开始时间比结束时间晚
    }
}

void manager::on_pushButton_2_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QMessageBox::information(this,tr("提示"),tr("请输入驾驶证号      \n\n     "));

    }
    else
    {
        int flag=0;
        //QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
        // qDebug()<< time.toString("yyyyMMdd"+creator); //设置显示格式<<"看看看";//如果查到那人的驾驶证号，
        QString license=ui->lineEdit->text();
        licensenumber=license;//将驾照号码传递给全局变量
        if(license.length()==5)
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
                    *query.value(0).toInt()  licenseid
                    *model->index(curRow,0).data().toString()  carid
                    *产生rentnum  日期加经理账号加carid
                    * 需要查询shopid
                    * ui->dateEdit->date()  rentbegin开始
                    * ui->dateEdit_2->date() preend结束
                    * 生成订单号
                    */
                    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
                    qDebug()<< time.toString("yyyyMMdd"+creator+license); //设置显示格式<<"看看看";//如果查到那人的驾驶证号，
                    QSqlQuery query7;
                    query7.prepare("INSERT INTO rentinfo(rentnum,shopid,licenseid,carid,rentbegin,preend,premoney,rentstatus,creater,amenddate) values(:rentnum,:shopid,:licenseid,:carid,:rentbegin,:preend,:premoney,:rentstatus,:creater,:amenddate)");
                    query7.bindValue(":rentnum",time.toString("yyyyMMddhhmmss"+creator+license));
                    query7.bindValue(":shopid",shopid);
                    query7.bindValue(":licenseid",query.value(0).toInt());
                    query7.bindValue(":carid",model->index(curRow,0).data().toInt());
                    query7.bindValue(":rentbegin",ui->dateEdit->text());
                    query7.bindValue(":preend",ui->dateEdit_2->text());
                    query7.bindValue(":premoney",premon);       //preend
                    query7.bindValue(":rentstatus",0);  //premoney

                    query7.bindValue(":creater",creator);
                    query7.bindValue(":amenddate",QString(QDateTime::currentDateTime().toString("yyyy-MM-dd")));
                    query7.exec();
                    qDebug()<<"bigbigibgi"<<shopid<<query.value(0).toInt()<<model->index(curRow,0).data().toInt();
                    qDebug()<<ui->dateEdit->date()<<ui->dateEdit_2->text();//如果查到那人的驾驶证号，
                    model->setQuery(QString("select carid,carnumber from carinfo where carid not in(select carid from rentinfo where ( rentbegin<='%1'and preend>='%2') or ('%3'>preend and preend>='%4'))").arg(ui->dateEdit_2->text()).arg(ui->dateEdit_2->text()).arg(ui->dateEdit_2->text()).arg(ui->dateEdit->text()));
                    QMessageBox::information(this,tr("提示"),tr("租赁成功！      \n\n     "));


            }
            if(flag==0)   //flag=0时说明没有该驾驶证
            {
                inputlicense license1;
                license1.exec();
            }
        }
        else
        {
            QMessageBox::information(this,tr("提示"),tr("请选择要租赁的车型！      \n\n     "));
        }
        }
        else
        {
            QMessageBox::information(this,tr("提示"),tr("请输入正确的五位驾驶证号      \n\n     "));
        }

}
}
void manager::on_pushButton_3_clicked()
{
    //model2->setQuery(QString("select * from rentinfo"));
    /*
     * 首先判断驾驶证号是否合法
     *在订单表查询该驾驶证未完成的订单
     */
    int licenidflag=0;
    QString license5=ui->lineEdit_3->text();
    //现在在licenseinfo里面查是否有这个驾驶证号,如果有则返回licenseid
    QSqlQuery query;
    query.exec(QString("select licenseid from licenseid where licensenum='%1'").arg(license5)) ;//"delete from carmodel where carmodelid=")
    while(query.next())
    {
        licenidflag=query.value(0).toInt();
        //qDebug()<<licenidflag<<query.value(6)<<"8888888j";//如果查到那人的驾驶证号，

    }
    //qDebug()<<licenidflag<<query.value(6)<<"8888888j";//如果查到那人的驾驶证号，
    model2->setQuery(QString("select * from rentinfo where licenseid='%1' and rentstatus='0'").arg(licenidflag));//
    //现在通过获取的licenseflag在rent表中查该司机的订单，并返回到table
    //licensenumber=license;//将驾照号码传递给全局变量



}

void manager::on_pushButton_4_clicked()
{
    int curRow = ui->tableView_2->currentIndex().row();
    if(ui->lineEdit_3->text().isEmpty())
    {
        QMessageBox::information(this,tr("提示"),tr("请输入需要查询的驾驶证号      \n\n     "));

    }
    else
    {
    if(model2->index(curRow,0).data().toInt()!=0)
    {
        qDebug()<<model2->index(curRow,6).data().toDate();
        //先判断是否选中表格的车型
        //然后判断时间是否小于原来的preend
        if(ui->dateEdit_3->date()>model2->index(curRow,6).data().toDate())
        {
             //进行续租操作
             /*
              * 更新rentinfo里preend
              * 更新relet里
              *
              */
             QSqlQuery query7;
             query7.prepare("INSERT INTO reletinfo(rentid,reletbegin,reletend,totaltime,creater,reletdate) values(:rentid,:reletbegin,:reletend,:totaltime,:creater,:reletdate)");
             query7.bindValue(":rentid",model2->index(curRow,0).data().toInt());
             query7.bindValue(":reletbegin",model2->index(curRow,6).data().toString());
             query7.bindValue(":reletend",ui->dateEdit_3->text());
             query7.bindValue(":totaltime",model2->index(curRow,6).data().toDate().daysTo(ui->dateEdit_3->date()));
             query7.bindValue(":creater",creator);
             query7.bindValue(":reletdate",QString(QDateTime::currentDateTime().toString("yyyy-MM-dd")));
             query7.exec();
             QSqlQuery query6;
             query6.prepare("UPDATE rentinfo SET preend=? where rentid=?");
             query6.addBindValue(ui->dateEdit_3->text());
             query6.addBindValue(model2->index(curRow,0).data().toInt());
             qDebug()<<ui->dateEdit_3->text()<<model2->index(curRow,0).data().toInt()<<"这里这里";

             query6.exec();
             QSqlQuery query;
             query.exec(QString("select licenseid from licenseid where licensenum='%1'").arg(ui->lineEdit_3->text())) ;//"delete from carmodel where carmodelid=")
             while(query.next())
             {
                 model2->setQuery(QString("select * from rentinfo where licenseid='%1' and rentstatus='0'").arg(query.value(0).toInt()));
             }
             QMessageBox::information(this,tr("提示"),tr("恭喜续租成功\n\n     "));

        }
        else
        {
             QMessageBox::information(this,tr("提示"),tr("续租日期小于原定交车时间，请选择大于时间      \n\n     "));
        }
    }
    else
    {

        QMessageBox::information(this,tr("提示"),tr("请选择需要续租的ding'd订单号      \n\n     "));

    }
    }
}

void manager::on_pushButton_5_clicked()
{
    /*
     * 还车
     * 将订单状态rentstatus改为1
     * 统计所有费用realmoney
     * 更新realend
     *判断是否点击了某行
     * 获取rentid,将该车状态改为0
     * 把realend改为今天
     * 计算钱  减去押金
    */
    int curRow = ui->tableView_2->currentIndex().row();
    // model2->index(curRow,0).data().toInt()
    if(model2->index(curRow,0).data().toInt()!=0)
    {

        if(ui->lineEdit_2->text().toInt()<ui->tableWidget_2->item(4, 1)->text().toInt())
        {
            QMessageBox::information(this,tr("提示"),tr("请输入正确公里数      \n\n     "));

        }//行驶公里数
        else
        {
            //开始还车
            /*  修改该订单status 为已完成、
             * 修改realend为当前日期
             * 填写realmoney、
             * 当前公里写carmodel对应的数据
             * 弹出qmessbox提示该缴纳的金额
             *model2初始查询
             */
             int h=ui->lineEdit_2->text().toInt()-ui->tableWidget_2->item(4, 1)->text().toInt();//获得超公里数
             //int w=h*;
             QSqlQuery query;
             query.exec(QString("select cartypeid from carinfo where carid='%1'").arg(model2->index(curRow,4).data().toInt())) ;//"delete from carmodel where carmodelid=")
             while(query.next())
             {
                 QSqlQuery query2;
                 query2.exec(QString("select overkilmmoney from carmodel where cartypeid='%1'").arg(query.value(0).toString())) ;//"delete from carmodel where carmodelid=")
                 while(query2.next())
                 {
                      qDebug()<<query2.value(0).toInt()<<"金三盘";
                      qDebug()<<h*query2.value(0).toInt();//超公里产生的费用
                                                          //ui->tableWidget_2->item(3, 1)->text().toInt()
                      qDebug()<<h*query2.value(0).toInt()+ui->tableWidget_2->item(3, 1)->text().toInt();//总费用产生
                      QSqlQuery query3;
                      query3.prepare("UPDATE rentinfo SET rentstatus=?,realend=?,realmoney=? where rentid=?");
                      query3.addBindValue("1");
                      query3.addBindValue(QString(QDateTime::currentDateTime().toString("yyyy-MM-dd")));
                      if(model2->index(curRow,5).data().toDate()>QDate::currentDate())
                      {
                      query3.addBindValue(0);
                      }
                      else
                      {
                          query3.addBindValue(h*query2.value(0).toInt()+ui->tableWidget_2->item(3, 1)->text().toInt());

                      }
                      query3.addBindValue(model2->index(curRow,0).data().toInt());
                      query3.exec();
                      if(model2->index(curRow,5).data().toDate()<=QDate::currentDate())
                      {
                          QMessageBox::information(this,tr("提示"),
                                                tr("成功还车,用户还需缴纳%1元!!").arg(h*query2.value(0).toInt()-ui->tableWidget_2->item(1, 1)->text().toInt()+ui->tableWidget_2->item(3, 1)->text().toInt()),QMessageBox::Ok);
                          QSqlQuery query4;
                          query4.prepare("UPDATE carinfo SET runkilm=? where carid=?");
                          query4.addBindValue(ui->lineEdit_2->text().toInt());
                          query4.addBindValue(model2->index(curRow,4).data().toInt());
                          query4.exec();
                      }
                      else
                      {
                          QMessageBox::information(this,tr("提示"),
                                                tr("用户未使用,需退还用户押金%1元!!").arg(ui->tableWidget_2->item(1, 1)->text().toInt()),QMessageBox::Ok);
                      }

                      //公里数更新

                      //model2更新
                      model2->setQuery(QString("select * from rentinfo where licenseid='%1' and rentstatus='0'").arg(model2->index(curRow,3).data().toInt()));//

                 }
             }
        }
    }
    else
    {
       QMessageBox::information(this,tr("提示"),tr("请选择需要归还的订单号      \n\n     "));

    }
}
void manager::on_tableView_2_clicked(const QModelIndex &index)
 {
    ui->tableWidget_2->setRowCount(5);  //行
    ui->tableWidget_2->setColumnCount(2); // 列
/*
 *
 * QString proName = tableWidget->item(row, col)->text();/获取tablewidget某个数据
 *
 *
 *
 *
 *
 */
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int curRow = ui->tableView_2->currentIndex().row();
    //QString orderNum=model2->index(curRow,0).data().toString();
    // ui->tableWidget_2->model()->data(ui->tableView_2->model()->index(index.row(),0)).toString();
    // QString("select * from rentinfo ");
    //search.append(QString("where rentid='%1'").arg(orderNum));
    qDebug()<<model2->index(curRow,0).data().toInt()<<model2->index(curRow,1).data().toString();
    qDebug()<<model2->index(curRow,3).data().toInt()<<model2->index(curRow,4).data().toInt();
    qDebug()<<model2->index(curRow,5).data().toString()<<model2->index(curRow,6).data().toString();
    ui->tableWidget_2->setItem(0,0,new QTableWidgetItem("车型"));
    ui->tableWidget_2->setItem(1,0,new QTableWidgetItem("总押金"));
    ui->tableWidget_2->setItem(2,0,new QTableWidgetItem("司机"));
    ui->tableWidget_2->setItem(3,0,new QTableWidgetItem("当前产生费用费"));
    ui->tableWidget_2->setItem(4,0,new QTableWidgetItem("初始行驶公里数"));
    ui->tableWidget_2->setItem(1,1,new QTableWidgetItem(model2->index(curRow,8).data().toString()));
   //获取车型,初始公里
    QSqlQuery query;
    query.exec(QString("select cartypeid,runkilm from carinfo where carid='%1'").arg(model2->index(curRow,4).data().toInt())) ;//"delete from carmodel where carmodelid=")
    while(query.next())
    {
         ui->tableWidget_2->setItem(4,1,new QTableWidgetItem(query.value(1).toString()));
         QSqlQuery query2;
         query2.exec(QString("select carmodel,dayrentmoney,overdatemoney from carmodel where cartypeid='%1'").arg(query.value(0).toString())) ;//"delete from carmodel where carmodelid=")
         while(query2.next())
         {
              ui->tableWidget_2->setItem(0,1,new QTableWidgetItem(query2.value(0).toString()));
              //判断是否提前还车
              /*  query2.value(1).toInt()  日租金
               *  query2.value(2).toInt()   超天数费用
               */
              //QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
              // QString str = time.toString("yyyy-MM-dd"); //设置显示格式
              if(model2->index(curRow,6).data().toDate()>QDate::currentDate()&&model2->index(curRow,5).data().toDate()<=QDate::currentDate())
              {
                    // model2->index(curRow,6).data().toDate().daysTo(QDate::currentDate());
                    qDebug()<<"朝田淑啦"<<(model2->index(curRow,5).data().toDate().daysTo(QDate::currentDate()))*query2.value(1).toInt();
                    int h=((model2->index(curRow,5).data().toDate().daysTo(QDate::currentDate()))*query2.value(1).toInt());
                    qDebug()<<h<<QString(h);//
                    ui->tableWidget_2->setItem(3,1,new QTableWidgetItem(QString::number(h)));

              }
              else if(model2->index(curRow,5).data().toDate()>QDate::currentDate())   //说明还未提车
              {
                    ui->tableWidget_2->setItem(3,1,new QTableWidgetItem("当前未产生费用"));
                    qDebug()<<"苟利国家生死以";
              }
              else if(model2->index(curRow,6).data().toDate()<QDate::currentDate())   //说明和没有续租，超期了
              {
                    qDebug()<<"+1s";
                    int h=model2->index(curRow,5).data().toDate().daysTo(model2->index(curRow,6).data().toDate());
                    int m=h*query2.value(1).toInt();
                    qDebug()<<query2.value(1).toInt()<<query2.value(2).toInt()<<"rizujin";
                    int j=model2->index(curRow,6).data().toDate().daysTo(QDate::currentDate());
                    int g=j*query2.value(2).toInt();
                    qDebug()<<h<<m<<"__"<<j<<"haha"<<g;
                    ui->tableWidget_2->setItem(3,1,new QTableWidgetItem(QString::number(g+m)));

              }
          }
       }

      //获取司机
      QSqlQuery query3;
      query3.exec(QString("select drivername from licenseid where licenseid='%1'").arg(model2->index(curRow,3).data().toInt())) ;//"delete from carmodel where carmodelid=")
      while(query3.next())
      {
         ui->tableWidget_2->setItem(2,1,new QTableWidgetItem(query3.value(0).toString()));

      }



}

void manager::on_pushButton_6_clicked()
{
    ui->tableWidget->setRowCount(3);  //行
    ui->tableWidget->setColumnCount(2); // 列

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setItem(0,0,new QTableWidgetItem("订单数量"));
    ui->tableWidget->setItem(1,0,new QTableWidgetItem("总金额"));
    ui->tableWidget->setItem(2,0,new QTableWidgetItem("均价"));

    /*订单数量
     * q.exec("select count(id) as iCount from xx");
     if (q.next())
     {
      q.value(0).toInt();
     }
     */

    QString strqueryOrders=QString("select realmoney from rentinfo where rentstatus='1'");

   /* if(ui->comboBoxVtypeS->currentIndex()>0)
    strqueryOrders.append(QString(" and VtypeID=%1").arg(ui->comboBoxVtypeS->currentIndex()));
    if(!ui->lineEditCarnoS->text().trimmed().isEmpty())
    strqueryOrders.append(QString(" and Vno='%1'").arg(ui->lineEditCarnoS->text().trimmed()));
    qDebug()<<"debug1"<<strqueryOrders;
*/
    if(ui->checkBox->isChecked())     //所有时间
    {
      qDebug()<<"所有时间"<<"debug2";
    }
    else                              //获取时间段，时间段开始小于结束判断
    {
        if(ui->dateEdit_4->date().daysTo(ui->dateEdit_5->date())<=0)
        {
             QMessageBox::information(this,tr("提示"),tr("请输入正确时间间隔！      \n\n     "));
        }
        else  //时间间隔正确
        {
            qDebug()<<"按时间段"<<"debug3";
            strqueryOrders.append(QString(" and rentbegin='%1'' and realend='%2'").arg(ui->dateEdit_4->text()).arg(ui->dateEdit_5->text()));

        }
    }
    if(ui->checkBox_2->isChecked())   //所有车型
    {
          qDebug()<<"debug4"<<"所有车型";
    }
    else                              //获取车型
    {
        QString a=ui->comboBox->currentText();
        QString first = a.split('-', QString::SkipEmptyParts).first();
        QString second = a.split('-', QString::SkipEmptyParts).last();
        strqueryOrders.append(QString(" and carid='%1'").arg(first.toInt()));
        qDebug()<<"按车型"<<"debug5";
        qDebug()<<first.toInt()<<second<<"hehhehe";
    }

    qDebug()<<shopid<<strqueryOrders<<"debug6";
    QSqlQuery query3;
    query3.exec(strqueryOrders) ;//"delete from carmodel where carmodelid=")
    int num=0;
    int total=0;
    while(query3.next())
    {
        num++;
        total=query3.value(0).toInt()+total;
        qDebug()<< query3.value(0).toInt();
    }
    ui->tableWidget->setItem(0,1,new QTableWidgetItem(QString::number(num)));
    ui->tableWidget->setItem(1,1,new QTableWidgetItem(QString::number(total)));
    if(total!=0)
    {
        ui->tableWidget->setItem(2,1,new QTableWidgetItem(QString::number(total/num)));
    }
    else
    {
        ui->tableWidget->setItem(2,1,new QTableWidgetItem("没有记录"));
    }
        qDebug()<<"total money"<<num<<total;
}


