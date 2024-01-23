#include "thing.h"
#include "ui_thing.h"
#include "warning_page.h"
thing::thing(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::thing)
{
    ui->setupUi(this);
    ui->pic->setScaledContents(true);
}
QSize thing::sizeHint() {
    return QSize((*this).width(), (*this).height()); // 返回合适的尺寸，例如宽度为200，高度为50
}
void thing::init(QString s,QVector<QString> o){
    ui->name->setText(s);
    QString picdir = ":/src/text_content/img/"+ui->name->text()+".png";
    QPixmap tmp(picdir);
    if(tmp.isNull()){
        tmp=QPixmap(":/src/text_content/img/logo.png");
    }
    ui->pic->setPixmap(tmp);
    words=o;
}
void thing::setid(int x){
    id=x;
}
int thing::Getid(){
    return id;
}
QString thing::Getname(){
    return ui->name->text();
}
thing::~thing()
{
    close();
    delete ui;
}


void thing::on_pushButton_clicked()
{
    auto *tmp = new WARNING_PAGE();
    tmp->init(words);
    tmp->show();
}

