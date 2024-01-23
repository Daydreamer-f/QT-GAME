#ifndef THING_H
#define THING_H

#include <QWidget>

namespace Ui {
class thing;
}

class thing : public QWidget
{
    Q_OBJECT
    QVector<QString> words;
    int id;
public:
    explicit thing(QWidget *parent = nullptr);
    ~thing();
    QSize sizeHint();
    void init(QString s,QVector<QString> o);
    QString Getname();
    void setid(int x);
    int Getid();
private slots:
    void on_pushButton_clicked();

private:
    Ui::thing *ui;
};

#endif // THING_H
