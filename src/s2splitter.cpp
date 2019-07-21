#include "s2splitter.h"

#include "s2/s2cell.h"
#include "s2/s2latlng.h"
#include "s2/s2cell_id.h"
#include <osmium/io/writer.hpp>
#include <osmium/io/input_iterator.hpp>
#include <osmium/io/any_output.hpp>
#include <osmium/builder/osm_object_builder.hpp>
#include <osmium/builder/attr.hpp>

#include <sstream>

S2Splitter::S2Splitter(int s2Level)
: mS2Level(s2Level) 
{

}

void S2Splitter::setOutputDirectory(const std::string& dir)
{
  mOutputDirectory = dir;
}

void S2Splitter::setOutputXml(bool xml)
{
  mOutXml = xml;
}

S2Splitter::SetOfNodeIds& S2Splitter::getSetOfNodesForS2Cell(uint64_t cellId)
{
  const auto& iter = mWrittenNodesOfCellId.find(cellId);
  
  if(iter != mWrittenNodesOfCellId.end()) {
    return iter->second;      
  }
  else {
    mWrittenNodesOfCellId[cellId] = SetOfNodeIds();
    return mWrittenNodesOfCellId[cellId];
  }
}


std::string S2Splitter::fileNameOfS2Cell(uint64_t cellId)
{
  std::stringstream ss;

  if(mOutputDirectory.size() > 0) {
    ss << mOutputDirectory;
    if(mOutputDirectory.back() != '/') {
      ss << '/';
    }
  }

  ss << "s2_" << cellId << (mOutXml ? ".osm" : ".osm.pbf");
  return ss.str();
}
void S2Splitter::way(osmium::Way& way)
{
  auto& nodeList = way.nodes();

  std::unordered_set<uint64_t> cellsCovered;

  //create a list of s2cells which the nodes in this way occupy
  for(auto& node : nodeList) {

    cellsCovered.insert(
      S2Cell(S2LatLng::FromDegrees( // s2cell based on lat lon coords of node
        node.location().lat(), //node's lat lon coords
        node.location().lon()
      )) 
      .id().parent(mS2Level).id() // s2cell's id of parent at given level
    );
  }

  //for each s2cell covered by the way, add any nodes not yet added to it's file and then the way as well
  for(auto cellId : cellsCovered) {

    auto writer = std::make_shared<osmium::io::Writer>(osmium::io::File(fileNameOfS2Cell(cellId)), osmium::io::overwrite::allow);

    SetOfNodeIds& nodeIdSet = getSetOfNodesForS2Cell(cellId);

    osmium::memory::Buffer nodeBuffer{16, osmium::memory::Buffer::auto_grow::yes};

    for(auto& node : nodeList) {
      if(nodeIdSet.find(node.ref()) == nodeIdSet.end()) { // if the node is not already in the set we want to write it to the s2's file

        osmium::builder::add_node(nodeBuffer,
          osmium::builder::attr::_id(node.ref()),
          osmium::builder::attr::_location(node.location())
        );
      }
    }

    osmium::builder::add_way(nodeBuffer,
      osmium::builder::attr::_id(way.id()),
      osmium::builder::attr::_tags(way.tags()),
      osmium::builder::attr::_nodes(way.nodes())
    );

    (*writer)(std::move(nodeBuffer));
  }
}

