#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/timer/timer.hpp>

class Combination{
	std::vector<int> prev;
	std::vector<int> flag;
	int set;
	int choice;
	int count;
	int combinations;

public:
	Combination(int set, int choice){
		reset(set, choice);
	}

	void reset(int set, int choice){
		this->set = set;
		this->choice = choice;
		this->count =0;
		prev.resize(choice, 0);
		flag.resize(choice, 0);

		int result = 1;
		for(int i=0; i<choice; ++i){
			result *= set-i;
		}
		for(int i=1; i<=choice; ++i){
			result /= i;
		}
		this->combinations = result;
	}

	bool is_end() const{
		return count < combinations ? true : false;
	}

	int getCombinationNum() const{
		return combinations;
	}

	void getNextCombination(std::vector<int> &result){
		++count;
		result.assign(prev.begin(), prev.end());

		++result[result.size()-1];
		bool end=false;
		while(!end){
			end =true;
			if(flag[0]){
				++result[0];
				end = false;
				flag[0]=0;
			}
			if(result[0] >= set){
				result[0]=0;
				end = false;
			}
			for(int i=1;i<choice;++i){
				if(result[i-1] >= result[i] || flag[i]){
					++result[i];
					end = false;
					flag[i] = 0;
				}
				if(result[i] >= set){
					result[i]=0;
					flag[i-1]=1;
					end = false;
				}
			}
		}
		prev.assign(result.begin(), result.end());
	}

	const std::vector<int>& getNextCombination(){
		++count;
		++prev[prev.size()-1];
		bool end=false;
		while(!end){
			end =true;
			if(flag[0]){
				++prev[0];
				end = false;
				flag[0]=0;
			}
			if(prev[0] >= set){
				prev[0]=0;
				end = false;
			}
			for(int i=1;i<choice;++i){
				if(prev[i-1] >= prev[i] || flag[i]){
					++prev[i];
					end = false;
					flag[i] = 0;
				}
				if(prev[i] >= set){
					prev[i]=0;
					flag[i-1]=1;
					end = false;
				}
			}
		}
		return prev;
	}

	const std::vector<int>& operator ++(){
		return getNextCombination();
	}

	const std::vector<int> operator ++(int){
		std::vector<int> tmp = prev;
		getNextCombination();
		return tmp;
	}

	const std::vector<int>& operator *(){
		return prev;
	}

	const int operator [](int index){
		return prev[index];
	}
};

int main(int argc, char const* argv[])
{
	std::ofstream fout("result");
	Combination combo(boost::lexical_cast<int>(argv[1]), boost::lexical_cast<int>(argv[2]));

	int c = combo.getCombinationNum();
	fout << "Combinations: " << c << std::endl;

	boost::timer::cpu_timer timer;

	for(int i=0; i < c; ++i){
		timer.resume();
		const std::vector<int> &r = combo.getNextCombination();
		timer.stop();

		fout << "(";
		for (int val: r) {
			fout << val <<" ";
		}
		fout << ")" <<std::endl;
	}

	fout << "#wall[sec], user[sec], system[sec], CPU%" << std::endl;
	fout << timer.format(10, "%w, %u, %s, %p") << std::endl;

	return 0;
}
