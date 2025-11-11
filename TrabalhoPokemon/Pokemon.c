#include <stdio.h>

char jogadores[2][20];
char pokemons[3][20] = {"Charmander", "Squirtle", "Bulbasaur"};
int hp[2][3] = {{39,44,45}, {39,44,45}};
int ataque[2][3] = {{52,48,49}, {52,48,49}};
int defesa[2][3] = {{43,65,49}, {43,65,49}};
int tipos[2][3] = {{1,2,3}, {1,2,3}};

char ataques[3][4][20] = {
    {"Arranhar","Brasa","Lanca-Chamas","Investida"},
    {"Tackle","Jato d'Agua","Bolha","Mordida"},
    {"Chicote Vinha","Folha Navalha","Investida","Ataque Rapido"}
};
int poder[3][4] = {{40,40,90,35}, {40,40,40,60}, {45,55,35,40}};
int tipo_ataque[3][4] = {{0,1,1,0}, {0,2,2,0}, {3,3,0,0}};

int ativo[2] = {0, 0};


int calcular_dano(int atacante, int defensor, int ataque_escolhido) {
    int nivel = 50;
    int poder_ataque = poder[ativo[atacante]][ataque_escolhido];
    int atk = ataque[atacante][ativo[atacante]];
    int def = defesa[defensor][ativo[defensor]];
    

    int dano = ((2 * nivel + 10) * poder_ataque * atk / def / 250) + 2;
    

    if((tipo_ataque[ativo[atacante]][ataque_escolhido] == 1 && tipos[defensor][ativo[defensor]] == 3) ||
       (tipo_ataque[ativo[atacante]][ataque_escolhido] == 3 && tipos[defensor][ativo[defensor]] == 2) ||
       (tipo_ataque[ativo[atacante]][ataque_escolhido] == 2 && tipos[defensor][ativo[defensor]] == 1)) {
        dano = (dano * 3) / 2;
        printf("SUPER EFETIVO! ");
    }
    
    return (dano < 1) ? 1 : dano;
}

int tem_pokemon_vivo(int jogador) {
    for(int i = 0; i < 3; i++) {
        if(hp[jogador][i] > 0) return 1;
    }
    return 0;
}

void escolher_pokemon(int jogador) {
    printf("\n%s, escolha pokemon:\n", jogadores[jogador]);
    for(int i = 0; i < 3; i++) {
        if(hp[jogador][i] > 0) 
            printf("[%d] %s (HP: %d)\n", i+1, pokemons[i], hp[jogador][i]);
        else
            printf("[X] %s (DESMAIADO)\n", pokemons[i]);
    }
    
    int escolha;
    do {
        printf("Escolha: ");
        scanf("%d", &escolha);
    } while(escolha < 1 || escolha > 3 || hp[jogador][escolha-1] <= 0);
    
    ativo[jogador] = escolha - 1;
}

int escolher_ataque(int jogador) {
    printf("\n%s, escolha ataque:\n", jogadores[jogador]);
    for(int i = 0; i < 4; i++) 
        printf("[%d] %s (Poder: %d)\n", i+1, ataques[ativo[jogador]][i], poder[ativo[jogador]][i]);
    
    int escolha;
    do {
        printf("Escolha: ");
        scanf("%d", &escolha);
    } while(escolha < 1 || escolha > 4);
    
    return escolha - 1;
}

void executar_turno(int atacante, int defensor) {
    int ataque_escolhido = escolher_ataque(atacante);
    int dano = calcular_dano(atacante, defensor, ataque_escolhido);
    
    hp[defensor][ativo[defensor]] -= dano;
    if(hp[defensor][ativo[defensor]] < 0) hp[defensor][ativo[defensor]] = 0;
    
    printf("%s usou %s! Dano: %d (%d HP restante)\n", 
           pokemons[ativo[atacante]], ataques[ativo[atacante]][ataque_escolhido], 
           dano, hp[defensor][ativo[defensor]]);
    
    if(hp[defensor][ativo[defensor]] == 0) {
        printf("%s desmaiou!\n", pokemons[ativo[defensor]]);
        if(tem_pokemon_vivo(defensor)) {
            escolher_pokemon(defensor);
        }
    }
}

void mostrar_status() {
    printf("\n%s: %s (%d HP) vs %s: %s (%d HP)\n", 
           jogadores[0], pokemons[ativo[0]], hp[0][ativo[0]],
           jogadores[1], pokemons[ativo[1]], hp[1][ativo[1]]);
}

int main() {
    printf("Jogador 1: "); scanf("%s", jogadores[0]);
    printf("Jogador 2: "); scanf("%s", jogadores[1]);
    
    printf("\n--- BATALHA POKEMON ---\n");
    

    escolher_pokemon(0);
    escolher_pokemon(1);
    
    int turno = 1;
    while(tem_pokemon_vivo(0) && tem_pokemon_vivo(1)) {
        printf("\n=== Turno %d ===\n", turno);
        mostrar_status();
        
        executar_turno(0, 1);
        if(!tem_pokemon_vivo(1)) break;
        
        executar_turno(1, 0);
        turno++;
    }
    
    printf("\n=== VITORIA ===\n");
    printf("🎉 %s venceu!\n", tem_pokemon_vivo(0) ? jogadores[0] : jogadores[1]);
    
    return 0;
}