class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        // отсортирвоали массив для прохода по всем элементам по возрастанию
        sort(nums.begin(), nums.end());
        // массив для ответа
        vector<vector<int>> ans;
        // временный массив для поиска сабсета в проходе dfs
        vector<int> subset;
        // поиск в глубину всех решений
        dfs(ans, subset, nums, 0);
        return ans;
    }
private:
    void dfs(vector<vector<int>>& ans, vector<int>& subset, vector<int>& nums, int len) {
        // на глубине len мы находим всевозможные сабсеты длины len и кладем их в общий сет
        ans.push_back(subset);
        for (int i = len; i < nums.size(); ++i) {
            // так как массив отсортирован, то эл-ты для построения сабсета не будут повторятся
            // (ищем сабсеты из уникальных значений по возрастанию. неуникальные значения будут повторяться в самом начале (напр. len, element = (2,'4'), (3,'4'),...))
            if (i > len && nums[i] == nums[i - 1])
                continue;
            // добавляем новый эл-т в сабсет (и получаем новый сабсет соответсвтенно)
            subset.push_back(nums[i]);
            // ищем продолжение построения данного сабсета (и кладем его в сам сет)
            dfs(ans, subset, nums, i + 1);
            // возвращаем сабсет к исходному состоянию
            subset.pop_back();
        }
    }
};
