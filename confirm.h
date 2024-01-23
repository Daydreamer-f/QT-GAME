#ifndef CONFIRM_H
#define CONFIRM_H

#include <QWidget>

namespace Ui {
class confirm;
}

class confirm : public QWidget
{
    Q_OBJECT

public:
    explicit confirm(QWidget *parent = nullptr);
    ~confirm();
    void init(QString words,QString picdir="./text_content/warn.png");
signals:
    void yes(bool clicked);
    void no(bool clicked);
private slots:
    void on_YES_clicked();

    void on_NO_clicked();

private:
    Ui::confirm *ui;
};

#endif // CONFIRM_H
