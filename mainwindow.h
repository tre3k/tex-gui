#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QThread>

#include "qledindicator.h"
#include "server.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
        explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
        void httpReply(QByteArray content);

        void onShiberButtonClick(void);

protected:
        QWidget *main_widget;
        QHBoxLayout *main_layout;

        QPushButton *shiber_button;
        QLedIndicator *led_ind;

        Server *server;

};

#endif // MAINWINDOW_H
