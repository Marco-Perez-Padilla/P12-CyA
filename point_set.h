#ifndef POINT_SET_H
#define POINT_SET_H

#include <vector>
#include <utility>
#include <iostream>

namespace CyA {
  
typedef std::pair<double,double> point;
typedef std::pair<point, point> line;
typedef std::vector<point> point_vector;

// Enum to determinate the side
enum side {
  kLeft = -1,
  kCenter,
  kRight
};
 
class point_set : public point_vector {
 private:
  point_vector hull_;

  void quickHull(const line &l, int side);
 
  double distance(const line &l, const point &p) const;
  int find_side(const line &l, const point &p) const;
  void x_bounds(point &min_x, point &max_x) const;
  double point_2_line(const line &l, const point &p) const;
  bool farthest_point(const line &l, int side, point &farthest) const;
 public:
  point_set(const vector<point> &points) : point_vector(points) {}
  ~point_set(void) = default;
 
  void quickHull(void);
 
  void write_hull(std::ostream &os) const;
  void write(std::ostream &os) const;
  void write_graphviz(std::ostream &os) const;

  inline const point_vector& get_hull(void) const { return hull_; }
  inline const point_vector& get_points(void) const { return *this; }  
};
}

#endif