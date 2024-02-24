#include <iostream>
#include <locale.h>
#include <string>
#include <time.h>

#ifdef _WIN32
#define PAUSE(msg) system("pause")
#define CLEAR() system("cls")
#else
#define PAUSE(msg) system("echo " msg " ; read _")
#define CLEAR() system("clear")
#endif

// Struct Jogador que tem o nome e a pontuação
struct Jogador {
	std::string nome = "Jogador";
	int pontuacao = 0;
};

// Define o tipo de ordenação da troca caso sejam iguais
enum TipoDeOrganizacao {
	NOME,
	PONTUACAO
};

// Define o tipo de ordenação da troca
enum TipoDeAlgoritmo {
	QUICK,
	BUBBLE,
	SHELL
};

// Função que imprime o vetor de Jogadores com a posição, nome e a pontuação
void ImprimirVetorDeJogadores(Jogador* vetorDeJogadores, int numeroDeJogadores) {

	std::cout << "\n Vetor de jogadores\n\n";
	for (int i = 0; i < numeroDeJogadores; i++) {
		std::cout << " " << i + 1 << "º Jogador Nome: " << vetorDeJogadores[i].nome << ", pontuação: " << vetorDeJogadores[i].pontuacao << std::endl;
	}

	std::cout << "\n ";
	PAUSE("clique em algo para continuar... ");
	std::cout << std::endl;
}

//Troca a posição dos jogadoress, dependendo de qual algoritmo é usado muda a forma
void TrocaDePosicao(Jogador* vetorDeJogadores, int i, int j, TipoDeAlgoritmo tipoDeOrganizacao, int gap = 0) {

	if (tipoDeOrganizacao == QUICK) {
		Jogador aux;
		aux = vetorDeJogadores[i];
		vetorDeJogadores[i] = vetorDeJogadores[j];
		vetorDeJogadores[j] = aux;
	}
	if (tipoDeOrganizacao == BUBBLE) {
		Jogador aux;
		aux = vetorDeJogadores[j];
		vetorDeJogadores[j] = vetorDeJogadores[j + 1];
		vetorDeJogadores[j + 1] = aux;
	}
	if (tipoDeOrganizacao == SHELL) {
		Jogador aux;
		aux = vetorDeJogadores[j];
		vetorDeJogadores[j] = vetorDeJogadores[j + gap];
		vetorDeJogadores[j + gap] = aux;
	}
}

// Ordena caso tenha nome ou pontuação igual
void OrganiaNomesOuPontuacaoIguais(Jogador* vetorDeJogadores, int numeroDeJogadores, TipoDeOrganizacao tipoDeOrganizacao) {

	for (int i = 0; i < numeroDeJogadores - 1; i++) {
		for (int j = 0; j < numeroDeJogadores - i - 1; j++) {
			if (tipoDeOrganizacao == PONTUACAO) {
				if (vetorDeJogadores[j].pontuacao == vetorDeJogadores[j + 1].pontuacao) {
					if (vetorDeJogadores[j].nome > vetorDeJogadores[j + 1].nome) {
						TrocaDePosicao(vetorDeJogadores, i, j, BUBBLE);
					}
				}
			}

			if (tipoDeOrganizacao == NOME) {
				if (vetorDeJogadores[j].nome == vetorDeJogadores[j + 1].nome) {
					if (vetorDeJogadores[j].pontuacao < vetorDeJogadores[j + 1].pontuacao) {
						TrocaDePosicao(vetorDeJogadores, i, j, BUBBLE);
					}
				}
			}
		}
	}

}

// Ordenar Nome Quick sort
// Jogadores com nome iguais devem ser aparecer ordenados em ordem de pontuação
void QuickSort(Jogador* vetorDeJogadores, int inicio, int fim) {
	int i = inicio;
	int j = fim;
	int meio = (i + j) / 2;
	Jogador pivo = vetorDeJogadores[meio];
	while (i <= j) {
		while (vetorDeJogadores[i].nome < pivo.nome) {
			i++;
		}
		while (vetorDeJogadores[j].nome > pivo.nome) {
			j--;
		}
		if (i <= j) {
			TrocaDePosicao(vetorDeJogadores, i, j, QUICK);
			i++;
			j--;
		}
	}

	if (inicio < j) {
		QuickSort(vetorDeJogadores, inicio, j);
	}
	if (i < fim) {
		QuickSort(vetorDeJogadores, i, fim);
	}
}

// Deve mostrar no console o nome de todos os jogadores ordenados em ordem alfabética
void ExibirJogadores(Jogador* vetorDeJogadores, int numeroDeJogadores) {
	QuickSort(vetorDeJogadores, 0, numeroDeJogadores - 1);

	OrganiaNomesOuPontuacaoIguais(vetorDeJogadores, numeroDeJogadores, NOME);

	ImprimirVetorDeJogadores(vetorDeJogadores, numeroDeJogadores);
}

// Deve mostrar no console as 10 melhores pontuações, ordenadas da melhor para a pior no bubble sort
// Jogadores com pontuações iguais devem ser aparecer ordenados em ordem alfabética
void MelhoresPontuacoes10(Jogador* vetorDeJogadores, int numeroDeJogadores) {
	int i, j;

	for (i = 0; i < numeroDeJogadores - 1; i++) {
		for (j = 0; j < numeroDeJogadores - i - 1; j++) {
			if (vetorDeJogadores[j].pontuacao < vetorDeJogadores[j + 1].pontuacao) {
				TrocaDePosicao(vetorDeJogadores, i, j, BUBBLE);
			}
		}
	}

	OrganiaNomesOuPontuacaoIguais(vetorDeJogadores, numeroDeJogadores, PONTUACAO);

	ImprimirVetorDeJogadores(vetorDeJogadores, 10);
}

// Deve mostrar no console as 100 melhores pontuações, ordenadas da melhor para a pior por shell sort
// Jogadores com pontuações iguais devem ser aparecer ordenados em ordem alfabética
void MelhoresPontuacoes100(Jogador* vetorDeJogadores, int numeroDeJogadores) {
	int i, j, gap;

	for (gap = numeroDeJogadores / 2; gap > 0; gap /= 2) {
		for (i = gap; i < numeroDeJogadores; i++) {
			for (j = i - gap; j >= 0 && vetorDeJogadores[j].pontuacao < vetorDeJogadores[j + gap].pontuacao; j -= gap) {
				TrocaDePosicao(vetorDeJogadores, i, j, SHELL, gap);
			}
		}
	}

	OrganiaNomesOuPontuacaoIguais(vetorDeJogadores, numeroDeJogadores, PONTUACAO);

	ImprimirVetorDeJogadores(vetorDeJogadores, 100);
}

// Gera o nomes aleatórios para os jogadores
std::string GeraNomeAleatorio(int tamanhoDoNome) {

	char consoantes[] = { 'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z' };
	char vogais[] = { 'a','e','i','o','u' };

	std::string nome = "";

	int random = rand() % 2;
	int count = 0;

	for (int i = 0; i < tamanhoDoNome; i++) {

		if (random < 2 && count < 2) {
			nome += consoantes[rand() % 21];
			count++;
		}
		else {
			nome += vogais[rand() % 5];
			count = 0;
		}

		random = rand() % 2;
	}

	return nome;
}

// Criar o vetor de jogadores com nomes aleatórios e pontuações aleatórias
Jogador* CriarVetorDeJogadores(int tamanhoDoNome, int numeroDeJogadores) {
	Jogador* vetorDeJogadores = new Jogador[numeroDeJogadores];

	for (int i = 0; i < numeroDeJogadores; i++) {
		vetorDeJogadores[i].nome = GeraNomeAleatorio(tamanhoDoNome);
		vetorDeJogadores[i].pontuacao = rand() % 10000;
	}

	return vetorDeJogadores;
}

void MenuDosAlgoritmos() {

	int tamanhoDoNome = 10;
	int numeroDeJogadores = 1000;

	Jogador* vetorDeJogadores = CriarVetorDeJogadores(tamanhoDoNome, numeroDeJogadores);
	std::cout << std::endl;

	int opcaoMenu = 0;

	while (opcaoMenu != 4) {
		//system("cls");
		std::cout << " Escolha uma opção:\n 1- Ordenar por nome\n 2- Ordenar por pontuação, 10 melhores\n 3- Ordenar por pontuação, 100 melhores\n 4- Sair\n Opção: ";
		std::cin >> opcaoMenu;

		switch (opcaoMenu) {
		case 1:
			ExibirJogadores(vetorDeJogadores, numeroDeJogadores);
			break;
		case 2:
			MelhoresPontuacoes10(vetorDeJogadores, numeroDeJogadores);
			break;
		case 3:
			MelhoresPontuacoes100(vetorDeJogadores, numeroDeJogadores);
			break;
		default:
			std::cout << "\n Opcão inválida!\n";
			break;
		}
	}

	delete[] vetorDeJogadores;
}

int main()
{
	setlocale(LC_ALL, "Portuguese");
	srand(time(NULL));

	int opcaoDeMenuJogo = 0;

	while (opcaoDeMenuJogo != 3) { //Menu principal
		CLEAR();
		std::cout << " Escolha uma opção:\n 1- Jogar \n 2- Informações \n 3- Sair \n Opção: ";
		std::cin >> opcaoDeMenuJogo;

		switch (opcaoDeMenuJogo) {
		case 1:
			MenuDosAlgoritmos();
			break;
		case 2:
			std::cout << "\n Informações:\n Jogo feito por Eduardo Savian de Oliveira, João Filipe Gohr e Miguel Luiz Dalpra Pereira\n\n ";
			PAUSE("clique em algo para continuar... ");
			break;
		case 3:
			std::cout << "\n Saiu do jogo! \n";
			break;
		default:
			std::cout << "\n Opção inválida, escolha outra opção!\n";
			break;
		}

	}

	return 0;
}
