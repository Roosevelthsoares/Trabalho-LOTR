#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
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

    public:
        Soldado(string nome="soldado", int saude=100, int poder_ataque=10):
            nome(nome), saude(saude),vida_inicial(saude), poder_ataque(poder_ataque){}

        Soldado(const Soldado &p):
            nome(p.nome), saude(p.saude), vida_inicial(p.saude), poder_ataque(p.poder_ataque){}
        
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
            // cout<<"Elfo "<< this->nome <<" atacando!"<<endl;
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
                case 2:{ /* CHANCE DE DESVIO 30% */
                    if(chance >= 35 && chance <= 65){
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
                // cout<<"Anao "<<this->nome<<" ATACANDO!"<<endl;
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
            // cout<<"Humano "<<this->nome<<" ATACANDO!"<<endl;
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

class Orc: public Soldado{
    public:
        Orc(string nome, int saude, int poder_ataque):
            Soldado(nome, saude, poder_ataque * 1.1){} //10% de bonus de poder de ataque
        
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
            Soldado(nome, saude*10, poder_ataque){}

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
            Soldado(nome, saude * 9, poder_ataque * 3){}

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

// class Bem{
//     protected:
//         void poderProtagonista(){

//         }

//         void ataqueCombinado(){

//         }

// };

// class Mal{
//     protected:

// };

// class MuitoMal{
//     protected:

// };

Soldado batalha(vector<Soldado *> &vec){
    int cont = 1;
    while(vec.size() > 1){
        srand(time(NULL));
        random_shuffle(vec.begin(), vec.end());

        auto it = vec.rbegin();
        Soldado *guerreiro1 = *it;
        vec.pop_back();

        it = vec.rbegin();
        Soldado *guerreiro2 = *it;
        vec.pop_back();
        
        cout<<"==========> Batalha "<<cont<<" <=========="<<endl;
        while(true){
            cout<< "\n" <<guerreiro1->getNome() <<" atacou "<< guerreiro2->getNome() <<"."<<endl;
            guerreiro1->atacar(*guerreiro2);
            cout<<"Agora "<< guerreiro2->getNome() << " tem "<<guerreiro2->getSaude()<<" de vida."<<endl;
            if (guerreiro2->getSaude() == 0){
                cout<<guerreiro2->getNome()<<" esta morto."<<endl;
                vec.push_back(guerreiro1);
                break;
            }

            cout<< guerreiro2->getNome() <<" atacou "<< guerreiro1->getNome() <<"."<<endl;
            guerreiro2->atacar(*guerreiro1);
            cout<<"Agora "<< guerreiro1->getNome() << " tem "<<guerreiro1->getSaude()<<" de vida."<<endl;
            if (guerreiro1->getSaude() == 0){
                cout<<guerreiro1->getNome()<<" esta morto."<<endl;
                vec.push_back(guerreiro2);
                break;
            }
        }
        cout<<"Vencedor da batalha "<< cont <<": ";
        if(guerreiro1->getSaude() > 0){
            cout<<guerreiro1->getNome()<<endl;
            cout<<"\n"<<endl;

        }
        else if(guerreiro2->getSaude() > 0){
            cout<<guerreiro2->getNome();
            cout<<"\n"<<endl;
        }

        cont++;
    }

    return *(vec.at(0));
}

ostream& operator<<(ostream &os, const Soldado &s){
    os << s.nome;
    return os;
}


int main(){
    srand(time(0));
    Mago *Gandalf = new Mago("Gandalf", 100, 20);
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

    Elfo *E_Balrieth = new Elfo("E_Balrieth", 100, 20);
    Elfo *E_Mirarel = new Elfo("E_Mirarel", 100, 20);
    Elfo *E_Shaorin = new Elfo("E_Shaorin", 100, 20);
    Elfo *E_Aranhad = new Elfo("E_Aranhad", 100, 20);
    Elfo *E_Elorin = new Elfo("E_Elorin", 100, 20);

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


    vector<Soldado *> guerreiros {
        Gandalf, sauron,
        O_Pridehammer, O_Bobrum, O_Vicnan, O_Otimorn, O_Rilug, O_Yakgnath, O_Tog, O_Dhob, O_Ombilge, O_Elnan,
        E_Balrieth, E_Mirarel, E_Shaorin, E_Aranhad, E_Elorin,
        H_Xahidey, H_Liand, H_Tyan, H_Jensa, H_Barret,
        A_Thostili, A_Dolrur, A_Boforic, A_Fruian, A_Hatrom
    };


    Soldado vencedor = batalha(guerreiros);
    string nomeVencedor = vencedor.getNome();
    transform(nomeVencedor.begin(), nomeVencedor.end(), nomeVencedor.begin(), ::toupper);
    cout<<"\n\nO grande vencedor da batalha eh "<< nomeVencedor <<"!"<<endl;

    return 0;
}