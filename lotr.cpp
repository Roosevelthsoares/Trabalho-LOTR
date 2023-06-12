/*
bruce e roosevelth
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

class Soldado{
    protected:
        string nome;
        int saude;
        int vida_inicial;
        int poder_ataque;
    public:
        Soldado(string nome, int saude, int poder_ataque):
            nome(nome), saude(saude),vida_inicial(saude), poder_ataque(poder_ataque){}

        Soldado(const Soldado &p):
            nome(p.nome), saude(p.saude), vida_inicial(p.saude), poder_ataque(p.poder_ataque){}

        void atacar(Soldado &enemy){ //necessário passar por referêcia para modificar o valor
            int dano = poder_ataque;
            defender(enemy, dano);
        }

        void defender(Soldado &enemy, int dano){
            enemy.saude = enemy.saude - dano;
        }

        string getNome(){return nome;}
        int getSaude(){return saude;}

        void setSaude(int p){ saude = p;}
        int getVida_inicial(){return vida_inicial;}

        void setVida_inicial(int &p){ vida_inicial = p;}
        int getPoder(){return poder_ataque;}
};

class Elfo:public Soldado{
    protected:
        int poder_ataque;//precisa disso?
    public:
        Elfo(string nome, int saude, int poder_ataque):
            Soldado(nome, saude, poder_ataque+1){
                // poder_ataque += 1;  //como criar outra maneira de ter iniciliar o bonus?
            }
        // int getPoder(){return poder_ataque;}
};

class Anao:public Soldado{
    private:
        int poder_ataque;//precisa disso?
    public:
        Anao(string nome, int saude, int poder_ataque):
            Soldado(nome, saude, poder_ataque+20){}
            
        void atacar(Soldado &oponente){ //necessário passar por referêcia para modificar o valor
            
            srand(time(0));
            int chance = (1+rand()%100);
            
            if(chance >= 1 && chance <= 40){ //chance de errar

            }
            else{
                Soldado::atacar(oponente);
            }
        }
};

class Humano:public Soldado{
    private:
        int poder_ataque; //precisa disso?
    public:
        Humano(string nome, int saude, int poder_ataque):
            Soldado(nome, saude, poder_ataque){

            }

        void atacar(Soldado &oponente){

            srand(time(0));
            int chance = (1+rand()%100);
            
            if(chance >= 1 && chance <= 10){ //chance de acertar 10%
                Soldado::atacar(oponente);
                Soldado::atacar(oponente);
            }
            else{
                Soldado::atacar(oponente);
            }
        }
};

class Sauron:public Soldado{
    public:
        Sauron(string nome, int saude, int poder_ataque):
            Soldado(nome, saude*10, poder_ataque){

            }

        void atacar(Soldado &oponente){
            srand(time(0));
            int chance = (1+rand()%100);
            
            if(chance >= 1 && chance <= 30){ //30% de chance de acertar um ataque duplo
                Soldado::atacar(oponente);
                Soldado::atacar(oponente);
            }
            else{
                Soldado::atacar(oponente);
            }
        }
};

class Orc:public Soldado{
    public:
        Orc(string nome, int saude, int poder_ataque):
            Soldado(nome, saude, poder_ataque*1.1){ //10% de bonus de poder de ataque
                
            }
        void atacar(Soldado &oponente){
            srand(time(0));
            int chance = (1+rand()%100);
            
            if(chance >= 1 && chance <= 20){ // 20% de chance de ataque duplo
                Soldado::atacar(oponente);
                Soldado::atacar(oponente);
            }
            else{
                Soldado::atacar(oponente);
            }
        }

};

class Mago:public Soldado{
    public:
        Mago(string nome, int saude, int poder_ataque):
            Soldado(nome, saude, poder_ataque){
            }
        void curar(Soldado &amigo){
            if(amigo.getSaude() != 0){ //só cura se tiver vida
            int valor = 10 + amigo.getSaude();
            amigo.setSaude(valor);
            }
        }
};

struct Confronto{
        vector <Soldado> combatentes;

        Confronto(vector <Soldado> combatentes):
            combatentes(combatentes){
        
        }

        void setCombatentes(vector <Soldado> &p){
            combatentes = p;
        }
        Soldado getCombatentes(int i){
            return combatentes[i];
        }

        void lutar(Soldado &lado1, Soldado &lado2){
            
            if(combatentes.size() != 1){

                cout << endl;
                cout << "Batalha entre " << lado1.getNome() << " (Saude: " << lado1.getSaude()<<") ";
                cout<< "e " << lado2.getNome() << " (Saude: " << lado2.getSaude() << ")" << endl;

                while(lado1.getSaude() > 0 && lado2.getSaude() > 0){

                    if(combatentes.size() == 1)
                        break;

                    if(lado1.getSaude() > 0 && lado2.getSaude() > 0){
                        cout << lado1.getNome() << " ataca " << lado2.getNome() << endl;
                        lado1.atacar(lado2);
                        if(lado2.getSaude() <= 0){
                            cout << lado2.getNome() << " morreu. ";
                            cout << lado1.getNome() << " venceu " << lado2.getNome()<<endl;
                            cout << endl;

                            combatentes[0].setSaude(combatentes[0].getVida_inicial());//reseta a vida
                            combatentes.insert(combatentes.end(), combatentes[0]); //ganhador vai pro fim
                            combatentes.erase(combatentes.begin()); //sai do inicio ganhador
                            combatentes.erase(combatentes.begin()); //sai do inicio perdedor
                            // cout << "******* size *********"<< combatentes.size() << endl;
                            if(combatentes.size() == 1){
                                cout << "CAMPEAO " << combatentes[0].getNome();
                                break;
                            }
                                break;
                        }
                        else{
                            cout << "Saude restante de "<< lado2.getNome() << " = "<<lado2.getSaude() << endl;
                        }
                    }
    
                    if(lado1.getSaude() > 0 && lado2.getSaude() > 0){
                        cout << lado2.getNome() << " ataca " << lado1.getNome() << endl;
                        lado2.atacar(lado1);

                        if(lado1.getSaude() <= 0){
                            cout << lado1.getNome() << " morreu. ";

                                cout << lado2.getNome() << " venceu " << lado1.getNome()<<endl;
                                cout << endl;

                            combatentes[1].setSaude(combatentes[1].getVida_inicial());//reseta a vida
                            combatentes.insert(combatentes.end(), combatentes[1]);
                            combatentes.erase(combatentes.begin()+1);
                            combatentes.erase(combatentes.begin());
                            // cout << "******* size *********"<< combatentes.size() << endl;
                            if(combatentes.size() == 1){
                                cout << "CAMPEAO " << combatentes[0].getNome();
                                break;
                            }
                                break;
                        }
                        else{
                            cout << "Saude restante de "<< lado2.getNome() << " = "<<lado1.getSaude() << endl;
                        }
                    }
                }
            }
        }

        void torneio(){

            static int i = 1;
            vector <Soldado> perdedores;
            while(combatentes.size() != 1){
                cout << "       LUTA: " << i << endl; 
                lutar(combatentes[0], combatentes[1]);
                i++;
            }

        }
        
};

bool Existe(int valores[], int tam, int valor){
    for(int i = 0;i<tam;i++){
        if(valores[i] == valor)
            return true;
    }
    return false;
}

void GeraAleatorios(int numeros[], int quantNumeros, int Limite){
    srand(time(0));

    int v;
    for(int i=0; i<quantNumeros; i++){
        v = rand() % Limite;
        while(Existe(numeros,i,v)){
            v = rand() % Limite;
        }
        numeros[i] = v;
    }
}


int main(){
    srand(time(NULL));

    Sauron s1("Sauron", 7, 30);
    Mago m1("Gandalf", 40, 5);

    Orc  o1("Orc 1", 50, 10);
    Orc  o2("Orc 2", 50, 10);
    Orc  o3("Orc 3", 50, 10);
    Orc  o4("Orc 4", 50, 10);
    Orc  o5("Orc 5", 50, 10);
    Orc  o6("Orc 6", 50, 10);
    Orc  o7("Orc 7", 50, 10);
    Orc  o8("Orc 8", 50, 10);
    Orc  o9("Orc 9", 50, 10);
    Orc o10("Orc 10", 50, 10);
    
    Elfo e1("Elfo 1", 50, 15);
    Elfo e2("Elfo 2", 50, 15);
    Elfo e3("Elfo 3", 50, 15);
    Elfo e4("Elfo 4", 50, 15);
    Elfo e5("Elfo 5", 50, 15);
    
    Humano h1("man 1", 40, 10);
    Humano h2("man 2", 40, 10);
    Humano h3("man 3", 40, 10);
    Humano h4("man 4", 40, 10);
    Humano h5("man 5", 40, 10);
    
    Anao a1("Anao 1", 70, 10);
    Anao a2("Anao 2", 70, 10);
    Anao a3("Anao 3", 70, 10);
    Anao a4("Anao 4", 70, 10);
    Anao a5("Anao 5", 70, 10);


    // vector <Soldado> combatentes = { m1, o1,o2,o3,o4,o5,o6,o7,o8,o9,o10, a1,a2,a3,a4,a5, h1,h2,h3,h4,h5, o1,o2,o3,o4,o5};
    // vector <Soldado> combatentes = { m1,o5,a1,a2,a3,a4,a5,s1, o1,o2,o3,o4,o5,o6,o7,o8,o9,o10,h1,h5};

    vector <Soldado> combatentes;
    Confronto c1(combatentes);

    // cout << c1.combatentes[0];

    // c1.lutar(c1.combatentes[0], c1.combatentes[1]);
    // c1.lutar(c1.combatentes[0], c1.combatentes[1]);
    // c1.lutar(c1.combatentes[0], c1.combatentes[1]);
    // c1.lutar(c1.combatentes[0], c1.combatentes[1]);
    
    c1.combatentes.push_back(s1);
    c1.combatentes.push_back(m1);
    c1.combatentes.push_back(o1);
    c1.combatentes.push_back(o2);
    c1.combatentes.push_back(o3);
    c1.combatentes.push_back(o4);
    c1.combatentes.push_back(o5);
    c1.combatentes.push_back(o6);
    c1.combatentes.push_back(o7);
    c1.combatentes.push_back(o8);
    c1.combatentes.push_back(o9);
    c1.combatentes.push_back(o10);
    c1.combatentes.push_back(e1);
    c1.combatentes.push_back(e2);
    c1.combatentes.push_back(e3);
    c1.combatentes.push_back(e4);
    c1.combatentes.push_back(e5);
    c1.combatentes.push_back(h1);
    c1.combatentes.push_back(h2);
    c1.combatentes.push_back(h3);
    c1.combatentes.push_back(h4);
    c1.combatentes.push_back(h5);
    c1.combatentes.push_back(a1);
    c1.combatentes.push_back(a2);
    c1.combatentes.push_back(a3);
    c1.combatentes.push_back(a4);
    c1.combatentes.push_back(a5);
    
    random_shuffle(c1.combatentes.begin(), c1.combatentes.end());
    c1.torneio();

    // for (int i = 0; i< combatentes.size(); i++)
    //     cout << combatentes[i].getNome() << endl;

    // for(int i=0; i<27; i++){
    //     combatentes[ordem_combates[i]];
    //     // Confronto().lutar(combatentes[ordem_combates[i]], combatentes[ordem_combates[i+1]]);
    // }
    // for(int i = 0; i<27; i++){
    //     Confronto().lutar(combatentes[ordem_combates[i]], combatentes[ordem_combates[i+1]]);
    // }



    return 0;
}