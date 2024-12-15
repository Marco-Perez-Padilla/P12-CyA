/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Computabilidad y Algoritmia
** Curso: 2º
** Practica 8: Gramáticas en Forma Normal de Chomsky
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 18/10/2024

** Archivo check_functions.h: Declaracion de las funciones de chequeo de parámetros.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      18/10/2024 - Creacion (primera version) del codigo
**      18/10/2024 - Creación de funciones de validación de formatos y de ValidateNumber
**/

#include <iostream>
#include <string>

struct options {
  bool generate_dot = false;
  std::string dot_file_name = "output.DOT"; 
};

bool ValidateInputFile (const std::string& name);
bool ValidateOutputFile (const std::string& name);
bool ValidateNumber (const std::string& line);
void CheckFileError (const std::string& name, const std::string& output_name);
void ValidateCommand(int argc, char* argv[], options generate);
void Help ();
void Usage();