#include "achart.h"
#include "ui_achart.h"

#include <QPainter>
#include <QPen>

achart::achart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::achart)
{
    ui->setupUi(this);

    data      = NULL;
    data_size = 0;

    miny = -1000;
    maxy =  1000;
}

achart::~achart()
{
    delete ui;
}

void achart::set_y( int maxy, int miny )
{
    this->maxy = maxy;
    this->miny = miny;
}

void achart::set_data( int *data, int data_size )
{
    this->data      = data;
    this->data_size = data_size;
}

void achart::resizeEvent(QResizeEvent *event)
{
    //qDebug() << "Width: " << this->width();
    //qDebug() << "Height: " << this->height();
}

int achart::to_wnd_y( int y )
{
    float step = (float) this->height() / ( maxy - miny );

    return (int) height() - (float) ( y - miny ) * step;
}

void achart::draw_grid( QPainter &p )
{
    int i;

    QPen pen_save = p.pen();
    QPen pen_grid;

    pen_grid.setStyle( Qt::DashLine );
    pen_grid.setColor( Qt::gray );

    p.drawLine( 0, to_wnd_y( 0 ), this->width(), to_wnd_y( 0 ) );

    p.setPen( pen_grid );

    for ( i = 1; i < 6; i++ ) {
        p.drawLine( (float) width() / 6 * i, 0, (float) width() / 6 * i, height() );
    }

    for ( i = 0; i > miny; i -= 1000 ) {
        p.drawLine( 0, to_wnd_y( (float) i ), width(), to_wnd_y( (float) i ) );
    }

    for ( i = 0; i < maxy; i += 1000 ) {
        p.drawLine( 0, to_wnd_y( (float) i ), width(), to_wnd_y( (float) i ) );
    }

    p.setPen( pen_save );
}

void achart::paintEvent(QPaintEvent *event)
{
    QPainter p;

    if ( !data || ( data_size < 2 ) ) {
        return;
    }

    int max_x;
    float step_gra;
    float step_arr;

    if ( data_size > this->width() ) {
        max_x = this->width();
        step_arr = (float) data_size / ( this->width() - 1 );
        step_gra = 1;
    }
    else {
        max_x = data_size;
        step_arr = 1;
        step_gra =  (float) this->width() / ( data_size - 1 );
    }

    p.begin( this );

    draw_grid( p );

    float pos_arr_prev = 0;
    float pos_gra_prev = 0;
    float pos_arr = step_arr;
    float pos_gra = step_gra;

    for ( int i = 1; i < max_x; i++ ) {
        p.drawLine(
            pos_gra_prev,
            to_wnd_y( data[ (int) pos_arr_prev ] ),
            pos_gra,
            to_wnd_y( data[ (int) pos_arr ] ) );

        pos_gra_prev = pos_gra;
        pos_arr_prev = pos_arr;

        pos_gra += step_gra;
        pos_arr += step_arr;
    }

    p.end();
}
