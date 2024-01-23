#include "activity.h"
#include "ui_activity.h"

activity::activity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::activity)
{
    ui->setupUi(this);
}

activity::~activity()
{
    delete ui;
}

