#include "jeu.h"
#include "murpart.h"

#include <QApplication>
#include <QSplashScreen>

Jeu* jeu;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    jeu = new Jeu();
    jeu->show();
    jeu->afficherMenu();

    a.processEvents();
    return a.exec();
}
