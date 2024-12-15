#include <iostream>
#include <fstream>
#include "point_set.h"
#include "check_functions.h"

int main(int argc, char* argv []) {
  options generate;
  ValidateCommand(argc, argv, generate);

  std::ifstream input_file (argv[1]);
  if (!input_file.is_open()) {
    std::cerr << "Failed to open points.txt" << std::endl;
  }

  int num_points;
  input_file >> num_points;
  if (num_points <= 0) {
    std::cerr << "Invalid number of points in the file" << std::endl;
  }

  CyA::point_vector points;
  for (int i = 0; i < num_points; ++i) {
    double x, y;
    input_file >> x >> y;
    points.emplace_back(x, y);
  }
  
  input_file.close();

  CyA::point_set point_set(points);

  point_set.quickHull();

  point_set.write_hull(std::cout);
  
  if (generate.generate_dot == 0) {
    std::ofstream dot_file(generate.dot_file_name);
    if (dot_file.is_open()) {
      point_set.write_graphviz(dot_file);
      dot_file.close();
    } else {
      std::cerr << "File: " << generate.dot_file_name << " couldn't be opened" << std::endl;
      return 1;
    }
  }

  return 0;
}
