#pragma once 
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <cassert>

namespace ResourceHolders
{   
    template <typename Resource, typename Identifier>
    class ResourceHolder 
    {
    private:
        std::map<Identifier, std::unique_ptr<Resource>> ResourceMap; 
    public:
        template <typename Parameter> 
        void load(Identifier id, const std::string& filename, const Parameter& secondParam);
        void load(Identifier id, const std::string& filename);
        const Resource& get(Identifier id) const;
        Resource& get(Identifier id);
    };

    template <typename Resource, typename Identifier>
    void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
    {
        std::unique_ptr<Resource> resource(new Resource());
        if (!resource->loadFromFile(filename))
            throw std::runtime_error("ResouceHolder::load - Failed to load " + filename);

        auto inserted = ResourceMap.insert(std::make_pair(id, std::move(resource)));
        assert(inserted.second);    
    }

    template <typename Resource, typename Identifier>
    const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const 
    {
        auto found_element = ResourceMap.find(id);
        assert(found_element != ResourceMap.end());

        return *found_element->second;
    }

    template <typename Resource, typename Identifier>
    Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
    {
        auto found_element = ResourceMap.find(id);
        assert(found_element != ResourceMap.end());
        
        return *found_element->second;
    }

    template <typename Resource, typename Identifier>
    template <typename Parameter>
    void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam)
    {
        std::unique_ptr<Resource> resource(new Resource());
        if (!resource->loadFromFile(filename, secondParam))
            throw std::runtime_error("ResouceHolder::load - Failed to load " + filename);

        auto inserted = ResourceMap.insert(std::make_pair(id, std::move(resource)));
        assert(inserted.second); 
    }

    extern ResourceHolder<sf::Shader, std::string>* ShaderHolder;
    extern ResourceHolder<sf::Font, std::string>* FontHolder;
};