#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
// teste


using namespace std;

class Soldado{

    protected:
        string nome;
        int saude;
        int vida_inicial;
        int poder_ataque;
    public:
        Soldado(string nome, int saude, int poder_ataque):
            nome(nome), saude(saude),vida_inicial(saude), poder_ataque(poder_ataque){

            }
        Soldado(const Soldado &p):
            nome(p.nome), saude(p.saude), vida_inicial(p.saude), poder_ataque(p.poder_ataque){

            }

        void atacar(Soldado &enemy){ //necessário passar por referêcia para modificar o valor
            int dano = poder_ataque;
            defender(enemy, dano);
        }
        void defender(Soldado &enemy, int dano){
            enemy.saude = enemy.saude - dano;
        }

        string getNome(){return nome;}
        int getSaude(){return saude;}
        int setSaude(int &p){ saude = p;}
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
            Soldado(nome, saude, poder_ataque+20){
            }
            
        void atacar(Soldado &oponente){ //necessário passar por referêcia para modificar o valor
            
            srand(time(0));
            int valor = (1+rand()%10);
            
            if(valor == 1 || valor == 2 || valor == 3 || valor == 4){ //chance de errar

            }else{
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
            int valor = (1+rand()%10);
            
            if(valor == 1){ //chance de acertar 10%
                Soldado::atacar(oponente);
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
            int valor = (1+rand()%10);
            
            if(valor == 1 || valor == 2 || valor == 3){ //chance de acertar 10%
                Soldado::atacar(oponente);
                Soldado::atacar(oponente);
            }
        }
};

class Orc:public Soldado{
    public:
        Orc(string nome, int saude, int poder_ataque):
            Soldado(nome, saude, poder_ataque*1.1){ //10% de bonus
                
            }
        void atacar(Soldado &oponente){
            srand(time(0));
            int valor = (1+rand()%10);
            
            if(valor == 1 || valor == 2){ //chance de acertar 20%
                Soldado::atacar(oponente);
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
            cout << " size "<< combatentes.size() << endl;

                cout << "Batalha entre " << lado1.getNome() << " (Saude: " << lado1.getSaude()<<") ";
                cout<< "e " << lado2.getNome() << " (Saude: " << lado2.getSaude() << ")" << endl;

                while(lado1.getSaude() > 0 && lado2.getSaude() > 0){
                    if(lado1.getSaude() > 0 && lado2.getSaude() > 0){
                        cout << lado1.getNome() << " ataca " << lado2.getNome() << endl;
                        lado1.atacar(lado2);
                        if(lado2.getSaude() < 0){
                            cout << lado2.getNome() << " morreu. ";
                            // if(lado2.getSaude() <= 0){
                                cout << lado1.getNome() << " venceu " << lado2.getNome()<<endl;
                                // cout << lado2.getSaude() << endl;
                            // }

                            // combatentes.pop_back(); //sai do vector
                            combatentes.insert(combatentes.end(), combatentes[0]); //ganhador vai pro fim
                            combatentes.erase(combatentes.begin()); //sai do inicio ganhador
                            combatentes.erase(combatentes.begin()); //sai do inicio perdedor
            cout << "******* size *********"<< combatentes.size() << endl;
                            if(combatentes.size() == 1){
                                cout << "CAMPEAO " << combatentes[0].getNome();
                                break;
                            }
                        }else{
                            cout << "Saude restante de "<< lado2.getNome() << " = "<<lado2.getSaude() << endl;
                        }
                    }
 
                    if(lado1.getSaude() > 0 && lado2.getSaude() > 0){
                        cout << lado2.getNome() << " ataca " << lado1.getNome() << endl;
                        lado2.atacar(lado1);
                        if(lado1.getSaude() < 0){
                            cout << lado1.getNome() << " morreu. ";

                            // if(lado1.getSaude() <= 0){
                                cout << lado2.getNome() << " venceu " << lado1.getNome()<<endl;
                                // cout << lado1.getSaude() << endl;
                            // }
                            combatentes.insert(combatentes.end(), combatentes[1]);
                            combatentes.erase(combatentes.begin()+1);
                            combatentes.erase(combatentes.begin());
            cout << "******* size *********"<< combatentes.size() << endl;
                            if(combatentes.size() == 1){

                                cout << "CAMPEAO " << combatentes[0].getNome();
                                break;
                            }

                        }else{
                            cout << "Saude restante de "<< lado2.getNome() << " = "<<lado1.getSaude() << endl;
                        }
                    }
 
                        
                }

            // }

                // cout << "CAMPEAO " << combatentes.at(0);
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
    Sauron s1("Sauron", 100, 30);
    Mago m1("Gandolfi", 40, 5);

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


    vector <Soldado> combatentes = { m1, o1, a1, h1, o3};

    Confronto c1(combatentes);

    // cout << c1.combatentes[0];

    c1.lutar(c1.combatentes[0], c1.combatentes[1]);
    c1.lutar(c1.combatentes[0], c1.combatentes[1]);
    
    // combatentes.push_back(s1);
    // combatentes.push_back(m1);
    // combatentes.push_back(o1);
    // combatentes.push_back(o2);
    // combatentes.push_back(o3);
    // combatentes.push_back(o4);
    // combatentes.push_back(o5);
    // combatentes.push_back(o6);
    // combatentes.push_back(o7);
    // combatentes.push_back(o8);
    // combatentes.push_back(o9);
    // combatentes.push_back(o10);
    // combatentes.push_back(e1);
    // combatentes.push_back(e2);
    // combatentes.push_back(e3);
    // combatentes.push_back(e4);
    // combatentes.push_back(e5);
    // combatentes.push_back(h1);
    // combatentes.push_back(h2);
    // combatentes.push_back(h3);
    // combatentes.push_back(h4);
    // combatentes.push_back(h5);
    // combatentes.push_back(a1);
    // combatentes.push_back(a2);
    // combatentes.push_back(a3);
    // combatentes.push_back(a4);
    // combatentes.push_back(a5);
    


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