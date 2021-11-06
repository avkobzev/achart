#ifndef ACHART_H
#define ACHART_H

#include <QWidget>

namespace Ui {
class achart;
}

class achart : public QWidget
{
    Q_OBJECT

    int maxy, miny;
    int *data;
    int  data_size;

public:
    explicit achart(QWidget *parent = nullptr);
    ~achart();

    void set_y( int maxy, int miny );
    void set_data( int *data, int data_size );
    void resizeEvent(QResizeEvent *event);
    int to_wnd_y( int y );

    void draw_grid( QPainter &p );
    void paintEvent(QPaintEvent *event);

private:
    Ui::achart *ui;
};

#endif // ACHART_H
