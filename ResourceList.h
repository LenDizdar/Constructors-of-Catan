#ifndef RESOURCE_LIST_H
#define RESOURCE_LIST_H
enum Resource {
    BRICK,
    ENERGY,
    GLASS,
    HEAT,
    WIFI,
    PARK
};

class ResourceList {
    int brick;
    int energy;
    int glass;
    int heat;
    int wifi;
    public:
        ResourceList();
        ResourceList(int brick, int energy, int glass, int heat, int wifi);
        int get(Resource res);
        int getTotal();
        void set(Resource res, int amt);
        void set(ResourceList &resList);
        void change(Resource res, int amt);
        bool operator>=(ResourceList other);
        void operator-=(ResourceList other);
        void operator+=(ResourceList other);
};

#endif
