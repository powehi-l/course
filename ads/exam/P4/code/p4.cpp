#include <iostream>
#include <vector>

class Solution
{
	//根节点为黑色，节点数为n，黑高为bh的红黑树个数为distinct_black_root_n[n][bh]
	std::vector<std::vector<long long>> distinct_black_root_n;
	//根节点为红色，节点数为n，黑高为bh的红黑树个数为distinct_red_root_n[n][bh]
	std::vector<std::vector<long long>> distinct_red_root_n;

	//由节点数计算黑高上界
	long long get_max_bh(long long node_n) {
		//简便起见这里直接取对数，都是logn
		long long bh = 1;
		long long n = 1;
		while (n <= node_n) {
			++bh;
			n <<= 1;
		}
		return bh;
	}

	//初始化数组
	void init(long long node_n) {
		distinct_black_root_n.clear();
		distinct_red_root_n.clear();
		auto max_bh = get_max_bh(node_n);
		std::vector<long long> t;
		for (auto i = 0; i <= max_bh + 1; ++i) {	//O(logN)
			t.push_back(0);
		}
		for (auto i = 0; i <= node_n + 1; ++i) {	//O(N)
			distinct_black_root_n.push_back(t);
			distinct_red_root_n.push_back(t);
		}
		//总空间复杂度为O(NlogN)
	}

	//根节点为黑的情况，左右为黑高相等的（黑+红）*（黑+红）
	//根节点为红的情况，左右为黑高相等的（黑*黑）
	//为简化动规代码，同时省略数组的最小条件初始化，这里定义两个动规过程辅助函数

	//返回n个节点，黑高为bh的黑根树+红根树个数
	long long get_r_and_b(long long n, long long bh) {
		//边界条件，节点数为0，黑高为0，“总共”只有1种
		if (n == 0 && bh == 0) {
			return 1;
		}
		//边界条件，节点数为0，黑高不为0，不存在
		if (n == 0) {
			return 0;
		}
		//一般情况，直接从动规数组返回
		return distinct_black_root_n[n][bh] + distinct_red_root_n[n][bh];
	}

	//返回n个节点，黑高为bh的黑根树个数
	long long get_b(long long n, long long bh) {
		//边界条件，节点数为0，黑高为0，只有1种
		if (n == 0 && bh == 0) {
			return 1;
		}
		//边界条件，节点数为0，黑高不为0，不存在
		if (n == 0) {
			return 0;
		}
		//一般情况，直接从动规数组返回
		return distinct_black_root_n[n][bh];
	}

	//以上两个函数包括了节点数为0的所有情况，因此动规从节点数为1开始

public:
	long long mod = 1000000007;

	long long solve(long long node_n) {
		init(node_n);
		//从1个节点解到n个节点
		for (long long n = 1; n <= node_n; ++n) {	//O(N)
			//最大黑高
			auto max_bh = get_max_bh(n);	//O(logN)
			//遍历黑高
			for (long long bh = 0; bh <= max_bh; ++bh) {
				//循环开始左节点数
				long long begin = 0;	//O(N)
				//分配左右节点数
				for (
					long long left_node_n = begin, right_node_n = n - 1 - begin;
					right_node_n >= begin;
					++left_node_n, --right_node_n
					)
				{
					//至此总共三层循环，总时间复杂度O(N^2logN)
					distinct_black_root_n[n][bh + 1] += get_r_and_b(left_node_n, bh) * get_r_and_b(right_node_n, bh) % mod;
					distinct_red_root_n[n][bh] += get_b(left_node_n, bh) * get_b(right_node_n, bh) % mod;
					distinct_black_root_n[n][bh + 1] %= mod;
					distinct_red_root_n[n][bh] %= mod;
				}
			}
		}
		//我们只需要根节点为黑的解
		long long ans = 0;
		auto max_bh = get_max_bh(node_n);
		for (long long bh = 0; bh <= max_bh; ++bh) {
			ans += get_b(node_n, bh);
			ans %= mod;
		}
		return ans;
	}
};

using namespace std;

int main()
{
	auto solution = Solution();
	long long n_node;
	cin >> n_node;
	auto ans = solution.solve(n_node);
	cout << ans << endl;
	return 0;
}