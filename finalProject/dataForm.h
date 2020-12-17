#ifndef DATAFORM_H
#define DATAFORM_H

#include <QString>
#include <QStringList>

class orderDataForm{
public:
    orderDataForm(QStringList);

    QString order_id;
    quint32 departure_time, end_time;
    double orig_lng,orig_lat,dest_lng,dest_lat,fee;
};

class gridDataForm{
public:
    gridDataForm(QStringList);

    quint16 grid_id;
    double vertex0_lng,vertex0_lat,vertex1_lng,vertex1_lat,vertex2_lng,vertex2_lat,vertex3_lng,vertex3_lat;
};

#endif // DATAFORM_H
