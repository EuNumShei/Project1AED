//
// Created by Utiizador on 12/10/2023.
//

#include <iostream>
#include <algorithm>
#include "Aula.h"
/** Retorna o dia da semana de uma aula
 *
 * @return string com o dia da semana
 *
 * Time complexity: O(1)
 */
string Aula::get_dia() const{
    return dia;
}
/** Retorna o código da cadeira de uma aula
 *
 * @return string com o código da cadeira
 *
 * Time complexity: O(1)
 */
string Aula::get_codigo_cadeira() const{
    return codigo_cadeira;
}
/** Retorna o tipo de aula: Teórica(T), Teórico-Prática(TP) ou Prática Laboratorial(PL)
 *
 * @return string com o tipo de aula
 *
 * Time complexity: O(1)
 */
string Aula::get_tipo_de_aula() const{
    return tipo_de_aula;
}
/** Retorna a hora de início da aula
 *
 * @return float com a hora de início
 *
 * Time complexity: O(1)
 */
float Aula::get_hora_inicio() const{
    return hora_inicio;
}
/** Retorna a duração de uma aula
 *
 * @return float com a duração
 *
 * Time complexity: O(1)
 */
float Aula::get_duracao() const{
    return duracao;
}
/** Retorna o código da turma da aula
 *
 * @return string com o código da turma
 *
 * Time complexity: O(1)
 */
string Aula::get_codigo_turma() const{
    return codigo_turma;
}

/** Faz print de uma aula
 *  @details no formato: cadeira | dia | hora de início | duração | tipo de aula
 *
 * Time complexity: O(1)
 */
void Aula::print_aula(){
    cout << codigo_cadeira << " | " << dia << " | " << hora_inicio << " | " << duracao << " | " << tipo_de_aula << endl;
}

/** Faz print dos alunos inscritos numa determinada aula
 * @details no format: nome de aluno | código do aluno
*
* Time complexity: O(N)
*/
void Aula::ver_alunos_na_turma(){
    for(pair<int, string> aluno : alunos_na_aula){
        cout << aluno.second << " | " << aluno.first << '\n';
    }
}

/** Verifica se um aluno pertence a uma turma
* @param int com o código do aluno que quermos verificar
* @return true se esta na turma e false se o aluno nao pertence a esta turma
*
* Time complexity: O(logN)
*/
bool Aula::esta_na_aula( int aluno_ID_){
    auto index = find_if(alunos_na_aula.begin(), alunos_na_aula.end(),
                         [aluno_ID_](const pair<int, string>& aluno) {
                             return aluno.first == aluno_ID_;
                         });
    return index != alunos_na_aula.end() ;
}


/** Adiciona um aluno ao vetor de alunos da aula. Os alunos ficam guardados por pares < codigo de aluno, nome de aluno >
* @param int com o codigo do aluno
* @param string com o nome do aluno
*
* Time complexity: O(1)
*/
void Aula::adicionar_aluno(const int aluno_id, const string& aluno_nome){
    alunos_na_aula.push_back(make_pair(aluno_id, aluno_nome));
}

/** Verifica se duas aulas são compatíveis no mesmo horário
* @param Aula com a aula a qual vamos verificar se é compatível
* @return true se as aulas forem compatíveis, caso contrário false
*
* Time complexity: O(1)
*/
bool Aula::aula_compativel(const Aula& outra_aula){
    if(dia != outra_aula.dia) return true;
    if((hora_inicio >= (outra_aula.hora_inicio + outra_aula.duracao) && hora_inicio > outra_aula.hora_inicio) || (outra_aula.hora_inicio >= (hora_inicio + duracao) && outra_aula.hora_inicio > hora_inicio)) {
        return true;
    }if(outra_aula.get_tipo_de_aula() == "T" || tipo_de_aula == "T") return true;
    return false;
}

