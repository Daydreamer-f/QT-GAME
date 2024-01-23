#include "text_page.h"
#include "ui_text_page.h"
#include "warning_page.h"
#include "gameserver.h"
#include "thing.h"
#include "confirm.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>
TEXT_PAGE::TEXT_PAGE(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TEXT_PAGE)
{

    ui->setupUi(this);
    setWindowTitle("信科教务重度依赖");
    setWindowIcon(QIcon(":/src/text_content/icon.png"));
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint|Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint|Qt::FramelessWindowHint);
    setFixedSize(this->width(),this->height());
    setWindowModality(Qt::ApplicationModal);
    ui->CHOOSE->setDisabled(true);
    connect(ui->list, &QListWidget::itemSelectionChanged, this, [=]() {
        QListWidgetItem* selectedItem = ui->list->currentItem();
        if (selectedItem) {
            ui->CHOOSE->setDisabled(false);
        } else {
            ui->CHOOSE->setDisabled(true);
        }
    });

}

TEXT_PAGE::~TEXT_PAGE()
{
    delete ui;
}
void TEXT_PAGE::init(QString S,QVector<QVector<QString> > Words,int tag){
    id=tag;
    ui->title->setText(S);
    if(id==0){
        ui->EXIT->setDisabled(true);
    }
    for(int i=0;i<Words.size();++i){
        auto tmp = new thing();
        vecs x=Words[i];
        auto y=x.front();
        x.pop_front();
        QFile inputFile(":/src/text_content/description/"+y+".txt");
        if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&inputFile);
            while (!in.atEnd()) {
                QString ss = in.readLine();
                x.push_back(ss);
            }
            inputFile.close();
        }
        tmp->init(y,x);
        tmp->setid(i);
        QListWidgetItem* item = new QListWidgetItem(ui->list);
        item->setSizeHint(tmp->sizeHint()); // 设置item的大小为widget的大小

        ui->list->addItem(item);
        ui->list->setItemWidget(item, tmp);
    }
    if(id==4){
        ui->CHOOSE->setVisible(false);
    }
}
void TEXT_PAGE::on_EXIT_clicked()
{
    if(id==1||id==2){
        confirm *temp = new confirm();
        temp->init("确认退出吗?你将无法回到此页面！");
        temp->show();
        connect(temp, &confirm::yes, this, &TEXT_PAGE::close);
    }
    else{
        close();
    }
}
void TEXT_PAGE::reset_list(QVector<QVector<QString> > Words){
    ui->list->clear();
    for(int i=0;i<Words.size();++i){
        auto tmp = new thing();
        auto x=Words[i];

        auto y=x.front();
        x.pop_front();
        QFile inputFile(":/src/text_content/description/"+y+".txt");
        if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&inputFile);
            while (!in.atEnd()) {
                QString ss = in.readLine();
                x.push_back(ss);
            }
            inputFile.close();
        }
        tmp->init(y,x);
        tmp->setid(i);
        QListWidgetItem* item = new QListWidgetItem(ui->list);
        item->setSizeHint(tmp->sizeHint()); // 设置item的大小为widget的大小

        ui->list->addItem(item);
        ui->list->setItemWidget(item, tmp);
    }
}
void TEXT_PAGE::on_CHOOSE_clicked()
{
    QListWidgetItem* selectedItem = ui->list->currentItem();
    auto selectedWidget = ui->list->itemWidget(selectedItem);
    QVector<QString> owo;
    if (selectedWidget) {
        thing* tmp = qobject_cast<thing*>(selectedWidget);
        if (tmp) {
            owo.append(tmp->Getname());
        }
        if(id==0){
            confirm *temp = new confirm();
            temp->init("确定吗，这个还需要你自己衡量！");
            temp->show();
            connect(temp, &confirm::yes, this, [this, tmp]() {
                PLAYER = new game_player(tmp->Getid());
                auto* qwq = new WARNING_PAGE();
                qwq->init({"选择成功！"});
                qwq->show();
                connect(qwq, &WARNING_PAGE::destroyed, this,&TEXT_PAGE::close);
            });

        }
        if(id==1){
            confirm *temp = new confirm();
            temp->init("确定吗，这个还需要你自己衡量！");
            temp->show();
            connect(temp, &confirm::yes, this, [this, tmp]() {
                auto* qwq = new WARNING_PAGE();
                auto [x,y] = PLAYER->choose_course(PLAYER->clock_.week_,tmp->Getid());
                qwq->init(y);
                qwq->show();
            });
        }
        if(id==2){
            confirm *temp = new confirm();
            temp->init("确定吗，这个还需要你自己衡量！");
            temp->show();
            connect(temp, &confirm::yes, this, [this, tmp]() {
                auto* qwq = new WARNING_PAGE();
                auto [x,y] = PLAYER->participate_(tmp->Getid());
                qwq->init(y);
                qwq->show();
            });
        }
    }

}
void TEXT_PAGE::mousePressEvent(QMouseEvent *event)  {
    if (event->button() == Qt::LeftButton) {
        m_previousPosition = QCursor::pos();
    }
}

void TEXT_PAGE::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        QPoint delta = QCursor::pos() - m_previousPosition;

        move(this->x() + delta.x(), this->y() + delta.y());

        m_previousPosition = QCursor::pos();
    }
}

