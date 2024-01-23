#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QDialog>

namespace Ui {
class activity;
}

class activity : public QDialog
{
    Q_OBJECT

public:
    explicit activity(QWidget *parent = nullptr);
    ~activity();

private:
    Ui::activity *ui;
};

#endif // ACTIVITY_H
