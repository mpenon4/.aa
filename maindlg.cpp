#include "maindlg.h"
#include "ui_maindlg.h"

void mainDlg::connected(){
  ui->list->addItem("Conectado");
  cliente.subscribe("/ej06/cont", 2);
}
void mainDlg::disconnected(){
  ui->list->addItem("Desconectado");
}
void mainDlg::error(const QMQTT::ClientError error){
  ui->list->addItem("Error: " + QString::number(error));
}
void mainDlg::subscribed(const QString& topic, const quint8 qos){
  ui->list->addItem("Subscripto: " + topic + "( Qos: " + QString::number(qos) + ")");
}
void mainDlg::unsubscribed(const QString& topic){
 ui->list->addItem("Unsubscripto: " + topic);
}
void mainDlg::published(const QMQTT::Message& message, quint16 msgid){
 ui->list->addItem("Publicado:" + message.topic() + ":" + message.payload() + "MsgId: " +QString::number(msgid));
}
void mainDlg::pingresp(){

}
void mainDlg::received(const Message &message){
  Message msg;
  if(message.topic() == "/ej06/cont"){
      ui->list->addItem(message.payload());
   }
  else
    ui->list->addItem("Recibido - Tópico: " + message.topic() + " Message:" + message.payload());

}

mainDlg::mainDlg(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::mainDlg)
{
  ui->setupUi(this);
  connect(&cliente, SIGNAL(connected()), this, SLOT(connected()));
  connect(&cliente, SIGNAL(disconnected()), this, SLOT(disconnected()));
  connect(&cliente, SIGNAL(error(const QMQTT::ClientError)), this, SLOT(error(const QMQTT::ClientError)));
  connect(&cliente, SIGNAL(subscribed(const QString&, const quint8)), this, SLOT(subscribed(const QString&, const quint8)));
  connect(&cliente, SIGNAL(unsubscribed(const QString&)), this, SLOT(unsubscribed(const QString&)));

  connect(&cliente, SIGNAL(published(const QMQTT::Message&, quint16 )), this, SLOT(published(const QMQTT::Message&, quint16 )));
  connect(&cliente, SIGNAL(pingresp()), this, SLOT(pingresp()));
  connect(&cliente, SIGNAL(received(const QMQTT::Message&)), this, SLOT(received(const QMQTT::Message&)));
}

mainDlg::~mainDlg()
{
  if(cliente.isConnectedToHost()){
      cliente.disconnectFromHost();
    }
  delete ui;
}


void mainDlg::on_btnConnect_clicked()
{

  cliente.setHostName(ui->leHost->text());
  if((ui->leUser->text().length() > 0) && (ui->lePass->text().length() > 0)){
      cliente.setUsername(ui->leUser->text());
      cliente.setPassword(ui->lePass->text().toLatin1());
    }
  cliente.setPort(ui->lePort->text().toInt());
  cliente.connectToHost();
}


void mainDlg::on_btnSubs_clicked()
{
    cliente.subscribe(ui->leTopicSub->text());
}


void mainDlg::on_pushButton_clicked()
{
  QMQTT::Message msg;
  msg.setTopic(ui->leTopicPub->text());
  msg.setPayload(ui->leMessagePub->text().toLatin1());
  cliente.publish(msg);
}


void mainDlg::on_btnSalir_clicked()
{
    close();
}

