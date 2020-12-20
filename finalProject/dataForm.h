#ifndef DATAFORM_H
#define DATAFORM_H

#include <QString>
#include <QStringList>

class coordinate {
public:
    coordinate(double, double);
    coordinate();

    coordinate& operator=(const coordinate& co);

    double lng, lat;
};

class orderDataForm {
public:
    orderDataForm(QStringList);

    QString order_id;
    quint32 departure_time, end_time;
    coordinate orig, dest;
    double fee;

    //    void operator=(const orderDataForm& order);
};

class gridDataForm {
public:
    gridDataForm(QStringList);

    quint16 grid_id;

    coordinate vertex0, vertex1, vertex2, vertex3;
};

bool timeLessThan(orderDataForm, orderDataForm);


#endif// DATAFORM_H
