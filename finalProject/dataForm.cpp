#include "dataForm.h"

coordinate::coordinate(double longitude, double latitude) : lng(longitude), lat(latitude)
{
}

coordinate::coordinate():lng(0), lat(0){}

coordinate& coordinate::operator=(const coordinate& co)
{
    if(this != &co){
        lng = co.lng;
        lat = co.lat;
    }
    return *this;
}


orderDataForm::orderDataForm(QStringList lst):
    orig(lst[3].trimmed().toDouble(), lst[4].trimmed().toDouble()),
    dest(lst[5].trimmed().toDouble(), lst[6].trimmed().toDouble())
{
    order_id = lst[0].trimmed();
    departure_time = lst[1].trimmed().toUInt();
    end_time = lst[2].trimmed().toUInt();
    fee = lst[7].trimmed().toDouble();
}

//void orderDataForm::operator=(const orderDataForm& order):
//    order_id(order.order_id), depature_time(order.departure_time),
//    end_time(order.end_time), orig_lng(order.orig_lng),
//    orig_lat(order)
//{

//}


//gridDataForm::gridDataForm(QStringList lst):
//    vertex0(lst[1].trimmed().toDouble(), lst[2].trimmed().toDouble()),
//    vertex1(lst[3].trimmed().toDouble(), lst[4].trimmed().toDouble()),
//    vertex2(lst[5].trimmed().toDouble(), lst[6].trimmed().toDouble()),
//    vertex3(lst[7].trimmed().toDouble(), lst[8].trimmed().toDouble())
//{
//    grid_id = lst[0].trimmed().toUInt();
//}

bool timeLessThan(orderDataForm order1, orderDataForm order2)
{
    return order1.departure_time < order2.departure_time;
}
