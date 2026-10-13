#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

struct pacholek
{
    int id;
    double x, y;
    bool active;
    int cell;
    int how_many_or;
    int basic_a, basic_b;
};

vector <pacholek> P;

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

vector <vector <pacholek>> K(1000);

int number_of_points[1000];

queue <pacholek> Q;

bool is_closer (pacholek P1, pacholek P2, double m)
{
    int dis_x = abs(P1.x - P2.x);
    int dis_y = abs(P1.y - P2.y);

    if (dis_x * dis_x + dis_y * dis_y > m * m) return false;
    return true;
}


int calculate_cell (pacholek P1, double min_x, double min_y, double m, int columns)
{
        double bad_x = P1.x;
        double bad_y = P1.y;

        double dif_x = abs(bad_x - min_x);
        double dif_y = abs(bad_y - min_y);

        dif_x /= m;
        dif_y /= m;

        int col_ind = ceil(dif_x);
        int row_ind = ceil(dif_y) + 1;
       // cout << col_ind << " " << row_ind << endl;
        int cell_number = columns * row_ind + col_ind + columns + 2;   //columns + 2 to index zerowej koomorki

        return cell_number;
}

pacholek calculate_average (pacholek P1, pacholek P2)
{
        pacholek s;
        s.x = ((P1.x * P1.how_many_or) + (P2.x * P2.how_many_or))/(P1.how_many_or + P2.how_many_or);
        s.y = ((P1.y * P1.how_many_or) + (P2.y * P2.how_many_or))/(P1.how_many_or + P2.how_many_or);
        s.id = 0;
        s.active = true;    
        s.how_many_or = P1.how_many_or + P2.how_many_or;
        return s;
}

vector <vector <int>> M(100);

void get_old_cones (pacholek P1, int n)
{
    if (P1.basic_a == 0) return;
    if (P1.basic_a <= n) cout << P1.basic_a << " ";
    if (P1.basic_b <= n) cout << P1.basic_b << " ";
    get_old_cones(P[P1.basic_a - 1], n);
    get_old_cones(P[P1.basic_b - 1], n);
}

int main()
{
    int n;
    double m;
    cin >> n >> m;
    int n_copy = n + 1;
    int n_another_copy = n;
    double min_x = 100, min_y = 100; //to arbitralne liczby - trzeba je dopasowac w zaleznosci od potrzeb
    double max_x = -100, max_y = -100;

    for (int i = 0; i < n; i++)
    {
        pacholek A; //A to dokladany w tej chwili wierzcholek
        cin >> A.id >> A.x >> A.y;
        A.active = true;
        A.how_many_or = 1;
        A.basic_a = 0;
        A.basic_b = 0;
        P.push_back(A); //dodajemy do vectora P ktory ma wszystkie pacholki
        min_x = min(min_x, A.x);
        min_y = min(min_y, A.y);

        max_x = max(max_x, A.x);
        max_y = max(max_y, A.y);
    }

    sort (P.begin(), P.end(), cmp); //sortujemy po x


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
        K[cell_number].push_back(P[i]);
        number_of_points[cell_number]++;
        cout << P[i].id << " " << cell_number << endl;
        
        Q.push(P[i]);
    }

    int licznik = 0;

    sort(P.begin(), P.end(), cmp2);

    for (int i = 0; i < n; i++)
    {
        cout << i << " " << P[i].id << endl;
    }


    while (!Q.empty())
    {
        pacholek t = Q.front();
        int t_index = t.id - 1;
        t.active = P[t_index].active;

        if (t.active == false) 
        {
            Q.pop();
            continue; //sprawdzamy, czy punkt t juz nie jest wyrzucony z planszy
        }

        double bad_x = t.x;
        double bad_y = t.y;

        int cell_index = t.cell;

        for (int k = -columns; k <= columns; k += columns)
        {
            for (int i = -1; i <= 1; i++)
            {
                int temp_cell = cell_index + i + k;
                if (number_of_points[temp_cell] > 0 && t.active)  
                {
                    for (int j = 0; j < K[temp_cell].size(); j++)
                    {
                        int k_index = K[temp_cell][j].id - 1;

                        cout << t.id << " " << K[temp_cell][j].id << " " << is_closer(t, K[temp_cell][j], m) << endl;
                        if (is_closer(t, K[temp_cell][j], m) && t.id != K[temp_cell][j].id)
                        {
                            if (!P[k_index].active) continue;
                            pacholek s = calculate_average(t, K[temp_cell][j]);
                            n++;
                            s.id = n;
                            s.cell = calculate_cell(s, min_x, min_y, m, columns);
                            s.basic_a = t.id;
                            s.basic_b = k_index + 1;
                            Q.push(s);
                            P.push_back(s);
                            cout << t.id << " - " << K[temp_cell][j].id << " new = " << s.id << endl;
                            cout << "x = " << s.x << " y = " << s.y << " cell = " << s.cell << "how many: " << s.how_many_or<< endl;
                            cout << s.basic_a << " " << s.basic_b << endl;
                            t.active = false;
                            P[t_index].active = false;
                            K[temp_cell][j].active = false;

                            cout << k_index << endl;
                            P[k_index].active = false;
                            
                            number_of_points[temp_cell]--;
                            break;
                        }
                    }
                }
            }
        }
        Q.pop();
    }
    cout << endl << "PO PETLI " << endl;
    for (int i = 0; i < n; i++)
    {
        if (P[i].active && P[i].id > n_copy) 
        {
            P[i].id = n_copy;
            n_copy++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (P[i].active && P[i].how_many_or > 1) 
        {
            cout << "NEW CONE ID: " << P[i].id << " x = " << P[i].x << " y = " << P[i].y << " MERGED CONES: ";
            get_old_cones(P[i], n_another_copy);
            cout << endl;
        }
    }


    return 0;
}