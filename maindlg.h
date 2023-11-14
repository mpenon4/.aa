#ifndef MAINDLG_H
#define MAINDLG_H

#include <QDialog>
#include "qmqtt.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainDlg; }
QT_END_NAMESPACE

using namespace QMQTT;
class mainDlg : public QDialog
{
  Q_OBJECT

public:
  mainDlg(QWidget *parent = nullptr);
  ~mainDlg();
  Client cliente;
private slots:
  void on_btnConnect_clicked();
  void connected();
  void disconnected();
  void error(const QMQTT::ClientError);
  void subscribed(const QString& topic, const quint8 qos);
  void unsubscribed(const QString& topic);
  void published(const QMQTT::Message& message, quint16 msgid=0);
  void pingresp();
  void received(const QMQTT::Message&);

  void on_btnSubs_clicked();

  void on_pushButton_clicked();

  void on_btnSalir_clicked();

private:
  Ui::mainDlg *ui;
};
#endif // MAINDLG_H
