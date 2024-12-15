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

** Archivo point_set.h: Declaración de la clase point_set.

** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      13/10/2024 - Creacion (primera version) del codigo
**      15/10/2024 - Creación de métodos restantes y de escritura
**/

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