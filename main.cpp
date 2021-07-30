#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <algorithm>

using namespace std;

class Vertex {

	public:

		vector <Vertex*> adjVer;
                vector <int> adjVerW;

		set <Vertex*> vSet;
		bool known;
		int dist;
		Vertex* path;
		string name;
		string data;

		Vertex();
		void PushAdjVer(Vertex* v);
		void PushAdjVerW(int x);
		void SetKnown(bool known);
		void SetDist(int dist);
		void SetPath(Vertex* path);
		void SetName(string name);
		void SetData(string data);
		string GetData();

		vector <Vertex*> &GetAdjVer();
                vector <int> &GetAdjVerW();

		bool GetKnown();
		int GetDist();
		Vertex* GetPath();
		string GetName();
};

class Edge      {
        public:
        Vertex *u;
        Vertex *v;
        int dist;
        Edge();
        void SetU(Vertex *u);
        void SetV(Vertex *v);
        void SetDist(int dist);
        Vertex *GetU();
        Vertex *GetV();
        int GetDist();
};


class Graph	{

	public:

	vector <Vertex*> adjList;
	vector <Edge*> edgeList;
	vector <Edge*> mstK;
	vector <Edge*> mstP;

	Graph();
	void Bfs(int x);
	void Dfs(Vertex *v);
	void PrintPath(Vertex *v);
	void ReadInFile();
	void PushAdjList(Vertex* v);
	vector <Vertex*> GetAdjList();
	void PushEdgeList(Edge* e);
        vector <Edge*> GetEdgeList();
	int FindV(string name);
	void BuildEdgeList();
	void PrintEdgeList();
	void Kruskal();
	void Prims(int x);
};

int main()	{

	int c = 0;

	Graph g;

	g.ReadInFile();

	g.BuildEdgeList();

	while(c != 9)	{

		cout << endl << "1 - Breadth First Search" << endl << endl << "2 - Depth First Search" << endl << endl << "3 - Prim's Algorithm" << endl << endl << "4 - Kruskal's Algorithm" << endl << endl << "9 - Quit" << endl << endl;

		cout <<  "Choose betweem 1 - 9: ";

		cin >>  c;

		switch(c)	{

			case 1:

				g.Bfs(0);

				break;

			case 2:

				g.Dfs(g.GetAdjList().at(0));

				cout << "All Counties found. Graph is connected. " << endl;

				break;

			case 3:

				g.Prims(0);

				break;

			case 4:

				g.Kruskal();

				break;

			case 9:

				break;

			default:

				cout << "Not a choice" << endl;

				break;
		}
	}
	return 0;
}

Vertex::Vertex()	{

	this->known = false;
	this->dist = 10000;
	this->path = NULL;
	this->name = "XXXXXXX";
}

void Vertex::PushAdjVer(Vertex* v)	{

	GetAdjVer().push_back(v);
}

void Vertex::SetKnown(bool known)	{

	this->known = known;
}

void Vertex::SetDist(int dist)	{

	this->dist = dist;
}

void Vertex::SetPath(Vertex* path)	{

	this-> path = path;
}

void Vertex::SetName(string name)	{

	this->name = name;
}

vector <Vertex*> &Vertex::GetAdjVer()	{

	return this->adjVer;
}

bool Vertex::GetKnown()	{

	return this->known;
}

int Vertex::GetDist()	{

	return this->dist;
}

Vertex* Vertex::GetPath()	{

	return this->path;
}

string Vertex::GetName()	{

	return this->name;
}

void Vertex::SetData(string data)	{

	this->data = data;
}

string Vertex::GetData()	{

	return this->data;
}

void Graph::ReadInFile()	{

	ifstream in;

	in.open("texas_counties_adjacency.csv");

	int c = 0;

	string temp;

	while(!in.eof())	{

		getline(in,temp);

		Vertex* x = new Vertex();

		x->SetData(temp);

		int pos1, pos2, pos3, posx, posy = 0;

		string  temp1, temp2, temp3;

		pos1 = temp.find(",");

		temp1 = temp.substr(0,pos1);

			if(temp1.size() > 6)	{

				x->SetName(temp1);

			}

			while(pos3 != -1)	{

				pos2 = temp.find("(",pos2 + 1);

				pos3 = temp.find(")",pos3 + 1);

				temp2 = temp.substr(pos2+1,pos3-pos2-1);

					if(temp2.size() < temp.size()- 3 & temp2.size() > 2)      {

						int pos4 = temp2.find("-");

						string temp4, temp5;

						temp4 = temp2.substr(0,pos4 - 1);

						temp5 = temp2.substr(temp2.size()-2, 2);

						int z = stoi(temp5);

						Vertex *y = new Vertex();

						y->SetName(temp4);

						y->SetDist(z);

						x->adjVer.push_back(y);

					}

			}

			pos3 = 0;

                        if(temp1.size() > 6)    {

				adjList.push_back(x);
			}

			;


		//}
		c++;
	//}
	}

	in.close();
}

void Graph::PushAdjList(Vertex* v)	{

	this->adjList.push_back(v);
}

vector <Vertex*> Graph::GetAdjList()	{

	return this-> adjList;
}

void Graph::PushEdgeList(Edge* e)	{

	this->edgeList.push_back(e);
}
 vector <Edge*> Graph::GetEdgeList()	{

	return this->edgeList;
}

Graph::Graph()	{

}

void Vertex::PushAdjVerW(int x)	{

	GetAdjVerW().push_back(x);
}

vector <int> &Vertex::GetAdjVerW()	{

	return this->adjVerW;
}

int Graph::FindV(string name)	{

	for(int i = 0; i < GetAdjList().size(); i++)  {

		if(GetAdjList().at(i)->GetName() == name)	{

			return i;
		}
	}

	return -5;
}

void Graph::Bfs(int x)	{

        for(int i = 0; i < GetAdjList().size(); i++)  {

		GetAdjList().at(i)->SetDist(100000);

		GetAdjList().at(i)->SetKnown(false);
	}

	GetAdjList().at(x)->SetDist(0);

	GetAdjList().at(x)->SetPath(GetAdjList().at(x));


	bool stop = false;

	int count = 0;

	while(stop == false)	{

		count = 0;

		for(int i = 0; i < GetAdjList().size(); i++)  {

			if(GetAdjList().at(i)->GetKnown() == true)	{

				count++;
			}
		}

		if(count == GetAdjList().size() - 1)	{

			stop = true;
		}

		int smallest = 10000000;

		int minIndex = 0;

                for(int i = 0; i < GetAdjList().size(); i++)  {

                        if(GetAdjList().at(i)->GetKnown() == false)      {

				if(GetAdjList().at(i)->GetDist() < smallest)	{

						smallest = GetAdjList().at(i)->GetDist();

						minIndex = i;
				}
                        }
                }

		GetAdjList().at(minIndex)->SetKnown(true);

                for(int j = 0; j < GetAdjList().at(minIndex)->GetAdjVer().size(); j++)       {

			int z = FindV(GetAdjList().at(minIndex)->GetAdjVer().at(j)->GetName());

			if(GetAdjList().at(z)->GetKnown() == false)	{

				int cvw = GetAdjList().at(minIndex)->GetAdjVer().at(j)->GetDist();

				if(GetAdjList().at(minIndex)->GetDist() + cvw < GetAdjList().at(z)->GetDist())	{

					GetAdjList().at(z)->SetDist(GetAdjList().at(minIndex)->GetDist()+cvw);

					GetAdjList().at(z)->SetPath(GetAdjList().at(minIndex));

					cout << GetAdjList().at(minIndex)->GetName() << " to " << GetAdjList().at(z)->GetName() << " distance : " << GetAdjList().at(z)->GetDist() << " miles from " << GetAdjList().at(x)->GetName() << endl;
				}
			}
                }
	}

        for(int i = 0; i < GetAdjList().size(); i++)  {

                GetAdjList().at(i)->SetDist(100000);

                GetAdjList().at(i)->SetKnown(false);
        }

	cout << "All Counties found. Graph is connected. " << endl;
}

void Graph::PrintPath(Vertex *v)	{

	//int z = FindV(GetAdjList().at(x)->GetPath()->GetName());

	if(v != NULL)	{

		PrintPath(v->GetPath());

		cout << " to ";
	}

	cout << v->GetName();
}

void Graph::Dfs(Vertex *v)     {

	int z = FindV(v->GetName());

	GetAdjList().at(z)->SetKnown(true);

        for(int j = 0; j < GetAdjList().at(z)->GetAdjVer().size(); j++)       {

		int y = FindV(GetAdjList().at(z)->GetAdjVer().at(j)->GetName());

                if(GetAdjList().at(y)->GetKnown() == false)     {

			Dfs(GetAdjList().at(y));
		}
	}

	//cout << "All Counties found. Graph is connected. "" << endl;


	cout << GetAdjList().at(z)->GetName() << endl;
}

void Edge::SetU(Vertex *u)	{

	this->u = u;
}

void Edge::SetV(Vertex *v)	{

	this->v = v;
}

void Edge::SetDist(int dist)	{

	this->dist = dist;
}

Vertex *Edge::GetU()	{

	return this->u;
}

Vertex *Edge::GetV()	{

	return this->v;
}

int Edge::GetDist()	{

	return this->dist;
}

Edge::Edge()	{

}

void Graph::BuildEdgeList()	{

        for(int i = 0; i < GetAdjList().size(); i++)  {

                Vertex * u = GetAdjList().at(i);

		for(int j = 0; j < GetAdjList().at(i)->GetAdjVer().size(); j++)       {

			Vertex * v = GetAdjList().at(i)->GetAdjVer().at(j);

			int z = GetAdjList().at(i)->GetAdjVer().at(j)->GetDist();

			Edge *e = new Edge();

			e->SetU(u);

			e->SetV(v);

			e->SetDist(z);

			edgeList.push_back(e);
		}
        }

	for(int i = 1; i < edgeList.size(); i++) {

                Edge *temp = edgeList.at(i);

                int j;

                for(j = i; j > 0 && temp->GetDist() < edgeList.at(j - 1)->GetDist(); --j) {

                        edgeList.at(j) = edgeList.at(j - 1);
                }
                edgeList.at(j) = temp;
        }
	//PrintEdgeList();
}

void Graph::PrintEdgeList()	{

	for(int i = 0; i < GetEdgeList().size(); i++)  {

		cout << i << GetEdgeList().at(i)->GetU()->GetName() <<  " to " << GetEdgeList().at(i)->GetV()->GetName() << " ----- " << GetEdgeList().at(i)->GetDist() << endl;
	}
}

void Graph::Kruskal()	{

	for(int i = 0; i < GetAdjList().size(); i++)  {

		GetAdjList().at(i)->vSet.insert(GetAdjList().at(i));
	}

	int indexE = 0;

	while(mstK.size() != GetAdjList().size() - 1)	{

		Edge *e = edgeList.at(indexE);

		int z = FindV(e->u->GetName());

                int y = FindV(e->v->GetName());

		if(GetAdjList().at(z)->vSet != GetAdjList().at(y)->vSet)	{

			mstK.push_back(e);

			set <Vertex*> tempS;

			set_union(GetAdjList().at(z)->vSet.begin(),GetAdjList().at(z)->vSet.end(),GetAdjList().at(y)->vSet.begin(),GetAdjList().at(y)->vSet.end(),inserter(tempS,tempS.begin()));

			GetAdjList().at(z)->vSet = tempS;

                        GetAdjList().at(y)->vSet = tempS;
		}

		//else{cout << "No" << indexE << endl;}

		indexE++;
	}

        cout << "MST using Kruskal's" << endl;

	for(int i = 0; i < mstK.size(); i++)  {

		cout << mstK.at(i)->u->GetName() << " to " << mstK.at(i)->v->GetName() << " -distance- " << mstK.at(i)->GetDist() << endl;
	}
}

void Graph::Prims(int x)	{

        for(int i = 0; i < GetAdjList().size(); i++)  {

                GetAdjList().at(i)->SetDist(100000);

                GetAdjList().at(i)->SetKnown(false);
        }

        GetAdjList().at(x)->SetDist(0);

        GetAdjList().at(x)->SetPath(GetAdjList().at(x));

        bool stop = false;

        int count = 0;

        while(stop == false)    {

                count = 0;

                for(int i = 0; i < GetAdjList().size(); i++)  {

                        if(GetAdjList().at(i)->GetKnown() == true)      {

                                count++;
                        }
                }

                if(count == GetAdjList().size() - 1)    {

                        stop = true;
                }

                int smallest = 10000000;

                int minIndex = 0;

                for(int i = 0; i < GetAdjList().size(); i++)  {

                        if(GetAdjList().at(i)->GetKnown() == false)      {

                                if(GetAdjList().at(i)->GetDist() < smallest)    {

                                                smallest = GetAdjList().at(i)->GetDist();

                                                minIndex = i;
                                }
                        }
                }

                GetAdjList().at(minIndex)->SetKnown(true);

                for(int j = 0; j < GetAdjList().at(minIndex)->GetAdjVer().size(); j++)       {

                        int z = FindV(GetAdjList().at(minIndex)->GetAdjVer().at(j)->GetName());

                        if(GetAdjList().at(z)->GetKnown() == false)     {

                                int cvw = GetAdjList().at(minIndex)->GetAdjVer().at(j)->GetDist();

                                if( cvw < GetAdjList().at(z)->GetDist())  {

                                        GetAdjList().at(z)->SetDist(cvw);

                                        GetAdjList().at(z)->SetPath(GetAdjList().at(minIndex));
                                }

				else{

					GetAdjList().at(z)->SetDist(GetAdjList().at(z)->GetDist());

					GetAdjList().at(z)->SetPath(GetAdjList().at(minIndex));
				}
                        }
                }
        }

	for(int i = 0; i < GetAdjList().size(); i++)  {

		Vertex *u = GetAdjList().at(i);

		Vertex *v = GetAdjList().at(i)->GetPath();

		int d = GetAdjList().at(i)->GetDist();

		Edge *e = new Edge();

		e->SetU(u);

		e->SetV(v);

		e->SetDist(d);

		mstP.push_back(e);
	}

	cout << "MST using Prim's" << endl;

	for(int i = 0; i < mstP.size(); i++)  {

		if(mstP.at(i)->GetV() != NULL)       {

			cout << mstP.at(i)->GetU()->GetName() << " to " << mstP.at(i)->GetV()->GetName() << " distance " << mstP.at(i)->GetDist() << endl;
		}
	}

        for(int i = 0; i < GetAdjList().size(); i++)  {

                GetAdjList().at(i)->SetDist(100000);

                GetAdjList().at(i)->SetKnown(false);
        }
}

