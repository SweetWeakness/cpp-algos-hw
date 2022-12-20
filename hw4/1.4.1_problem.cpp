class Solution {
public:
    // создание DSU (каждый элемент представляет свое множество)
    void MakeDSU(vector<vector<pair<int, int>>>& p) {
        for (int i = 0; i < p.size(); ++i) {
            for (int j = 0; j < p[0].size(); ++j) {
                p[i][j] = pair<int, int> (i, j);
            }
        }
    }
    // поиск принадлежности к множеству
    pair<int, int> Find(vector<vector<pair<int, int>>>& p, pair<int, int> x_y) {
        int x = x_y.first;
        int y = x_y.second;
        // если указывает сам на себя, то это и есть искомое множество
        if (p[x][y] == x_y)
            return x_y;
        // иначе ищем предка со сжатием путей
        return p[x][y] = Find(p, p[x][y]);
    }
    // объединение двух множеств
    void Union(vector<vector<pair<int, int>>>& p, pair<int, int> x_y1, pair<int, int> x_y2) {
        // получаем класс этих множеств
        pair<int, int> xy1 = Find(p, x_y1);
        pair<int, int> xy2 = Find(p, x_y2);
        // случайно выбираем общий корень
        if (rand() % 2 == 0) 
            swap(xy1, xy2);
        // присваиваем одно множество другому
        int x = xy1.first;
        int y = xy1.second;
        p[x][y] = xy2;
    }

    int numIslands(vector<vector<char>>& grid) {
        // если массив пустой то ответ 0
        if (grid.size() == 0)
            return 0;
        // иначе ищем острова
        // создаем массив для хранения DSU
        vector<vector<pair<int, int>>> p = vector<vector<pair<int, int>>> (grid.size(),
         vector<pair<int, int>>(grid[0].size(), pair<int, int>(0, 0)));
        // создаем DSU
        MakeDSU(p);
        // проходим по каждом элементу grid'а и находим общие множества == искомые острова
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == '1') {
                    // с учетом, что мы можем находиться на границе массива
                    if (i > 0) {
                        if (grid[i - 1][j] == '1')
                            Union(p, Find(p, pair<int, int>(i, j)), Find(p, pair<int, int>(i - 1, j)));
                    }
                    if (i < grid.size() - 1) {
                        if (grid[i + 1][j] == '1')
                            Union(p, Find(p, pair<int, int>(i, j)), Find(p, pair<int, int>(i + 1, j)));
                    }
                    if (j > 0) {
                        if (grid[i][j - 1] == '1')
                            Union(p, Find(p, pair<int, int>(i, j)), Find(p, pair<int, int>(i, j - 1)));
                    }
                    if (j < grid[0].size() - 1) {
                        if (grid[i][j + 1] == '1')
                            Union(p, Find(p, pair<int, int>(i, j)), Find(p, pair<int, int>(i, j + 1)));
                    }
                }
            }
        }
        // подсчет всех множеств, заведем сет
        set<pair<int, int>> cointer_set;
        for (int i = 0; i < p.size(); ++i) {
            for (int j = 0; j < p[0].size(); ++j) {
                // для каждого острова ("1") найдем множество, к которому он принадлежит ("большому" острову)
                if (grid[i][j] == '0')
                    continue;
                pair<int, int> x_y = Find(p, pair<int, int>(i, j));
                cointer_set.insert(x_y);
            }
        }
        return cointer_set.size();
    }
};
