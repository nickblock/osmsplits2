
#pragma once

#include <osmium/handler.hpp>
#include <osmium/osm/node.hpp>
#include <osmium/osm/way.hpp>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <stdint.h>


class S2Splitter : public osmium::handler::Handler {

public:
  
  S2Splitter(int s2level);

  void setOutputDirectory(const std::string&);

  void way(osmium::Way& way);

private:

  using SetOfNodeIds = std::unordered_set<osmium::unsigned_object_id_type>;
  
  SetOfNodeIds& getSetOfNodesForS2Cell(uint64_t);
  std::string fileNameOfS2Cell(uint64_t);

  std::unordered_map<uint64_t, SetOfNodeIds> mWrittenNodesOfCellId;

  int mS2Level;
  std::string mOutputDirectory;

};