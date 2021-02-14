#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>
#include "rapidxml.hpp"

using namespace rapidxml;

char* dump_file(std::ifstream& file) {
  char *out;

  //std::string out;
  file.seekg(0, std::ios::end);
  //out.reserve(file.tellg());
  out = new char[static_cast<int>(file.tellg())+1];
  file.seekg(0, std::ios::beg);
  std::copy((std::istreambuf_iterator<char>(file)),
     std::istreambuf_iterator<char>(), out);
  //out.assign((std::istreambuf_iterator<char>(file)),
  //   std::istreambuf_iterator<char>());
  return out;
}

void check(auto doc_node) {
  if (!doc_node) {
    std::cerr << "Node not found\n";
  }
  std::exit(1);
}


int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usgage: lptotxt [FILE]\n";
    return 1;
  }

  std::ifstream file{argv[1]};
  if (!file.good()) {
    std::cerr << "Could not open " << argv[1] << '\n';
    return 1;
  }

  char *contents = dump_file(file);


  xml_document<> doc;
  doc.parse<0>(contents);
  std::cout << "Name of first node: " << doc.first_node()->name() << '\n';

  // Hierarchy: Document -> DataSet -> DataColumn -> ColumnCells
  auto doc_node = doc.first_node();
  auto dataset_node = doc_node()->first_node("DataSet");
  for (auto node = dataset_node->first_node(); node != nullptr; node = node->next_sibling()) {
    if (strcmp(node->name(), "DataColumn")) continue;
    // Loop over DataColumns
  }





  delete[] contents;

  return 0;
}
