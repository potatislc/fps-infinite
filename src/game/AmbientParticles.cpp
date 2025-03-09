#include "AmbientParticles.h"
#include "engine/Camera3D.h"
#include "engine/ResourceLoader.h"

void AmbientParticles::draw(SDL_Renderer* renderer, SDL_Rect& viewport, Camera3D& camera, float time)
{
    // Parameters for particle motion
    constexpr int numLayers = 5;       // Number of sine/cosine layers per axis
    constexpr float speed = 0.3f;      // Base movement speed multiplier
    constexpr float amplitude = 5.0f; // Maximum displacement in any direction
    constexpr float scale = 0.1f;     // Base scale factor for noise
    static std::vector<float> seeds;

    // Initialize seeds once
    if (seeds.empty())
    {
        seeds.resize(maxParticles);
        for (int i = 0; i < maxParticles; i++)
        {
            seeds[i] = static_cast<float>(i) * 7.77f + 13.337f; // Arbitrary unique values per particle
        }
    }

    for (int i = 0; i < maxParticles; i++)
    {
        float seed = seeds[i];
        glm::vec3 particlePos(0.0f);

        // Accumulate multiple layers for each axis
        for (int layer = 0; layer < numLayers; layer++)
        {
            float layerSpeed = speed * (1.0f + layer * 0.1f); // Slightly vary speed per layer
            float layerAmplitude = amplitude / (layer + 1);   // Reduce amplitude for higher layers
            float layerScale = scale * (1.0f + layer * 0.5f); // Vary scale for each layer

            particlePos.x += glm::sin(time * layerSpeed + seed * layerScale) * layerAmplitude;
            particlePos.y += glm::cos(time * layerSpeed + seed * layerScale * 1.3f) * layerAmplitude * 0.8f;
            particlePos.z += glm::sin(time * layerSpeed * 1.5f + seed * layerScale * 0.7f) * layerAmplitude * 0.6f;
        }

        // Draw the particle
        camera.drawTexture3D(renderer, ResourceLoader::loadedTextures.entityShadow, particlePos, viewport);
    }
}


AmbientParticles::AmbientParticles(uint8_t count, float radius) : radius(radius)
{

}
