#pragma once

#include <cstdlib>
#include <memory>

#include "bot.h"
#include "map.h"

class Behavior {
protected:
    inline static Map* today_map_ = nullptr;
    inline static Map* tomorrpow_map_ = nullptr;

public:
    Behavior() = default;
    
    Behavior(Map* today_map, Map* tomorrow_map);

    std::vector<std::unique_ptr<Behavior>> get_behaviors() const;

    virtual void action(const Bot&);
};

class Fight : public Behavior {
public:
    Fight() {}
    
    void action(const Bot& bot) override;
};
