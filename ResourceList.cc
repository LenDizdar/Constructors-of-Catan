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

int ResourceList::getTotal() {
    return brick + energy + glass + heat + wifi;
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

bool ResourceList::operator>=(ResourceList other) {
    return brick >= other.brick && energy >= other.energy && glass >= other.glass &&
           heat >= other.heat && wifi >= other.wifi;
}

void ResourceList::operator-=(ResourceList other) {
    brick -= other.brick;
    energy -= other.energy;
    glass -= other.glass;
    heat -= other.heat;
    wifi -= other.wifi;
}

void ResourceList::operator+=(ResourceList other) {
    brick += other.brick;
    energy += other.energy;
    glass += other.glass;
    heat += other.heat;
    wifi += other.wifi;
}

bool ResourceList::operator!=(ResourceList other) {
    return brick != other.brick ||
           energy != other.energy ||
           glass != other.glass ||
           heat != other.heat ||
           wifi != other.wifi;
}

ResourceList operator*(ResourceList lhs, int rhs) {
    lhs.set(Resource::BRICK, lhs.get(Resource::BRICK) * rhs);
    lhs.set(Resource::ENERGY, lhs.get(Resource::ENERGY) * rhs);
    lhs.set(Resource::GLASS, lhs.get(Resource::GLASS) * rhs);
    lhs.set(Resource::HEAT, lhs.get(Resource::HEAT) * rhs);
    lhs.set(Resource::WIFI, lhs.get(Resource::WIFI) * rhs);
    return lhs;
}

std::string res_to_str(Resource res) {
    switch (res) {
        case Resource::BRICK:
            return "brick";
            break;
        case Resource::ENERGY:
            return "energy";
            break;
        case Resource::GLASS:
            return "glass";
            break;
        case Resource::HEAT:
            return "heat";
            break;
        case Resource::WIFI:
            return "WiFi";
            break;
        case Resource::PARK:
            return "nothing";
            break;
    }
    return "error";
}
