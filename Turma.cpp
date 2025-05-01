//
// Created by Utiizador on 12/10/2023.
//

#include "Turma.h"
/** Retorna o código da turma
 *
 * @return string com o código da turma
 *
 * Time complexity: O(1)
 */
string Turma::get_codigo_turma() const{
    return codigo_turma;
}

/** Retorna o horário da turma
 *
 * @return Horario que contém o horário da turma
 *
 * Time complexity: O(1)
 */
Horario & Turma::get_horario_turma(){
    return horario_da_turma;
}

/** Adiciona uma cadeira ao vetor de cadeiras da turma
* @param string codigo_uc com o código da cadeira que se vai adicionar
*
* Time complexity: O(1)
*/
void Turma::adicionar_cadeira(const string& codigo_uc){
    lista_cadeiras.push_back(codigo_uc);

}
