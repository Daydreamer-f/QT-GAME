#ifndef WELCOME_PAGE_H
#define WELCOME_PAGE_H

#include <QWidget>

namespace Ui {
class Welcome_Page;
}

class Welcome_Page : public QWidget
{
    Q_OBJECT

public:
    explicit Welcome_Page(QWidget *parent = nullptr);
    ~Welcome_Page();

private slots:
    void on_NEW_START_clicked();

    void on_EXIT_clicked();

private:
    Ui::Welcome_Page *ui;
};

#endif // WELCOME_PAGE_H
