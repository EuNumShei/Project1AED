//
// Created by Utiizador on 26/10/2023.
//

#include <iostream>
#include "Pedido.h"

int Pedido::n_ultimo_pedido = 0;
/** Retorna a cadeira que vai ser alterada no horário do aluno
 *
 * @return string com o código da cadeira
 *
 * Time complexity: O(1)
 */
string Pedido::get_cadeira_1() const{
    return cadeira_1;
}
/** Retorna a turma atual que o aluno está inscrito
 *
 * @return string com o código da turma
 *
 * Time complexity: O(1)
 */
string Pedido::get_turma_1() const {
    return turma_1;
}
/** Retorna a turma para qual o aluno se quer inscrever
 *
 * @return string com o código da turma
 *
 * Time complexity: O(1)
 */
string Pedido::get_turma_2() const {
    return turma_2;
}
/** Retorna o tipo de pedido realizado
 *
 * @return string com o tipo de pedido
 *
 * Time complexity: O(1)
 */
string Pedido::get_pedido_q_foi_feito() const {
    return pedido_q_foi_feito;
}
/** Faz print de um pedido
 *  @details no formato: número do pedido - tipo de pedido - cadeira alterada - turma anterior  turma que o aluno pretende ingressar
 *
 * Time complexity: O(1)
 */
void Pedido::print_pedido() const{
    cout << "Pedido numero " <<numero_pedido<< " - " << pedido_q_foi_feito << " de " << cadeira_1
         << " com base em " << turma_1 << " " << turma_2 << endl;
}
