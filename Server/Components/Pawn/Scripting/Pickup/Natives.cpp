#include "../Types.hpp"
#include "sdk.hpp"
#include <iostream>

SCRIPT_API(CreatePickup, int(int model, int type, Vector3 position, int virtualWorld))
{
    IPickupsComponent* component = PawnManager::Get()->pickups;
    if (component) {
        IPickup* pickup = component->create(model, type, position, virtualWorld, false);
        if (pickup) {
            return pickup->getID();
        }
    }
    return INVALID_PICKUP_ID;
}

SCRIPT_API(AddStaticPickup, bool(int model, int type, Vector3 position, int virtualWorld))
{
    IPickupsComponent* component = PawnManager::Get()->pickups;
    if (component) {
        IPickup* pickup = component->create(model, type, position, virtualWorld, true);
        if (pickup) {
            return true;
        }
    }
    return false;
}

SCRIPT_API(DestroyPickup, bool(IPickup& pickup))
{
    IPickupsComponent* component = PawnManager::Get()->pickups;
    component->release(pickup.getID());
    return true;
}
