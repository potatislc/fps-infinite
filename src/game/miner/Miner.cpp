#include "Miner.h"

#include <utility>
#include "engine/Application.h"
#include "engine/ResourceLoader.h"

UniqueTexture Miner::mockupLook;

Miner::Miner(Tunnel* tunnel, StateMachine<Miner> stateMachine) : tunnel(tunnel), stateMachine(std::move(stateMachine))
{

}

void Miner::start()
{
    mockupLook.set(ResourceLoader::loadTexture(TEXTURES_PATH"miner/mockup.png"));
    stateMachine.nextState(SI_DIG);
}

void Miner::update()
{
    stateMachine.update();
}

void Miner::draw(SDL_Renderer* renderTarget)
{
    stateMachine.draw(renderTarget);
    MessageTexture::renderMessage(renderTarget, MessageTexture::FAI_DEFAULT, stateMachine.getCurrentState()->name, (Utils::Vector2I){0, 0}, (SDL_Color){255, 255, 255, 255});
}

StateMachine<Miner> Miner::defaultStateMachine()
{
    std::vector<std::shared_ptr<StateMachine<Miner>::State>> sm = {
            std::make_shared<StateIdle>(StateIdle("Idle", this, &stateMachine)),
            std::make_shared<StateDig>(StateDig("Dig", this, &stateMachine)),
            std::make_shared<StateFall>(StateFall("Fall", this, &stateMachine))
                    };
    return {this, sm};
}

void Miner::digLayer()
{
    depth++;
    Tunnel::Layer currentLayer = tunnel->nextLayer();
    materialsMined[currentLayer.materialType] += currentLayer.amount;
    // Send to ui
    dug.send(depth, currentLayer.materialType, materialsMined[currentLayer.materialType]);

    // How miner will react to standing on the new top layer
    switch (tunnel->layers[tunnel->getFloorLayerIndex()].materialType)
    {
        case Material::T_AIR:
            stateMachine.nextState(SI_FALL);
            break;
        default:
            // Default is an ore you can stand on and mine regularly
            break;
    }
}
