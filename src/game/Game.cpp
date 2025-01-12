#include <iostream>
#include <thread>
#include <numeric>
#include "Game.h"
#include "engine/InputMap.h"
#include "game/characters/Player.h"
#include "engine/ResourceLoader.h"
#include "engine/App.h"

glm::vec2 Game::cellSize = {MAX_CELL_W, MAX_CELL_W};
std::shared_ptr<Player> Game::currentPlayer = std::make_shared<Player>((glm::vec3){0, 0, 0}, 0, 1);
Renderer::ViewPortCamera Game::mapCamera = Renderer::ViewPortCamera((SDL_Rect){0, 0, 426, 240});
Camera3D Game::camera3D = Camera3D((glm::vec3){0, 0, 0}, 0, 90, 170);
Game::Settings Game::settings;

Game::Game()
{
    InputMap::addKeyBinding("Quit", SDLK_ESCAPE);
    InputMap::addKeyBinding("Left", SDLK_a);
    InputMap::addKeyBinding("Right", SDLK_d);
    InputMap::addKeyBinding("Up", SDLK_w);
    InputMap::addKeyBinding("Down", SDLK_s);
    InputMap::addKeyBinding("LookLeft", SDLK_LEFT);
    InputMap::addKeyBinding("LookRight", SDLK_RIGHT);
    InputMap::addKeyBinding("FlyUp", SDLK_UP);
    InputMap::addKeyBinding("FlyDown", SDLK_DOWN);
}

void Game::start()
{
    ResourceLoader::loadedTextures.loadAll();
    ResourceLoader::loadedPixelArrays.loadAll();
    Camera3D::initFloorProjectionSurface(projectedFloor, App::renderer.viewport.w, (int) App::renderer.viewportCenter.y);
    mapCamera.setRenderTarget(App::renderer.sdlRenderer);
    world.addChild(currentPlayer);
    currentPlayer->position = (glm::vec3){cellSize.x / 2, cellSize.y / 2, 0};

    initShadowRaster();
    waterRipples = PixelArray<uint32_t>(
            new uint32_t[ResourceLoader::loadedPixelArrays.water.width
            * ResourceLoader::loadedPixelArrays.water.height],
            ResourceLoader::loadedPixelArrays.water.width,
            ResourceLoader::loadedPixelArrays.water.height);

    world.addChild(std::make_shared<Entity3D>((glm::vec3){5, 6, 1}, 0));
    world.addChild(std::make_shared<Entity3D>((glm::vec3){-4, -12, 1}, 0));
    world.addChild(std::make_shared<Entity3D>((glm::vec3){1, 27, 10}, 0));
    world.addChild(std::make_shared<Entity3D>((glm::vec3){30, -36, 6}, 0));


    // Should print 0, 0 (It does!)
    std::cout << getCellPos(centerCellId).x << ", " << getCellPos(centerCellId).y << std::endl;
    std::cout << centerCellId << std::endl;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            world.addChild(std::make_shared<Entity3D>((glm::vec3){i * 7 - 1 * 63, j * 7 - 1 * 63, glm::sin(j) * 2 + 2}, 0));
        }
    }
}

void Game::update()
{
    if (InputMap::getBoundKeyInput("Quit") == InputMap::S_PRESSED)
    {
        App::quit = true;
    }

    for (const auto& child : world.children)
    {
        child->update();
        wrapInsideWorld(child->position);
        // child->position += glm::vec3(0, 4 * App::deltaTime, 0); Test!
    }
}

void Game::draw(SDL_Renderer *renderer)
{
    // castEntityShadows(renderer, 1);
    rasterizeShadowMap();

    SDL_Rect rect = {0, 0, App::renderer.viewport.w, App::renderer.viewport.h};

    {
        // Double viewport height, reflections are stored at the bottom outside the screen
        UniqueTexture renderTarget = UniqueTexture(
                SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h * 2));
        SDL_SetTextureBlendMode(renderTarget.get(), SDL_BLENDMODE_BLEND);
        SDL_SetRenderTarget(renderer, renderTarget.get());
        PixelArray<uint32_t>::rippleize(ResourceLoader::loadedPixelArrays.water, waterRipples.pixels,
                                        (float)(App::timeSinceInit * 2), 2);
        drawBackground(renderer);
        auto reflectOrigin = SDL_Point(0, 0);
        auto reflectSrc = SDL_Rect(0, 0, rect.w, rect.h / 2);
        auto reflectDst = SDL_Rect(0, rect.h / 2 + rect.h, rect.w, rect.h / 2);
        SDL_RenderCopyEx(renderer, renderTarget.get(), &reflectSrc, &reflectDst, 0, &reflectOrigin, SDL_FLIP_VERTICAL);
        drawEntityCells(renderer);
        SDL_SetRenderTarget(renderer, nullptr);

        camera3D.drawFloor(renderer, projectedFloor, waterRipples, floorPixelDensity, shadowPixelDensity, shadowMapPx);
        reflectSrc.h = rect.h / 2;
        reflectSrc.y = rect.h + rect.h / 2;
        reflectDst.y = rect.h / 2;
        SDL_SetTextureAlphaMod(renderTarget.get(), 25);
        SDL_RenderCopy(renderer, renderTarget.get(), &reflectSrc, &reflectDst);
        SDL_SetTextureAlphaMod(renderTarget.get(), 255);
        SDL_RenderCopy(renderer, renderTarget.get(), &rect, &rect);
    }

    /*for (int i = 0; i < shadowMap.getRect()->w * shadowMap.getRect()->h / 4; i++)
    {
        SDL_SetRenderDrawColor(renderer, shadowMapPx[i], 0, 0, 255);
        SDL_RenderDrawPoint(renderer, i % shadowMap.getRect()->w, i / shadowMap.getRect()->h);
    }*/

    // SDL_RenderCopy(renderer, shadowMap.get(), shadowMap.getRect(), shadowMap.getRect());
    drawEntitiesToMap(renderer);
    drawMap(renderer);
    std::string playerPosMsg = "x: " + std::to_string(currentPlayer->position.x) + ", y: " + std::to_string(currentPlayer->position.y);
    MessageTexture::renderMessage(renderer, MessageTexture::FAI_DEFAULT, playerPosMsg.c_str(), (Utils::Vector2I){0, 32}, Utils::Colors::white);
    // camera3D.drawFovLines(renderer);
}

void Game::drawEntitiesToMap(SDL_Renderer* renderer)
{
    SDL_Surface* mapSurface = SDL_CreateRGBSurface(0, mapRect.w, mapRect.h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

    SDL_LockSurface(mapSurface);
    {
        auto* pixels = (uint32_t*)mapSurface->pixels;
        glm::vec3 worldCenter = currentPlayer->position;
        float worldRotationY = -currentPlayer->rotationZ;
        const glm::vec2 cellCenter = {cellSize.x / 2, cellSize.y / 2};
        for (const auto& entity : world.children)
        {
            glm::vec2 dist = entity->position - worldCenter;
            if (dist.x > cellCenter.x) dist.x -= cellSize.x;
            else if (dist.x < -cellCenter.x) dist.x += cellSize.x;
            if (dist.y > cellCenter.y) dist.y -= cellSize.y;
            else if (dist.y < -cellCenter.y) dist.y += cellSize.y;
            // glm::vec2 shortestDist = {glm::min(dist.x, cellSize.x - dist.x), glm::min(dist.y, cellSize.y - dist.y)};
            float mapDistSq = dist.x * dist.x + dist.y * dist.y;
            if (mapDistSq < mapRenderRadiusSq)
            {
                glm::vec2 relativePos =
                        Utils::vec2Rotate(dist, worldRotationY);
                SDL_Point mapPos = {mapCenter.x + (int)relativePos.x, mapCenter.y + (int)relativePos.y};
                float distAlpha = mapDistSq / mapRadiusSq;
                pixels[mapRect.w * mapPos.y + mapPos.x] =
                        SDL_MapRGBA(mapSurface->format, 255, 255, 255, (uint8_t)(255 - 255 * distAlpha));
            }
        }
    }
    SDL_UnlockSurface(mapSurface);

    mapTexture = SDL_CreateTextureFromSurface(renderer, mapSurface);
    SDL_UpdateTexture(mapTexture, &mapRect, mapSurface->pixels, mapSurface->pitch);
    SDL_FreeSurface(mapSurface);
}

void Game::drawEntitiesDepth(SDL_Renderer* renderer, int cellId)
{
    auto farPlaneSquared = static_cast<float>(camera3D.farPlane * camera3D.farPlane);
    std::vector<std::pair<float, Entity3D*>> entityDistances;
    entityDistances.reserve(world.getSize());
    glm::vec2 camPos = camera3D.position;
    glm::vec2 forward = {std::cos(camera3D.rotationZ), std::sin(camera3D.rotationZ)};
    glm::vec2 right = {-forward.y, forward.x};
    glm::vec2 cellOffset = getCellPos(cellId) * cellSize;

    for (const auto& entity : world.children)
    {
        auto* entityPtr = entity.get();

        if (entityPtr != currentPlayer.get())
        {
            glm::vec2 relativePos = (glm::vec2)entity->position - cellOffset - camPos;
            float distForward = glm::dot(relativePos, forward);
            if (distForward >= 0) continue;
            float distRight = glm::dot(relativePos, right);
            float screenX = (distRight / distForward);

            if (screenX > -1 && screenX < 1)
            {
                float distSq = relativePos.x * relativePos.x + relativePos.y * relativePos.y;
                if (distSq < farPlaneSquared)
                    entityDistances.emplace_back(distSq, entityPtr);
            }
        }
    }

    std::sort(entityDistances.begin(), entityDistances.end(),
              [](const auto& a, const auto& b) { return a.first > b.first; });

    UniqueTexture& testTex = ResourceLoader::loadedTextures.swarm;
    SDL_Rect& viewport = App::renderer.viewport;
    for (const auto& [_, entity] : entityDistances)
    {
        camera3D.drawTexture3D(renderer, testTex, entity->position - glm::vec3(cellOffset.x, cellOffset.y, 0), entity->rotationZ, viewport);
    }
}

void Game::drawBackground(SDL_Renderer* renderer)
{
    SDL_Rect dst = *ResourceLoader::loadedTextures.testBg.getRect();
    dst.x = (int)((dst.w / M_PI_2) * -camera3D.rotationZ * .25f) % dst.w;

    SDL_RenderCopy(
            renderer,
            ResourceLoader::loadedTextures.testBg.get(),
            ResourceLoader::loadedTextures.testBg.getRect(),
            &dst);

    dst.x -= dst.w * Utils::sgn(dst.x);

    SDL_RenderCopy(
            renderer,
            ResourceLoader::loadedTextures.testBg.get(),
            ResourceLoader::loadedTextures.testBg.getRect(),
            &dst);
}

void Game::drawMap(SDL_Renderer* renderer)
{
    SDL_Point screenCenter = {(int)App::renderer.viewportCenter.x, (int)App::renderer.viewportCenter.y};
    SDL_Rect dstRect = {screenCenter.x - mapRect.w / 2, screenCenter.y - mapRect.h / 2, mapRect.w, mapRect.h};
    SDL_RenderCopy(renderer, mapTexture, &mapRect, &dstRect);

    SDL_DestroyTexture(mapTexture);
}

void Game::castShadow(SDL_Renderer* renderer, UniqueTexture& shadowTexture, glm::vec2 castPos)
{
    SDL_Rect* src = shadowTexture.getRect();
    SDL_Rect dst = *src;
    dst.x = (int)(castPos.x * shadowPixelDensity) - dst.w / 2;
    dst.y = (int)(castPos.y * shadowPixelDensity) - dst.h / 2;
    SDL_RenderCopy(renderer, shadowTexture.get(), src, &dst);
}

void Game::wrapInsideWorld(glm::vec3& vec)
{
    vec.x = Utils::fmod(vec.x, cellSize.x);
    vec.y = Utils::fmod(vec.y, cellSize.y);
}

glm::vec2 Game::getCellPos(int cellId)
{
    return glm::vec2{(cellId % CELLS_W) - CELLS_W / 2, (cellId / CELLS_W) - CELLS_W / 2};
}

void Game::drawEntityCells(SDL_Renderer* renderer)
{
    glm::vec2 camPos = camera3D.position;
    glm::vec2 forward = {std::cos(camera3D.rotationZ), std::sin(camera3D.rotationZ)};
    glm::vec2 right = {-forward.y, forward.x};
    std::vector<std::pair<float, int>> cellDistances;
    cellDistances.reserve(world.getSize());
    const glm::vec2 cellCenter = {cellSize.x / 2, cellSize.y / 2};

    for (int id = 0; id < CELLS_W * CELLS_W; id++)
    {
#if CELLS_W > 3
        if (id == centerCellId || id == 0 || id == CELLS_W-1 || id == (CELLS_W * CELLS_W) - CELLS_W || id == (CELLS_W * CELLS_W) - 1)
            continue;
#endif

        glm::vec2 relativePos = getCellPos(id) * cellSize;

        for (int corner = 0; corner < 4; corner++)
        {
            glm::vec2 cellCorner = camPos - (glm::vec2){corner % 2, corner / 2} * cellSize;
            float distForward = glm::dot(relativePos + cellCorner, forward);
            if (distForward <= 0) continue;
            float distRight = glm::dot(relativePos + cellCorner, right);
            float screenX = (distRight / distForward);

            if (screenX > -1 && screenX < 1)
            {
                relativePos += cellCenter;
                float distSq = relativePos.x * relativePos.x + relativePos.y * relativePos.y;
                cellDistances.emplace_back(distSq, id);
                break;
            }
        }
    }

    std::sort(cellDistances.begin(), cellDistances.end(),
              [](const auto& a, const auto& b) { return a.first > b.first; });

    // Calculate depth of all entities in cell in center of view
    // Use the depth for every rendered cell in back row
    // How is this slower?!?!?
    // const std::vector<Entity3D*> cellEntityDists = getEntitiesDepthOrder();

    for (const auto& [_, id] : cellDistances)
    {
        drawEntitiesDepth(renderer, id);
        // drawEntities(renderer, id, cellEntityDists);
    }

    // Draw center last
    drawEntitiesDepth(renderer, centerCellId);

    // Draw cell grid
    for (int i = 0; i < CELLS_W * CELLS_W; i++)
    {
        SDL_Rect drawRect = {32 + (int)getCellPos(i).x * 16, 32 + (int)getCellPos(i).y * 16, 16, 16};

        for (auto& cellDistance : cellDistances)
        {
            if (cellDistance.second == i)
            {
                SDL_RenderDrawRect(renderer, &drawRect);
            }
        }
    }
}

void Game::drawEntities(SDL_Renderer* renderer, int cellId,
                        const std::vector<Entity3D*>& entityDistances)
{
    auto farPlaneSquared = static_cast<float>(camera3D.farPlane * camera3D.farPlane);
    glm::vec2 camPos = camera3D.position;
    glm::vec2 cellOffset = getCellPos(cellId) * cellSize;
    glm::vec2 forward = {std::cos(camera3D.rotationZ), std::sin(camera3D.rotationZ)};
    glm::vec2 right = {-forward.y, forward.x};

    UniqueTexture& testTex = ResourceLoader::loadedTextures.swarm;
    SDL_Rect& viewport = App::renderer.viewport;
    for (auto* entity : entityDistances)
    {
        glm::vec2 relativePos = (glm::vec2)entity->position - cellOffset - camPos;

        float distSq = relativePos.x * relativePos.x + relativePos.y * relativePos.y;
        if (distSq < farPlaneSquared)
            camera3D.drawTexture3D(renderer, testTex, entity->position - glm::vec3(cellOffset.x, cellOffset.y, 0), entity->rotationZ, viewport);
    }
}

std::vector<Entity3D*> Game::getEntitiesDepthOrder()
{
    std::vector<float> entityDists;
    std::vector<Entity3D*> entityOrder;
    entityDists.reserve(world.getSize());
    entityOrder.reserve(world.getSize());
    glm::vec2 camPos = camera3D.position;
    glm::vec2 forward = {std::cos(camera3D.rotationZ), std::sin(camera3D.rotationZ)};
    glm::vec2 cellOffset = forward * cellSize;

    for (const auto& entity : world.children)
    {
        auto* entityPtr = entity.get();
        if (entityPtr != currentPlayer.get())
        {
            glm::vec2 relativePos = (glm::vec2)entity->position - cellOffset - camPos;
            float distSq = relativePos.x * relativePos.x + relativePos.y * relativePos.y;
            entityDists.emplace_back(distSq);
            entityOrder.emplace_back(entityPtr);
        }
    }

    std::vector<size_t> indices(entityDists.size());
    std::iota(indices.begin(), indices.end(), 0);

    std::sort(indices.begin(), indices.end(),
              [&entityDists](size_t i1, size_t i2) {
                  return entityDists[i1] > entityDists[i2];
              });

    std::vector<Entity3D*> sortedEntityOrder;

    for (size_t index : indices)
    {
        sortedEntityOrder.emplace_back(entityOrder[index]);
    }

    return sortedEntityOrder;
}

void Game::initShadowRaster()
{
    UniqueTexture shadowSTex =
            UniqueTexture(ResourceLoader::loadTextureStreaming(TEXTURES_PATH"/entities/entity-shadow-small-opaque.png"));

    auto* texPixels = new uint32_t[SHADOW_PX_S * SHADOW_PX_S];
    int texPitch;

    SDL_LockTexture(shadowSTex.get(), shadowSTex.getRect(), (void**)&texPixels, &texPitch);

    for (int i = 0; i < SHADOW_PX_S * SHADOW_PX_S; i++)
    {
        uint8_t red = (texPixels[i] & 0x00FF0000) >> 16;
        shadowTexPx[i] = red;
    }

    SDL_UnlockTexture(shadowSTex.get());

    shadowMapPx = new uint8_t[(int)(cellSize.x * shadowPixelDensity * cellSize.y * shadowPixelDensity)];
}

void Game::rasterizeShadowMap()
{
    SDL_Point mapDims = {
            static_cast<int>(cellSize.x * shadowPixelDensity),
            static_cast<int>(cellSize.y * shadowPixelDensity)};

    // delete[] shadowMapPx;
    // shadowMapPx = new uint8_t[mapDims.x * mapDims.y];
    std::fill(shadowMapPx, shadowMapPx + mapDims.x * mapDims.y, 0); // Clear shadow map

    int offset = SHADOW_PX_S / 2;

    for (const auto& entity : world.children)
    {
        for (int i = 0; i < SHADOW_PX_S * SHADOW_PX_S; i++)
        {
            int shadowX = (i % SHADOW_PX_S) - offset;
            int shadowY = (i / SHADOW_PX_S) - offset;

            int rawX = static_cast<int>(entity->position.x * shadowPixelDensity) + shadowX;
            int rawY = static_cast<int>(entity->position.y * shadowPixelDensity) + shadowY;

            int wrappedX = ((rawX % mapDims.x) + mapDims.x) % mapDims.x;
            int wrappedY = ((rawY % mapDims.y) + mapDims.y) % mapDims.y;

            int mapIndex = wrappedY * mapDims.x + wrappedX;

            shadowMapPx[mapIndex] += shadowTexPx[i];
        }
    }
}
