
#pragma once

#include <osmium/index/node_locations_map.hpp>
#include <osmium/handler/node_locations_for_ways.hpp>
#include <osmium/index/map/sparse_mem_array.hpp>

using NodeLocatorMap = osmium::index::map::SparseMemArray<osmium::unsigned_object_id_type, osmium::Location>;
using location_handler_type = osmium::handler::NodeLocationsForWays<NodeLocatorMap>;

class S2Splitter : public location_handler_type {
public:
  S2Splitter(NodeLocatorMap& store, int s2level);

  void node(const osmium::Node& node);
  void way(osmium::Way& way);



};