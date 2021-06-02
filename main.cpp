#include "jeu.h"
#include "murpart.h"

#include <QApplication>
#include <QSplashScreen>

Jeu* jeu;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/bg/imageMenu.jpg");
    QSplashScreen splash(pixmap.scaled(1200,600));
    splash.show();
    splash.showMessage("Loading");

    jeu = new Jeu();
    jeu->show();

    jeu->afficherMenu();
    qDebug() << "aficher menu 2";

    a.processEvents();
    return a.exec();
}
