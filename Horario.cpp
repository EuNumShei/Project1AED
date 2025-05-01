//
// Created by Utiizador on 12/10/2023.
//

#include "Horario.h"
#include <iostream>
/** Retorna um vetor de aulas que consistui um horário
 *
 * @return vetor de aulas
 *
 * Time complexity: O(1)
 */
vector<Aula>& Horario::get_horario(){
    return horario;
}


/** Faz print do horário: imprime cada aula no horário
*
*Time complexity: O(N)
*/
void Horario::print_horario(){
    cout << "      ////////////////Horario////////////////" << endl;
    for(Aula aula:horario){
        cout << "       ";
        aula.print_aula();
    }
    cout << "      //////////////////////////////////////" << endl;
}

/** Adiciona uma aula ao horário
* @param Aula com a aula que se vai adicionar ao horário
*
* Time complexity: O(N)
*/
void Horario::adicionar_aula(Aula aula){
    auto posicaodeinsercao = lower_bound(horario.begin(),horario.end(),aula);
    horario.insert(posicaodeinsercao,aula);
}

/** Remove uma aula do horário
 *
 * @param Aula com a aula que se vai remover do horário
 *
 * Time complexity: O(N*logN)
 */
void Horario::remover_aula(Aula aula){
    if(std::find(horario.begin(), horario.end(),aula) != horario.end()){
        horario.erase(std::find(horario.begin(), horario.end(),aula));
    }
}
