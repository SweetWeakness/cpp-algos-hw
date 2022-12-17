    class Solution {
    public:
        int coinChange(vector<int>& coins, int amount) {
            // при поиске bfs в начале будем брать большие монеты (для этого и сортируем массив)
            sort(coins.begin(), coins.end());
            if (amount == 0)
                return 0;
            
            // для поиска кротчайших путей и отметений слишком больших (например, будем брать только "1")
            unordered_map<int, int> dict;
            // для bfs
            deque<pair<int, int>> q;
            // закидываем корень bfs
            q.push_back(pair<int, int>(amount, 0));
            // bfs, будем брать каждый вид монет
            while (!q.empty()) {
                pair<int, int> q_pop = q.front();
                q.pop_front();
                int amt = q_pop.first;
                int cnt = q_pop.second;

                // если в словаре[amt] есть cnt 
                if (auto search = dict.find(amt); search != dict.end()) {
                    // и если значение в словаре[amt] меньше, чем для случая, в котором мы находимся
                    if (search->second <= cnt) {
                        // то нет смысла смотреть, что будет дальше, так как есть вариант по-лучше
                        continue;
                    }
                    // иначе находим новый минимум операций для достижения данного amt
                    if (search->second > cnt) {
                        search->second = cnt;
                    }
                } else {
                    // либо dict[amt] не существует, тогда заведем новый
                    dict.insert(pair<int, int>(amt, cnt));
                }
                for (int i = coins.size() - 1; i >= 0; --i) {
                    // поскольку это bfs, то 1ое полученное значение и есть наименьший ответ
                    if (amt - coins[i] == 0)
                        return cnt + 1;
                    // иначе ищем на следующем слое
                    if (amt - coins[i] > 0) {
                        q.push_back(pair<int, int>(amt - coins[i], cnt + 1));
                    }
                }
            }
            return -1;
        }
    };
