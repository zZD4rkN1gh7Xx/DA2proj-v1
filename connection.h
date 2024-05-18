//
// Created by Administrador on 15/05/2024.
//

/**
    *@file connection.h
    *@brief Header of Connection class methods
*/

#ifndef DAPROJ2_V2_CONNECTION_H
#define DAPROJ2_V2_CONNECTION_H


class Connection {

    private:
        int id_A;
        int id_B;
        double distance;

    public:
        Connection(int id_A, int id_B, double distance);
        int get_id_A();
        int get_id_B();
        double get_distance();
};


#endif //DAPROJ2_V2_CONNECTION_H
