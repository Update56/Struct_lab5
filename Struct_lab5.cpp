#include <iostream> 
#include <vector> 
#include <stack> 
#include <fstream>
using namespace std;

const int MAXN = 100;
int vert, edges; // число вершин и ребер 
vector<int> g[MAXN]; // граф в виде списка смежности 
bool used[MAXN] = { false }; // массив для отслеживания посещенных вершин 
stack<int> path; // стек для сохранения пути 
ifstream in("input.dat"); //файл для чтения
ofstream out("output.dat"); //файл для записи

void dfs(int v) // функция поиска в глубину 
{
	used[v] = true;
	for (int i = 0; i < g[v].size(); i++) 
	{
		int to = g[v][i];
		if (!used[to]) 
		{
			dfs(to);
		}
	}
	path.push(v); // добавляем вершину в стек после того, как все её смежные вершины были посещены 
}

void longest_path() // функция для поиска самого длинного пути в графе 
{
	for (int i = 0; i < vert; i++) {
		if (!used[i]) {
			dfs(i);
		}
	}

	int parent[MAXN] = { -1 }; // массив для отслеживания предыдущих вершин в пути 
	int dist[MAXN] = { 0 }; // массив для отслеживания длин путей до каждой вершины 
	int longest_path_end = -1; // вершина, на которой заканчивается самый длинный путь 
	int longest_path_length = 0; // длина самого длинного пути 
	
	while (!path.empty()) // находим самый длинный путь с помощью алгоритма Дийкстры 
	{
		int v = path.top(); //достаём точку из стэка
		path.pop();
		for (int i = 0; i < g[v].size(); i++) //поверка всех связанных точек  
		{
			int to = g[v][i]; //точка связанная с точкой из стэка
			if (dist[to] < dist[v] + 1) //если расстояние до проверянмой точки меньше чем от начальной + 1
			{
				dist[to] = dist[v] + 1; //то увеличиваем расстояние
				parent[to] = v;	//и объявлем начальную точку родителем
				if (dist[to] > longest_path_length)  //если найденое расстояние больше чем уже имеющееся
				{
					longest_path_end = to; //то назначаем конечную точку последней в пути
					longest_path_length = dist[to]; //и длинну пути
				}
			}
		}
	}

	if (longest_path_length == 0) // выводим результат 
	{
		cout << "Граф не содержит путей\n";
		out << "Граф не содержит путей\n";
	}
	else {
		cout << "Самый длинный простой путь в графе имеет длину " << longest_path_length << " и проходит через вершины: ";
		out << "Самый длинный простой путь в графе имеет длину " << longest_path_length << " и проходит через вершины: ";
		vector<int> answer;
		for (int i = longest_path_end; i != -1; i = parent[i]) {
			answer.push_back(i);
		}
		for (int i = answer.size() - 1; i >= 0; i--) {
			cout<< answer[i] + 1 << " ";
			out << answer[i] + 1 << " ";
		}
		cout << endl;
		out << endl;
	}
}

int main() 
{
	setlocale(LC_ALL, "Russian");
	
	if (!in.is_open())
	{
		cout << "не удалось открыть файл \"input.dat\"";
		return 0;
	}

	if (in.is_open())
	{
		in >> vert >> edges;
		cout << "Кол-во вершин: " << vert << endl;
		cout << "Кол-во рёбер: " << vert << endl;
		out << "Кол-во вершин: " << vert << endl;
		out << "Кол-во рёбер: " << vert << endl;
		for (int i = 0; i < edges; i++) {
			int u, v;
			in >> u >> v;
			cout << "Ребро " << i + 1 << ": " << u << '-' << v << endl;
			out << "Ребро " << i + 1 << ": " << u << '-' << v << endl;
			u--;
			v--; // приводим номера вершин к нумерации с нуля  
			g[u].push_back(v);
			
		}
		longest_path();
	}
	return 0;
}