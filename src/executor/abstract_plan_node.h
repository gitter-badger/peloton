#include "storage/tile.h"

#pragma once

namespace nstore {
namespace executor {

class AbstractPlanNode {
  public:
    bool init();
    storage::Physical_Tile *getNextTile();
    void cleanup();
  protected:
    virtual bool p_init() = 0;
    virtual storage::Physical_Tile *p_getNextTile() = 0;
    virtual void p_cleanup() = 0;
};

} // namespace executor
} // namespace nstore
