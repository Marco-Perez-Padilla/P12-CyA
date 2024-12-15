/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Computabilidad y Algoritmia
** Curso: 2º
** Practica 12: Algoritmos Divide y Vencerás
** Autor: Marco Pérez Padilla
** Correo: alu0101469348@ull.edu.es
** Fecha: 18/10/2024

** Archivo check_functions.cc: Implementación de las funciones de chequeo de parámetros.
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      18/10/2024 - Creacion (primera version) del codigo
**      18/10/2024 - Creación de funciones de validación de formatos y de ValidateNumber
**      19/10/2024 - Adición de aclaración en Help. & como símbolo reservado a cadena vacía
**      30/10/2024 - Eliminacion de validaciones usadas para los .fa
**      15/12/2024 - Adicion de validaciones de input y output files
**/

#include <regex>
#include <iostream>
#include <fstream>
#include "check_functions.h"

/**
 * @brief Validates the extension of the input text file
 * @param string  
 * @return bool-type. True if the file is accepted. False otherwise
 */
bool ValidateInputFile (const std::string& name) {
  if (name.find('.') == std::string::npos) {
    return false;  
  }
  std::regex pattern (R"((.*)\.(txt)$)");
  return std::regex_match(name, pattern);
}

/**
 * @brief Validates the extension of the input text file
 * @param string  
 * @return bool-type. True if the file is accepted. False otherwise
 */
bool ValidateOutputFile (const std::string& name) {
  if (name.find('.') == std::string::npos) {
    return false;  
  }
  std::regex pattern (R"((.*)\.(DOT)$)");
  return std::regex_match(name, pattern);
}

/**
 * @brief Checks if a given string is made out of (only) numbers or not
 * @param string
 * @return bool
 */
bool ValidateNumber (const std::string& line) {
  if (!line.empty()) {
    for (char chr : line) {
      if (!std::isdigit(chr)) {
        return false;
      }
    }
    return true;
  } else {
    return false;
  }
}


/**
 * @brief Uses ValidateFile function. Acts in consequence of the returned type
 * @param string  
 */
void CheckFileError (const std::string& input_name, const std::string& output_name) {
  if (!ValidateInputFile(input_name)) {
    std::cerr << "Error in file" << input_name << ": Wrong extension. Please, try \"./Grammar2CNF --help\" for further information" << std::endl;
    exit(EXIT_FAILURE);
  } else if (!ValidateOutputFile(output_name)) {
    std::cerr << "Error in file" << output_name << ": Wrong extension. Please, try \"./Grammar2CNF --help\" for further information" << std::endl;
    exit(EXIT_FAILURE);
  }
}


/**
 * @brief Validates the line of commands and uses Help, Usage and CheckFileError functions
 * @param int argc  
 * @param char* argv[]
 */
void ValidateCommand(int argc, char* argv[], options generate) {
  if (argc < 2 || argc > 4) {
    Usage();
    exit (EXIT_FAILURE);
  } else if (argc == 2 && std::string(argv[1]) == "-h") {
    Help();
    exit (EXIT_SUCCESS);
  } 

  // Checking if -d is used
  if (argc > 2) {
    for (int i = 2; i < argc; ++i) {
      if (std::string(argv[i]) == "-d") {
        generate.generate_dot = true;
        // If a name for the output file is given
        if (i + 1 < argc) {
          generate.dot_file_name = argv[i + 1];  
        }
        break;
      }
    }
  }
  CheckFileError (std::string(argv[1]), generate.dot_file_name);
}


/**
 * @brief Prints Help to the user
 */
void Help () {
    std::cout << "./Grammar2CNF -- Grammar conversor to Chomsky normal form\n"
              << "Usage:          ./Grammar2CNF input.gra output.gra\n"
              << "\n"
              << "input.fa:        Input file with extension gra. Codificates the information of the input grammar such as:\n"
              << "                       Line 1: N number of symbols of the alphabet.\n"
              << "                                      - For the following N lines, there will be specified a symbol of the alphabet each line.\n"
              << "                                      - '&' cannot be part of alphabet. Reserved symbol for empty string.\n"
              << "                       Line N+1: V number of non-terminal symbols.\n"
              << "                                      - For the following V lines, there will be specified an alpha-numeric chain without spaces.\n"
              << "                                      - The chain must be formed with the symbols of the alphabet.\n"
              << "                                      - The first line will be the Start Production.\n"
              << "                       Line N+M+2: P number of productions of the grammar.\n"
              << "                                      - For the following P lines, there will be specified each production of the grammar with format: A alpha.\n"
              << "                                      - A is a production.\n"
              << "                                      - alpha is a sequence (chain) of terminal and non-terminal symbols.\n"
              << "output.gra:       Input file with extension gra. It has same format as input.fa.\n"
              << "\n";
}


/**
 * @brief Prints how to use the program
 */
void Usage() {
  std::cout << "How to use: ./Grammar2CNF input.gra output.gra\n"
            << "Try './Grammar2CNF --help' for further information\n";
}