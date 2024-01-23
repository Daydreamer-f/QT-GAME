#include "welcome_page.h"
#include "ui_welcome_page.h"
#include "main_menu.h"
#include "text_page.h"
#include "gameserver.h"
#include <QDialog>
#include <QPropertyAnimation>
Welcome_Page::Welcome_Page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Welcome_Page)
{

    ui->setupUi(this);
    setWindowTitle("信科教务重度依赖");
    setWindowIcon(QIcon(":/src/text_content/icon.png"));
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint|Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    setFixedSize(this->width(),this->height());
}
Welcome_Page::~Welcome_Page()
{
    delete ui;
}

void Welcome_Page::on_NEW_START_clicked()
{
    MAIN_MENU *main;
    main = new MAIN_MENU();
    /*---初始化选角界面---*/
    TEXT_PAGE *c = new TEXT_PAGE();
    QVector<QVector<QString> > tmp;
    for(int i=0;i<4;++i) tmp.append(ask_role_information(i));
    c->init("请选择你的角色",tmp,0);
    QObject::connect(c, &TEXT_PAGE::destroyed, main, [main](){
        main->init();
        main->show();
    });
    c->show();
    QObject::connect(main, &MAIN_MENU::destroyed, this, &Welcome_Page::close);
    hide();
}
void Welcome_Page::on_EXIT_clicked()
{
    close();
}

