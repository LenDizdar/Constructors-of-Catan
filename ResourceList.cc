#include "ResourceList.h"
ResourceList::ResourceList(): brick{0}, energy{0}, glass{0}, heat{0}, wifi{0} {}

ResourceList::ResourceList(int brick, int energy, int glass, int heat, int wifi):
    brick{brick}, energy{energy}, glass{glass}, heat{heat}, wifi{wifi} {}

int ResourceList::get(Resource res) {
    switch (res) {
        case Resource::BRICK:
            return brick;
            break;
        case Resource::ENERGY:
            return energy;
            break;
        case Resource::GLASS:
            return glass;
            break;
        case Resource::HEAT:
            return heat;
            break;
        case Resource::WIFI:
            return wifi;
            break;
        case Resource::PARK:
            return -1;
            break;
    }
    return -1;
}

void ResourceList::set(Resource res, int amt) {
    switch (res) {
        case Resource::BRICK:
            brick = amt;
            break;
        case Resource::ENERGY:
            energy = amt;
            break;
        case Resource::GLASS:
            glass = amt;
            break;
        case Resource::HEAT:
            heat = amt;
            break;
        case Resource::WIFI:
            wifi = amt;
            break;
        case Resource::PARK:
            break;
    }
}

void ResourceList::set(ResourceList& resList) {
    brick = resList.get(Resource::BRICK);
    energy = resList.get(Resource::ENERGY);
    glass = resList.get(Resource::GLASS);
    heat = resList.get(Resource::HEAT);
    wifi = resList.get(Resource::WIFI);
}

void ResourceList::change(Resource res, int amt) {
    switch (res) {
        case Resource::BRICK:
            brick += amt;
            break;
        case Resource::ENERGY:
            energy += amt;
            break;
        case Resource::GLASS:
            glass += amt;
            break;
        case Resource::HEAT:
            heat += amt;
            break;
        case Resource::WIFI:
            wifi += amt;
            break;
        case Resource::PARK:
            break;
    }
}

// A bunch of operators to be added
