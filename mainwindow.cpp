#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mNetManager=new QNetworkAccessManager(this);
    connect(mNetManager, &QNetworkAccessManager::finished, this, &MainWindow::handleNetFinished);
    //connect(mNetManager, &QNetworkAccessManager::finished, this, &MainWindow::dataJson);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openUrl(const QString &url)
{
    mNetManager->get(QNetworkRequest(QUrl(url)));
}


void MainWindow::on_pushButton_edit_clicked()
{
    QString text = QInputDialog::getText(this, "Entry Message", "Text:");
    if(text.length()>0)
        ui->label_charname->setText(text);
}


void MainWindow::on_pushButton_generate_clicked()
{
    //take the text from label
    QString jsonurl = "https://pokeapi.co/api/v2/pokemon/";
    openUrl(jsonurl + ui->label_charname->text());
    //find it in "name" on json
    //display the results in the labels
}

void MainWindow::handleNetFinished(QNetworkReply *reply)
{
    if (reply->error()==QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        QJsonDocument jsondoc = QJsonDocument::fromJson(data);
        QJsonObject jsonobject = jsondoc.object();
        QString name = jsonobject["name"].toString();
        ui->label_pokename->setText(name);
        int base_experience = jsonobject["base_experience"].toInt();
        QString in_base_experience = QString::number(base_experience)+" xp";
        ui->label_baseexp->setText(in_base_experience);
        qDebug() << data;
        QJsonArray types = jsonobject["types"].toArray();
        QString element ="";
        foreach (const QJsonValue & rowvalue, types){
            QJsonObject obj_rowvalue = rowvalue.toObject();
            QJsonObject obj_rowvalue_type = obj_rowvalue["type"].toObject();
            QString obj_rowvalue_type_name = obj_rowvalue_type["name"].toString();
            element += obj_rowvalue_type_name + " ";
        }
        ui->label_element->setText(element);
    }else
        qDebug("Network Error");

}

