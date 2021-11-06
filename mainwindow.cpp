#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>

#include <math.h>

#include <QDebug>

int arr2[ 1024 ];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for ( int i = 0; i < 1024; i++ ) {
        arr2[ i ] = (float) 1000 * sin( (float) 2 * M_PI / ( 1024 / 2 ) * i );
        arr2[ i ] += (float) 300 * sin( (float) 2 * M_PI / 102.4 * i );
    }

    chart = new achart();

    ui->verticalLayout->addWidget( chart );

    chart->set_y( 1500, -1500 );
    chart->set_data( arr2, 1024 );
}

MainWindow::~MainWindow()
{
    delete chart;

    delete ui;
}

