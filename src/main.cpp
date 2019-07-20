
/*

  EXAMPLE osmium_pub_names

  Show the names and addresses of all pubs found in an OSM file.

  DEMONSTRATES USE OF:
  * file input
  * your own handler
  * access to tags

  SIMPLER EXAMPLES you might want to understand first:
  * osmium_read
  * osmium_count

  LICENSE
  The code in this example file is released into the Public Domain.

*/

#include <cstdlib>  // for std::exit
#include <cstring>  // for std::strncmp
#include <iostream> // for std::cout, std::cerr
#include "args.hxx"

// Allow any format of input files (XML, PBF, ...)
#include <osmium/io/any_input.hpp>

// We want to use the handler interface
#include <osmium/handler.hpp>

// For osmium::apply()
#include <osmium/visitor.hpp>

#include <osmium/index/map/flex_mem.hpp>
#include <osmium/handler/node_locations_for_ways.hpp>

#include "s2splitter.h"

using std::string;
using std::cout;
using std::endl;

class NamesHandler : public osmium::handler::Handler {

    void output_pubs(const osmium::OSMObject& object) {
      // cout << object.id() << endl;
    }

public:

    // Nodes can be tagged amenity=pub.
    void node(const osmium::Node& node) {
        output_pubs(node);
    }

    // Ways can be tagged amenity=pub, too (typically buildings).
    void way(const osmium::Way& way) {
        output_pubs(way);
    }

}; // class NamesHandler

int main(int argi, char* argv[]) {

  args::ArgumentParser          parser("osmsplits2. Take a single large osm file and split it into files defined by s2 cells", 
    "You must at least specify one input osm/som.pbf file, an output directory, and the s2 level to split dowm to");

  args::ValueFlag<string>  inputFileArg(parser, "*.osm|*.pbf", "Specify input .osm file", {'i'});
  args::ValueFlag<string>  outputDirArg(parser, "/", "Specify output directory", {'o'});
  args::ValueFlag<int>     s2LevelArg(parser, "1", "Specify number of splits wanted", {'l'});

  try
  {
      parser.ParseCLI(argi, argv);
  }
  catch (args::Help)
  {
      std::cout << parser;
      std::exit(1);
  }

  if(args::get(inputFileArg).size() == 0 || args::get(outputDirArg).size() == 0) 
  {
      std::cout << parser;
      std::exit(1);
  }

  
  try {

      NodeLocatorMap nodeLocatorStore;

      // Construct the handler defined above
      S2Splitter s2Splitter(nodeLocatorStore, 14);

      osmium::io::Reader reader{args::get(inputFileArg), osmium::osm_entity_bits::node | osmium::osm_entity_bits::way};

      // Apply input data to our own handler
      osmium::apply(reader, s2Splitter);

      cout << "done" << endl;

  } catch (const std::exception& e) {
      // All exceptions used by the Osmium library derive from std::exception.
      std::cerr << e.what() << '\n';
      std::exit(1);
  }
}

