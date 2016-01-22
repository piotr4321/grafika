#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QFileDialog>
#include <QDebug>
#include <QDir>
#include <QProcess>
#include <QMessageBox>

//Zmienne pomocnicze przechowujące ścieżki
QString currentPath = QDir::currentPath();
QString gamePath= currentPath.mid(0, currentPath.lastIndexOf("/")) + "/GRA/";
QString mapName;


QString getTimeFromFile() {
    QFile inputFile(gamePath + "wynik.log");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       return in.readLine();
    }
    return "0";
}



MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
        if(mapName != NULL && mapName != ""){
        QProcess* myProcess = new QProcess(this);
        QStringList arguments;
        arguments << mapName;
        myProcess->start(gamePath+"/labirynt",arguments);
        myProcess->waitForFinished(600000);
        myProcess->close();
        QString time = getTimeFromFile();
        if(time.compare("0") != 0)
            QMessageBox::information(this,tr("Wynik"),time);
        }
        else
            ui->label->setText("Nie podałeś mapy, lub typ pliku jest niepoprawny!");
}

void MainWindow::on_pushButton_2_clicked()
{
    mapName = QFileDialog::getOpenFileName(this, tr("Open File"), "/.", "Pliki tekstowe (*.map)");
    if(mapName != NULL && mapName != "")
    ui->label->setText("Wczytałeś plik: " + mapName);
}

void MainWindow::on_pushButton_3_clicked()
{
    MainWindow::close();
}
