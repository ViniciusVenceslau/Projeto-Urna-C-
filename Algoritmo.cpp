#include <iostream>
#include <cstring>
using namespace std;
struct Candidato {
    int idade;
    char nome[100];
    char matricula[50];
    int numero;
    char formacao[50];
    char sexo[50];
    int votos=0;
};
void cadastro(int quantidade, Candidato candidatos[quantidade]) {
    for(int i = 0; i < quantidade; i++) {
        cout << endl;
        cout << "Candidato " << i+1 << endl;
        cout << "Informe o nome: " << endl;
        do {
            cin.getline(candidatos[i].nome, 100);
        }while(strlen(candidatos[i].nome) == 0);
        cout << "Informe a idade: " << endl;
        cin >> candidatos[i].idade;
        while(candidatos[i].idade < 30){
          cout << "Idade insuficiente para participar do cadastro, por favor, digite novamente." << endl;
          cin >> candidatos[i].idade;
        }
        cout << "Digite a matrícula: " << endl;
        cin >> candidatos[i].matricula;
        //Lembrar da restrição -1, o candidato não pode ter -1 como número.
        cout << "Informe o número do candidato: " << endl;
        cin >> candidatos[i].numero;
        while(candidatos[i].numero == -1){
        cout << "Este número é inválido para representar o canditado, digite novamente!" << endl;
        cin >> candidatos[i].numero;
        }
        cout << "Insira sua graduação: " << endl;
        do{
        cin.getline(candidatos[i].formacao, 50);
        }while(strlen(candidatos[i].formacao) == 0);
        if(strcmp(candidatos[i].formacao, "Doutor") == 0 || strcmp(candidatos[i].formacao, "doutor") == 0){
          cout << "Gradução válida para cadastro, por favor, continue." << endl;
        }else while(strcmp(candidatos[i].formacao, "Doutor") != 0 && strcmp(candidatos[i].formacao, "doutor") != 0){
          cout << "Gradução INVÁLIDA para cadastro, por favor, insira novamente." << endl;
          do{
            cin.getline(candidatos[i].formacao, 50);
          }while (strlen(candidatos[i].formacao) == 0);
        }
        do{
        cout << "Escreva o sexo: " << endl;
        cin.getline(candidatos[i].sexo, 50);
      }while(strlen(candidatos[i].sexo) == 0);
      cout << endl;
    }
    cout << "\n\nCandidatos cadastrados.\n\n";
  }
void votacao(int num, int quantidade, Candidato candidatos[quantidade], int *votos_nulos, int aux) {
    char confirmacao;
    for (int i = 0; i < quantidade; ++i) {
        if (num == candidatos[i].numero) {
            cout << endl;              
            cout << "Dados do Candidato " << i+1 << endl;
            cout << "Nome: " << candidatos[i].nome << endl;
            cout << "Idade: " << candidatos[i].idade << endl;
            cout << "Matrícula: " << candidatos[i].matricula << endl;
            cout << "Sexo: " << candidatos[i].sexo << endl;
            cout << endl;
            cout << "Você deseja confirmar seu voto? Digite [S] para confirmar ou [N] para mudar o voto:\n";
            cin >> confirmacao;
            if (confirmacao == 'S') {
                candidatos[i].votos = 1 + candidatos[i].votos;
                cout << "Voto confirmado com sucesso!\n";
            }
            else if (confirmacao == 'N') {
                break; 
            }
            else { 
                while(confirmacao != 'S' && confirmacao != 'N') {
                    cout << "Digite APENAS [S] ou [N] para confirmar ou negar o voto.\n";
                    cin >> confirmacao;
                    if (confirmacao == 'S') {
                        candidatos[i].votos = 1 + candidatos[i].votos;
                        cout << "Agora sim, voto confirmado com sucesso!\n";
                    }
                    else if(confirmacao == 'N') {
                        break;
                    }
                }
            }
        }
        else if (num != candidatos[i].numero && num!= -1) {
            for (int i = 0; i < quantidade; ++i) {
                if (num != candidatos[i].numero && num !=-1) {
                    aux = 1+aux;
                    }
            }
            if (aux==quantidade) {
                cout << "VOTO NULO!\n";
                cout << "Você deseja confirmar seu voto? Digite [S] para confirmar ou [N] para mudar o voto: ";
                cin >> confirmacao;
                if (confirmacao == 'S') {
                    *votos_nulos += 1;
                    cout << "Voto confirmado com sucesso!\n";
                }
                else if (confirmacao == 'N') {
                    break; 
                }
                else { 
                    while(confirmacao != 'S' && confirmacao != 'N'){
                        cout << "Digite SOMENTE [S] ou [N] para confirmar ou negar o voto.\n";
                        cin >> confirmacao;
                        if (confirmacao == 'S') {
                            *votos_nulos += 1;
                            cout << "Agora sim, voto confirmado com sucesso!\n";
                        }
                        else if(confirmacao == 'N') {
                            break;
                        }
                    }
                }
            }
        }
    }
}
void vencedor(int maior, int quantidade, Candidato candidatos[quantidade]) {
    for(int i = 0; i < quantidade; i++){
        if(candidatos[i].votos > maior){
            maior = candidatos[i].votos;
        }
    }
    for(int i = 0; i < quantidade; i++){
        if(maior == candidatos[i].votos){
            cout << "O candidato vencedor foi: " << candidatos[i].nome << endl;
            cout << "Parabéns!\n";
        }
    }
}
void resultado(int quantidade, Candidato candidatos[quantidade], int *ponteiro) {
    //Imprimir quantidade de votos de cada candidato.
    for (int i = 0; i < quantidade; ++i) {
        cout << "Total de votos do candidato " << candidatos[i].nome << ": " << candidatos[i].votos << endl;
    }
    //Imprimir votos nulos.
    cout << "Total de votos nulos: " << *ponteiro << endl;
}
int main() {
    int num;
    int quantidade;
    int aux = 0;
    int maior = 0;
    int votos_nulos = 0;
    int *ponteiro;
    ponteiro = &votos_nulos;
    cout << "Eleição para cargo de Reitor\n";
    cout << "Bem-vindo!\n\n";
    cout << "Digite a quantidade de candidatos a reitor: ";
    cin >> quantidade;
    Candidato candidatos[quantidade];
    cadastro(quantidade, candidatos);
    cout << "Votação iniciada.\n";
    cout << "Insira -1 para encerrar a votação.\n";
    do {
        cout << "Digite o número do candidato para o qual deseja votar: ";
        cin >> num;
        votacao(num,quantidade,candidatos,ponteiro,aux);
    } while (num != -1);
    cout << "Votação encerrada!\n\n";
    resultado(quantidade, candidatos, ponteiro);
    int contador;
    do{
    contador = 0;
    for(int i = 0; i < quantidade; i++){
      if(candidatos[i].votos > maior){
        maior = candidatos[i].votos;
      }
    }
    for(int j = 0; j < quantidade; j++){
      if(candidatos[j].votos == maior){
        contador = contador + 1;
      }
    }
    if(contador != 1){
      int k = 0;
      cout << "Os " << contador << " candidatos mais votados empataram, um novo turno é necessário." << endl;
          for(int l = 0; l < quantidade; l++){
            if(candidatos[l].votos == maior){
              candidatos[l].votos = 0;
              candidatos[k] = candidatos[l];
              k = k+1;
            }
          }
    quantidade = contador;    
    cout << "Votação de desempate iniciada.\n";
    cout << "Insira -1 para encerrar a votação.\n";
    votos_nulos = 0;
    ponteiro = &votos_nulos;
     do {
        cout << "Digite o número do candidato para o qual deseja votar: ";
        cin >> num;
        votacao(num,contador,candidatos,ponteiro,aux);
} while (num != -1);
    cout << "Votação encerrada!\n\n"; 
      resultado(contador, candidatos, ponteiro);
      maior = 0;
      vencedor(maior, contador, candidatos);
      break;
}else{
        maior = 0;
        vencedor(maior, quantidade, candidatos);
    }
    }while(contador != 1);
return 0;
}
