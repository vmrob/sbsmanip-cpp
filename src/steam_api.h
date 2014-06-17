#pragma once

namespace sbsmanip {

/**
 * Asynchronously retrieve a steam user's username via the Valve Community Data API
 * See https://partner.steamgames.com/documentation/community_data
 *
 * This is an asynchronous function and so a callback is required.
 * Values returned from this are cached for quick access. To force a
 * refresh, set the forceRefresh value appropriately.
 * 
 * @param id 64bit numerical id of the steam user
 * @param forceRefresh whether or not to force an overwrite of the cached value
 */
std::future<std::string> GetSteamId(uint64_t id, bool forceRefresh = false);

} // namespace sbsmanip