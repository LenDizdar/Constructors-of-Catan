export module resourcelist;

export enum Resource {
    BRICK,
    ENERGY,
    GLASS,
    HEAT,
    WIFI
};

export class ResourceList {
    int brick;
    int energy;
    int glass;
    int heat;
    int wifi;
    public:
        ResourceList();
        ResourceList(int brick, int energy, int glass, int heat, int wifi);
        int get(Resource res);
        void set(Resource res, int amt);
        void change(Resource res, int amt);
};
