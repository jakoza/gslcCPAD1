#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openUrl(const QString& url);
   // void dataJson(QNetworkReply*reply);
    void handleNetFinished(QNetworkReply * reply);

private slots:
    void on_pushButton_edit_clicked();

    void on_pushButton_generate_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager* mNetManager=NULL;
};
#endif // MAINWINDOW_H
