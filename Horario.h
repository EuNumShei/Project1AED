//
// Created by Utiizador on 12/10/2023.
//

#ifndef AED2324_P03_HORARIO_H
#define AED2324_P03_HORARIO_H

//#include <vector>
#include <algorithm>
#include "Aula.h"
using namespace std;

class Horario {
private:
    vector<Aula> horario;

public:
    vector<Aula> & get_horario();
    void adicionar_aula(Aula aula);
    void remover_aula(Aula aula);
    void print_horario();
};


#endif //AED2324_P03_HORARIO_H
