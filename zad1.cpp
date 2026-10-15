#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <unordered_map>

struct pacholek
{
    int id;
    double x, y;
    bool active;
    int cell;
};

std::vector <pacholek> P;
std::vector <pacholek> hull;
std::unordered_map <int, std::vector <int>> grid;
std::vector <std::vector <pacholek>> sets(1000);
int parent[1000];
int size[1000];

bool cmp (pacholek &P1, pacholek &P2)
{
    if (P1.x < P2.x) return true;
    return false;
}

bool cmp2 (pacholek &P1, pacholek &P2)
{
    if (P1.id < P2.id) return true;
    return false;
}


bool is_closer (pacholek P1, pacholek P2, double m)
{
    double dis_x = (P1.x - P2.x);
    double dis_y = (P1.y - P2.y);

    if (dis_x * dis_x + dis_y * dis_y > m * m) return false;
    return true;
}

int calculate_cell (pacholek P1, double min_x, double min_y, double m, int columns)
{
    double dif_x = abs(P1.x - min_x);
    double dif_y = abs(P1.y - min_y);

    dif_x /= m;
    dif_y /= m;


    int col_ind = floor(dif_x);
    int row_ind = floor(dif_y);
    int cell_number = columns * row_ind + col_ind + columns + 2;   //columns + 2 to index zerowej koomorki

    return cell_number;
}

int find_set (int id)
{
    if (parent[id] == id) return id;
    return find_set(parent[id]);
}

void unite (pacholek P1, pacholek P2)
{
    int a = find_set(P1.id);
    int b = find_set(P2.id);

    if (size[a] > size[b]) 
    {
        parent[P2.id] = a;
        size[a] += size[b];
    }
    else 
    {
        parent[P1.id] = b;
        size[b] += size[a];
    }
}


double cross_product (pacholek A, pacholek B, pacholek C)
{
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}


pacholek average (std::vector <pacholek> W)
{
    pacholek average_point;

    double sum_x = 0, sum_y = 0;

    for (int i = 0; i < W.size(); i++)
    {
        sum_x += W[i].x;
        sum_y += W[i].y;
    }
    sum_x /= W.size();
    sum_y /= W.size();

    average_point.x = sum_x;
    average_point.y = sum_y;

    return average_point;    
}


int main()
{
    int n;
    double m;
    std::cin >> n >> m;

    double min_x = 100, min_y = 100; //to arbitralne liczby - trzeba je dopasowac w zaleznosci od potrzeb
    double max_x = -100, max_y = -100;
    
    for (int i = 0; i < n; i++) 
    {
        pacholek A;
        std::cin >> A.id >> A.x >> A.y;
        A.active = true;
        
        P.push_back(A); //dodajemy do vectora P ktory ma wszystkie pacholki

        parent[A.id] = A.id;
        size[A.id] = 1;

        min_x = std::min(min_x, A.x);
        min_y = std::min(min_y, A.y);

        max_x = std::max(max_x, A.x);
        max_y = std::max(max_y, A.y);
    }


    double width = max_x - min_x;
    int columns = width/m + 1;

    columns += 2; //po dwoch bokach zeby nie wyjsc poza zakres

    double height = max_y - min_y;
    int rows = height/m + 1;

    rows += 2; //analogicznie co z kolumnami

    for (int i = 0; i < n; i++)
    {
        int cell_number = calculate_cell(P[i], min_x, min_y, m, columns);

        P[i].cell = cell_number;
        grid[cell_number].push_back(P[i].id);

    }

    sort(P.begin(), P.end(), cmp2); //sortuje po indeksach - nie ma gwarancji, ze na wejsciu byly po kolej

    for (int g = 0; g < n; g++)
    {
        int t_index = g; //t_index to miejsce ktore badany pacholek zajmuje na vectorze P
        int cell_index = P[t_index].cell;

        for (int k = -columns; k <= columns; k += columns)
        {
            for (int i = -1; i <= 1; i++)
            {
                int temp_cell = cell_index + i + k;

                auto it  = grid.find(temp_cell);
                if (it == grid.end()) continue; //jesli w siatce vector przypisany do komorki sprawdzanej jest pusty, to komorka jest pusta

                for (int j = 0; j < grid[temp_cell].size(); j++)
                {
                    int g_index = grid[temp_cell][j] - 1; //p_index to miejsce ktore sprawdzany pacholek zajmuje w P
                    if (is_closer(P[t_index], P[g_index], m) && P[t_index].id != P[g_index].id)
                    {
                        unite (P[t_index], P[g_index]);
                    }
                }
            }
        }
    }

    int next_id = n + 1;

    bool was_message = false;

    for (int i = 1; i <= n; i++)
    {
        int og_parent = find_set(i);
        sets[og_parent].push_back(P[i - 1]);
    }

    for (int i = 1; i <= n; i++)
    {
        if (size[i] <= 2) continue;

        if (!was_message) 
        {
            std::cout << "New_ID, x, y, [Merged Cones]" << std::endl;
            was_message = true;
        }
        pacholek new_point = average(sets[i]);

        new_point.id = next_id;
        next_id++;

        new_point.active = true;
        new_point.cell = 0; //dla nowych punktow komorka nie ma znaczenia

        std::cout << new_point.id << ", " << new_point.x << ", " << new_point.y << ", [";

        P.push_back(new_point);

        for (int j = 0; j < sets[i].size(); j++) 
        {
            int p_index = sets[i][j].id - 1;
            P[p_index].active = false;
            std::cout << sets[i][j].id;
            if (j != sets[i].size() - 1) std::cout << ",";
            else std::cout << "]";
        }
        std::cout << std::endl;
    }

    sort (P.begin(), P.end(), cmp); //sortwanie po x

    n = next_id; // n to liczba pacholkow, wiec ustawiamy sa na wartosc ostatniego pacholka

    std::cout << "Enclosure_Circumference, [Included Cones]" << std::endl;

    for (int i = 0; i < n; ++i) 
    {
        if (!P[i].active) continue;

        while (hull.size() >= 2 && cross_product(hull[hull.size() - 2], hull.back(), P[i]) <= 0) 
        {
            hull.pop_back(); 
        }
        hull.push_back(P[i]);
    }

    for (int i = n - 2, t = hull.size() + 1; i >= 0; --i) 
    {
        if (!P[i].active) continue; 
        
        while (hull.size() >= t && cross_product(hull[hull.size() - 2], hull.back(), P[i]) <= 0) 
        {
            hull.pop_back();
        }
        hull.push_back(P[i]);
    }

    hull.pop_back();

    double sum = 0;


    for (int i = 0; i < hull.size(); i++)
    {
        pacholek H1 = hull[i];
        pacholek H2 = hull[(i + 1) % (hull.size())];
        sum += hypot(H1.x - H2.x, H1.y - H2.y);
    }
    std::cout << sum << ", [";

    for (int i = 0; i < hull.size(); i++) 
    {
        std::cout << hull[i].id;
        if (i != hull.size() - 1) std::cout << ",";
        else std::cout <<"]" << std::endl;
    }
    

    return 0;
}