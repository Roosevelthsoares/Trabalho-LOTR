#include <iostream>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <algorithm>
#include <cctype>
#include <random>

using namespace std;

class Soldado{
    friend ostream& operator<<(ostream &os, const Soldado &s);

    protected:
        string nome;
        int saude;
        int vida_inicial;
        int poder_ataque;
        bool evil;

    public:
        Soldado(string nome="soldado", int saude=100, int poder_ataque=10):
            nome(nome), saude(saude),vida_inicial(saude), poder_ataque(poder_ataque), evil(false){}

        Soldado(const Soldado &p):
            nome(p.nome), saude(p.saude), vida_inicial(p.saude), poder_ataque(p.poder_ataque), evil(p.evil){}
        
        virtual ~Soldado(){}

        virtual void atacar(Soldado &enemy){
            int dano = poder_ataque;
            cout<<"Atacando como soldado"<<endl;
            enemy.defender(dano, *this);
        }

        virtual void defender(int dano, Soldado &atacker){
            saude -=  dano;
            cout<<"Defendendo como soldado"<<endl;
            if(saude < 0){
                saude = 0;
            }
            if(false){
                atacar(atacker);
            }
        }

        string getNome(){return nome;}

        int getSaude(){return saude;}
        void setSaude(int p){ saude = p;}

        int getVidaInicial(){return vida_inicial;}
        void setVidaInicial(int p){ vida_inicial = p;}

        int getPoder(){return poder_ataque;}

        bool getEvil(){ return evil;}
};

class Elfo: public Soldado{
    public:
        Elfo(string nome="elfo", int saude=100, int poder_ataque=20):
            Soldado(nome, saude, poder_ataque + 1){}
        
        virtual ~Elfo(){}

        virtual void atacar(Soldado &enemy) override {
            mt19937 gen(rand());

            int limiteInferior = (int)(poder_ataque - (poder_ataque * 0.2));
            int limiteSuperior = (int)(poder_ataque + (poder_ataque * 0.2));

            uniform_int_distribution<int> distribuicao(limiteInferior, limiteSuperior);

            int dano = distribuicao(gen);
            enemy.defender(dano, *this);
        }

        virtual void defender(int dano, Soldado &atacker) override {
            int chance = 1 + rand() % 100;
            int defesa = 1 + rand() % 3;

            switch(defesa){
                case 1:{ /* CHANCE DE BLOQUEIO 10% */
                    if(chance >= 45 && chance <= 55){
                        cout<<"O elfo "<< nome <<" BLOQUEOU o ataque."<<endl;
                    }
                    else{
                        saude -=  dano;
                        cout<<"O elfo "<< nome <<" tentou BLOQUEAR, mas nao conseguiu!"<<endl;
                        if(saude < 0){
                            saude = 0;
                        }
                    }
                    break;
                }
                case 2:{ /* CHANCE DE DESVIO 40% */
                    if(chance >= 30 && chance <= 70){
                        cout<<"O elfo "<< nome <<" DESVIOU do ataque."<<endl;
                    }
                    else{
                        saude -=  dano;
                        cout<<"elfo "<< nome <<" tentou DESVIAR, mas nao conseguiu!"<<endl;
                        if(saude < 0){
                            saude = 0;
                        }
                    }
                    break;
                }
                case 3:{ /* CHANCE DE CONTRA-ATAQUE 20% ( PENSAR COMO CONTRA-ATACAR) */
                    if(chance >= 40 && chance <= 60){
                        cout<<"O elfo "<< nome <<" CONTRA ATACOU."<<endl;
                        atacar(atacker);
                    }
                    break;
                }
            }
        }
};

class Anao:public Soldado{
    public:
        Anao(string nome="anao", int saude=100, int poder_ataque=20):
            Soldado(nome, saude, poder_ataque + 20){}
        
        virtual ~Anao(){}
            
        virtual void atacar(Soldado &enemy) override { //necessário passar por referêcia para modificar o valor
            int chance = 1 + rand() % 100;
            
            if(chance >= 30 && chance <= 70){ //chance de errar
                cout<<"O anao "<<this->nome<<" ERROU o ataque!"<<endl;
            }
            else{
                mt19937 gen(rand());

                int limiteInferior = (int)(poder_ataque - (poder_ataque * 0.2));
                int limiteSuperior = (int)(poder_ataque + (poder_ataque * 0.2));

                uniform_int_distribution<int> distribuicao(limiteInferior, limiteSuperior);

                int dano = distribuicao(gen);
                enemy.defender(dano, *this);
            }
        }

        virtual void defender(int dano, Soldado &atacker) override {
            int chance = 1 + rand() % 100;
            int defesa = 1 + rand() % 3;

            switch(defesa){
                case 1:{ /* CHANCE DE BLOQUEIO 30% */
                    if(chance >= 35 && chance <= 65){
                        cout<<"O anao "<< nome <<" BLOQUEOU o ataque!"<<endl;
                    }
                    else{
                        saude -= dano;
                        cout<<"O anao "<< nome <<" tentou BLOQUEAR, mas nao conseguiu!"<<endl;
                        if(saude < 0){
                            saude = 0;
                        }
                    }
                    break;
                }
                case 2:{ /* CHANCE DE DESVIO 10% */
                    if(chance >= 45 && chance <= 55){
                        cout<<"O anao "<< nome <<" DESVIOU do ataque."<<endl;
                    }
                    else{
                        saude -=  dano;
                        cout<<"O anao "<< nome <<" tentou DESVIAR, mas nao conseguiu!"<<endl;
                        if(saude < 0){
                            saude = 0;
                        }
                    }
                    break;
                }
                case 3:{ /* CHANCE DE CONTRA-ATAQUE 10% */
                    if (chance >= 45 && chance <= 55){
                        cout<<"O anao "<< nome <<" CONTRA ATACOU."<<endl;
                        atacar(atacker);
                    }
                    break;
                }
            }
        }
};

class Humano:public Soldado{
    public:
        Humano(string nome, int saude, int poder_ataque):
            Soldado(nome, saude, poder_ataque){}
        
        virtual ~Humano(){}

        virtual void atacar(Soldado &enemy) override {
            int chance = (1+rand()%100);
            
            mt19937 gen(rand());

            int limiteInferior = (int)(poder_ataque - (poder_ataque * 0.2));
            int limiteSuperior = (int)(poder_ataque + (poder_ataque * 0.2));

            uniform_int_distribution<int> distribuicao(limiteInferior, limiteSuperior);

            int dano = distribuicao(gen);
            
            if(chance >= 45 && chance <= 55){ //chance de ataque duplo 10%
                dano *= 2;
                cout<<enemy.getNome()<<" tomou um ATAQUE DUPLO!"<<endl;
            }
            enemy.defender(dano, *this);
        }

        virtual void defender(int dano, Soldado &atacker) override {
            int chance = 1 + rand() % 100;
            int defesa = 1 + rand() % 3;

            switch(defesa){
                case 1:{ /* CHANCE DE BLOQUEIO 10% */
                    if(chance >= 45 && chance <= 55){
                        cout<<"O humano "<< nome <<" BLOQUEOU o ataque."<<endl;
                    }
                    else{
                        saude -=  dano;
                        cout<<"O humano "<< nome <<" tentou BLOQUEAR, mas nao conseguiu!"<<endl;
                        if(saude < 0){
                            saude = 0;
                        }
                    }
                    break;
                }
                case 2:{ /* CHANCE DE DESVIO 20% */
                    if(chance >= 40 && chance <= 60){
                        cout<<"O humano "<< nome <<" DESVIOU o ataque."<<endl;
                    }
                    else{
                        saude -=  dano;
                        cout<<"O humano "<< nome <<" tentou DESVIAR, mas nao conseguiu!"<<endl;
                        if(saude < 0){
                            saude = 0;
                        }
                    }
                    break;
                }
                case 3:{ /* CHANCE DE CONTRA-ATAQUE 30% */
                    if(chance >= 35 && chance <= 65){
                        cout<<"O humano "<< nome <<" CONTRA ATACOU."<<endl;
                        atacar(atacker);
                    }
                    break;
                }
            }
        }
};

class Ents: public Soldado{
    public:
        Ents(string nome, int saude, int poder_ataque):
        Soldado(nome, saude*1.5, poder_ataque*0.5){}

        virtual ~Ents(){};

        virtual void atacar(Soldado &enemy) override {
            int chance = (1+rand()%100);
            
            mt19937 gen(rand());

            int limiteInferior = (int)(poder_ataque - (poder_ataque * 0.2));
            int limiteSuperior = (int)(poder_ataque + (poder_ataque * 0.2));

            uniform_int_distribution<int> distribuicao(limiteInferior, limiteSuperior);
            int dano = distribuicao(gen);

            if(chance >= 46 && chance <= 54){ // 8% de chance de ataque duplo
                dano *= 2;
                cout<<enemy.getNome()<<" tomou um ATAQUE DUPLO!"<<endl;
            }
            enemy.defender(dano, *this);
        }

        virtual void defender(int dano, Soldado &atacker) override {
            int chance = 1 + rand() % 100;
            int defesa = 1 + rand() % 3;

            switch(defesa){
                case 1:{ /* CHANCE DE BLOQUEIO 40% */
                    if(chance >= 30 && chance <= 70){
                        cout<<"O ent "<< nome <<" BLOQUEOU o ataque."<<endl;
                    }
                    else{
                        saude -=  dano;
                        cout<<"O ent "<< nome <<" tentou BLOQUEAR, mas nao conseguiu!"<<endl;
                        if(saude < 0){
                            saude = 0;
                        }
                    }
                    break;
                }
                case 2:{ /* CHANCE DE DESVIO 6% */
                    if(chance >= 47 && chance <= 53){
                        cout<<"O ent "<< nome <<" DESVIOU o ataque."<<endl;
                    }
                    else{
                        saude -=  dano;
                        cout<<"O ent "<< nome <<" tentou DESVIAR, mas nao conseguiu!"<<endl;
                        if(saude < 0){
                            saude = 0;
                        }
                    }
                    break;
                }
                case 3:{ /* CHANCE DE CONTRA-ATAQUE 10% */
                    if(chance >= 45 && chance <= 55){
                        cout<<"O ent "<< nome <<" CONTRA ATACOU."<<endl;
                        atacar(atacker);
                    }
                    break;
                }
            }
        }
};

class Balrog: public Soldado{
    public:
        Balrog(string nome, int saude, int poder_ataque):
        Soldado(nome, saude * 3, poder_ataque){evil = true;}

        virtual ~Balrog(){};

        virtual void atacar(Soldado &enemy) override {
            int chance = (1+rand()%100);
            
            mt19937 gen(rand());

            int limiteInferior = (int)(poder_ataque - (poder_ataque * 0.2));
            int limiteSuperior = (int)(poder_ataque + (poder_ataque * 0.2));

            uniform_int_distribution<int> distribuicao(limiteInferior, limiteSuperior);
            int dano = distribuicao(gen);

            if(chance >= 37 && chance <= 63){ // 26% de chance de ataque duplo
                dano *= 2;
                cout<<enemy.getNome()<<" tomou um ATAQUE DUPLO!"<<endl;
            }
            enemy.defender(dano, *this);
        }

        virtual void defender(int dano, Soldado &atacker) override {
            int chance = 1 + rand() % 100;
            int defesa = 1 + rand() % 3;

            switch(defesa){
                case 1:{ /* CHANCE DE BLOQUEIO 30% */
                    if(chance >= 35 && chance <= 65){
                        cout<<"O balrog "<< nome <<" BLOQUEOU o ataque."<<endl;
                    }
                    else{
                        saude -=  dano;
                        cout<<"O balrog "<< nome <<" tentou BLOQUEAR, mas nao conseguiu!"<<endl;
                        if(saude < 0){
                            saude = 0;
                        }
                    }
                    break;
                }
                case 2:{ /* CHANCE DE DESVIO 6% */
                    if(chance >= 47 && chance <= 53){
                        cout<<"O balrog "<< nome <<" DESVIOU o ataque."<<endl;
                    }
                    else{
                        saude -=  dano;
                        cout<<"O balrog "<< nome <<" tentou DESVIAR, mas nao conseguiu!"<<endl;
                        if(saude < 0){
                            saude = 0;
                        }
                    }
                    break;
                }
                case 3:{ /* CHANCE DE CONTRA-ATAQUE 10% */
                    if(chance >= 45 && chance <= 55){
                        cout<<"O balrog "<< nome <<" CONTRA ATACOU."<<endl;
                        atacar(atacker);
                    }
                    break;
                }
            }
        }
};

class Dragao: public Soldado{
    public:
        Dragao(string nome, int saude, int poder_ataque):
        Soldado(nome, saude * 2, poder_ataque){evil = true;}

        virtual ~Dragao(){};

        virtual void atacar(Soldado &enemy) override {
            int chance = (1+rand()%100);
            
            mt19937 gen(rand());

            int limiteInferior = (int)(poder_ataque - (poder_ataque * 0.2));
            int limiteSuperior = (int)(poder_ataque + (poder_ataque * 0.2));

            uniform_int_distribution<int> distribuicao(limiteInferior, limiteSuperior);
            int dano = distribuicao(gen);

            if(chance >= 45 && chance <= 55){ // 20% de chance de ataque duplo
                dano *= 2;
                cout<<enemy.getNome()<<" tomou um ATAQUE DUPLO!"<<endl;
            }
            enemy.defender(dano, *this);
        }

        virtual void defender(int dano, Soldado &atacker) override {
            int chance = 1 + rand() % 100;
            int defesa = 1 + rand() % 3;

            switch(defesa){
                case 1:{ /* CHANCE DE BLOQUEIO 8% */
                    if(chance >= 46 && chance <= 54){
                        cout<<"O dragao "<< nome <<" BLOQUEOU o ataque."<<endl;
                    }
                    else{
                        saude -=  dano;
                        cout<<"O dragao "<< nome <<" tentou BLOQUEAR, mas nao conseguiu!"<<endl;
                        if(saude < 0){
                            saude = 0;
                        }
                    }
                    break;
                }
                case 2:{ /* CHANCE DE DESVIO 16% */
                    if(chance >= 42 && chance <= 58){
                        cout<<"O dragao "<< nome <<" DESVIOU o ataque."<<endl;
                    }
                    else{
                        saude -=  dano;
                        cout<<"O dragao "<< nome <<" tentou DESVIAR, mas nao conseguiu!"<<endl;
                        if(saude < 0){
                            saude = 0;
                        }
                    }
                    break;
                }
                case 3:{ /* CHANCE DE CONTRA-ATAQUE 8% */
                    if(chance >= 46 && chance <= 54){
                        cout<<"O dragao "<< nome <<" CONTRA ATACOU."<<endl;
                        atacar(atacker);
                    }
                    break;
                }
            }
        }
};

class Orc: public Soldado{
    public:
        Orc(string nome, int saude, int poder_ataque):
            Soldado(nome, saude, poder_ataque * 1.1){evil = true;} //10% de bonus de poder de ataque
        
        virtual ~Orc(){}

        virtual void atacar(Soldado &enemy) override {
            int chance = (1+rand()%100);
            
            mt19937 gen(rand());

            int limiteInferior = (int)(poder_ataque - (poder_ataque * 0.2));
            int limiteSuperior = (int)(poder_ataque + (poder_ataque * 0.2));

            uniform_int_distribution<int> distribuicao(limiteInferior, limiteSuperior);
            int dano = distribuicao(gen);

            if(chance >= 40 && chance <= 60){ // 20% de chance de ataque duplo
                dano *= 2;
                cout<<enemy.getNome()<<" tomou um ATAQUE DUPLO!"<<endl;
            }
            // cout<<"Orc "<<this->nome<<" ATACANDO!"<<endl;
            enemy.defender(dano, *this);
        }

        virtual void defender(int dano, Soldado &atacker) override {
            int chance = 1 + rand() % 100;
            int defesa = 1 + rand() % 3;

            switch(defesa){
                case 1:{ /* CHANCE DE BLOQUEIO 20% */
                    if(chance >= 40 && chance <= 60){
                        cout<<"O orc "<< nome <<" BLOQUEOU o ataque."<<endl;
                    }
                    else{
                        saude -=  dano;
                        cout<<"O orc "<< nome <<" tentou BLOQUEAR, mas nao conseguiu!"<<endl;
                        if(saude < 0){
                            saude = 0;
                        }
                    }
                    break;
                }
                case 2:{ /* CHANCE DE DESVIO 20% */
                    if(chance >= 40 && chance <= 60){
                        cout<<"O orc "<< nome <<" DESVIOU o ataque."<<endl;
                    }
                    else{
                        saude -=  dano;
                        cout<<"O orc "<< nome <<" tentou DESVIAR, mas nao conseguiu!"<<endl;
                        if(saude < 0){
                            saude = 0;
                        }
                    }
                    break;
                }
                case 3:{ /* CHANCE DE CONTRA-ATAQUE 20% */
                    if(chance >= 40 && chance <= 60){
                        cout<<"O orc "<< nome <<" CONTRA ATACOU."<<endl;
                        atacar(atacker);
                    }
                    break;
                }
            }
        }
};

class Sauron: public Soldado{
    public:
        Sauron(string nome, int saude, int poder_ataque):
            Soldado(nome, saude*10, poder_ataque){evil = true;}

        virtual ~Sauron(){}

        virtual void atacar(Soldado &enemy) override {
            int chance = (1+rand()%100);
            
            mt19937 gen(rand());

            int limiteInferior = (int)(poder_ataque - (poder_ataque * 0.2));
            int limiteSuperior = (int)(poder_ataque + (poder_ataque * 0.2));

            uniform_int_distribution<int> distribuicao(limiteInferior, limiteSuperior);
            int dano = distribuicao(gen);

            if(chance >= 35 && chance <= 65){ //30% de chance de acertar um ataque duplo
                dano *= 2;
                cout<<enemy.getNome()<<" tomou um ATAQUE DUPLO!"<<endl;
            }
            // cout<<this->nome<<" ATACANDO!"<<endl;
            enemy.defender(dano, *this);
        }

        virtual void defender(int dano, Soldado &atacker) override {
            int chance = 1 + rand() % 100;
            int defesa = 1 + rand() % 3;

            switch(defesa){
                case 1:{ /* CHANCE DE BLOQUEIO 30% */
                    if(chance >= 35 && chance <= 65){
                        cout<< nome <<" BLOQUEOU o ataque."<<endl;
                    }
                    else{
                        saude -=  dano;
                        cout<< nome <<" tentou BLOQUEAR, mas nao conseguiu!"<<endl;
                        if(saude < 0){
                            saude = 0;
                        }
                    }
                    break;
                }
                case 2:{ /* CHANCE DE DESVIO 10% */
                    if(chance >= 45 && chance <= 55){
                        cout<< nome <<" DESVIOU o ataque."<<endl;
                    }
                    else{
                        saude -=  dano;
                        cout<< nome <<" tentou DESVIAR, mas nao conseguiu!"<<endl;
                        if(saude < 0){
                            saude = 0;
                        }
                    }
                    break;
                }
                case 3:{ /* CHANCE DE CONTRA-ATAQUE 30% */
                    if(chance >= 35 && chance <= 65){
                        cout<< nome <<" CONTRA ATACOU."<<endl;
                        atacar(atacker);
                    }
                    break;
                }
            }
        }
};

class Mago: public Soldado{ 
    public:
        Mago(string nome, int saude, int poder_ataque):
            Soldado(nome, saude * 8, poder_ataque * 2){}

        virtual ~Mago(){}

        virtual void atacar(Soldado &enemy) override {
            int chance = (1+rand()%100);
            
            mt19937 gen(rand());

            int limiteInferior = (int)(poder_ataque - (poder_ataque * 0.2));
            int limiteSuperior = (int)(poder_ataque + (poder_ataque * 0.2));

            uniform_int_distribution<int> distribuicao(limiteInferior, limiteSuperior);
            int dano = distribuicao(gen);

            if(chance >= 25 && chance <= 75){ // 50% de chance de ataque duplo
                dano *= 2;
                cout<<enemy.getNome()<<" tomou um ATAQUE DUPLO!"<<endl;
            }
            // cout<<this->nome<<" ATACANDO!"<<endl;
            enemy.defender(dano, *this);
        }

        virtual void defender(int dano, Soldado &atacker) override {
            int chance = 1 + rand() % 100;
            int defesa = 1 + rand() % 3;

            switch(defesa){
                case 1:{ /* CHANCE DE BLOQUEIO 10% */
                    if(chance >= 45 && chance <= 55){
                        cout<< nome <<" BLOQUEOU o ataque!"<<endl;
                    }
                    else{
                        saude -=  dano;
                        cout<< nome <<" tentou BLOQUEAR, mas nao conseguiu!"<<endl;
                        if(saude < 0){
                            saude = 0;
                        }
                    }
                    break;
                }
                case 2:{ /* CHANCE DE DESVIO 30% */
                    if(chance >= 35 && chance <= 65){
                        cout<< nome <<" DESVIOU do ataque!"<<endl;
                    }
                    else{
                        saude -=  dano;
                        cout<< nome <<" tentou DESVIAR, MAS nao conseguiu!"<<endl;
                        if(saude < 0){
                            saude = 0;
                        }
                    }
                    break;
                }
                case 3:{ /* CHANCE DE CONTRA-ATAQUE 30% */
                    if(chance >= 35 && chance <= 65){
                        cout<< nome <<" CONTRA ATACOU."<<endl;
                        atacar(atacker);
                    }
                    break;
                }
            }
        }
};

deque<Soldado *>& batalha(deque<Soldado *> &bem, deque<Soldado *> &mal){
    int cont = 1;
    random_shuffle(bem.begin(), bem.end());
    random_shuffle(mal.begin(), mal.end());

    while(bem.size() != 0 && mal.size() != 0){

        Soldado *guerreiro_bom = bem.front();
        bem.pop_front();

        Soldado *guerreiro_mal = mal.front();
        mal.pop_front();
        
        cout<<"==========> Batalha "<<cont<<" <=========="<<endl;
        while(true){
            cout<< "\n" <<guerreiro_bom->getNome() <<" atacou "<< guerreiro_mal->getNome() <<"."<<endl;
            guerreiro_bom->atacar(*guerreiro_mal);
            cout<<"Agora "<< guerreiro_mal->getNome() << " tem "<<guerreiro_mal->getSaude()<<" de vida."<<endl;
            if (guerreiro_mal->getSaude() == 0){
                cout<<guerreiro_mal->getNome()<<" esta morto."<<endl;
                bem.push_back(guerreiro_bom);
                break;
            }

            cout<< guerreiro_mal->getNome() <<" atacou "<< guerreiro_bom->getNome() <<"."<<endl;
            guerreiro_mal->atacar(*guerreiro_bom);
            cout<<"Agora "<< guerreiro_bom->getNome() << " tem "<<guerreiro_bom->getSaude()<<" de vida."<<endl;
            if (guerreiro_bom->getSaude() == 0){
                cout<<guerreiro_bom->getNome()<<" esta morto."<<endl;
                mal.push_back(guerreiro_mal);
                break;
            }
        }
        cout<<"Vencedor da batalha "<< cont <<": ";
        if(guerreiro_bom->getSaude() != 0){
            cout<<guerreiro_bom->getNome()<<endl;
            cout<<"\n"<<endl;

        }
        else if(guerreiro_mal->getSaude() != 0){
            cout<<guerreiro_mal->getNome();
            cout<<"\n"<<endl;
        }

        cont++;
    }

    if (bem.size() != 0){
        return bem;
    }
    
    return mal;
}

ostream& operator<<(ostream &os, const Soldado &s){
    os << s.nome<<"-> Vida: "<< s.saude;
    return os;
}


int main(){
    srand(time(0));
    Mago *Gandalf = new Mago("Gandalf", 100, 30);
    Sauron *sauron = new Sauron("Sauron", 100, 50);

    Orc *O_Pridehammer = new Orc("O_Pridehammer", 100, 10);
    Orc *O_Bobrum = new Orc("O_Bobrum", 100, 10);
    Orc *O_Vicnan = new Orc("O_Vicnan", 100, 10);
    Orc *O_Otimorn = new Orc("O_Otimorn", 100, 10);
    Orc *O_Rilug = new Orc("O_Rilug", 100, 10);
    Orc *O_Yakgnath = new Orc("O_Yakgnath", 100, 10);
    Orc *O_Tog = new Orc("O_Tog", 100, 10);
    Orc *O_Dhob = new Orc("O_Dhob", 100, 10);
    Orc *O_Ombilge = new Orc("O_Ombilge", 100, 10);
    Orc *O_Elnan = new Orc("O_Elnan", 100, 10);
    Orc *O_Wolfswift = new Orc("O_Wolfswift", 100, 10);
    Orc *O_Wheatchewer = new Orc("O_Wheatchewer", 100, 10);
    Orc *O_Dugorim = new Orc("O_Dugorim", 100, 10);
    Orc *O_Shageon = new Orc("O_Shageon", 100, 10);
    Orc *O_Muzgonk = new Orc("O_Muzgonk", 100, 10);

    Elfo *El_Balrieth = new Elfo("El_Balrieth", 100, 20);
    Elfo *El_Mirarel = new Elfo("El_Mirarel", 100, 20);
    Elfo *El_Shaorin = new Elfo("El_Shaorin", 100, 20);
    Elfo *El_Aranhad = new Elfo("El_Aranhad", 100, 20);
    Elfo *El_Elorin = new Elfo("El_Elorin", 100, 20);

    Humano *H_Xahidey = new Humano("H_Xahidey", 100, 20);
    Humano *H_Liand = new Humano("H_Liand", 100, 20);
    Humano *H_Tyan = new Humano("H_Tyan", 100, 20);
    Humano *H_Jensa = new Humano("H_Jensa", 100, 20);
    Humano *H_Barret = new Humano("H_Barret", 100, 20);

    Anao *A_Thostili = new Anao("A_Thostili",100, 20);
    Anao *A_Dolrur = new Anao("A_Dolrur",100, 20);
    Anao *A_Boforic = new Anao("A_Boforic",100, 20);
    Anao *A_Fruian = new Anao("A_Fruian",100, 20);
    Anao *A_Hatrom = new Anao("A_Hatrom",100, 20);

    Balrog *B_Balrog = new Balrog("B_Balrog", 100, 30);
    Balrog *B_Korgrak = new Balrog("B_Korgrak", 100, 30);

    Dragao *D_Baeloth = new Dragao("D_Baeloth", 100, 35);
    Dragao *D_Rorsirog = new Dragao("D_Rorsirog", 100, 35);
    Dragao *D_Guldroim = new Dragao("D_Guldroim", 100, 35);

    Ents *E_Sindarin = new Ents("E_Sindarin", 100, 20);
    Ents *E_Pabroth = new Ents("E_Pabroth", 100, 20);
    Ents *E_Balvroth = new Ents("E_Balvroth", 100, 20);
    Ents *E_Belfras = new Ents("E_Belfras", 100, 20);
    Ents *E_Frogar = new Ents("E_Frogar", 100, 20);


    deque<Soldado *> exercitoDeSauron {
        sauron,
        O_Pridehammer, O_Bobrum, O_Vicnan, O_Otimorn, O_Rilug, O_Yakgnath, O_Tog,
        O_Dhob, O_Ombilge, O_Elnan,O_Wolfswift,O_Wheatchewer, O_Dugorim,O_Shageon,O_Muzgonk,
        B_Balrog, B_Korgrak,
        D_Baeloth, D_Rorsirog, D_Guldroim
    };

    deque<Soldado *> sociedadeDoAnel{
        Gandalf,
        El_Balrieth, El_Mirarel, El_Shaorin, El_Aranhad, El_Elorin,
        H_Xahidey, H_Liand, H_Tyan, H_Jensa, H_Barret,
        A_Thostili, A_Dolrur, A_Boforic, A_Fruian, A_Hatrom,
        E_Sindarin, E_Pabroth, E_Balvroth, E_Belfras, E_Frogar
    };


    deque<Soldado *> exercitoVencedor = batalha(sociedadeDoAnel, exercitoDeSauron);
    string nomeVencedor = (exercitoVencedor.at(0)->getEvil()) ? "o EXERCITO DE SAURON" : "a SOCIEDADE DO ANEL";
    cout<<"\n\nO exercito vencedor da batalha foi "<< nomeVencedor <<"!"<<endl;
    cout<<"Lista de sobreviventes: "<<endl;

    auto it = exercitoVencedor.begin();
    for(it; it != exercitoVencedor.end(); it++){
        cout<< (*it)->getNome() << " -> vida: "<< (*it)->getSaude() <<endl;
    }
    return 0;
}