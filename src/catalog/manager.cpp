//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// manager.cpp
//
// Identification: src/catalog/manager.cpp
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "common/exception.h"
#include "common/logger.h"
#include "catalog/manager.h"
#include "catalog/foreign_key.h"
#include "storage/database.h"
#include "storage/data_table.h"
#include "concurrency/transaction_manager_factory.h"

namespace peloton {
namespace catalog {

Manager &Manager::GetInstance() {
  static Manager manager;
  return manager;
}

//===--------------------------------------------------------------------===//
// OBJECT MAP
//===--------------------------------------------------------------------===//

void Manager::AddTileGroup(const oid_t oid,
                           std::shared_ptr<storage::TileGroup> location) {

  // drop any existing catalog reference to the tile group
  locator.Erase(oid);

  // add a new catalog reference to the tile group
  locator.Insert(oid, location);
}

void Manager::DropTileGroup(const oid_t oid) {
  concurrency::TransactionManagerFactory::GetInstance().DroppingTileGroup(oid);
  LOG_TRACE("Dropping tile group %u", oid);

  // drop the catalog reference to the tile group
  locator.Erase(oid);
}

std::shared_ptr<storage::TileGroup> Manager::GetTileGroup(const oid_t oid) {
  std::shared_ptr<storage::TileGroup> location;

  locator.Find(oid, location);

  return location;
}

// used for logging test
void Manager::ClearTileGroup() {
  locator.Clear();
}

//===--------------------------------------------------------------------===//
// DATABASE
//===--------------------------------------------------------------------===//

void Manager::AddDatabase(storage::Database *database) {
  {
    std::lock_guard<std::mutex> lock(catalog_mutex);
    databases.push_back(database);
  }
}

storage::Database *Manager::GetDatabaseWithOid(const oid_t database_oid) const {
  for (auto database : databases) {
    if (database->GetOid() == database_oid) return database;
  }

  return nullptr;
}

void Manager::DropDatabaseWithOid(const oid_t database_oid) {
  {
    std::lock_guard<std::mutex> lock(catalog_mutex);

    oid_t database_offset = 0;
    for (auto database : databases) {
      if (database->GetOid() == database_oid) {
        delete database;
        break;
      }
      database_offset++;
    }
    PL_ASSERT(database_offset < databases.size());

    // Drop the database
    databases.erase(databases.begin() + database_offset);
  }
}

storage::Database *Manager::GetDatabase(const oid_t database_offset) const {
  PL_ASSERT(database_offset < databases.size());
  auto database = databases.at(database_offset);
  return database;
}

oid_t Manager::GetDatabaseCount() const { return databases.size(); }

//===--------------------------------------------------------------------===//
// CONVENIENCE WRAPPERS
//===--------------------------------------------------------------------===//

storage::DataTable *Manager::GetTableWithOid(const oid_t database_oid,
                                             const oid_t table_oid) const {
  // Lookup DB
  auto database = GetDatabaseWithOid(database_oid);

  // Lookup table
  if (database != nullptr) {
    auto table = database->GetTableWithOid(table_oid);
    return table;
  }

  return nullptr;
}

storage::DataTable *Manager::GetTableWithName(
    const oid_t database_oid, const std::string table_name) const {
  // Lookup DB
  auto database = GetDatabaseWithOid(database_oid);

  // Lookup table
  if (database != nullptr) {
    auto table = database->GetTableWithName(table_name);
    return table;
  }

  return nullptr;
}

index::Index *Manager::GetIndexWithOid(const oid_t database_oid,
                                       const oid_t table_oid,
                                       const oid_t index_oid) const {
  // Lookup table
  auto table = GetTableWithOid(database_oid, table_oid);

  // Lookup index
  if (table != nullptr) {
    auto index = table->GetIndexWithOid(index_oid);
    return index;
  }

  return nullptr;
}

}  // End catalog namespace
}  // End peloton namespace
