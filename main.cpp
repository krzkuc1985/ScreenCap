#include <QApplication>
#include <QScreen>
#include <QMessageBox>
#include <QDateTime>
#include <QDir>

#define ver "v1.0"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString filePath = QApplication::applicationDirPath().replace("/","\\");
    QString fileName = QString("%1.png").arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss.zzz"));
    int monitor = 1;

    for (int i = 0; i < app.arguments().size(); ++i) {
        QString tmp = app.arguments().at(i);
        if (tmp.compare("-p")==0) {
            filePath = app.arguments().at(i+1);
        }
        if (tmp.compare("-n")==0) {
            fileName = app.arguments().at(i+1);
        }
        if (tmp.compare("-m")==0) {
            monitor = QString(app.arguments().at(i+1)).toInt();
        }
        if (tmp.compare("-v")==0) {
            QMessageBox::information(Q_NULLPTR,QString("ScreenCap %1").arg(ver), QString("ScreenCap wersja: %1").arg(ver), QMessageBox::Close);
            app.quit();
        }
    }

    if (monitor >= 1 && monitor <= QGuiApplication::screens().length()) {
        if (!QDir().exists(filePath)) {
            QDir().mkpath(filePath);
        }
        QScreen *screen = QGuiApplication::screens().at(monitor-1);
        QPixmap originalPixmap = screen->grabWindow(0, screen->geometry().x(), screen->geometry().y(), screen->size().width(), screen->size().height());
        if (!originalPixmap.save(QString("%1\\%2").arg(filePath,fileName))){
            QMessageBox::warning(Q_NULLPTR,QString("ScreenCap %1").arg(ver),QString("Nie można zapisać pliku: \n %1\\%2").arg(filePath,fileName), QMessageBox::Close);
        }
    } else {
        QMessageBox::warning(Q_NULLPTR,QString("ScreenCap %1").arg(ver), QString("Nie można zrobić zrzutu ekranu monitora o nr. %1.").arg(monitor), QMessageBox::Close);
    }

    app.quit();
}
