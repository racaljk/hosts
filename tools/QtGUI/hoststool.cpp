#include "hoststool.h"
#include "ui_hoststool.h"
#include <qdebug.h>
HostsTool::HostsTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HostsTool)
{
    ui->setupUi(this);
    manager =new QNetworkAccessManager(this);
    ui->textEdit->append(">>Initialization success!");
    hosts_source = ui->comboBox->currentText();
    if(!hosts_source.isEmpty())
    {
        ui->textEdit->append("<p style=\"color:green\">>>读取hosts源地址成功</p>");
    }else{
        ui->textEdit->append("<body style=\" font-family;'微软雅黑\'; font-size:10pt; font-weight:72; font-style:normal;\"><p style=\"margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#ff0000;\">&gt;&gt;读取hosts失败，请执行：</span></p><p style=\"margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">·重启软件</span></p><p style=\"margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">·重新下载</span></p></body>");
    }
}

HostsTool::~HostsTool()
{
    delete ui;
}

void HostsTool::on_pushButton_clicked()
{
     ui->textEdit->append("<p style=\"color:green\">>>开始配置hosts</p>");
     QNetworkRequest request ;
     QSslConfiguration config;
     config.setPeerVerifyMode(QSslSocket::VerifyNone);
     config.setProtocol(QSsl::TlsV1_2);
     request.setSslConfiguration(config);

     request.setUrl(QUrl(hosts_source));
     request.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.2; rv:16.0) Gecko/20100101 Firefox/16.0");
     reply = manager->get(request);
     connect(reply, SIGNAL(finished()), this, SLOT(readyread()));
}
void HostsTool::readyread()
{
    QString get = QString::fromUtf8( reply->readAll());
    if(!get.isEmpty())
    {
        ui->textEdit->append("<p style=\"color:green\">>>服务器获取hosts成功,请保证网络通畅</p>");
        ui->textEdit->append(get);
        ui->textEdit->append(">>从<a href=\""+hosts_source+"\">"+hosts_source+"</a>获取hosts成功！");
        QFile file(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+"\\hosts.txt");
        file.open( QIODevice::WriteOnly|QFile::Text);
        if(file.isOpen()){
            QTextStream stream(&file);
            stream<<get;
            file.close();
            ui->textEdit->append("<p style=\"color:green\">>>你可以尝试复制上面的内容到C:\\Windows\\System32\\drivers\\etc\\hosts文件中,或者使用桌面生成的hosts文件(请重命名hosts.txt为hosts再进行覆盖)</p>");
        }else{
            ui->textEdit->append("<p style=\"color:red\">>>未知错误:尝试打开新创建的文件失败!</p>");
            file.close();
        }
    }else{
        ui->textEdit->append("<body style=\" font-family;'微软雅黑\'; font-size:10pt; font-weight:72; font-style:normal;\"><p style=\"margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#ff0000;\">&gt;&gt;从服务器获取hosts失败，请执行：</span></p><p style=\"margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">·打开网络连接</span></p><p style=\"margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">·检查hosts源是否存在</span></p><p style=\"margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">·更换hosts源</span></p></body>");
    }
    ui->textEdit->append("<p style=\"color:black\">>>有任何疑问请访问https://github.com/racaljk/hosts/blob/master/README.md</p>");

}

void HostsTool::on_actionAbout_A_triggered()
{
    QMessageBox::about(NULL, "About", "Copyright © 2014-2015  racal, All Rights Reserved");
}



void HostsTool::on_commandLinkButton_2_clicked()
{
    const QUrl issue("https://github.com/racaljk/hosts/issues");
    QDesktopServices::openUrl(issue);
}

void HostsTool::on_commandLinkButton_clicked()
{
    const QUrl issue("https://github.com/racaljk/hosts/blob/master/README.md");
    QDesktopServices::openUrl(issue);
}

void HostsTool::on_commandLinkButton_3_clicked()
{
    QMessageBox::about(NULL, "Info", "如果你有其他优质hosts源,并且也愿意分享,请联系邮箱1948638989@qq.com，或者在这个开源项目上直接添加.");
}

void HostsTool::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
    ui->textEdit->append(">>clear up!");
}
