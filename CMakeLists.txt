cmake_minimum_required(VERSION 2.8)

# Name of the project (will be the name of the plugin)
project(osmsplits2)

add_library(s2 STATIC
            s2geometry/src/s2/base/stringprintf.cc
            s2geometry/src/s2/base/strtoint.cc
            s2geometry/src/s2/encoded_s2cell_id_vector.cc
            s2geometry/src/s2/encoded_s2point_vector.cc
            s2geometry/src/s2/encoded_s2shape_index.cc
            s2geometry/src/s2/encoded_string_vector.cc
            s2geometry/src/s2/id_set_lexicon.cc
            s2geometry/src/s2/mutable_s2shape_index.cc
            s2geometry/src/s2/r2rect.cc
            s2geometry/src/s2/s1angle.cc
            s2geometry/src/s2/s1chord_angle.cc
            s2geometry/src/s2/s1interval.cc
            s2geometry/src/s2/s2boolean_operation.cc
            s2geometry/src/s2/s2builder.cc
            s2geometry/src/s2/s2builder_graph.cc
            s2geometry/src/s2/s2builderutil_closed_set_normalizer.cc
            s2geometry/src/s2/s2builderutil_find_polygon_degeneracies.cc
            s2geometry/src/s2/s2builderutil_lax_polygon_layer.cc
            s2geometry/src/s2/s2builderutil_s2point_vector_layer.cc
            s2geometry/src/s2/s2builderutil_s2polygon_layer.cc
            s2geometry/src/s2/s2builderutil_s2polyline_layer.cc
            s2geometry/src/s2/s2builderutil_s2polyline_vector_layer.cc
            s2geometry/src/s2/s2builderutil_snap_functions.cc
            s2geometry/src/s2/s2cap.cc
            s2geometry/src/s2/s2cell.cc
            s2geometry/src/s2/s2cell_id.cc
            s2geometry/src/s2/s2cell_index.cc
            s2geometry/src/s2/s2cell_union.cc
            s2geometry/src/s2/s2centroids.cc
            s2geometry/src/s2/s2closest_cell_query.cc
            s2geometry/src/s2/s2closest_edge_query.cc
            s2geometry/src/s2/s2closest_point_query.cc
            s2geometry/src/s2/s2contains_vertex_query.cc
            s2geometry/src/s2/s2convex_hull_query.cc
            s2geometry/src/s2/s2coords.cc
            s2geometry/src/s2/s2crossing_edge_query.cc
            s2geometry/src/s2/s2debug.cc
            s2geometry/src/s2/s2earth.cc
            s2geometry/src/s2/s2edge_clipping.cc
            s2geometry/src/s2/s2edge_crosser.cc
            s2geometry/src/s2/s2edge_crossings.cc
            s2geometry/src/s2/s2edge_distances.cc
            s2geometry/src/s2/s2edge_tessellator.cc
            s2geometry/src/s2/s2error.cc
            s2geometry/src/s2/s2furthest_edge_query.cc
            s2geometry/src/s2/s2latlng.cc
            s2geometry/src/s2/s2latlng_rect.cc
            s2geometry/src/s2/s2latlng_rect_bounder.cc
            s2geometry/src/s2/s2lax_loop_shape.cc
            s2geometry/src/s2/s2lax_polygon_shape.cc
            s2geometry/src/s2/s2lax_polyline_shape.cc
            s2geometry/src/s2/s2loop.cc
            s2geometry/src/s2/s2loop_measures.cc
            s2geometry/src/s2/s2measures.cc
            s2geometry/src/s2/s2metrics.cc
            s2geometry/src/s2/s2max_distance_targets.cc
            s2geometry/src/s2/s2min_distance_targets.cc
            s2geometry/src/s2/s2padded_cell.cc
            s2geometry/src/s2/s2point_compression.cc
            s2geometry/src/s2/s2point_region.cc
            s2geometry/src/s2/s2pointutil.cc
            s2geometry/src/s2/s2polygon.cc
            s2geometry/src/s2/s2polyline.cc
            s2geometry/src/s2/s2polyline_alignment.cc
            s2geometry/src/s2/s2polyline_measures.cc
            s2geometry/src/s2/s2polyline_simplifier.cc
            s2geometry/src/s2/s2predicates.cc
            s2geometry/src/s2/s2projections.cc
            s2geometry/src/s2/s2r2rect.cc
            s2geometry/src/s2/s2region.cc
            s2geometry/src/s2/s2region_term_indexer.cc
            s2geometry/src/s2/s2region_coverer.cc
            s2geometry/src/s2/s2region_intersection.cc
            s2geometry/src/s2/s2region_union.cc
            s2geometry/src/s2/s2shape_index.cc
            s2geometry/src/s2/s2shape_index_buffered_region.cc
            s2geometry/src/s2/s2shape_index_measures.cc
            s2geometry/src/s2/s2shape_measures.cc
            s2geometry/src/s2/s2shapeutil_build_polygon_boundaries.cc
            s2geometry/src/s2/s2shapeutil_coding.cc
            s2geometry/src/s2/s2shapeutil_contains_brute_force.cc
            s2geometry/src/s2/s2shapeutil_edge_iterator.cc
            s2geometry/src/s2/s2shapeutil_get_reference_point.cc
            s2geometry/src/s2/s2shapeutil_range_iterator.cc
            s2geometry/src/s2/s2shapeutil_visit_crossing_edge_pairs.cc
            s2geometry/src/s2/s2text_format.cc
            s2geometry/src/s2/s2wedge_relations.cc
            s2geometry/src/s2/strings/ostringstream.cc
            s2geometry/src/s2/strings/serialize.cc
            s2geometry/src/s2/third_party/absl/base/dynamic_annotations.cc
            s2geometry/src/s2/third_party/absl/base/internal/raw_logging.cc
            s2geometry/src/s2/third_party/absl/base/internal/throw_delegate.cc
            s2geometry/src/s2/third_party/absl/numeric/int128.cc
            s2geometry/src/s2/third_party/absl/strings/ascii.cc
            s2geometry/src/s2/third_party/absl/strings/match.cc
            s2geometry/src/s2/third_party/absl/strings/numbers.cc
            s2geometry/src/s2/third_party/absl/strings/str_cat.cc
            s2geometry/src/s2/third_party/absl/strings/str_split.cc
            s2geometry/src/s2/third_party/absl/strings/string_view.cc
            s2geometry/src/s2/third_party/absl/strings/strip.cc
            s2geometry/src/s2/third_party/absl/strings/internal/memutil.cc
            s2geometry/src/s2/util/bits/bit-interleave.cc
            s2geometry/src/s2/util/bits/bits.cc
            s2geometry/src/s2/util/coding/coder.cc
            s2geometry/src/s2/util/coding/varint.cc
            s2geometry/src/s2/util/math/exactfloat/exactfloat.cc
            s2geometry/src/s2/util/math/mathutil.cc
            s2geometry/src/s2/util/units/length-units.cc)

target_include_directories(s2 PUBLIC s2geometry/src)
target_compile_options(s2 PRIVATE -Wno-attributes)

add_executable(osms2split
  src/main.cpp
  src/s2splitter.cpp)

target_compile_options(osms2split PRIVATE -Wno-attributes)
target_include_directories(osms2split PUBLIC protozero/include)
target_include_directories(osms2split PUBLIC libosmium/include)
target_include_directories(osms2split PUBLIC s2geometry/src)

target_link_libraries(osms2split PUBLIC s2 ssl crypto bz2 z expat pthread)