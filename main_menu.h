#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <QWidget>

namespace Ui {
class MAIN_MENU;
}

class MAIN_MENU : public QWidget
{
    Q_OBJECT
public:
    explicit MAIN_MENU(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;
    void update();
    void init();
    void mouseMoveEvent(QMouseEvent *event) override;
    ~MAIN_MENU();
private slots:

    void on_EXIT_clicked();

    void changeEvent(QEvent* event)override;

    void on_pushButton_clicked();

    void on_SCHEDULE_clicked();

private:
    Ui::MAIN_MENU *ui;
    QPoint m_previousPosition;
};

#endif // MAIN_MENU_H
