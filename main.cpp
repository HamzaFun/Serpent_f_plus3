#include "jeu.h"
#include "murpart.h"

#include <QApplication>
#include <QSplashScreen>

Jeu* jeu;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/bg/blackbg.jpg");
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage("Loaded modules");

    jeu = new Jeu();
    jeu->show();
    jeu->afficherMenu("Jeu Serpent ", "Jouer");

    a.processEvents();
    return a.exec();
}
