
#pragma once

#include <osmium/handler.hpp>
#include <osmium/osm/node.hpp>
#include <osmium/osm/way.hpp>
#include <osmium/io/writer.hpp>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <memory>
#include <stdint.h>


class S2Splitter : public osmium::handler::Handler {

public:
  
  S2Splitter(int s2level);

  void setOutputDirectory(const std::string&);
  void setOutputXml(bool xml);

  void way(osmium::Way& way);

private:

  using SetOfNodeIds = std::unordered_set<osmium::unsigned_object_id_type>;
  
  SetOfNodeIds&                         getSetOfNodesForS2Cell(uint64_t cellId);
  std::shared_ptr<osmium::io::Writer>   getWriterForS2Cell(uint64_t cellId);
  std::string                           fileNameOfS2Cell(uint64_t cellId);

  std::unordered_map<uint64_t, SetOfNodeIds> mWrittenNodesOfCellId;
  std::unordered_map<uint64_t, std::shared_ptr<osmium::io::Writer>> mWritersForS2Cell;

  int mS2Level = 10;
  std::string mOutputDirectory;
  bool mOutXml = false;

};