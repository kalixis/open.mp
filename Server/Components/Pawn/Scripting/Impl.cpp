#include "Impl.hpp"

#include "Actor/Events.hpp"
#include "Checkpoint/Events.hpp"
#include "Class/Events.hpp"
#include "Core/Events.hpp"
#include "Dialog/Events.hpp"
#include "Menu/Events.hpp"
#include "Object/Events.hpp"
#include "Pickup/Events.hpp"
#include "Player/Events.hpp"
#include "TextDraw/Events.hpp"
#include "Vehicle/Events.hpp"

Scripting::~Scripting()
{
    PawnManager* mgr = PawnManager::Get();

    // remove event handlers
    if (mgr->players) {
        mgr->players->getEventDispatcher().removeEventHandler(PlayerEvents::Get());
        mgr->players->getPlayerUpdateDispatcher().removeEventHandler(PlayerEvents::Get());
    }
    if (mgr->actors) {
        mgr->actors->getEventDispatcher().removeEventHandler(ActorEvents::Get());
    }
    if (mgr->checkpoints) {
        mgr->checkpoints->getEventDispatcher().removeEventHandler(CheckpointEvents::Get());
    }
    if (mgr->classes) {
        mgr->classes->getEventDispatcher().removeEventHandler(ClassEvents::Get());
    }
    if (mgr->dialogs) {
        mgr->dialogs->getEventDispatcher().removeEventHandler(DialogEvents::Get());
    }
    if (mgr->menus) {
        mgr->menus->getEventDispatcher().removeEventHandler(MenuEvents::Get());
    }
    if (mgr->textdraws) {
        mgr->textdraws->getEventDispatcher().removeEventHandler(TextDrawEvents::Get());
    }
    if (mgr->pickups) {
        mgr->pickups->getEventDispatcher().removeEventHandler(PickupEvents::Get());
    }
    if (mgr->vehicles) {
        mgr->vehicles->getEventDispatcher().removeEventHandler(VehicleEvents::Get());
    }
    if (mgr->objects) {
        mgr->objects->getEventDispatcher().removeEventHandler(ObjectEvents::Get());
    }
    if (mgr->console) {
        mgr->console->getEventDispatcher().removeEventHandler(CoreEvents::Get());
    }
}

void Scripting::addEvents() const
{
    PawnManager* mgr = PawnManager::Get();

    // add event handlers
    if (mgr->players) {
        mgr->players->getEventDispatcher().addEventHandler(PlayerEvents::Get());
        mgr->players->getPlayerUpdateDispatcher().addEventHandler(PlayerEvents::Get());
    }
    if (mgr->actors) {
        mgr->actors->getEventDispatcher().addEventHandler(ActorEvents::Get());
    }
    if (mgr->checkpoints) {
        mgr->checkpoints->getEventDispatcher().addEventHandler(CheckpointEvents::Get());
    }
    if (mgr->classes) {
        mgr->classes->getEventDispatcher().addEventHandler(ClassEvents::Get());
    }
    if (mgr->dialogs) {
        mgr->dialogs->getEventDispatcher().addEventHandler(DialogEvents::Get());
    }
    if (mgr->menus) {
        mgr->menus->getEventDispatcher().addEventHandler(MenuEvents::Get());
    }
    if (mgr->textdraws) {
        mgr->textdraws->getEventDispatcher().addEventHandler(TextDrawEvents::Get());
    }
    if (mgr->pickups) {
        mgr->pickups->getEventDispatcher().addEventHandler(PickupEvents::Get());
    }
    if (mgr->vehicles) {
        mgr->vehicles->getEventDispatcher().addEventHandler(VehicleEvents::Get());
    }
    if (mgr->objects) {
        mgr->objects->getEventDispatcher().addEventHandler(ObjectEvents::Get());
    }
    if (mgr->console) {
        mgr->console->getEventDispatcher().addEventHandler(CoreEvents::Get());
    }
}