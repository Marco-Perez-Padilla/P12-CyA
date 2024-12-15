/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Computabilidad y Algoritmia
** Curso: 2º
** Practica 12: Algoritmos Divide y Vencerás
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 13/10/2024

** Archivo point_set.cc: Implementación de los métodos de la clase point_set.
**             Contiene lo necesario para implementar el algoritmo QuickHull.
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      13/10/2024 - Creacion (primera version) del codigo
**      15/10/2024 - Creación de métodos restantes y de escritura
**/

#include <algorithm>
#include <cmath>
#include <map>

#include "point_set.h"

/**
 * @brief Method that calculates the distance from a line to a point
 * @param line which will define two of the points
 * @param point the thrid point
 * @return double type, the distance
 */
double CyA::point_set::point_2_line(const CyA::line &l, const CyA::point &p) const {
  const CyA::point &p1 = l.first;
  const CyA::point &p2 = l.second;

  return (p.second - p1.second) * (p2.first - p1.first) - (p2.second - p1.second) * (p.first - p1.first);
}


/**
 * @brief Method to determine the side of a point given a line using point_2_line
 * @param line. Pair of points, forming a line
 * @param point whose side we are interested in
 * @return int type, enum depending on what side the point is compared to the line
 */
int CyA::point_set::find_side(const line& l, const point& p) const {
  double value = point_2_line(l, p);

  if (value > 0) {
    return side::kLeft;  
  } else if (value < 0) {
    return side::kRight; 
  } else {
    return side::kCenter; 
  }
}


/**
 * @brief QuickHull algorithm recursive
 * @param line. Pair of points, forming a line
 * @param int side
 */
void CyA::point_set::quickHull(const CyA::line &l, int side) {
  CyA::point farthest;

  if (farthest_point(l, side, farthest)) {
    quickHull(CyA::line(l.first, farthest), -find_side(CyA::line(l.first, farthest), l.second));
    quickHull(CyA::line(farthest, l.second), -find_side(CyA::line(farthest, l.second), l.first));
  } else {
    hull_.push_back(l.first);
    hull_.push_back(l.second);
  }
}


/**
 * @brief Calculates the distance between a line and a point
 * @param line
 * @param point
 * @return Distance (Absolute value)
 */
double CyA::point_set::distance(const CyA::line &l, const CyA::point &p) const {
  return fabs(point_2_line(l, p));
}


/**
 * @brief Method to calculate the farthest point
 * @param line
 * @param int side
 * @param point the farthest current point
 * @return bool-type. True if there is anhy further point than the current one, false otherwise
 */
bool CyA::point_set::farthest_point(const CyA::line &l, int side, CyA::point &farthest) const {
  farthest = CyA::point_vector::at(0);
  double max_dist = 0;
  bool found = false;

  for (const CyA::point &p : *this) {
    const double dist = distance(l, p);
    if (find_side(l, p) == side && dist > max_dist) {
      farthest = p;
      max_dist = dist;
      found = true;
    }
  }
  return found;
}


/**
 * @brief
 * @param point minimum point in x axis
 * @param point maximum point in x axis
 */
void CyA::point_set::x_bounds(point& min_x, point& max_x) const {
  // Checking if the point set is empty
  if (empty()) {
    throw std::invalid_argument("Point set is empty");
  }

  // Inicializating the values with the first point in the set
  min_x = at(0);
  max_x = at(0);

  // For each point in itself
  for (const point& p : *this) {
    if (p.first < min_x.first) { // If the point is minor than the actual minimum, upload the minimum
      min_x = p;
    }
    if (p.first > max_x.first) { // If the point is greater than the actual maximum, upload the maximum
      max_x = p;
    }
  }
}


/**
 * @brief QuickHull algorithm that uses the recursive version in left and right sides
 */
void CyA::point_set::quickHull(void) {
  hull_.clear();

  CyA::point min_x_point; 
  CyA::point max_x_point;

  x_bounds(min_x_point, max_x_point);

  quickHull(CyA::line(min_x_point, max_x_point), side::kLeft);
  quickHull(CyA::line(min_x_point, max_x_point), side::kRight);

  // Remove duplicates
  std::sort(hull_.begin(), hull_.end());
  hull_.erase(std::unique(hull_.begin(), hull_.end()), hull_.end());
}


/**
 * @brief Method to print all the points in the set point
 * @param os Output stream to write the Graphviz format
 */
void CyA::point_set::write(std::ostream& os) const {
  for (const point& p : *this) {
    os << "(" << p.first << ", " << p.second << ")\n";
  }
}


/**
 * @brief Method to write all the points in the hull
 * @param os Output stream to write the Graphviz format
 */
void CyA::point_set::write_hull(std::ostream& os) const {
  for (const point& p : hull_) {
    os << "(" << p.first << ", " << p.second << ")\n";
  }
}


/**
 * @brief Method to write the convex hull in .DOT format for Graphviz
 * @param os Output stream to write the Graphviz format
 **/
void CyA::point_set::write_graphviz(std::ostream &os) const {
  // Verifying if the hull is empty
  if (hull_.empty()) {
    os << "// Convex Hull is empty. Run quickHull() first.\n";
    return;
  }

  std::map<CyA::point, int> point_map; // Map for storing index-point relation
  int i = 0; // Index

  os << "graph ConvexHull {\n\n";

  for (const CyA::point& point : hull_) { // For each point
    point_map[point] = i; // Assign the index to the point and print the point
    os << "  " << i << " [label=\"(" << point.first << ", " << point.second << ")\", pos=\"" << point.first << "," << point.second << "!\"];\n";
    ++i;
  }

  os << "\n\n";

  for (long unsigned int j = 0; j < hull_.size(); ++j) { // For eaxh point
    int current = point_map[hull_[j]];
    int next = point_map[hull_[(j + 1) % hull_.size()]]; // Considering the cicle
    os << "  " << current << " -- " << next << ";\n"; // Print the relation
  }

  os << "}\n";
}