
#include <algorithm>
#include <cmath>

#include "point_set.h"

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


double CyA::point_set::point_2_line(const CyA::line &l, const CyA::point &p) const {
  const CyA::point &p1 = l.first;
  const CyA::point &p2 = l.second;

  return (p.second - p1.second) * (p2.first - p1.first) - (p2.second - p1.second) * (p.first - p1.first);
}


double CyA::point_set::distance(const CyA::line &l, const CyA::point &p) const {
  return fabs(point_2_line(l, p));
}