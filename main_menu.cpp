#include "main_menu.h"
#include "ui_main_menu.h"
#include "warning_page.h"
#include "text_page.h"
#include "gameserver.h"
#include "confirm.h"
#include <QFile>
#include <iostream>
#include <QEvent>
#include <QPixmap>
#include <QMouseEvent>
#include <QTimer>
#include <QPushButton>
#include <QString>
#include <QGraphicsDropShadowEffect>
MAIN_MENU::MAIN_MENU(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MAIN_MENU)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowTitle("信科教务重度依赖");
    setWindowIcon(QIcon(":/src/text_content/icon.png"));
    ui->background_pic->setScaledContents(true);
    ui->background_pic->setPixmap(QPixmap(":/src/text_content/main_menu.png"));
    ui->icon->setPixmap(QPixmap(":/src/text_content/icon.png"));
    ui->icon->setScaledContents(true);
    ui->title_background->setStyleSheet("background-color: white;");
    ui->bottom_background->setStyleSheet("background-color: white;");
    ui->EXIT->setIcon(QIcon(":/src/text_content/exit.png"));
    ui->EXIT->setCursor(Qt::PointingHandCursor);//鼠标悬浮在按钮上时指针改变
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint|Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint|Qt::FramelessWindowHint);
    setFixedSize(this->width(),this->height());
}
MAIN_MENU::~MAIN_MENU()
{
    close();
    delete ui;
}
void MAIN_MENU::changeEvent(QEvent* event) {
    if (event->type() == QEvent::WindowStateChange) {
        if (isWindow()) {
            // 检查窗口是否在顶端
            bool isOnTop = isWindow();

            // 设置窗口样式为灰色
            if (!isOnTop) {
                setStyleSheet("background-color: gray;");
            } else {
                setStyleSheet(""); // 清除样式，恢复默认背景颜色
            }
        }
    }
    QWidget::changeEvent(event);
}
void MAIN_MENU::on_EXIT_clicked()
{
    confirm *tmp = new confirm();
    tmp->init("确定要退出吗？");tmp->show();
    connect(tmp,&confirm::yes,this,&MAIN_MENU::close);
}
void MAIN_MENU::mousePressEvent(QMouseEvent *event)  {
    if (event->button() == Qt::LeftButton) {
        m_previousPosition = QCursor::pos();
    }
}

void MAIN_MENU::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        QPoint delta = QCursor::pos() - m_previousPosition;

        move(this->x() + delta.x(), this->y() + delta.y());

        m_previousPosition = QCursor::pos();
    }
}
void MAIN_MENU::init(){
    ui->time->setText(PLAYER->clock_.Get_time());
    WARNING_PAGE *X;
    X = new WARNING_PAGE();
    QFile file(":/src/text_content/rule.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream Qfile(&file);
    QVector<QString> tmp;
    while(!Qfile.atEnd()){
        tmp.append(Qfile.readLine());
    }
    X->init(tmp);
    file.close();
    X->show();
    connect(X,&WARNING_PAGE::destroyed,this,&MAIN_MENU::update);
}
void MAIN_MENU::update(){
    auto [id,day,week]=PLAYER->ask_time();
    ui->time->setText(PLAYER->clock_.Get_time());
    if(id==1&&day==1){
        TEXT_PAGE *course_list = new TEXT_PAGE();
        course_list->init("第"+QString::number(PLAYER->clock_.week_)+"周课程列表",PLAYER->ask_course_available(PLAYER->clock_.week_),1);
        course_list->show();
        TEXT_PAGE *event_list = new TEXT_PAGE();
        event_list->init("活动列表",PLAYER->Now_event(),2);
        connect(course_list,&TEXT_PAGE::destroyed,event_list,&TEXT_PAGE::show);
    }
    else{
        TEXT_PAGE *event_list = new TEXT_PAGE();
        event_list->init("活动列表",PLAYER->Now_event(),2);
        event_list->show();
    }
    if(week==3&&day==7&&id==3){
        WARNING_PAGE *tmp= new WARNING_PAGE();
        tmp->init({"你的大学生活结束啦，来看看你的成就吧！"});
        tmp->show();
        connect(tmp,&WARNING_PAGE::destroyed,this,&MAIN_MENU::close);
    }
}

void MAIN_MENU::on_pushButton_clicked()
{
    ++PLAYER->clock_;
    update();
}


void MAIN_MENU::on_SCHEDULE_clicked()
{
        TEXT_PAGE *course_list = new TEXT_PAGE();
        course_list->init("已选课程列表",PLAYER->now_course(),4);
        course_list->show();
}

