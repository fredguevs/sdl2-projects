#ifndef ECH_H
#define ECH_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID() {
  static ComponentID lastID = 0;
  return lastID++; 
}

template <typename T> 
inline ComponentID getComponentTypeID() noexcept { // noexcept - specifies function is non-throwing
  // Overload resolution prefers non-template functions when both match
  // this is a perfect match though since it doesn't include getComponentID<T>
  static ComponentID typeID = getComponentTypeID();
  return typeID;
}

constexpr std::size_t maxComponents = 32; // Non-type template parameters like N in std::bitset<N> must be compile-time constexpr

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
public:
  Entity * entity;

  virtual void init() {}
  virtual void update() {}
  virtual void draw() {}
  virtual ~Component() {}
};

class Entity {
private:
  bool active = true;
  // Don't know how many components an entity has at compile time
  // unique_ptr alows for automatic destruction when entity dies
  std::vector<std::unique_ptr<Component>> components; // there can be at most one unique_ptr pointing to any one resource
  
  ComponentArray componentArray;
  ComponentBitSet componentBitSet;

public:
  void update() {
    for (auto& c: components) {
      c->update();
    }
  }

  void draw() {
    for (auto& c: components) {
      c->draw();
    }

  };
  bool isActive() { return active; }

  // Component has reference to owner, call this function from any component, Manager class loops and checks
  // entity's active status, if false, removes them from the game
  void destroy() { active = false; }

  // Need to allow entity class to see whether or not it has components
  template <typename T> bool hasComponent() const {
    return componentBitSet[getComponentTypeID<T>];
  }

  template <typename T, typename... TArgs>
  T& addComponent(TArgs&&... mArgs) {
    // TArgs&& lets us preserve temporary arguments when passing them in

    // std::forward preserves lvalues & temporary lvalues when passed in 
    T* c(new T(std::forward<TArgs>(mArgs)...));
    c->entity = this;

    // uPtr owns component
    std::unique_ptr<Component> uPtr{ c };

    // casts pointer to component as rvalue
    // vector wants to take ownership can't do uPtr -> copy
    // move(uPtr) allows us to transfer ownership
    components.emplace_back(std::move(uPtr));

    componentArray[getComponentTypeID<T>()] = c;
    componentBitSet[getComponentTypeID<T>()] = true;

    c->init();
    return *c;
  }

  template <typename T>
  T& getComponent() const {
    auto ptr(componentArray[getComponentTypeID<T>()]);
    return *static_cast<T*>(ptr);
  }

};

class Manager {
private:
  std::vector<std::unique_ptr<Entity>> entities;

public:
  void update() {
    for (auto& e: entities) {
      e->update();
    }
  }

  void draw() {
    for (auto& e: entities) {
      e->draw();
    }
  }

  void refresh() {
    entities.erase(
      std::remove_if(
        std::begin(entities),
        std::end(entities),
        [](const std::unique_ptr<Entity>& mEntity) {
            return !mEntity->isActive();
        }
      ),
      std::end(entities)
    );
  }

  Entity& addEntity() {
    Entity* e = new Entity();
    std::unique_ptr<Entity> uPtr{ e };
    entities.emplace_back(std::move(uPtr));

    return *e;
  }
};


#endif // ECH_H