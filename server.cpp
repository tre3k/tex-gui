#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
    cookie = new QNetworkCookieJar();

    manager->setCookieJar(cookie);

    connect(manager,SIGNAL(finished(QNetworkReply *)),
            this,SLOT(slot_FinalReply(QNetworkReply *)));
}

void Server::setURL(QString url){
    mainURL = url;
}

void Server::Auth(QString user,QString pass, QString page){
        QString concatenated = user+":"+pass; //username:password
        QByteArray data = concatenated.toLocal8Bit().toBase64();
        QString headerData = "Basic " + data;

        QNetworkRequest request(QUrl(mainURL+page));
        request.setRawHeader("Authorization", headerData.toLocal8Bit());
        manager->get(request);
}

void Server::Request(QString user,QString pass, QString page, QUrlQuery params){
        QString concatenated = user+":"+pass; //username:password
        QByteArray data = concatenated.toLocal8Bit().toBase64();
        QString headerData = "Basic " + data;

        QNetworkRequest request(QUrl(mainURL+page));
        //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        request.setRawHeader("Authorization", headerData.toLocal8Bit());
        //manager->post(request,params.toString().toLocal8Bit());
        manager->put(request,params.toString().toLocal8Bit());
        //manager->get(request);
}

void Server::Put(QString user,QString pass, QString page, QString params){
        QString concatenated = user+":"+pass; //username:password
        QByteArray data = concatenated.toLocal8Bit().toBase64();
        QString headerData = "Basic " + data;

        QNetworkRequest request(QUrl(mainURL+page));
        request.setRawHeader("Authorization", headerData.toLocal8Bit());
        manager->put(request,params.toLocal8Bit());
}

void Server::slot_FinalReply(QNetworkReply *reply){
    if(reply->error()!=QNetworkReply::NoError){
        switch (reply->error()){
        case QNetworkReply::ContentNotFoundError:
            QMessageBox::critical(nullptr,"Error!","Content not found!\n");
            break;
        case QNetworkReply::TimeoutError:
            QMessageBox::critical(nullptr,"Error!","Timeout error!\n");
            break;
        case QNetworkReply::HostNotFoundError:
            QMessageBox::critical(nullptr,"Error!","Host not found!\n");
            break;
        default:
            QMessageBox::critical(nullptr,"Error!","Server reply error!\n");
            break;
        }
    }else{
        emit signal_reply(reply->readAll());
    }

    qDebug() << "Cookie: " << cookie;

}

