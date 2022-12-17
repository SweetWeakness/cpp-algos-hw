class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        // отсортирвоали массив для прохода по всем элементам по возрастанию
        sort(nums.begin(), nums.end());
        // массив для ответа
        vector<vector<int>> ans;

        // поиск в глубину всех решений
        dfs(ans, nums, 0);

        return ans;
    }
private:
    void dfs(vector<vector<int>>& ans, vector<int> nums, int pos) {
        if (pos == nums.size()) {
        // если осталася один элемент
        // то добавляем решение в массив и выходим из рекурсии
            ans.push_back(nums);
        } else {
        // иначе ставим элемент на i-ое место
        // (всевозомжные элементы, кроме повторений)
            for (int i = pos; i < nums.size(); ++i) {
                // пропускаем повторяющиеся эл-ты (массив отсортирован)
                if (i > pos && nums[i] == nums[pos])
                    continue;
                // поставили элемент справа на i-ое место
                swap(nums[i], nums[pos]);
                // поиск продолжения данных перестановок на оставшихчя элементах
                dfs(ans, nums, pos+1);
            }
        }
    }
};
