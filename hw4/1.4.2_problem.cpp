class Solution {
public:
    // создание DSU (каждый элемент представляет свое множество)
    void MakeDSU(vector<int>& p) {
        for (int i = 0; i < p.size(); ++i) {
            p[i] = i;
        }
    }
    // поиск принадлежности к множеству
    int Find(vector<int>& p, int x) {
        // если указывает сам на себя, то это и есть искомое множество
        if (p[x] == x)
            return x;
        // иначе ищем предка со сжатием путей
        return p[x] = Find(p, p[x]);
    }
    // объединение двух множеств
    void Union(vector<int>& p, int x_1, int x_2) {
        // получаем класс этих множеств
        int x1 = Find(p, x_1);
        int x2 = Find(p, x_2);
        // присваиваем второму множеству порядок первого (для хранения корня)
        p[x2] = x1;
    }

    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        vector<vector<int>> ans (1, vector<int> (0));
        // если массив пустой
        if (edges.size() == 0)
            return ans[0];
        // иначе ищем остовное дерево
        // найдем вершины, в которые входят ребра; найдем максимальную вершину (для DSU)
        vector<int> cnt = vector<int> (edges.size() + 1, 0);
        int max_node = 0;
        for (int i = 0; i < edges.size(); ++i) {
            int l = edges[i][0];
            int r = edges[i][1];
            cnt[r] += 1;
            if (r > max_node) max_node = r;
            if (l > max_node) max_node = l;
        }
        // найдем корень, если он не находится в цикле (иначе root_node == 0)
        int root_node = 0;
        for (int i = 1; i < max_node + 1; ++i) {
            if (cnt[i] == 0) {
                root_node = i;
                break;
            }
        }
        // создаем массив для хранения DSU
        vector<int> p = vector<int> (max_node + 1);
        // создаем DSU
        MakeDSU(p);

        // строим DSU
        for (int i = 0; i < edges.size() ; ++i) {
            int l = edges[i][0];
            int r = edges[i][1];
            int l_p = Find(p, l);
            int r_p = Find(p, r);
            if (r_p == r && l_p != r_p) {
                // если это простое объединение деревьев
                // т е вектор направлен в корень другого дерева
                Union(p, l_p, r_p);
            } else {
                // если это случай замыкания цикла (направлен на самого себя),
                // либо вектор лежит на пути из корня в вершину, содержащаю цикл
                ans.push_back(edges[i]);
            }
        }
        // рассмотрим оставшиеся ребра, которые не попали в DSU (ребра-кандидаты)
        for (int i = 1; i < ans.size(); ++i) {
            int l = ans[i][0];
            int r = ans[i][1];
            if (Find(p, l) == root_node) {
                // случай вхождения ребра на пути из корня в вершину, содержащаю цикл
                // (когда пропустили ребро, которое лежало на пути из корня в вершину цикла)
                // (тогда соседнее ребро из цикла и есть искомое)
                for (int j = edges.size() - 1; j >= 0; --j) {
                    if (edges[j][1] == r && Find(p, edges[j][0]) != root_node)
                        return edges[j];
                }
            }
            // либо же такого ребра нет; тогда DSU построился с учетом цикла и последнее ребро
            // которое выкинули на предыдущих итерациях и есть искомое (то самое "соседнее ребро из цикла")
        }
    return ans[ans.size()-1];
    }
};
