#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
        server = new Server();
        server->setURL("http://10.8.0.30:10001/");
        //server->setURL("http://localhost:10001/");
        connect(server,SIGNAL(signal_reply(QByteArray)),this,SLOT(httpReply(QByteArray)));

        server->Auth("tango-cs","tango","tango/rest/rc4/hosts/10.8.0.30/10000/");

        main_layout= new QHBoxLayout();
        main_widget = new QWidget();
        main_widget->setLayout(main_layout);

        led_ind = new QLedIndicator(nullptr);

        shiber_button = new QPushButton("открыть/закрыть заслонку");
        main_layout->addWidget(shiber_button);
        main_layout->addWidget(led_ind);

        this->setCentralWidget(main_widget);


        connect(shiber_button,SIGNAL(clicked()),this,SLOT(onShiberButtonClick()));
}

void MainWindow::onShiberButtonClick()
{
        // for read!
        //server->Auth("tango-cs","tango","tango/rest/rc4/hosts/10.8.0.30/10000/devices/device/phymotion/diom1/attributes/o2/value");
        //server->Auth("tango-cs","tango","tango/rest/rc4/hosts/10.8.0.30/10000/devices/device/phymotion/diom1/attributes/o2/value?v=true");
        QUrlQuery query;
        //query.addQueryItem("o2","true");
        if(led_ind->isChecked()){
                server->Put("tango-cs","tango","tango/rest/rc4/hosts/localhost/10000/devices/device/PhyMOTION/diom1/attributes/o2/value?v=false","");
        }else{
                server->Put("tango-cs","tango","tango/rest/rc4/hosts/localhost/10000/devices/device/PhyMOTION/diom1/attributes/o2/value?v=true","");
        }
        led_ind->toggle();

}


void MainWindow::httpReply(QByteArray content){
        qDebug() << content;
}
