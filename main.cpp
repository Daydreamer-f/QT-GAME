#include "welcome_page.h"
#include <QApplication>
#include "gameserver.h"
#include <QFontDatabase>
game_player *PLAYER = nullptr;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int fontId = QFontDatabase::addApplicationFont(":/src/text_content/pixel.ttf");
    qDebug()<< "fontId ="<< fontId<<QFontDatabase::applicationFontFamilies(fontId);
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    qDebug()<<"fontName =" <<fontName;
    QFont font(fontName);
    QApplication::setFont(font);
    srand(unsigned(time(NULL)));
    Welcome_Page *NEWLIFE = new Welcome_Page();
    NEWLIFE->show();
    return a.exec();
}
