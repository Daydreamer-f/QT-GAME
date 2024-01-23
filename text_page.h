#ifndef TEXT_PAGE_H
#define TEXT_PAGE_H

#include <QWidget>

namespace Ui {
class TEXT_PAGE;
}

class TEXT_PAGE : public QWidget
{
    Q_OBJECT
    int id;
public:
    explicit TEXT_PAGE(QWidget *parent = nullptr);
    ~TEXT_PAGE();
    void init(QString S,QVector<QVector<QString> > Words,int tag);
    void mousePressEvent(QMouseEvent *event) override;
    void reset_list(QVector<QVector<QString> > Words);
    void mouseMoveEvent(QMouseEvent *event) override;
private slots:
    void on_EXIT_clicked();

    void on_CHOOSE_clicked();

private:
    Ui::TEXT_PAGE *ui;
    QPoint m_previousPosition;
};

#endif // TEXT_PAGE_H
