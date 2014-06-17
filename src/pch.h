#ifndef SBSMANIP_PCH_H
#define SBSMANIP_PCH_H

#include <cstdint>
#include <cstring>
#include <future>
#include <istream>
#include <limits>
#include <memory>
#include <mutex>
#include <sstream>
#include <type_traits>
#include <vector>
#include <unordered_map>

#include <pugixml.hpp>

#include <boost/call_traits.hpp>
#include "boost/format.hpp"
#include <boost/iterator/iterator_facade.hpp>
#include <boost/operators.hpp>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcomment"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>

#pragma clang diagnostic pop

#endif // SBSMANIP_PCH_H