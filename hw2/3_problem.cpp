class Solution {
public:
    vector<string> generateParenthesis(int n) {
        // массив для ответа
        vector<string> ans;
        // поиск в глубину всех решений
        dfs(ans, n, 0, "");
        return ans;
    }
private:
    void dfs(vector<string>& ans, int free_to_open, int need_to_close, string s) {
        // (выход из рекурсии для верных значений)
        // если кол-во открытых и закрытых скобок == 0 (т е все скобки израсходованы)
        if (free_to_open == 0 && need_to_close == 0) {
            // то кладем данную последовательность в массив для ответа
            ans.push_back(s);
            return;
        }
        // (выход из рекурсии для неверных значений)
        if (free_to_open < 0|| need_to_close < 0)
            return;
        // ищем всевозможные варианты чз dfs
        dfs(ans, free_to_open - 1, need_to_close + 1, s + "(");
        dfs(ans, free_to_open, need_to_close - 1, s + ")");
    }
};
