#include <iostream>
#include <memory>
#define MAXV 1000
using namespace std;

struct Engenode
{
    int y;                  //информация о смежности
    int weight;             //вес ребра
    Engenode *next;         //следующее ребро в списке
};

struct Vertice
{
    string name;
    //Node(int i, string n) : index(i), name(n) {}
};

class Graph
{
public:
    Vertice* vertices[MAXV+1];
    Engenode* edges[MAXV+1];
//    unique_ptr<Engenode*> edges[MAXV+1];
    int degree[MAXV+1];       //степень каждой вершины
    int nvertices;            //кол-во вершин в графе
    int nedges;               //кол-во ребер в графе
    bool directed;            //граф ориентированный?
    Graph(bool d) : nvertices(0), nedges(0), directed(d)
    {
        int i;
        for(i=1; i<=MAXV; i++) {
            degree[i] = 0;
            edges[i] = nullptr;
        }
    }
    ~Graph()
    {
        for(int i=0; i<nedges; i++) delete edges[i];
    }
    void read();
    void insertEdge(int x, int y, bool d);
    void addNode(string name);
    void addEdge(int x, int y);
    void print();
    void showInfo();
};

void Graph::read()
{
    int m;                          //количество вершин
    int x, y;                       //вершины в ребре(x,y)
    cout << "Insert vertices count"<< endl;
    cin >> nvertices;
    cout << "Insert m (edges count)"<< endl;
    cin >> m;
    for(int i=1; i<=m; i++) {
        cout << "x for edge " << i << endl;
        cin >> x;
        cout << "y for edge " << i << endl;
        cin >> y;
        insertEdge(x, y, directed);
    }
}

void Graph::addNode(string s)
{
    Vertice *v = new Vertice;
    v->name = s;
    vertices[nvertices] = v;
    nvertices++;
}

void Graph::insertEdge(int x, int y, bool directed)
{
    Engenode* p = new Engenode;
    p->weight = 0;
    p->y = y;
    p->next = edges[x];
    edges[x] = p;
    degree[x]++;
    if(!directed) {
        nedges++;
        insertEdge(y,x,true);
    }
    else
        nedges++;
}

void Graph::addEdge(int x, int y)
{
    bool flag {false};
    if((x>nvertices) || (y>nvertices) || (x==y)) flag = true;
    if(!flag) {
        Engenode* p = new Engenode;
        for(int i=1; i<=nvertices; i++){
            p = edges[i];
            while(p!=nullptr) {
                if((i==x) && (p->y == y)) {
                    cout << "Repeat!!!" << endl;
                    flag = true;
                    break;
                }
                p = p->next;
            }
            if(flag) break;
        }
        if(!flag) insertEdge(x, y, directed);
    }
}

void Graph::print()
{
//    unique_ptr<Engenode> p(new Engenode);
    Engenode* p = new Engenode;
    for(int i=1; i<=nvertices; i++) {
        cout << i << ":  ";
        p = edges[i];
        while(p!=nullptr) {
            cout << p->y;
            p = p->next;
        }
        cout << endl;
    }
    delete p;
}

void Graph::showInfo()
{
    cout << "Directed: " << directed << endl;
    cout << "Vertices count: " << nvertices << endl;
    cout << "Edges count: " << nedges << endl;
}

class User
{
private:
    string m_name;  //имя
public:
    User(string n) : m_name(n) {}
    void setName(string s)  {m_name = s;}
    string name()       {return m_name;}
};

class Chat : public Graph
{
private:
    int m_quantity;
    User* m_users[MAXV+1];
public:
    Chat(bool b,int i) : Graph(b), m_quantity(i) {}
    void addUser(User*);
};
void Chat::addUser(User* newUser)
{
    addNode(newUser->name());
    m_users[m_quantity] = newUser;
}

int main()
{
    Chat* chat = new Chat(false, 0);
    User* user1 = new User("zel");
    User* user2 = new User("anna");
    chat->addUser(user1);
    chat->addUser(user2);
    chat->addEdge(1,2);
    chat->showInfo();
    chat->print();




//    unique_ptr<Graph> graph(new Graph(true));
//    graph->read();
//    graph->print();
//    graph->addEdge(3, 9);

//    graph->showInfo();
//    graph->print();
    return 0;
}
