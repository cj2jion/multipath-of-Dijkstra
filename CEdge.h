
class CEdge{
private:
     int head,tail;
     int weight, capacity;
public:
     CEdge(int, int, int, int);
     CEdge(int a, int b, int c);
     CEdge(CEdge*);
     ~CEdge();
     int gethead();
     int gettail();
     int getweight();
     int getcapacity();
     bool operator<(CEdge& x);

};
CEdge::CEdge(int a, int b,int c, int d)
{
    head=a;
    tail=b;
    weight=c;
    capacity=d;
}

CEdge::~CEdge()
{

}
int CEdge::gethead()
{
    return head;
}

int CEdge::gettail()
{
    return tail;
}
int CEdge::getweight()
{
    return weight;
}
int CEdge::getcapacity()
{
    return capacity;
}
bool CEdge:: operator<(CEdge& x)
{
    if(weight< x.weight)
        return true;
    else
        return false;
}
