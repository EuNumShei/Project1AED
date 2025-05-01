//
// Created by Utiizador on 12/10/2023.
//

#ifndef AED2324_P03_SECRETARIA_H
#define AED2324_P03_SECRETARIA_H
#include <string>
#include <vector>
#include <set>
#include "Aluno.h"
#include "Turma.h"
#include "Pedido.h"

using namespace std;

class Secretaria {
private:
    vector<Aluno> lista_de_alunos;
    vector<Turma> lista_de_turmas;
    vector<string> historico_de_mudancas;
    vector<Pedido> fila_pedidos;
    int index_fila_pedidos = 0;
    set<Pedido> stack_pedidos;
public:
    //set<pair<string,int>> set;
    void criar_turmas();
    void criar_horarios_turmas();
    void criar_alunos_horarios();
    bool ver_se_existe_aluno(int ID);
    bool ver_se_existe_turma(string turma);
    bool ver_se_existe_cadeira(string codigo_uc);
    void menu_inicial();
    void guardar_dados();
    void consultar_horario();
    void ver_horario_do_aluno(const int& ID);
    void ver_horario_da_turma(const string& codigo_turma);
    void consultar_alunos();
    void ver_alunos_da_turma(const string& codigo_turma);
    void ver_alunos_da_uc(const string& codigo_uc);
    void ver_alunos_do_curso();
    void ver_alunos_do_ano(const int&ano);
    void alunos_nas_cadeiras( int n);
    void consultar_ocupacao();
    void ver_ocupacao_da_turma(const string& codigo_turma);
    void ver_ocupacao_do_ano(const int& ano);
    void ver_ocupacao_da_cadeira();
    void consultar_ucs();
    void alterar_horario(Aluno * aluno);
    Aluno* obter_aluno(const int& ID);
    void escolha_do_pedido(const string & nome_pedido,Aluno * aluno);
    void realizar_pedidos(Aluno * aluno);
    void desfazer_pedido(Aluno * aluno);
    bool fazer_pedido_inverso(const Pedido& ultimo_pedido, Aluno * aluno);
    void remover_aula(Aluno * aluno,const string & codigo_cadeira,const string & codigo_turma,bool e_fake);
    void adicionar_aula(Aluno* aluno, const string & codigo_cadeira,const string & codigo_turma);
    void trocar_aula(Aluno* aluno,const string & codigo_cadeira,const string & codigo_turma_presente,const string & codigo_turma_futura);
    bool ocupacao_desiquilibrada(const string& codigo_cadeira,const string & codigo_turma);
    bool ver_se_operacao_vai_dar(const Pedido& pedido, Aluno* aluno);
    void fazer_primeiro_pedido(Aluno * aluno);
    vector<Aula*> obter_aulas(const int& aluno_ID ,const string& codigo_turma,const string& codigo_cadeira);

    template< class T>
    typename std::vector<T>::const_iterator find(const vector<T>& vetor, const T& value) const;
    template< class T>
    void escolher_ordem(vector<pair<string,T>>& lista) const;
    template< class T>
    void print_lista(vector<pair<string,T>>& vetor, const string & ordem) const;

};


#endif //AED2324_P03_SECRETARIA_H
