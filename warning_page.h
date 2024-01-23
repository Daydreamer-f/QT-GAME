#ifndef WARNING_PAGE_H
#define WARNING_PAGE_H

#include <QWidget>
#include <QString>
#include <QLabel>
namespace Ui {
class WARNING_PAGE;
}

class WARNING_PAGE : public QWidget
{
    Q_OBJECT
    QVector<QString> str;
public:
    explicit WARNING_PAGE(QWidget *parent = nullptr);
    ~WARNING_PAGE();
    void init(QVector<QString> s);
    void display(QString s,int num);
private slots:

    void on_button_clicked();

private:
    Ui::WARNING_PAGE *ui;
};

#endif // WARNING_PAGE_H
