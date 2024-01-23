#include "confirm.h"
#include "ui_confirm.h"
#include <QPixmap>
confirm::confirm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::confirm)
{
    ui->setupUi(this);
    setWindowTitle("信科教务重度依赖");
    setWindowIcon(QIcon(":/src/text_content/icon.png"));
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint|Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint|Qt::FramelessWindowHint);
    setFixedSize(this->width(),this->height());
    setWindowModality(Qt::ApplicationModal);
    ui->PIC->setScaledContents(true);
}
confirm::~confirm()
{
    close();
    delete ui;
}
void confirm::init(QString words,QString picdir){
    ui->TEXT->setText(words);
    QPixmap tmp =QPixmap(picdir);
    if(tmp.isNull()){
        tmp=QPixmap(":/src/text_content/warn.png");
    }
    ui->PIC->setPixmap(tmp);
}

void confirm::on_YES_clicked()
{
    emit yes(true);
    close();
}
void confirm::on_NO_clicked()
{
    emit no(true);
    close();
}

