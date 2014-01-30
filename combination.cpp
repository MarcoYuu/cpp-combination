#include "combination.h"

combination::combination(int set, int choice){
	reset(set, choice);
}

void combination::reset(int set, int choice){
	set_    = set;
	choice_ = choice;
	count_  = 0;
	prev_.resize(choice, 0);
	flag_.resize(choice, 0);

	int result = 1;
	for(int i=0; i<choice; ++i){
		result *= set-i;
	}
	for(int i=1; i<=choice; ++i){
		result /= i;
	}
	combo_ = result;
}

void combination::next(std::vector<int> &result){
	next();
	result.assign(prev_.begin(), prev_.end());
}

const std::vector<int>& combination::next(){
	++count_;
	++prev_[prev_.size()-1];
	bool end=false;
	while(!end){
		end =true;
		if(flag_[0]){
			++prev_[0];
			end = false;
			flag_[0]=0;
		}
		if(prev_[0] >= set_){
			prev_[0]=0;
			end = false;
		}
		for(int i=1;i<choice_;++i){
			if(prev_[i-1] >= prev_[i] || flag_[i]){
				++prev_[i];
				end = false;
				flag_[i] = 0;
			}
			if(prev_[i] >= set_){
				prev_[i]=0;
				flag_[i-1]=1;
				end = false;
			}
		}
	}
	return prev_;
}
