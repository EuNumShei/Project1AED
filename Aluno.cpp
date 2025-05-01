//
// Created by Utiizador on 12/10/2023.
//

#include <sstream>
#include "Aluno.h"
/** Retorna o nome do aluno
 *
 * @return string com o nome do aluno
 *Time complexity: O(1)
*/
string Aluno::get_aluno_nome() const{
    return aluno_nome;
}
/** Retorna o código do aluno
 *
 * @return int com o código do aluno
 *
 * Time complexity: O(1)
 */
int Aluno::get_aluno_ID() const{
    return aluno_ID;
}
/** Retorna o horário do aluno
 *
 * @return Horario com o horário do aluno
 *
 * Time complexity: O(1)
 */
Horario & Aluno::get_horario(){
    return horario;
}
/** Retorna os anos das cadeiras em que o aluno está inscrito
 *
 * @return vetor de inteiros com os anos em que o aluno está inscrito
 *
 *Time complexity: O(1)
 */
vector<int> Aluno::get_anos_do_aluno() const{
    return anos_do_aluno;
}
/** Retorna as cadeiras em que o aluno está inscrito
 *
 * @return vetor com stings com os códigos das cadeiras do aluno
 *
 * Time complexity: O(1)
 */
vector<string> Aluno::get_cadeiras_do_aluno() const{
    return cadeiras_do_aluno;
}

/** Adiciona uma cadeira à lista de cadeiras do aluno
*
* @param string com o código da cadeira que queremos adicionar ao aluno
*
* Time complexity: O(logN)
*/
void Aluno::adicionar_cadeira_ao_aluno(const string& nome_cadeira){
    if(std::find(cadeiras_do_aluno.begin(), cadeiras_do_aluno.end(),nome_cadeira) == cadeiras_do_aluno.end()){
        cadeiras_do_aluno.push_back(nome_cadeira);
    }
}
/** Remove uma cadeira ao aluno
 *
 * @param string com o código da cadeira que queremos remover ao aluno
 *
 * Time complexity: O(N*logN)
 */
void Aluno::remover_cadeira_ao_aluno(const std::string &nome_cadeira){
    if(std::find(cadeiras_do_aluno.begin(), cadeiras_do_aluno.end(),nome_cadeira) != cadeiras_do_aluno.end()){
        cadeiras_do_aluno.erase(std::find(cadeiras_do_aluno.begin(), cadeiras_do_aluno.end(),nome_cadeira));
    }
}

/** Faz print de um aluno
*   @details no formato: nome do aluno | codigo do aluno
*
* Time complexity: O(1)
*/
void Aluno::print_aluno(){
    cout << aluno_nome << " | " << aluno_ID << endl;
}


/** Verifica se o aluno está inscrito em uma cadeira
*
* @param string com o código da cadeira que queremos verificar
* @return true se o aluno estiver inscrito na cadeira, caso contrário false
*
* Time complexity: O(N)
*/
bool Aluno::ver_se_existe_cadeira_no_aluno(string nome_cadeira){
    for (Aula aula: get_horario().get_horario()) {
        if( nome_cadeira == aula.get_codigo_cadeira()){
            return true;
        }
    }
    return false;
}

/** Verifica se o aluno frequenta cadeiras de um determinado ano
* @param int com o ano que queremos verificar
* @return true se o aluno estiver inscrito na cadeira do ano, caso contrário false
*
* Time complexity: O(N)
*/
bool Aluno::aluno_no_ano(int ano){
    for(int anos : anos_do_aluno){
        if(anos == ano) return true;
    }
    return false;
}

/** Coloca no vetor anos_do_aluno os anos das cadeiras em que o aluno está inscrito
*
* Time complexity: O(N²)
*/
void Aluno::colocar_anos_no_aluno(){
    for(string cadeira : cadeiras_do_aluno){
        istringstream iss(cadeira);
        char lixo;
        while(iss >> lixo and lixo != '0'){
            continue;
        }
        char numero;
        iss >> numero;
        int ano = (numero - '0') + 1;
        bool repetido = false;
        for (int n : anos_do_aluno) {
            if (ano == n) {
                repetido = true;
                break;
            }
        }
        if (!repetido) {
            anos_do_aluno.push_back(ano);
        }
    }
}
