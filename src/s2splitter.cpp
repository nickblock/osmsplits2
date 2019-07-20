#include "s2splitter.h"

#include "s2/s2cell.h"
#include "s2/s2latlng.h"
#include "s2/s2cell_id.h"

S2Splitter::S2Splitter(int s2level)
: mS2Level(mS2Level) 
{

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

void S2Splitter::way(osmium::Way& way)
{
  auto& nodeList = way.nodes();

  std::unordered_set<uint64_t> cellsCovered;

  //create a list of s2cells which the nodes in this way occupy
  for(auto& node : nodeList) {

    auto node_loc = node.location();

    auto s2Cell = S2Cell(S2LatLng::FromDegrees(node_loc.lat(), node_loc.lon()));

    cellsCovered.insert(s2Cell.id().parent(mS2Level).id());
  }

  //for each s2cell covered add any nodes not yet added to it and then the way to it's file
  for(auto cellId : cellsCovered) {

    SetOfNodeIds nodeIdSet = getSetOfNodesForS2Cell(cellId);

    for(auto& node : nodeList) {
      if(nodeIdSet.find(node.ref()) == nodeIdSet.end()) {

      }
    }
  }
}

