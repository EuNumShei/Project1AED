#include "Secretaria.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

/** Define uma mensagem inicial para o menu com os comandos disponíveis
* @param vetor de strings com os comandos disponíveis
* Time complexity: O(n)
*/
void print_inicio(const vector<string>& vetor) {
    cout << endl <<"Aqui se encontram todos os comandos disponiveis:" << endl;
    for (const string &metodo: vetor) {
        cout << "     * " << metodo << endl;
    }
}


/** Define o resultado de um comando mal introduzido
* Time complexity: O(1)
*/
void print_incorreto(){
    cout << "Escrito incorretamente. Tente novamente." << endl ;
}



template< class T>
typename std::vector<T>::const_iterator Secretaria::find(const vector<T>& vetor, const T& value) const{
    auto it = vetor.begin();
    for (; it != vetor.end(); ++it) {
        if (*it == value) {
            return it;
        }
    }
    return vetor.end();
}


/** Define a ordem que se pretende ver uma lista
* @tparam T
* @param vetor de pares de elementos que se pretende analisar
* Time complexity: O(n*logN)
*/
template< class T>
void Secretaria::escolher_ordem(vector<pair<string,T>>& lista) const{
    vector<string> vetor = {"normal                 Para ver elementos da lista com a ordem predefinida",
                            "inversa                Para ver elementos da lista com a ordem inversa da predefinida",
                            "crescente              Para ver elementos com menor numero primeiro",
                            "decrescente            Para ver elementos com maior numero primeiro"};
    cout<<"-------Ordem de visualizacao-------" << endl;
    print_inicio(vetor);
    string ordem;
    cin >> ordem;

    while((ordem != "normal") and (ordem != "inversa" ) and (ordem != "crescente") and (ordem != "decrescente") ){
        print_incorreto();
        cin >> ordem;
    }
    print_lista(lista,ordem);
}


/** Faz print de elementos de um vetor de acordo com uma dada ordem
* @tparam T
* @param vetor com os elementos que se pretende analisar
* @param string com a ordem pela qual os elementos serão imprimidos
* Time complexity: θ(n^2)
*/
template< class T>
void Secretaria::print_lista(vector<pair<string,T>>& vetor, const string & ordem) const{
    if(ordem == "crescente") {
        std::sort(vetor.begin(), vetor.end(), [](const std::pair<std::string, T>& lhs, const std::pair<std::string, T>& rhs) {
            return lhs.second < rhs.second;
        });
    }
    else if(ordem == "decrescente") {
        std::sort(vetor.begin(), vetor.end(), [](const std::pair<std::string, T>& lhs, const std::pair<std::string, T>& rhs) {
            return rhs.second < lhs.second;
        });
    }else if(ordem == "inversa") {
        auto it = vetor.rbegin();
        for (; it != vetor.rend(); ++it) {
            cout << "       ////" << it->first << "////" << '\n';
            cout << "              " << it->second << endl;
        }
    }
    else if(ordem == "decrescente_ucs") {
        std::sort(vetor.begin(), vetor.end(), [](const std::pair<std::string, T>& lhs, const std::pair<std::string, T>& rhs) {
            return rhs.second < lhs.second;
        });
        cout << "   As Unidades Curriculares com mais alunos sao as seguintes:" << endl;
        for (int i = 0; i < vetor.size(); ++i) {
            cout << "           "<< i+1 << "-   " << vetor[i].first << " com " << vetor[i].second << '\n';
        }
    }

    if(ordem == "normal" or ordem == "crescente" or ordem == "decrescente"){
        auto it = vetor.begin();
        for (; it != vetor.end(); ++it) {
            cout << "       ////" << it->first << "////" << '\n';
            cout << "              " << it->second << endl;
        }
    }
    cout << "saindo..." << endl;
}

/** Lê o ficheiro com as turmas, cria e adiciona as turmas ao vetor lista_de_turmas
*  que guarda todas as turmas
* Time complexity: O(n²)
*/
void Secretaria::criar_turmas() {
    ifstream in("../classes_per_uc.csv");
    if (!in) {
        cerr << "Erro ao abrir o arquivo." << endl;
    } else {
        string linha;
        getline(in, linha);
        while (std::getline(in, linha)) {
            std::istringstream iss(linha);
            std::string palavra;
            string codigo_uc;
            string codigo_turma;
            int count = 0;

            while (std::getline(iss, palavra, ',')) {
                switch (count) {
                    case 0:
                        codigo_uc = palavra;
                        break;
                    case 1:
                        codigo_turma = palavra;
                        break;
                }
                count++;
            }
            Turma nova_turma = Turma(codigo_turma);
            nova_turma.adicionar_cadeira(codigo_uc);
            bool not_found = true;
            auto it = lista_de_turmas.begin();
            for (; it != lista_de_turmas.end(); ++it) {
                if (*it == nova_turma) {
                    *it = nova_turma;
                    not_found = false;
                    break;
                }
            }
            if(not_found){
                lista_de_turmas.push_back(nova_turma);
            }

        }
    }
}


/** Lê o ficheiro relativo às aulas, cria e adiciona todas as aulas aos horários das turmas relativas
* Time complexity: O(n³)
*/
void Secretaria::criar_horarios_turmas() {
    ifstream in("../classes.csv");
    if (!in) {
        cerr << "Erro ao abrir o arquivo." << endl;
    } else {
        string linha;
        getline(in, linha);
        while (getline(in, linha)) {
            string codigo_turma;
            string codigo_uc;
            string dia;
            string tipo_de_aula;
            float hora_inicio = 0;
            float duracao = 0;
            istringstream iss(linha);
            std::string palavra;
            int count = 0;

            while (std::getline(iss, palavra, ',')) {
                switch (count) {
                    case 0:
                        codigo_turma = palavra;
                        break;
                    case 1:
                        codigo_uc = palavra;
                        break;
                    case 2:
                        dia = palavra;
                        break;
                    case 3:
                        hora_inicio = stof(palavra);
                        break;
                    case 4:
                        duracao = stof(palavra);
                        break;
                    case 5:
                        tipo_de_aula = palavra;
                        break;
                }
                count++;
            }

            Aula aula = Aula(codigo_turma, codigo_uc, dia,  hora_inicio, duracao,tipo_de_aula);
            for(Turma& turma: lista_de_turmas){
                if(turma.get_codigo_turma() == aula.get_codigo_turma()){
                    turma.get_horario_turma().adicionar_aula(aula);
                }
            }
        }
    }
}

/** Lê o ficheiro relativo aos alunos e as respetivas turmas e cadeiras. Cria os alunos e adiciona-os ao vetor
*  lista_de_alunos que guarda todos os alunos. Depois, adiciona as aulas do aluno ao seu horário
*  e adiciona os alunos à aula
* Time complexity: O(n⁶)
*/
void Secretaria::criar_alunos_horarios(){
    ifstream in("../students_classes.csv");
    if (!in) {
        cerr << "Erro ao abrir o arquivo." << endl;
    } else {
        string linha;
        getline(in, linha);
        while (getline(in, linha)) {
            int codigo_aluno;
            string nome_aluno;
            string codigo_uc;
            string codigo_turma;
            istringstream iss(linha);
            std::string palavra;
            int count = 0;

            while (std::getline(iss, palavra, ',')) {
                switch (count) {
                    case 0:
                        codigo_aluno = stoi(palavra);
                        break;
                    case 1:
                        nome_aluno = palavra;
                        break;
                    case 2:
                        codigo_uc = palavra;
                        break;
                    case 3:
                        codigo_turma = palavra;
                        break;
                }
                count++;
            }

            Aluno novo_aluno = Aluno(codigo_aluno, nome_aluno);

            if (find(lista_de_alunos, novo_aluno) == lista_de_alunos.end()) {
                lista_de_alunos.push_back(novo_aluno);
            }

            for(Aluno& aluno : lista_de_alunos){
                if(aluno.get_aluno_ID() == codigo_aluno){
                    for(Turma & turma : lista_de_turmas){
                        if(turma.get_codigo_turma() == codigo_turma){
                            for(Aula & aula : turma.get_horario_turma().get_horario()){
                                if(aula.get_codigo_cadeira() == codigo_uc){
                                    aluno.get_horario().adicionar_aula(aula);
                                    aula.adicionar_aluno(aluno.get_aluno_ID(), aluno.get_aluno_nome());
                                    aluno.adicionar_cadeira_ao_aluno(aula.get_codigo_cadeira());
                                }
                            }
                        }
                    }
                    aluno.colocar_anos_no_aluno();
                }
            }
        }
        //cout << lista_de_alunos.empty() << "????" << lista_de_alunos.size() << "^^^^";
    }
}

/* Verifica se o ID fornecido corresponde a um aluno
 * Time complexity: O(logN)
 */
bool Secretaria::ver_se_existe_aluno(int ID){
    for(Aluno aluno : lista_de_alunos){
        if(aluno.get_aluno_ID() == ID) return true;
    }
    return false;
}

/* Verifica se o código de turma fornecido corresponde a uma turma
 * Time complexity: O(logN)
 */
bool Secretaria::ver_se_existe_turma(string codigo_turma){
    for(Turma turma : lista_de_turmas){
        if(turma.get_codigo_turma() == codigo_turma) return true;
    }
    return false;
}

/* Verifica se o código de cadeira fornecido corresponde a uma cadeira
 * Time complexity: O(logN)
 */
bool Secretaria::ver_se_existe_cadeira(string codigo_uc){
    vector<string> cadeiras = {"L.EIC001", "L.EIC002", "L.EIC003", "L.EIC004", "L.EIC005", "L.EIC011", "L.EIC012",
                               "L.EIC013", "L.EIC014", "L.EIC015", "L.EIC021", "L.EIC022", "L.EIC023",
                               "L.EIC024", "L.EIC025"};
    for(int i = 0; i < cadeiras.size(); i++){
        if(cadeiras[i] == codigo_uc) return true;
    }
    return false;
}

/** Função que gera o menu inicial. Indica as opções de operações possíveis
* Time complexity: Ver funções anteriores, pois a complexidade temporal varia extremamente dependendo das escolhas do user
*/
void Secretaria::menu_inicial(){
    vector<string> vetor = {"consultar_horario              Para ver horario de um dado aluno ou turma ",
                            "consultar_alunos               Para consultar alunos da turma, curso ou ano " ,
                            "consultar_ocupacao_n_ucs       Para consultar o numero de alunos registados em n unidades curriculares",
                            "consultar_ocupacao             Para consultar quantidade de alunos em cada unidade curricular" ,
                            "consultar_ucs                  Para consultar unidade curriculares com maior numero de alunos",
                            "alterar_horario                Para o aluno alterar o seu horario",
                            "consultar_alteracoes           Para consultar todas as alteracoes feitas ao sistema",
                            "sair                           Para terminar programa"};

    while (true){
        cout << "---------Menu inicial---------" << endl;
        print_inicio(vetor);
        string comando;
        cin >> comando;
        if(comando == "consultar_horario"){
            consultar_horario();
        }
        else if(comando == "consultar_alunos"){
            consultar_alunos();
        }
        else if(comando == "consultar_ocupacao_n_ucs"){
            cout<<"Escreva a quantidade de unidades curriculares que os alunos estao registados no minimo:";
            int n;
            cin >> n;
            alunos_nas_cadeiras(n);
        }
        else if(comando == "consultar_ocupacao"){
            consultar_ocupacao();
        }
        else if(comando == "consultar_ucs"){
            consultar_ucs();
        }
        else if(comando == "alterar_horario"){
            int ID;
            Aluno* aluno = nullptr;
            while(aluno == nullptr){
                cout<<"Escreva o ID do aluno (Ex.: 2020xxxxx) :";
                cin >> ID;
                if(ver_se_existe_aluno(ID)) {
                    aluno = obter_aluno(ID);
                }else{
                    cout << "ID nao encontrado. Tente novamente." << endl;
                }
            }
            alterar_horario(aluno);
        }
        else if(comando == "consultar_alteracoes"){
            cout << "/////////////////////////////////Historico das alteracoes/////////////////////////////////" << endl;
            for(const string& mudanca: historico_de_mudancas){
                cout <<mudanca << endl;
            }
            cout << "//////////////////////////////////////////////////////////////////////////////////////////" << endl;
        }
        else if(comando == "sair"){
            guardar_dados();
            break;
        }
        else{
            print_incorreto();
        }
    }
}

void Secretaria::guardar_dados(){
    ofstream ofs;
    ofs.open("../students_classes.csv", ios::trunc);
    ofs << "StudentID,StudentName,UCCode,ClassCode" << "\n";
    for(Aluno aluno : lista_de_alunos){
        for(Aula aula : aluno.get_horario().get_horario()){
            if(aula.get_tipo_de_aula() == "TP" || aula.get_tipo_de_aula() == "PL") {
                ofs << aluno.get_aluno_ID() << ',' << aluno.get_aluno_nome() << ',' << aula.get_codigo_cadeira() << ','
                    << aula.get_codigo_turma() << "\n";
            }
        }
    }
    ofs.close();
}

/** Redirecionar para o menu de consulta de horarios: de um dado aluno ou turma
*  As funções de consulta de horário indicam o horário de um aluno ou turma
* Time complexity: O(n²logN)(embora tenha um loop infinito, a opção sair será escolhida bastante cedo em maior parte dos casos, sendo a complexidade temporal do while de O(1))
*/
void Secretaria::consultar_horario(){
    vector<string> vetor = {"horario_do_aluno               Para consultar o horario de um dado aluno",
                            "horario_da_turma               Para consultar o horario de uma dada turma",
                            "sair"};
    while (true){
        cout << "-------Consulta de horarios-------" << endl;
        print_inicio(vetor);
        string comando;
        cin >> comando;
        if(comando == "horario_do_aluno"){
            cout<<"Escreva o ID do aluno (Ex.: 2020xxxxx) :";
            int ID;
            cin >> ID;
            if(ver_se_existe_aluno(ID)) {
                ver_horario_do_aluno(ID);
            }else{
                cout << "ID nao encontrado. Tente novamente" << endl;
            }
        }
        else if(comando == "horario_da_turma"){
            cout<<"Escreva o codigo da turma (Ex.: xLEICxx) :";
            string codigo_turma;
            cin >> codigo_turma;
            if(ver_se_existe_turma(codigo_turma)) {
                ver_horario_da_turma(codigo_turma);
            }else{
                cout << "Codigo da turma nao encontrado. Tente novamente" << endl;
            }
        }
        else if(comando == "sair"){
            break;
        }
        else{
            print_incorreto();
        }

    }
}


/** Consultar horario de um dado aluno
* @param int com o código de aluno do estudante que se pretende ver o horário
* Time complexity: O(n²)
*/
void Secretaria::ver_horario_do_aluno(const int& ID){
    for(Aluno aluno: lista_de_alunos){
        if(aluno.get_aluno_ID() == ID){
            aluno.get_horario().print_horario();
        }
    }

}


/** Consultar horario de uma dada turma
* @param string com o código da turma que se pretende ver o horário
* Time complexity: O(n²)
*/
void Secretaria::ver_horario_da_turma(const string& codigo_turma){
    for(Turma turma: lista_de_turmas){
        if(turma.get_codigo_turma() == codigo_turma){
            turma.get_horario_turma().print_horario();
        }
    }
    cout << "saindo..." << endl;
}


/** Redirecionar para o menu de consulta de alunos: da turma, cadeira, curso ou ano
*  As funções de consulta indicam os estudantes de uma turma, cadeira, turma ou ano
* Time complexity: O(n)(Ver alunos do ano), O(nlogN)(Ver alunos do curso), O(n²logN)(Ver alunos da UC), O(n³logN)(Ver alunos da turma)
*/
void Secretaria::consultar_alunos(){
    vector<string> vetor = {"da_turma                       Para consultar alunos de uma dada turma",
                            "da_cadeira                     Para consultar alunos de uma dada cadeira",
                            "do_curso                       Para consultar alunos do curso",
                            "do_ano                         Para consultar alunos de um dado ano" ,"sair"};
    while (true){
        cout << "-------Consulta de alunos-------" << endl;
        print_inicio(vetor);
        string comando;
        cin >> comando;
        if(comando == "da_turma"){
            cout<<"Escreva o codigo da turma (Ex.: xLEICxx) :";
            string codigo_turma;
            cin >> codigo_turma;
            if(ver_se_existe_turma(codigo_turma)){
                ver_alunos_da_turma(codigo_turma);
            }else{
                cout << "Codigo da turma nao encontrado. Tente novamente" << endl;
            }
        }
        else if(comando == "do_curso"){
            ver_alunos_do_curso();
        }
        else if(comando == "da_cadeira"){
            cout<<"Escreva o codigo da cadeira (Ex.: L.EIC0xx) :";
            string cadeira;
            cin >> cadeira;
            if(ver_se_existe_cadeira(cadeira)) {
                ver_alunos_da_uc(cadeira);
            }else{
                cout << "Codigo da cadeira nao encontrado. Tente novamente" << endl;
            }
        }
        else if(comando == "do_ano"){
            cout<<"Escreva o ano dos alunos (Ex.: 1) :";
            int ano;
            cin >> ano;
            if(ano > 0 && ano < 4){
                ver_alunos_do_ano(ano);
            }else{
                cout << "Ano nao encontrado. Tente novamente" << endl;
            }
        }
        else if(comando == "sair"){
            break;
        }
        else{
            print_incorreto();
        }
    }
}


/** Faz print dos alunos inscritos em cada cadeira de uma turma
* @param string com o código da turma que se quer analisar
* Time complexity: O(n³)
*/
void Secretaria::ver_alunos_da_turma(const string& codigo_turma){
    for(Turma turma: lista_de_turmas){
        if(turma.get_codigo_turma() == codigo_turma){
            for(Aula aula:turma.get_horario_turma().get_horario()){
                if(aula.get_tipo_de_aula() == "TP" or aula.get_tipo_de_aula() == "PL") {
                    cout << aula.get_codigo_cadeira() << '\n';
                    aula.ver_alunos_na_turma();
                    cout << "//////////////////////////////////////" << endl;
                }

            }
        }
    }
    cout << "saindo..." << endl;
}


/** Faz print de todos os alunos inscritos no curso LEIC
* Time complexity: O(n)
*/
void Secretaria::ver_alunos_do_curso(){
    for(Aluno aluno: lista_de_alunos){
        aluno.print_aluno();
    }
    cout << "saindo..." << endl;
}


/** Indica o número de alunos inscritos numa determinada cadeira
* @param string com o código da cadeira
* Time complexity: O(n²)
*/
void Secretaria::ver_alunos_da_uc(const string& codigo_uc){
    int numero_de_alunos = 0;
    for(Aluno aluno : lista_de_alunos){
        for(Aula aula : aluno.get_horario().get_horario()){
            if(aula.get_codigo_cadeira() == codigo_uc){
                numero_de_alunos++;
                aluno.print_aluno();
                break;
            }
        }
    }
    cout << "O numero de alunos em " << codigo_uc << " e: " << numero_de_alunos <<endl;
    cout << "saindo..." << endl;
}


/** Faz print de todos os alunos inscritos em pelo menos uma cadeira de determinado ano
* @param int com o ano que se quer ver os alunos
* Time complexity: O(n)
*/
void Secretaria::ver_alunos_do_ano(const int& ano){
    cout << "Alunos do " << ano << " ano:" << '\n';
    for(Aluno aluno: lista_de_alunos){
        if(aluno.aluno_no_ano(ano)) aluno.print_aluno();
    }
    cout << "saindo..." << endl;
}


/** Indica o número de alunos que estão inscritos em pelo menos um dado número de cadeiras
* @param int com o número de cadeiras que se utiliza na verificação da função
* Time complexity: O(n³)
*/
void Secretaria::alunos_nas_cadeiras( int n){
    vector<string> cadeiras = {"L.EIC001", "L.EIC002", "L.EIC003", "L.EIC004", "L.EIC005", "L.EIC011", "L.EIC012",
                               "L.EIC013", "L.EIC014", "L.EIC015", "L.EIC021", "L.EIC022", "L.EIC023",
                               "L.EIC024", "L.EIC025"};
    int contador_de_alunos = 0;
    for(Aluno aluno: lista_de_alunos){
        int contador = 0;
        for(const string& nome_cadeira : cadeiras ) {
            bool verificcao = aluno.ver_se_existe_cadeira_no_aluno(nome_cadeira);
            if(verificcao){
                contador++;
            }
            if(contador >= n){
                contador_de_alunos ++;
                break;
            }
        }
    }
    cout <<  endl << "Existem " << contador_de_alunos
    << " alunos que estao registados em pelo menos " << n << " unidades curriculares." << endl;
}

/** Redirecionar para o menu de consulta de ocupação: da turma, cadeira ou ano
*  As funções de consulta de ocupação indicam o número de alunos numa determinada turma, inscritos numa cadeira ou num ano
* Time complexity: O(nlogN) or O(n²logN) or O(n³logN) (Depende da escolha do user)
 */
void Secretaria::consultar_ocupacao(){
    vector<string> vetor = {"da_turma                        Para consultar numero de alunos da turma",
                            "da_cadeira                      Para consultar numero de alunos da unidade curricular",
                            "do_ano                          Para consultar numero de alunos do ano" ,
                            "sair"};
    while (true){
        cout << "-------Consulta de numero de alunos-------" << endl;
        print_inicio(vetor);
        string comando;
        cin >> comando;
        if(comando == "da_turma"){
            cout<<"Escreva o codigo da turma (Ex.: xLEICxx) :";
            string codigo_turma;
            cin >> codigo_turma;
            if(ver_se_existe_turma(codigo_turma)) {
                ver_ocupacao_da_turma(codigo_turma);
            }else{
                cout << "Codigo da turma nao encontrado. Tente novamente" << endl;
            }
        }
        else if(comando == "do_ano"){
            cout<<"Escreva o ano dos alunos (Ex.: 1) :";
            int ano;
            cin >> ano;
            if(ano > 0 && ano < 4) {
                ver_ocupacao_do_ano(ano);
            }else{
                cout << "Ano nao encontrado. Tente novamente" << endl;
            }
        }
        else if(comando == "da_cadeira"){
            cout<<"Escreva o codigo da cadeira (Ex.: L.EIC0xx) :";
            string cadeira;
            cin >> cadeira;
            if(ver_se_existe_cadeira(cadeira)) {
                ver_alunos_da_uc(cadeira);
            }else{
                cout << "Codigo da cadeira nao encontrado. Tente novamente" << endl;
            }
        }
        else if(comando == "sair"){
            break;
        }
        else{
            print_incorreto();
        }
    }
}


/** Indica o número de alunos inscritos em cada cadeira de uma dada turma
* @param string com o código da turma a ser analisada
* Time complexity: O(n²)
*/
void Secretaria::ver_ocupacao_da_turma(const string& codigo_turma){
    vector<pair<string,int>> lista_ocupacao;
    for(Turma turma: lista_de_turmas){
        if(turma.get_codigo_turma() == codigo_turma){
            for(Aula aula:turma.get_horario_turma().get_horario()){
                if(aula.get_tipo_de_aula() == "TP" or aula.get_tipo_de_aula() == "PL") {
                    lista_ocupacao.push_back({aula.get_codigo_cadeira(),aula.get_alunos_na_aula().size()});
                }
            }
        }
    }
    escolher_ordem(lista_ocupacao);
   }


/** Indica o número de alunos inscritos em pelo menos uma cadeira de um determinado ano
* @param int com o ano de qual se pretende ver o número de alunos inscritos
* Time complexity: O(n)
*/
void Secretaria::ver_ocupacao_do_ano(const int& ano){
    cout << "Numero de alunos do " << ano << " ano: ";
    int numero_alunos = 0;
    for(Aluno aluno: lista_de_alunos){
        if(aluno.aluno_no_ano(ano)) numero_alunos++;
    }
    cout << numero_alunos << '\n';
    cout << "saindo..." << endl;
}


/** Indica o número de alunos inscritos em cada cadeira dependendo da ordem escolhida
* Time complexity: O(n³)
*/
void Secretaria::ver_ocupacao_da_cadeira() {
    vector<string> cadeiras = {"L.EIC001", "L.EIC002", "L.EIC003", "L.EIC004", "L.EIC005", "L.EIC011", "L.EIC012",
                               "L.EIC013", "L.EIC014", "L.EIC015", "L.EIC021", "L.EIC022", "L.EIC023",
                               "L.EIC024", "L.EIC025"};
    vector<pair<string,int>> lista_ocupacao;
    for(const string& cadeira : cadeiras) {
        int contador = 0;
        for (Turma turma: lista_de_turmas) {
            for (Aula aula: turma.get_horario_turma().get_horario()) {
              if ((aula.get_codigo_cadeira() == cadeira)  and (aula.get_tipo_de_aula() == "TP" or aula.get_tipo_de_aula() == "PL")) {
                  contador += aula.get_alunos_na_aula().size();
              }
            }
        }
        lista_ocupacao.push_back({cadeira,contador});
    }
    escolher_ordem(lista_ocupacao);
}


/** Indica o número de alunos inscritos em cada cadeira na ordem decrescente
* Time complexity: O(n³)
*/
void Secretaria::consultar_ucs(){
vector<string> cadeiras = {"L.EIC001", "L.EIC002", "L.EIC003", "L.EIC004", "L.EIC005", "L.EIC011", "L.EIC012",
                           "L.EIC013", "L.EIC014", "L.EIC015", "L.EIC021", "L.EIC022", "L.EIC023",
                           "L.EIC024", "L.EIC025"};
vector<pair<string,int>> lista_ocupacao;
    for(const string& cadeira : cadeiras) {
        int contador = 0;
        for (Turma turma: lista_de_turmas) {
            for (Aula aula: turma.get_horario_turma().get_horario()) {
                if ((aula.get_codigo_cadeira() == cadeira)  and (aula.get_tipo_de_aula() == "TP" or aula.get_tipo_de_aula() == "PL")) {
                    contador += aula.get_alunos_na_aula().size();
                }
            }
        }
        lista_ocupacao.push_back({cadeira,contador});
    }
    print_lista(lista_ocupacao,"decrescente_ucs");
}


/** Retorna um apontador de um aluno específico se existir na lista_de_alunos
*
* @param int com ocódigo do aluno
* @return Aponyador de Aluno com o aluno se este existir
* Time complexity: O(n)
*/
Aluno* Secretaria::obter_aluno(const int& ID){
 for (auto& aluno : lista_de_alunos) {
     if (aluno.get_aluno_ID() == ID) {
         return &aluno; // Retorna um ponteiro para o Aluno encontrado
     }
 }
 return nullptr;
}


/** Retorna um vetor com as aulas de uma determinada turma e cadeira
* @param string com o código da turma
* @param string com o código da cadeira
* @return vetor de aulas
* Time complexity: O(n²)
*/
vector<Aula*> Secretaria::obter_aulas(const int& aluno_ID ,const string& codigo_turma,const string& codigo_cadeira){
    vector<Aula*> aulas;
    for(Turma& turma : lista_de_turmas){
        if(turma.get_codigo_turma() == codigo_turma){
            for(Aula& aula : turma.get_horario_turma().get_horario()){
                if(aula.get_codigo_cadeira() == codigo_cadeira){
                    aulas.push_back(&aula);
                }
            }
        }
    }
    return aulas;
}


/** Redirecionar para o menu de alteração de horários de um determinado aluno
* @param apontador de Aluno, aponta para o aluno que pretende realizar pedidos de alteração de horário
* Time complexity: Depende dos pedidos escolhidos, tendo os pedidos remover aula e trocar aula O(n³*logN), e adicionar aula O(n²*logN)
*/
void Secretaria::alterar_horario(Aluno * aluno) {
 vector<string> vetor = {"adicionar_aula                 Para adicionar aula ao horario",
                         "remover_aula                   Para remover aula do horario",
                         "trocar_aula                    Para trocar aula do horario por outra", "sair"};
 while (true) {
     cout << "-------Mudanca de horario do aluno " << aluno->get_aluno_nome() << "-------" << endl;
     print_inicio(vetor);
     string comando;
     cin >> comando;
     if (comando == "adicionar_aula") {
         escolha_do_pedido("adicionar_aula",aluno);
     } else if (comando == "remover_aula") {
         escolha_do_pedido("remover_aula",aluno);
     } else if (comando == "trocar_aula") {
         escolha_do_pedido("trocar_aula",aluno);
     } else if (comando == "sair") {
        if( index_fila_pedidos < fila_pedidos.size()){
             cout << "Nem todos os pedidos foram concluidos.Tem que continuar a realizacao dos pedidos" << endl;
             realizar_pedidos(aluno);
        }else{
             break;
        }
     } else {
         print_incorreto();
     }
 }
}
/** Gera os pedidos de alteração de horário de um aluno e coloca-os numa fila de pedidos
 *  Os pedidos são realizados assim que o aluno terminar de fazer pedidos
 *
 * @param string com o tipo de pedido: remover, adicionar cadeira ou troca de turmas
 * @param Apontador de Aluno com o aluno que pretende mudar o horário
 * Time complexity: (O(n³*logN) ou O(n²*logN)(dependendo da ordem de pedidos escolhidos))*número de pedidos
 */
void Secretaria::escolha_do_pedido(const string & nome_pedido,Aluno*  aluno){
 cout << "Escreva o codigo da cadeira (Ex.: L.EIC0xx ) :";
 string codigo_cadeira;
 cin >> codigo_cadeira;
 if(ver_se_existe_cadeira(codigo_cadeira)){
     cout << endl << "Escreva o codigo da turma a que pertence (Ex.: xLEICxx ) :";
     string codigo_turma;
     cin >> codigo_turma;
     if(ver_se_existe_turma(codigo_turma)){
         if (nome_pedido == "adicionar_aula") {
             Pedido pedido = Pedido(codigo_cadeira, codigo_turma, "", nome_pedido);
             fila_pedidos.push_back(pedido);
         } else if (nome_pedido == "remover_aula") {
             Pedido pedido = Pedido(codigo_cadeira, codigo_turma, "", nome_pedido);
             fila_pedidos.push_back(pedido);
         } else if (nome_pedido == "trocar_aula") {
             cout << endl << "Escreva o codigo da turma com que deseja trocar (Ex.: xLEICxx ) :";
             string codigo_turma_2;
             cin >> codigo_turma_2;
             if(ver_se_existe_turma(codigo_turma_2)){
                 Pedido pedido = Pedido(codigo_cadeira, codigo_turma, codigo_turma_2, nome_pedido);
                 fila_pedidos.push_back(pedido);
             }else{
                 cout << "Codigo da turma nao encontrado. Tente novamente." << endl;
                 alterar_horario(aluno);
             }
         }
         cout << "Deseja fazer mais pedidos? [sim/nao] ";
         string resposta;
         while (resposta != "sim" && resposta != "nao") {
             cin >> resposta;
             if (resposta == "sim") {
                 break;
             }
             if (resposta == "nao") {
                 cout << endl;
                 realizar_pedidos(aluno);
             }
         }
     }else{
         cout << "Codigo da turma nao encontrado. Tente novamente." << endl;
     }
 }else{
     cout << "Codigo da cadeira nao encontrado. Tente novamente." << endl;
 }
}
/** Redirecionar para o menu de realização de pedidos de alteração de horário
 *
 * @param Apontador de Aluno com o aluno que pretende alterar o seu horário
 * Time complexity: O(n³*logN)(Trocar aula ou remover aula), O(n²*logN)(Adicionar aula), O(1)(Todas as outras opções)
 */
void Secretaria::realizar_pedidos(Aluno * aluno){
 vector<string> vetor = {"consultar_pedidos              Para consultar todos os pedidos",
                         "desfazer_ultimo                Para desfazer ultimo pedido feito",
                         "fazer_um                       Para fazer so o primeiro pedido na lista",
                         "fazer_todos                    Para fazer todos os pedidos da lista", "sair"};
 while (true) {
     cout << "-------Realizar pedidos do aluno"<< "-------" << endl;
     print_inicio(vetor);
     string comando;
     cin >> comando;
     if (comando == "desfazer_ultimo") {
         desfazer_pedido(aluno);
     } else if (comando == "fazer_um") {
         if(index_fila_pedidos != fila_pedidos.size()){
             fazer_primeiro_pedido(aluno);
         }else{
             cout << "Nao ha mais pedidos para fazer.";
         }
     } else if (comando == "fazer_todos") {
         while (index_fila_pedidos != fila_pedidos.size()){
             fazer_primeiro_pedido(aluno);
         }
         cout << "Nao ha mais pedidos para fazer.";
     } else if (comando == "consultar_pedidos") {
         for(const Pedido& pedido: fila_pedidos){
             pedido.print_pedido();
         }
     } else if (comando == "sair") {
         break;
     } else {
         print_incorreto();
     }
 }
}
/** Desfaz a última alteração feita ao horário de um aluno
 *
 * @param Apontador de Aluno com o aluno que pretende alterar o seu horário
 * Time complexity: O(n³*logN)(Caso o último pedido seja trocar aula ou remover aula), O(n²*logN)(Caso o último pedido seja adicionar aula)
 */
void Secretaria::desfazer_pedido(Aluno * aluno){
 if(!stack_pedidos.empty()){
     auto ultimo_pedido = *(stack_pedidos.rbegin());
     bool funcionou = fazer_pedido_inverso(ultimo_pedido, aluno);
     if(funcionou){
         historico_de_mudancas.push_back("Desfeito pedido anterior");
         stack_pedidos.erase(ultimo_pedido);
     }else{
         cout << "Desculpe, mas nao foi possivel desfazer o ultimo pedido.Nao foram elimanadas as alteracoes que esse pedido fez." << endl;
     }

 }else{
     cout << "Nao ha pedidos para desfazer.";
 }
}
/** Função auxiliar à função de desfazer a última alteração
 *
 * @param Pedido com o último pedido realizado
 * @param Apontador de Aluno com o aluno que pretende alterar o horário
 * @return
 * Time complexity: O(n³*logN), O(n²*logN) e O(n³*logN), respetivamente
 */
bool Secretaria::fazer_pedido_inverso(const Pedido& ultimo_pedido, Aluno * aluno){
 bool der;
 if (ultimo_pedido.get_pedido_q_foi_feito() == "adicionar_aula") {
     Pedido pedido_inverso = Pedido(ultimo_pedido.get_cadeira_1(), ultimo_pedido.get_turma_1(),"","remover_aula");
     der = ver_se_operacao_vai_dar(pedido_inverso, aluno);
     if(der) {
         remover_aula(aluno,ultimo_pedido.get_cadeira_1(), ultimo_pedido.get_turma_1(),false);
         return true;
     }
 } else if (ultimo_pedido.get_pedido_q_foi_feito() == "remover_aula") {
     Pedido pedido_inverso = Pedido(ultimo_pedido.get_cadeira_1(), ultimo_pedido.get_turma_1(),"","adicionar_aula");
     der = ver_se_operacao_vai_dar(pedido_inverso, aluno);
     if(der) {
         adicionar_aula(aluno, ultimo_pedido.get_cadeira_1(), ultimo_pedido.get_turma_1());
         return true;
     }
 } else if (ultimo_pedido.get_pedido_q_foi_feito() == "trocar_aula") {
     Pedido pedido_inverso = Pedido(ultimo_pedido.get_cadeira_1(), ultimo_pedido.get_turma_2(),
                                    ultimo_pedido.get_turma_1(), "trocar_aula");
     der = ver_se_operacao_vai_dar(pedido_inverso, aluno);
     if (der) {
         trocar_aula(aluno,ultimo_pedido.get_cadeira_1(), ultimo_pedido.get_turma_2(), ultimo_pedido.get_turma_1());
         return true;
     }
 }
 return false;
}
/** Remove uma cadeira de um aluno
 *
 * @param Apontador de Aluno com o aluno que pretende alterar o horário
 * @param string com o código da cadeira
 * @param string com o código da turma
 * @param e_fake
 * Time complexity: O(n³*logN)
 */
void Secretaria::remover_aula(Aluno* aluno,const string & codigo_cadeira,const string & codigo_turma,bool e_fake){
 pair<int,string> al = {aluno->get_aluno_ID(),aluno->get_aluno_nome()};

 for (Turma& turma : lista_de_turmas) {
     if (turma.get_codigo_turma() == codigo_turma) {
         for (Aula& aula : turma.get_horario_turma().get_horario()) {
             if (aula.get_codigo_cadeira() == codigo_cadeira) {
                 if(!e_fake) {
                     vector<pair<int, std::string>> &alunos_na_turma = aula.get_alunos_na_aula();
                     alunos_na_turma.erase(std::remove(alunos_na_turma.begin(), alunos_na_turma.end(), al),alunos_na_turma.end());
                 }
                 aluno->get_horario().remover_aula(aula);
                 aluno->remover_cadeira_ao_aluno(codigo_cadeira);
             }
         }
     }
 }
 if(!e_fake){
     cout << "As aulas da cadeira " << codigo_cadeira
          << " da turma " << codigo_turma <<" foram removidas do seu horario." << endl;
 }

}
/** Adiciona uma cadeira a um aluno, se for possível
 *
 * @param Apontador de Aluno com o aluno que pretende alterar o horário
 * @param string com o código da cadeira
 * @param string com o código da turma que o aluno que se inscrever
 * Time complexity: O(n²*logN)
 */
void Secretaria::adicionar_aula(Aluno* aluno,const string & codigo_cadeira,const string & codigo_turma){
 pair<int,string> al = {aluno->get_aluno_ID(),aluno->get_aluno_nome()};

 for (Turma& turma : lista_de_turmas) {
     if (turma.get_codigo_turma() == codigo_turma) {
         for (Aula& aula : turma.get_horario_turma().get_horario()) {
             if (aula.get_codigo_cadeira() == codigo_cadeira) {
                 aula.get_alunos_na_aula().push_back(al);
                 aluno->get_horario().adicionar_aula(aula);
                 aluno->adicionar_cadeira_ao_aluno(codigo_cadeira);
             }
         }
     }
 }
 cout << "As aulas da cadeira " << codigo_cadeira
 << " da turma " << codigo_turma <<" foram adicionadas ao seu horario." << endl;
}
/** Realiza a troca de turmas de um aluno para uma dada cadeira
 *
 * @param Apontador de Aluno com o aluno que pretende alterar o horário
 * @param string com o código da cadeira
 * @param string com o código da turma atual do aluno
 * @param string com o código da turma futura do aluno
 * Time complexity: O(n³*logN)
 */
void Secretaria::trocar_aula(Aluno* aluno,const string & codigo_cadeira,const string & codigo_turma_presente,const string & codigo_turma_futura){
 //Pedido pedido_para_adicionar = Pedido(codigo_cadeira, codigo_turma_futura,"","adicionar_aula");
 remover_aula(aluno,codigo_cadeira,codigo_turma_presente,false);
 adicionar_aula(aluno,codigo_cadeira, codigo_turma_futura);

 cout << "As aulas da cadeira " << codigo_cadeira
      << " da turma " << codigo_turma_presente << " foram trocadas pelas aulas da turma "
      << codigo_turma_futura << "." << endl;
}
/** Verifica se entre as turmas de uma cadeira existe uma ocupação desiquilibrada (diferença de 4 ou mais alunos entre turmas)
 *
 * @param string com o codigo da cadeira
 * @param string codigo da turma
 * @return true se não existir desiquilibrio entre turmas, caso contrário false
 * Time complexity: O(n²)
 */
bool Secretaria::ocupacao_desiquilibrada(const string& codigo_cadeira, const string & codigo_turma){
 vector<int> n_alunos_em_turma;
 int n_alunos;
 for(Turma turma: lista_de_turmas){
     for(Aula aula: turma.get_horario_turma().get_horario()) {
         if(aula.get_codigo_cadeira() == codigo_cadeira && (aula.get_tipo_de_aula() == "TP" || aula.get_tipo_de_aula() == "PL")) {
            n_alunos_em_turma.push_back(aula.get_alunos_na_aula().size());
         }
         if(turma.get_codigo_turma() == codigo_turma){
             n_alunos = aula.get_alunos_na_aula().size();
         }
     }
 }
 sort(n_alunos_em_turma.begin(),n_alunos_em_turma.end());
 //cout << n_alunos << " A diferenca entre " << (n_alunos_em_turma[0]) << " e " << (n_alunos_em_turma[n_alunos_em_turma.size()-1]) << " e de " << - ( n_alunos_em_turma[0]) + (n_alunos_em_turma[n_alunos_em_turma.size()-1]) << endl;
 if((n_alunos_em_turma[n_alunos_em_turma.size()-1]) - (n_alunos+1)  <= 4){
     return false;
 }
 return true;
}
/** Verifica se a realização de uma operação de alteração de horário é possivel
 *
 * @param Pedido com o pedido feito
 * @param Apontador de Aluno com o aluno que pretende alterar o horário
 * @return
 * Time complexity: O(n²)(Adicionar aula), O(1)(Remover aula), O(n³*logN)(Trocar aula)
 */
bool Secretaria::ver_se_operacao_vai_dar(const Pedido& pedido, Aluno * aluno){
 if(pedido.get_pedido_q_foi_feito() == "adicionar_aula"){
     if(((1 + aluno->get_cadeiras_do_aluno().size()) <= 7)){
         vector<Aula*> aulas_uc = obter_aulas(aluno->get_aluno_ID(),pedido.get_turma_1(),pedido.get_cadeira_1());
         if(aulas_uc.empty()){
             cout << "Nenhuma aula dessa cadeira foi encontrada na turma." << endl;
             return false;
         }
         for(Aula *aula: aulas_uc) {
             if (aula->get_tipo_de_aula() == "PL" or aula->get_tipo_de_aula() == "TP") {
                 if (aula->get_alunos_na_aula().size() <= 23) {
                     for (Aula &aulas_em_horario: aluno->get_horario().get_horario()){
                         if (!aulas_em_horario.aula_compativel(*aula)) {
                             cout << "Horario imcompativel com a aula pratica.";
                             return false;
                         }
                     }
                     if(ocupacao_desiquilibrada(pedido.get_cadeira_1(),pedido.get_turma_1())){
                         return false;
                     }
                 }
             }
         }
         return true;
     }
 }else if(pedido.get_pedido_q_foi_feito() == "remover_aula"){
     vector<Aula*> aulas_uc = obter_aulas(aluno->get_aluno_ID(),pedido.get_turma_1(),pedido.get_cadeira_1());
     if(aulas_uc.empty() || !aulas_uc[0]->esta_na_aula(aluno->get_aluno_ID())){
         cout << "Nenhuma aula encontrada em aluno com essa cadeira e turma." << endl;
         return false;
     }
     return true;

 } else if(pedido.get_pedido_q_foi_feito() == "trocar_aula"){
     Pedido pedido_para_remover = Pedido(pedido.get_cadeira_1(),pedido.get_turma_1(),"","remover_aula");
     Pedido pedido_para_adicionar = Pedido(pedido.get_cadeira_1(), pedido.get_turma_2(),"","adicionar_aula");
     bool der_remover = ver_se_operacao_vai_dar(pedido_para_remover,aluno);
     if(der_remover){
         Aluno fake_aluno = *aluno;
         Aluno* p_fake_aluno = &fake_aluno;
         remover_aula(p_fake_aluno,pedido.get_cadeira_1(),pedido.get_turma_1(),true);
         bool der_adicionar = ver_se_operacao_vai_dar(pedido_para_adicionar,p_fake_aluno);
         if(der_adicionar) {
             return true;
         }
     }
 }
 return false;
}
/** Realiza o primeiro pedido da fila de pedidos feitos
 *
 * @param Apontador de Aluno com o aluno que pretende alterar o horário
 * Time complexity: O(n²*logN)(Adicionar aula), O(n³*logN)(Remover aula e Trocar aula)
 */
void Secretaria::fazer_primeiro_pedido(Aluno * aluno){
 cout << "Realizando: ";fila_pedidos[index_fila_pedidos].print_pedido();
 bool der =  ver_se_operacao_vai_dar(fila_pedidos[index_fila_pedidos],aluno);
 if(der){
     string mudanca = "Foi feito ";
     mudanca.append(fila_pedidos[index_fila_pedidos].get_pedido_q_foi_feito()+ " de "+fila_pedidos[index_fila_pedidos].get_cadeira_1() +" da turma " + fila_pedidos[index_fila_pedidos].get_turma_1() );

     if(fila_pedidos[index_fila_pedidos].get_pedido_q_foi_feito() == "adicionar_aula"){
         adicionar_aula(aluno,fila_pedidos[index_fila_pedidos].get_cadeira_1(),fila_pedidos[index_fila_pedidos].get_turma_1());
     }else if(fila_pedidos[index_fila_pedidos].get_pedido_q_foi_feito() == "remover_aula"){
         remover_aula(aluno,fila_pedidos[index_fila_pedidos].get_cadeira_1(),fila_pedidos[index_fila_pedidos].get_turma_1(),false);
     }else if(fila_pedidos[index_fila_pedidos].get_pedido_q_foi_feito() == "trocar_aula"){
         trocar_aula(aluno,fila_pedidos[index_fila_pedidos].get_cadeira_1(),fila_pedidos[index_fila_pedidos].get_turma_1(),fila_pedidos[index_fila_pedidos].get_turma_2());
         mudanca.append(" para a turma " + fila_pedidos[index_fila_pedidos].get_turma_2() );
     }
     stack_pedidos.insert(fila_pedidos[index_fila_pedidos]);
     mudanca.append( " ao aluno " + aluno->get_aluno_nome());
     historico_de_mudancas.push_back(mudanca);
     cout <<"Adicionada ao historico: " << mudanca << endl;
 }else{
     cout << "Desculpe, mas nao foi possivel realizar o pedido.Nao foram feitas as alteracoes pedidas." << endl;
 }
 index_fila_pedidos++;
}
