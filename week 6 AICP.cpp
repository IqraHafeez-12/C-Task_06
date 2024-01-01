#include <iostream>
#include <string>

const double cementWeight = 25.0;
const double gravelWeight = 50.0;
const double sandWeight = 50.0;
const double cementPrice = 3.0;
const double gravelPrice = 2.0;
const double sandPrice = 2.0;
const double specialPackPrice = 10.0;
const double specialPackSize = 1.0 * cementWeight + 2.0 * sandWeight + 2.0 * gravelWeight;

enum Material {cement, gravel, sand};

class Sack {
    public:
        Material material;
        double weight;
        bool isValid();
};

bool Sack::isValid() {
    if (material == cement && weight > cementWeight && weight < cementWeight + 0.1) return true;
    if (material == gravel && weight > gravelWeight && weight < gravelWeight + 0.1) return true;
    if (material == sand && weight > sandWeight && weight < sandWeight + 0.1) return true;
    return false;
}

void checkSack(Sack sack) {
    if (sack.isValid()) {
        std::cout << "Sack contains " << (sack.material == cement ? "cement" : (sack.material == gravel ? "gravel" : "sand"))
                 << " with a weight of " << sack.weight << " kg.\n";
    } else {
        std::cout << "Sack rejected due to invalid weight or material.\n";
    }
}

int checkOrder(int cementCount, int gravelCount, int sandCount) {
    int rejectedCount = 0;
    double totalWeight = 0.0;
    for (int i = 0; i < cementCount; i++) {
        Sack sack = {cement, cementWeight};
        if (!sack.isValid()) rejectedCount++;
        totalWeight += sack.weight;
    }
    for (int i = 0; i < gravelCount; i++) {
        Sack sack = {gravel, gravelWeight};
        if (!sack.isValid()) rejectedCount++;
        totalWeight += sack.weight;
    }
    for (int i = 0; i < sandCount; i++) {
        Sack sack = {sand, sandWeight};
        if (!sack.isValid()) rejectedCount++;
        totalWeight += sack.weight;
    }
    std::cout << "Total weight of the order: " << totalWeight << " kg.\n";
    std::cout << "Number of sacks rejected from the order: " << rejectedCount << ".\n";
    return rejectedCount;
}

void calculatePrice(int cementCount, int gravelCount, int sandCount) {
    int orderSize = cementCount + gravelCount + sandCount;
    int specialPackCount = orderSize / 6;
    double regularPrice = (cementCount * cementPrice + gravelCount * gravelPrice + sandCount * sandPrice) * (orderSize - specialPackCount * 6) / orderSize;
    double specialPackPriceSum = specialPackCount * specialPackPrice;
    double totalPrice = regularPrice + specialPackPriceSum;
    std::cout << "Regular price for the order: $" << regularPrice << ".\n";
    if (specialPackCount > 0) {
        std::cout << "Total price for the order: $" << totalPrice << " (discount price of $" << specialPackPriceSum << ").\n";
    } else {
        std::cout << "Total price for the order: $" << totalPrice << ".\n";
    }
}

int main() {
    Sack sack;
    sack.material = cement;
    sack.weight = cementWeight;
    checkSack(sack);

    int cementCount = 3;
    int gravelCount = 2;
    int sandCount = 1;
    checkOrder(cementCount, gravelCount, sandCount);

    calculatePrice(cementCount, gravelCount, sandCount);

    return 0;
}
