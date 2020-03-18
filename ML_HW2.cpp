#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <cfloat>
#include <queue>

using namespace std;

/*============================Seperate=Line===========================================*/
/*Variables*/

struct data
{
    int index;
    string name;
    double attr[9];
    string clazz;
    double distance=-1;
};

struct node
{
    node* parent;
    bool isLeaf;
    int splitBy;
    data d;
    int index;
    node* left;
    node* right;
};

struct int_double_pair{
    int index;
    double distance;
};

/*============================Seperate=Line===========================================*/
/*Utility*/

bool compare0(data i,data j){return (i.attr[0]<j.attr[0]);}
bool compare1(data i,data j){return (i.attr[1]<j.attr[1]);}
bool compare2(data i,data j){return (i.attr[2]<j.attr[2]);}
bool compare3(data i,data j){return (i.attr[3]<j.attr[3]);}
bool compare4(data i,data j){return (i.attr[4]<j.attr[4]);}
bool compare5(data i,data j){return (i.attr[5]<j.attr[5]);}
bool compare6(data i,data j){return (i.attr[6]<j.attr[6]);}
bool compare7(data i,data j){return (i.attr[7]<j.attr[7]);}
bool compare8(data i,data j){return (i.attr[8]<j.attr[8]);}
bool compareDis(data d1,data d2){return (d1.distance<d2.distance);}//Compare functions

void sortByAxis(vector<data> &v,int axis)
{
    switch(axis)
    {
        case 0:sort(v.begin(),v.end(),compare0);return;
        case 1:sort(v.begin(),v.end(),compare1);return;
        case 2:sort(v.begin(),v.end(),compare2);return;
        case 3:sort(v.begin(),v.end(),compare3);return;
        case 4:sort(v.begin(),v.end(),compare4);return;
        case 5:sort(v.begin(),v.end(),compare5);return;
        case 6:sort(v.begin(),v.end(),compare6);return;
        case 7:sort(v.begin(),v.end(),compare7);return;
        case 8:sort(v.begin(),v.end(),compare8);return;
    }
    return;
}

double calDistance(data d1,data d2)
{
    double p=0;
    for(int i=0;i<9;i++)
    {
        p+=pow(d1.attr[i]-d2.attr[i],2);
    }
    return p;
}

double calDistance(node* n1,node* n2)
{
    if(n1==NULL || n2==NULL)
        return DBL_MAX;
    return calDistance(n1->d, n2->d);
}

vector<data> load_csv(string file_name)
{
    vector<data> result;
    ifstream ifile(file_name);
    if(!ifile.is_open())
    {
        cout << "File not found!!" << endl;
        return result;
    }
    string tmp;
    getline(ifile,tmp);
    while(!ifile.eof())
    {
        data d;
        char dump;
        ifile >> d.index;
        ifile >> dump;
        getline(ifile,d.name,',');
        for(int i=0;i<9;i++)
        {
            ifile >> d.attr[i];
            ifile >> dump;
        }
        ifile >> d.clazz;
        result.push_back(d);
    }
    if(result[result.size()-1].index==result[result.size()-2].index)
        result.pop_back();
    ifile.close();
    return result;
}

void outputFile(vector<data> best[],vector<data> test)
{
    int size=(int)test.size();
    int correct=0;
    for(int i=0;i<size;i++)
    {
        if(best[i][0].clazz==test[i].clazz)
            correct++;
    }
    cout << "KNN accuracy: " << (double)correct/size << endl;
    for(int i=0;i<size;i++)
    {
        cout << best[i][0].index << endl;
    }
    cout << endl;
    
    correct=0;
    for(int i=0;i<size;i++)
    {
        for(int k=0;k<3;k++)
            if(best[i][k].clazz==test[i].clazz)
                correct++;
    }
    cout << "KNN accuracy: " << (double)correct/(size*3) << endl;
    for(int i=0;i<size;i++)
    {
        for(int k=0;k<3;k++)
            cout << best[i][k].index << " ";
        cout << endl;
    }
    cout << endl;
    
    correct=0;
    for(int i=0;i<size;i++)
    {
        for(int k=0;k<20;k++)
            if(best[i][k].clazz==test[i].clazz)
                correct++;
    }
    cout << "KNN accuracy: " << (double)correct/(size*20) << endl;
    for(int i=0;i<size;i++)
    {
        for(int k=0;k<20;k++)
            cout << best[i][k].index << " ";
        cout << endl;
    }
    cout << endl;
    
    correct=0;
    for(int i=0;i<size;i++)
    {
        for(int k=0;k<100;k++)
            if(best[i][k].clazz==test[i].clazz)
                correct++;
    }
    cout << "KNN accuracy: " << (double)correct/(size*100) << endl;
    for(int i=0;i<size;i++)
    {
        for(int k=0;k<100;k++)
            cout << best[i][k].index << " ";
        cout << endl;
    }
}

/*============================Seperate=Line===========================================*/
/*Debug*/

void print_vector(vector<data> v)
{
    for(int i=0;i<v.size();i++)
    {
        cout << v[i].index << " " << v[i].name << " ";
        for(int j=0;j<9;j++)
        {
            cout << v[i].attr[j] << " ";
        }
        cout << v[i].clazz << endl;
    }
}

void print_vector(vector<int> v)
{
    for(int i=0;i<v.size();i++)
    {
        cout << v[i] << " " ;
    }
    cout << endl;
}

void print_result_vector(vector<data> v)
{
    sort(v.begin(),v.end(),compareDis);
    for(int i=0;i<v.size();i++)
    {
        cout << v[i].index << " ";
    }
    cout << endl;
}

void print_vector(vector<node> v)
{
    for(int i=0;i<v.size();i++)
        cout << v[i].d.index << " ";
    cout << endl;
}

void print_tree(node* root)
{
    cout << root->index << " " << root->splitBy << " " << root->d.attr[root->splitBy] << endl << endl;
    if(root->isLeaf)
    {
        cout << "isLeaf" << endl;
        return;
    }
    cout << "left" << endl;
    print_tree(root->left);
    cout << endl << endl << "right" << endl;
    print_tree(root->right);
    return;
}

bool find_in_tree(node* root, data d)
{
    while(root)
    {
        if(d.index==root->index)
        {
            return true;
        }
        int axis=root->splitBy;
        if(d.attr[axis] < root->d.attr[axis])
            root=root->left;
        else
            root=root->right;
    }
    return false;
}

int bruteForceClosest(data pivot,vector<data> v)
{
    double best=DBL_MAX;
    int index=-1;
    for(int i=0;i<v.size();i++)
    {
        double d=calDistance(pivot,v[i]);
        if(d<best)
        {
            best=d;
            index=v[i].index;
        }
    }
    return index;
}

bool bruteForceKNN_compare(int_double_pair p1,int_double_pair p2)
{
    return (p1.distance < p2.distance);
}

vector<int> bruteForceKNN(data pivot,vector<data> &v,int k)
{
    vector<int> result;
    
    vector<int_double_pair> dis;
    for(int i=0;i<v.size();i++)
    {
        int_double_pair tmp;
        tmp.index=v[i].index;
        tmp.distance=calDistance(pivot,v[i]);
        dis.push_back(tmp);
    }
    sort(dis.begin(),dis.end(),bruteForceKNN_compare);
    for(int i=0;i<k;i++)
    {
        result.push_back(dis[i].index);
    }
    return result;
}

void outputAccu(vector<data> best[],vector<data> test)
{
    int size=(int)test.size();
    int correct=0;
    for(int k=0;k<200;k++)
    {
        correct=0;
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<k;j++)
            {
                if(best[i][j].clazz==test[i].clazz)
                    correct++;
            }
        }
         cout << "KNN accuracy of " << k << ": " << (double)correct/(size*k) << endl;   
    }
    
}

/*============================Seperate=Line===========================================*/
/*Build Tree*/

vector<data> getHalfVector(int from,int to,vector<data> &v)
{
    vector<data> result;
    for(int i=from;i<to;i++)
    {
        result.push_back(v[i]);
    }
    return result;
}

node* build_tree(vector<data> v,int depth,node* parentNode)
{
    int n=(int)v.size();
    int axis=depth%9;
    if(n<=0)
    {
        parentNode->isLeaf=true;
        return NULL;
    }
    node* newNode=new node;
    sortByAxis(v,axis);
    newNode->isLeaf=false;
    newNode->splitBy=axis;
    newNode->d=v[n/2];
    newNode->parent=parentNode;
    newNode->index=v[n/2].index;
    newNode->left=build_tree(getHalfVector(0,n/2,v),depth+1,newNode);
    newNode->right=build_tree(getHalfVector(n/2+1,n,v),depth+1,newNode);
    return newNode;
}

/*============================Seperate=Line===========================================*/
/*Search Tree*/

data closer_distance(data pivot,data p1,data p2)
{
    double d1=calDistance(pivot,p1);
    double d2=calDistance(pivot,p2);
    return d1<d2?p1:p2;
}

data kdTreeClosest(data pivot,node* root,int depth,data best)
{
    if(root==NULL)
        return best;
    int axis=depth%9;
    node* next_branch;
    node* oppisite_branch;
    if(root->d.attr[axis]>pivot.attr[axis])
    {
        next_branch=root->left;
        oppisite_branch=root->right;
    }
    else
    {
        next_branch=root->right;
        oppisite_branch=root->left;
    }
    best = closer_distance(pivot,root->d,kdTreeClosest(pivot,next_branch,depth+1,best));
    if(calDistance(pivot,best)>abs(root->d.attr[axis]-pivot.attr[axis]))
    {
        best=closer_distance(pivot,best,kdTreeClosest(pivot,oppisite_branch,depth+1,best));
    }
    return best;
}

vector<data> kdTreeKNN(data &pivot,node* root,int depth,vector<data> &bestV,int k)
{
    if(root==NULL)
        return bestV;
    int axis=depth%9;
    node* next_branch;
    node* oppisite_branch;
    if(root->d.attr[axis]>pivot.attr[axis])
    {
        next_branch=root->left;
        oppisite_branch=root->right;
    }
    else
    {
        next_branch=root->right;
        oppisite_branch=root->left;
    }
    root->d.distance=calDistance(root->d, pivot);
    bestV.push_back(root->d);
    if(bestV.size()>k)
    {
        sort(bestV.begin(),bestV.end(),compareDis);
        bestV.pop_back();
    }
    kdTreeKNN(pivot, next_branch, depth+1, bestV, k);
    if(calDistance(pivot,root->d)>abs(root->d.attr[axis]-pivot.attr[axis]))
        kdTreeKNN(pivot, oppisite_branch, depth+1, bestV, k);
    
    return bestV;
}

/*============================Seperate=Line===========================================*/
/*Main Funtion*/

int main(int argc, char *argv[])
{
    if(argv[1]==NULL||argv[2]==NULL)
    {
        cout << "Please input file name!!" << endl;
        return 0;
    }
    vector<data> v=load_csv(argv[1]);
    vector<data> test=load_csv(argv[2]);
    node* root=new node;
    root=build_tree(v,0,root);
    vector<data> bestV[test.size()];
    for(int i=0;i<test.size();i++)
    {
        node tmp;
        tmp.d=test[i];
        kdTreeKNN(test[i], root, 0, bestV[i], 100);
    }
    //outputAccu(bestV,test);
    outputFile(bestV,test);
}
