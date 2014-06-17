#include "pch.h"
#include "steam_api.h"

#include "utility.h"
#include "XmlDocument.h"

namespace sbsmanip {

namespace detail {

	static std::unordered_map<uint64_t, std::string> _gSteamIds;
	static std::mutex _gSteamIdsMutex;

	std::string _DoGetSteamId(uint64_t id) {
		{
			std::lock_guard<std::mutex> lock(_gSteamIdsMutex);
			_gSteamIds[id] = "";
		}

		std::string url = Format("http://steamcommunity.com/profiles/%u/?xml=1", id);
		std::stringstream ss;

		try {
			curlpp::Cleanup myCleanup;
			curlpp::Easy request;

			request.setOpt(new curlpp::options::Url(url));
			request.setOpt(new curlpp::options::FollowLocation(true));

			ss << request;

		} catch ( curlpp::LogicError& e) {
			std::cout << e.what() << std::endl;
		} catch ( curlpp::RuntimeError& e) {
			std::cout << e.what() << std::endl;
		}

		std::string username;

		try {
			XmlDocument response(ss);

			std::string error = response.root().child("response").child_value("error");
			if (!error.empty()) {
				throw std::runtime_error(error);
			}
			username = response.root().child("profile").child_value("steamID");
		} catch (std::runtime_error& e) {
			std::cerr << e.what() << std::endl;
			return "";
		} catch (...) {
			std::cerr << "unable to parse response for steamid " << id << std::endl;
			return "";
		}

		{
			std::lock_guard<std::mutex> lock(_gSteamIdsMutex);
			_gSteamIds[id] = username;
		}
		
		return username;
	}

}

std::future<std::string> GetSteamId(uint64_t id, bool forceRefresh) {
	if (!forceRefresh) {
		std::lock_guard<std::mutex> lock(detail::_gSteamIdsMutex);
		auto it = detail::_gSteamIds.find(id);
		if (it != detail::_gSteamIds.end()) {
			return std::async(std::launch::async, [idStr = it->second]() { return idStr; });
		}
	}

	return std::async(std::launch::async, [=]() { return detail::_DoGetSteamId(id); });
}

} // namespace sbsmanip