//
// Created by Utiizador on 12/10/2023.
//

#ifndef AED2324_P03_AULA_H
#define AED2324_P03_AULA_H

#include <string>
#include <vector>

using namespace std;

class Aula {
private:
    vector<pair<int,string>> alunos_na_aula;
    string dia; //da semana
    string codigo_cadeira;
    string tipo_de_aula; // (T/TP/PL)
    float hora_inicio;
    float duracao;
    string codigo_turma;
public:
    vector<pair<int,string>>& get_alunos_na_aula(){ return  alunos_na_aula;};
    Aula(const string& codigo_turma_,const string& codigo_cadeira_,const string& dia_  ,const float& hora_inicio_ ,const float& duracao_,const string& tipo_de_aula_): codigo_turma (codigo_turma_ ), codigo_cadeira (codigo_cadeira_), dia(dia_) ,hora_inicio (hora_inicio_), duracao(duracao_), tipo_de_aula(tipo_de_aula_) {}
    string get_dia() const;
    string get_codigo_cadeira() const;
    string get_tipo_de_aula() const;
    float get_hora_inicio() const;
    float get_duracao() const;
    string get_codigo_turma() const;
    void print_aula();
    void ver_alunos_na_turma();
    bool aula_compativel(const Aula& outra_aula);
    bool esta_na_aula( int aluno_ID_);
    /*
    Aluno get_aluno(int aluno_ID_);

    vector<Aluno> get_alunos_na_turma();
    */
    void adicionar_aluno(const int aluno_id, const string& aluno_nome);
    bool operator==(const Aula& outra_aula) const {
        return this->codigo_cadeira == outra_aula.codigo_cadeira;
    }
    bool operator<(const Aula& outra_aula) const {
        return this->codigo_cadeira < outra_aula.codigo_cadeira;
    }
};


#endif //AED2324_P03_AULA_H
