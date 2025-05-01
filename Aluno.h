//
// Created by Utiizador on 12/10/2023.
//

#ifndef AED2324_P03_ALUNO_H
#define AED2324_P03_ALUNO_H

#include <string>
#include <algorithm>
#include <iostream>
#include "Horario.h"
using namespace std;

class Aluno {
    private:
        int aluno_ID;
        string aluno_nome;
        Horario horario;
        vector<int> anos_do_aluno;
        vector<string> cadeiras_do_aluno;
    public:
        Aluno(int aluno_ID_, string aluno_nome_, Horario horario_, int ano_);
        string get_aluno_nome() const;
        int get_aluno_ID() const;
        Horario & get_horario();
        vector<int> get_anos_do_aluno() const;
        vector<string> get_cadeiras_do_aluno() const;
        void adicionar_cadeira_ao_aluno(const string& nome_cadeira);
        void remover_cadeira_ao_aluno(const std::string &nome_cadeira);
        void print_aluno();
        bool ver_se_existe_cadeira_no_aluno(string nome_cadeira);
        bool aluno_no_ano(int ano);
        void colocar_anos_no_aluno();

        Aluno(int aluno_ID_,const string& aluno_nome_): aluno_ID(aluno_ID_), aluno_nome(aluno_nome_) {}
        bool operator==(const Aluno& outro_aluno) const {
            return this->aluno_ID == outro_aluno.aluno_ID;
        }
        bool operator<(const Aluno& outro_aluno) const {
            return this->aluno_ID < outro_aluno.aluno_ID;
        }
};


#endif //AED2324_P03_ALUNO_H
