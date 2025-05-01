//
// Created by Utiizador on 12/10/2023.
//

#ifndef AED2324_P03_TURMA_H
#define AED2324_P03_TURMA_H

#include <vector>
#include "Horario.h"
using namespace std;

class Turma {
private:
    string codigo_turma;
    Horario horario_da_turma;
    vector<string> lista_cadeiras;
public:
    string get_codigo_turma() const;
    Horario & get_horario_turma();
    void adicionar_cadeira(const string& codigo_uc);

    Turma(string codigo_turma_): codigo_turma(codigo_turma_) {}

    bool operator==(const Turma& outra_turma) const {
        return this->codigo_turma == outra_turma.codigo_turma;
    }
};


#endif //AED2324_P03_TURMA_H
