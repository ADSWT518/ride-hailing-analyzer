#include "dataForm.h"
#include "global.h"
#include <QDebug>

coordinate::coordinate(double longitude, double latitude) : lng(longitude), lat(latitude) {}

coordinate::coordinate():lng(0), lat(0){}

coordinate& coordinate::operator=(const coordinate& co)
{
    if(this != &co){
        lng = co.lng;
        lat = co.lat;
    }
    return *this;
}


orderDataForm::orderDataForm(QStringList lst)
{
    if(order_id_selected){
        order_id = lst[0].trimmed();
    }
    if(departure_time_selected){
        departure_time = lst[1].trimmed().toUInt();
    }
    if(end_time_selected){
        end_time = lst[2].trimmed().toUInt();
    }
    if(orig_selected){
        coordinate Orig(lst[3].trimmed().toDouble(), lst[4].trimmed().toDouble());
        orig = Orig;
    }
    if(dest_selected){
        coordinate Dest(lst[5].trimmed().toDouble(), lst[6].trimmed().toDouble());
        dest = Dest;
    }
    if(fee_selected){
        fee = lst[7].trimmed().toDouble();
    }
}

bool timeLessThan(orderDataForm order1, orderDataForm order2)
{
    return order1.departure_time < order2.departure_time;
}
