//
// Created by Utiizador on 26/10/2023.
//

#ifndef AED2324_P03_PEDIDO_H
#define AED2324_P03_PEDIDO_H

#include <string>

using namespace std;

class Pedido {
private:
    static int n_ultimo_pedido;
    int numero_pedido;
    string cadeira_1;
    string turma_1;
    string turma_2;
    string pedido_q_foi_feito;
public:
    Pedido(const string & cadeira_1_,const string & turma_1_, const string & turma_2_,const string & pedido_q_foi_feito_):cadeira_1(cadeira_1_)  ,turma_1(turma_1_) ,turma_2(turma_2_) ,pedido_q_foi_feito(pedido_q_foi_feito_){
        numero_pedido = n_ultimo_pedido + 1;
        n_ultimo_pedido = numero_pedido;
    }
    static int get_n_ultimo_pedido(){
        return n_ultimo_pedido;
    }
    int get_numero_pedido() const;
    string get_cadeira_1() const;
    string get_turma_1() const;
    string get_turma_2() const;
    string get_pedido_q_foi_feito() const;
    void print_pedido() const;
    bool operator<(const Pedido& outro_pedido) const {
        return this->numero_pedido < outro_pedido.numero_pedido;
    }
};






#endif //AED2324_P03_PEDIDO_H
