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

    SetOfNodeIds& nodeIdSet = getSetOfNodesForS2Cell(cellId);

    for(auto& node : nodeList) {
      if(nodeIdSet.find(node.ref()) == nodeIdSet.end()) { // if the node is not already in the set we want to write it to the s2's file

      }
    }
  }
}

